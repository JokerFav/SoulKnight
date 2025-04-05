#include "audio.hpp"
#include "Window.hpp"
using namespace std;

Audio sound;

Audio::Audio()
{
	//title_theme = Mix_LoadMUS()
}

void Audio::init()
{
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        cout << "Audio failed due to an error: " << Mix_GetError() << endl;  
    }
    Mix_AllocateChannels(25);
    boss_theme = Mix_LoadMUS("res/boss_theme.wav");
	ingame = Mix_LoadMUS("res/ingame.wav");
	title = Mix_LoadMUS("res/title.wav");
	wave = Mix_LoadMUS("res/wave.wav");
	Mix_VolumeMusic(15);
}

void Audio::play(string music)
{
	string music_path = "res/" + music + ".wav";
	current_chunk = Mix_LoadWAV(music_path.c_str());
	if(channel_list.find(music_path) == channel_list.end())
		channel_list[music_path] = channel_list.size();
	Mix_Volume(channel_list[music_path], 60);
	if(!Mix_Playing(channel_list[music_path]))
		Mix_PlayChannel(channel_list[music_path], current_chunk, 0);
}