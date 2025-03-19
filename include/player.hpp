#ifndef player_HPP
#define player_HPP

#include "entity.hpp"
using namespace std;

class Player : public Entity 
{
public:
	Player();
	void player_render();
	void player_update(float now, bool is_attacking);
	void camera_update();
	SDL_Rect get_leg_rect();
private:
	SDL_Rect hitbox; //real hitbox = +8, +10, 15, 20
	int order;
};


#endif