#ifndef player_HPP
#define player_HPP

#include "Window.hpp"
using namespace std;

class Player : public Entity 
{
public:
	Player();
	void player_render();
	SDL_Rect get_hitbox();
	void update(float current_time, bool is_attacking, float delta_time);
	void camera_update();
	SDL_Rect get_leg_rect();
private:
	//real hitbox = +8, +10, 15, 20
};


#endif