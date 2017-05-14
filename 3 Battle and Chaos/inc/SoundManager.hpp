/**
 * \class
 * This class manage various sounds in the game.
 * 
 */

#ifndef SoundManager_HPP
#define SoundManager_HPP
#include <list>
#include <map>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager();	///<constructor
	~SoundManager();	///<destructor
	sf::SoundBuffer* getResource( const std::string FileName );	///<returns the corresponding sound buffer
	void playSound(const std::string& FileName, float volume);	///<plays the sound
	void update();	///<removes stopped sounds
	inline static SoundManager& getInstance() {
		return singleton;
	}
private:
	std::list<sf::Sound> soundList;	///<vector of sound
	std::map<std::string, sf::SoundBuffer*> buffMap;
	static SoundManager singleton;
};

#endif // SoundManager_hpp__
