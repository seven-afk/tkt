#pragma once
#include"Framework.h"
#include<Vorbis/vorbisfile.h>
#include<Ogg/Ogg.h>

struct OggStream
{
	ALuint		    uiBuffers[4];
	ALuint		    uiSource;
	ALuint			uiBuffer;
	ALint			iState;
	ALint			iLoop;
	ALint			iBuffersProcessed, iTotalBuffersProcessed, iQueuedBuffers;
	unsigned long	ulFrequency = 0;
	unsigned long	ulFormat = 0;
	unsigned long	ulChannels = 0;
	unsigned long	ulBufferSize;
	unsigned long	ulBytesWritten;
	char* pDecodeBuffer;
	FILE* pOggVorbisFile;
	ov_callbacks	sCallbacks;
	OggVorbis_File	sOggVorbisFile;
	vorbis_info* psVorbisInfo;
};

public class Ogg
{
	OggStream stream{};
	HANDLE hThread = NULL;
	volatile bool bStopRequested = false;
	bool bOpen = false;

	static DWORD WINAPI StreamThread(LPVOID param);
	void StreamLoop();

public :
	Ogg();
	bool InitFile(const char* fileName);
	bool PlayOgg();//JE SUIS AMOUREUX DE CLEMENT
	bool Stop();
	bool Pause();
	bool Resume();
};
