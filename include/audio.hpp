#ifndef audio_HPP
#define audio_HPP
#include "vector2f.hpp"

class Audio
{
public:
	Audio();
	void init();
	void play(string music);
	Mix_Music* boss_theme;
	Mix_Music* ingame;
	Mix_Music* title;
	Mix_Music* wave;
private:
	Mix_Chunk* current_chunk;
	unordered_map <string, int> channel_list;
};

extern Audio sound;









#endif