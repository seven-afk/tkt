#include "Wav.h"

Wav::Wav() {

	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
	}
}
int Wav::PlayWav(const char* fileName) {


	// Generate an AL Buffer
	alGenBuffers(1, &(uiBuffer));

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)fileName, uiBuffer))
	{
		ALFWprintf("Failed to load %s\n", fileName);
	}

	// Generate a Source to playback the Buffer
	alGenSources(1, &uiSource);

	// Attach Source to Buffer
	alSourcei(uiSource, AL_BUFFER, uiBuffer);
	//pour boucler un son
	alSourcei(uiSource, AL_LOOPING, 1);
	// Play Source
	alSourcePlay(uiSource);
	return 0;
}
int Wav::PauseWav() {
	alSourcePause(uiSource);
	return 0;
}

int Wav::ResumeWav() {
	alSourcePlay(uiSource);
	return 0;
}

int Wav::StopWav() {
	alSourceStop(uiSource);
	alSourceRewind(uiSource);
	return 0;
}