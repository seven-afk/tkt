#include "Ogg.h"
//JE SUIS AMOUREUX DE FLORIAN
//J4ADORE TOOLS
//C4EST QUI JASON ?

#define NUMBUFFERS              (4)
#define	SERVICE_UPDATE_PERIOD	(20)

#define	TEST_OGGVORBIS_FILE		"stereo.ogg"

// Ogg Vorbis

// Ogg Voribis DLL Handle
HINSTANCE g_hVorbisFileDLL = NULL;

// Functions
void InitVorbisFile();
void ShutdownVorbisFile();
unsigned long DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels);
void Swap(short& s1, short& s2);

size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource);
int ov_seek_func(void* datasource, ogg_int64_t offset, int whence);
int ov_close_func(void* datasource);
long ov_tell_func(void* datasource);

// Function pointers
typedef int (*LPOVCLEAR)(OggVorbis_File* vf);
typedef long (*LPOVREAD)(OggVorbis_File* vf, char* buffer, int length, int bigendianp, int word, int sgned, int* bitstream);
typedef ogg_int64_t(*LPOVPCMTOTAL)(OggVorbis_File* vf, int i);
typedef vorbis_info* (*LPOVINFO)(OggVorbis_File* vf, int link);
typedef vorbis_comment* (*LPOVCOMMENT)(OggVorbis_File* vf, int link);
typedef int (*LPOVOPENCALLBACKS)(void* datasource, OggVorbis_File* vf, char* initial, long ibytes, ov_callbacks callbacks);

// Variables
LPOVCLEAR			fn_ov_clear = NULL;
LPOVREAD			fn_ov_read = NULL;
LPOVPCMTOTAL		fn_ov_pcm_total = NULL;
LPOVINFO			fn_ov_info = NULL;
LPOVCOMMENT			fn_ov_comment = NULL;
LPOVOPENCALLBACKS	fn_ov_open_callbacks = NULL;

bool g_bVorbisInit = false;

Ogg::Ogg()
{
	// Initialize Framework
	ALFWInit();

	ALFWprintf("PlayOggVorbis Test Application\n");

	// Initialize OggVorbis libary
	InitVorbisFile();
	if (!g_bVorbisInit)
	{
		ALFWprintf("Failed to find OggVorbis DLLs (vorbisfile.dll, ogg.dll, or vorbis.dll)\n");
		ALFWShutdown();
		return;
	}

	// Initialise OpenAL
	if (!ALFWInitOpenAL())
	{
		ALFWprintf("Failed to initialize OpenAL\n");
		ALFWShutdown();
		return;
	}

}

bool Ogg::PlayOgg(const char* _filename)
{
	
	stream.sCallbacks.read_func = ov_read_func;
	stream.sCallbacks.seek_func = ov_seek_func;
	stream.sCallbacks.close_func = ov_close_func;
	stream.sCallbacks.tell_func = ov_tell_func;
	stream.ulFormat = 0;


	stream.pOggVorbisFile = fopen(ALFWaddMediaPath(_filename), "rb");

	if (!stream.pOggVorbisFile)
	{
		ALFWprintf("Could not find %s\n", ALFWaddMediaPath(_filename));
		ShutdownVorbisFile();
		ALFWShutdownOpenAL();
		ALFWShutdown();
		return 0;
	}


	// Create an OggVorbis file stream
	if (fn_ov_open_callbacks(stream.pOggVorbisFile, &stream.sOggVorbisFile, NULL, 0, stream.sCallbacks) == 0)
	{
		// Get some information about the file (Channels, Format, and Frequency)
		stream.psVorbisInfo = fn_ov_info(&stream.sOggVorbisFile, -1);
		if (stream.psVorbisInfo)
		{
			stream.ulFrequency = stream.psVorbisInfo->rate;
			stream.ulChannels = stream.psVorbisInfo->channels;
			if (stream.psVorbisInfo->channels == 1)
			{
				stream.ulFormat = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				stream.ulBufferSize = stream.ulFrequency >> 1;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				stream.ulBufferSize -= (stream.ulBufferSize % 2);
			}
			else if (stream.psVorbisInfo->channels == 2)
			{
				stream.ulFormat = AL_FORMAT_STEREO16;
				// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
				stream.ulBufferSize = stream.ulFrequency;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				stream.ulBufferSize -= (stream.ulBufferSize % 4);
			}
			else if (stream.psVorbisInfo->channels == 4)
			{
				stream.ulFormat = alGetEnumValue("AL_FORMAT_QUAD16");
				// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
				stream.ulBufferSize = stream.ulFrequency * 2;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				stream.ulBufferSize -= (stream.ulBufferSize % 8);
			}
			else if (stream.psVorbisInfo->channels == 6)
			{
				stream.ulFormat = alGetEnumValue("AL_FORMAT_51CHN16");
				// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
				stream.ulBufferSize = stream.ulFrequency * 3;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				stream.ulBufferSize -= (stream.ulBufferSize % 12);
			}
		}

		if (stream.ulFormat != 0)
		{
			// Allocate a buffer to be used to store decoded data for all Buffers
			stream.pDecodeBuffer = (char*)malloc(stream.ulBufferSize);
			if (!stream.pDecodeBuffer)
			{
				fn_ov_clear(&stream.sOggVorbisFile);
				ShutdownVorbisFile();
				ALFWShutdownOpenAL();
				ALFWShutdown();
				return false;
			}

			// Generate some AL Buffers for streaming
			alGenBuffers(NUMBUFFERS, stream.uiBuffers);

			// Generate a Source to playback the Buffers
			alGenSources(1, &stream.uiSource);

			// Fill all the Buffers with decoded audio data from the OggVorbis file
			for (stream.iLoop = 0; stream.iLoop < NUMBUFFERS; stream.iLoop++)
			{
				stream.ulBytesWritten = DecodeOggVorbis(&stream.sOggVorbisFile, stream.pDecodeBuffer, stream.ulBufferSize, stream.ulChannels);
				if (stream.ulBytesWritten)
				{
					alBufferData(stream.uiBuffers[stream.iLoop], stream.ulFormat, stream.pDecodeBuffer, stream.ulBytesWritten, stream.ulFrequency);
					alSourceQueueBuffers(stream.uiSource, 1, &stream.uiBuffers[stream.iLoop]);
				}
			}

			// Start playing source
			alSourcePlay(stream.uiSource);

			stream.iTotalBuffersProcessed = 0;

			Sleep(SERVICE_UPDATE_PERIOD);

			// Request the number of OpenAL Buffers have been processed (played) on the Source
			stream.iBuffersProcessed = 0;
			alGetSourcei(stream.uiSource, AL_BUFFERS_PROCESSED, &stream.iBuffersProcessed);

			// Keep a running count of number of buffers processed (for logging purposes only)
			stream.iTotalBuffersProcessed += stream.iBuffersProcessed;

			// For each processed buffer, remove it from the Source Queue, read next chunk of audio
			// data from disk, fill buffer with new data, and add it to the Source Queue
			while (stream.iBuffersProcessed)
			{
				// Remove the Buffer from the Queue.  (uiBuffer contains the Buffer ID for the unqueued Buffer)
				stream.uiBuffer = 0;
				alSourceUnqueueBuffers(stream.uiSource, 1, &stream.uiBuffer);

				// Read more audio data (if there is any)
				stream.ulBytesWritten = DecodeOggVorbis(&stream.sOggVorbisFile, stream.pDecodeBuffer, stream.ulBufferSize, stream.ulChannels);
				if (stream.ulBytesWritten)
				{
					alBufferData(stream.uiBuffer, stream.ulFormat, stream.pDecodeBuffer, stream.ulBytesWritten, stream.ulFrequency);
					alSourceQueueBuffers(stream.uiSource, 1, &stream.uiBuffer);
				}

				stream.iBuffersProcessed--;
			}

			// Check the status of the Source.  If it is not playing, then playback was completed,
			// or the Source was starved of audio data, and needs to be restarted.
			alGetSourcei(stream.uiSource, AL_SOURCE_STATE, &stream.iState);
			if (stream.iState != AL_PLAYING)
			{
				// If there are Buffers in the Source Queue then the Source was starved of audio
				// data, so needs to be restarted (because there is more audio data to play)
				alGetSourcei(stream.uiSource, AL_BUFFERS_QUEUED, &stream.iQueuedBuffers);
				if (stream.iQueuedBuffers)
				{
					alSourcePlay(stream.uiSource);
				}
			}

			// Stop the Source and clear the Queue
			alSourceStop(stream.uiSource);
			alSourcei(stream.uiSource, AL_BUFFER, 0);

			if (stream.pDecodeBuffer)
			{
				free(stream.pDecodeBuffer);
				stream.pDecodeBuffer = NULL;
			}

			// Clean up buffers and sources
			alDeleteSources(1, &stream.uiSource);
			alDeleteBuffers(NUMBUFFERS, stream.uiBuffers);
		}


		return true;
	}

	return false;
}

bool Ogg::Pause()
{

	return true;
}

bool Ogg::Stop()
{

	// Close OggVorbis stream
	fn_ov_clear(&stream.sOggVorbisFile);
	return true;
}
bool Ogg::Resume()
{


	return true;
}


void InitVorbisFile()
{
	if (g_bVorbisInit)
		return;

	// Try and load Vorbis DLLs (VorbisFile.dll will load ogg.dll and vorbis.dll)
	g_hVorbisFileDLL = LoadLibrary(TEXT("vorbisfile.dll"));
	if (g_hVorbisFileDLL)
	{
		fn_ov_clear = (LPOVCLEAR)GetProcAddress(g_hVorbisFileDLL, "ov_clear");
		fn_ov_read = (LPOVREAD)GetProcAddress(g_hVorbisFileDLL, "ov_read");
		fn_ov_pcm_total = (LPOVPCMTOTAL)GetProcAddress(g_hVorbisFileDLL, "ov_pcm_total");
		fn_ov_info = (LPOVINFO)GetProcAddress(g_hVorbisFileDLL, "ov_info");
		fn_ov_comment = (LPOVCOMMENT)GetProcAddress(g_hVorbisFileDLL, "ov_comment");
		fn_ov_open_callbacks = (LPOVOPENCALLBACKS)GetProcAddress(g_hVorbisFileDLL, "ov_open_callbacks");

		if (fn_ov_clear && fn_ov_read && fn_ov_pcm_total && fn_ov_info &&
			fn_ov_comment && fn_ov_open_callbacks)
		{
			g_bVorbisInit = true;
		}
	}
}

void ShutdownVorbisFile()
{
	if (g_hVorbisFileDLL)
	{
		FreeLibrary(g_hVorbisFileDLL);
		g_hVorbisFileDLL = NULL;
	}
	g_bVorbisInit = false;
}

unsigned long DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels)
{
	int current_section;
	long lDecodeSize;
	unsigned long ulSamples;
	short* pSamples;

	unsigned long ulBytesDone = 0;
	while (1)
	{
		lDecodeSize = fn_ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
		if (lDecodeSize > 0)
		{
			ulBytesDone += lDecodeSize;

			if (ulBytesDone >= ulBufferSize)
				break;
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (ulChannels == 6)
	{
		pSamples = (short*)pDecodeBuffer;
		for (ulSamples = 0; ulSamples < (ulBufferSize >> 1); ulSamples += 6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			Swap(pSamples[ulSamples + 1], pSamples[ulSamples + 2]);
			Swap(pSamples[ulSamples + 3], pSamples[ulSamples + 5]);
			Swap(pSamples[ulSamples + 4], pSamples[ulSamples + 5]);
		}
	}

	return ulBytesDone;
}

void Swap(short& s1, short& s2)
{
	short sTemp = s1;
	s1 = s2;
	s2 = sTemp;
}

size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	return fread(ptr, size, nmemb, (FILE*)datasource);
}

int ov_seek_func(void* datasource, ogg_int64_t offset, int whence)
{
	return fseek((FILE*)datasource, (long)offset, whence);
}

int ov_close_func(void* datasource)
{
	return fclose((FILE*)datasource);
}

long ov_tell_func(void* datasource)
{
	return ftell((FILE*)datasource);
}
