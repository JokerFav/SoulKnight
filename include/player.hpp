#ifndef player_HPP
#define player_HPP

#include "entity.hpp"
using namespace std;

class Player : public Entity 
{
public:
	Player(Window &main_window);
	void player_render(Window &main_window);
	void player_update(float delta_time, float now);
	void camera_update();
private:
	SDL_Rect hitbox; //real hitbox = +8, +10, 15, 20
	int order;
	float last;
};


#endif