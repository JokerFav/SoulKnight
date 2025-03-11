#ifndef entity_HPP
#define entity_HPP
#include "map.hpp"
using namespace std;


class Entity
{
public:
	Entity(SDL_Texture* new_texture = NULL, vector2f new_pos = {0.0f, 0.0f},
		int new_x = 0, int new_y = 0, int new_w = 32, int new_h = 32);
	Entity(SDL_Texture* new_texture, vector2f new_pos, SDL_Rect new_sprite);
	SDL_Texture* get_tex();
	SDL_RendererFlip get_flip();
	SDL_Rect get_rect();
	SDL_Rect get_sprite();
	float get_y();
	void set_flip(SDL_RendererFlip new_flip);
	void set_sprite(vector2f new_pos);
	bool collision_detection(SDL_Rect x, vector<SDL_Rect>& y);
	void move_x(int speed, float delta_time);
	void move_y(int speed, float delta_time);
protected:
	SDL_Texture* texture;
	vector2f pos;
	SDL_Rect sprite;
	SDL_RendererFlip flip;
};








#endif
