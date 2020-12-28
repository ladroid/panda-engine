#include <iostream>
#include <string>
#include "irrKlang.h"

using namespace irrklang;

class Audio
{
private:
	ISoundEngine* soundEngine;
public:
	Audio()
	{
		soundEngine = createIrrKlangDevice();
		if (!soundEngine)
		{
			throw("Could not launch audio");
		}
	}

	void play(std::string filename, bool loop = true, float volume = 1.0f)
	{
		soundEngine->setSoundVolume(volume);
		soundEngine->play2D(filename.c_str(), loop);
	}

	void play3D(std::string filename, vec3df pos = vec3df(0, 0, 0), bool loop = true, float volume = 1.0f)
	{
		soundEngine->setSoundVolume(volume);
		soundEngine->play3D(filename.c_str(), pos, loop, false, true);
	}

	void stop()
	{
		soundEngine->stopAllSounds();
	}

	~Audio()
	{
		soundEngine->drop();
	}
};