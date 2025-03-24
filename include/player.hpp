#ifndef player_HPP
#define player_HPP

#include "Window.hpp"
using namespace std;

class Player : public Entity 
{
public:
	Player();
	void player_render();
	void update(float current_time, bool is_attack, float delta_time);
	void camera_update();
	bool is_death();
	SDL_Rect get_leg_rect();
private:
	int wait;
	vector2f direction;
	//real hitbox = +8, +10, 15, 20
};

extern Player main_player;


#endif