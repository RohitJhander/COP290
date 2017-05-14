#include "SoundManager.hpp"
#include <iostream>

SoundManager SoundManager::singleton;

SoundManager::SoundManager() {
	buffMap.clear();
}

SoundManager::~SoundManager() {
	update();
}

sf::SoundBuffer* SoundManager::getResource( const std::string FileName ) {
	sf::SoundBuffer* SoundBuf = new sf::SoundBuffer();
	if(!SoundBuf->loadFromFile(("data/sounds/")+(FileName)))
	{
		delete SoundBuf;
		SoundBuf = NULL;
		return SoundBuf;
	}
	if(buffMap.find(FileName)==buffMap.end())
	{
		buffMap[FileName]=SoundBuf;
	}
	else
	{
		delete SoundBuf;
	}
	return buffMap[FileName];
}

void SoundManager::playSound( const std::string& FileName, float Volume ) {
	sf::Sound Sound;
	soundList.push_back(Sound);
	soundList.back().setVolume(Volume);
	soundList.back().setBuffer(*getResource(FileName));		
	soundList.back().play();
	update();
}

void SoundManager::update() {
	for(std::list<sf::Sound>::iterator It = soundList.begin(); It != soundList.end(); ++It)
	{
		if (It->getStatus() == sf::Sound::Stopped)
		{
			It = soundList.erase(It);
			if (It == soundList.end())
			{
				break;
			}
		}
	}
}

