#ifndef fantasy_HPP
#define fantasy_HPP
#include "entity.hpp"
using namespace std;

class Sword : public Entity
{
public:
	Sword();
	void sword_render();
	bool is_attacking();
	void attack(float now, vector2f player_pos, SDL_RendererFlip player_flip);
private:
	int order, state;
	double roll;
	float last_attack, last_update;
};









#endif