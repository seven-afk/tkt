#pragma once
#include"Framework.h"
public class Wav
{
public :
	Wav();
	ALuint      uiBuffer;
	ALuint      uiSource;
	ALint       iState;
	int PlayWav(const char* fileName);
	int StopWav();
	int PauseWav();
	int ResumeWav();
};

