#ifndef entity_HPP
#define entity_HPP
#include "map.hpp"
using namespace std;


class Entity
{
public:
	Entity(vector2f new_pos = {0.0f, 0.0f}, SDL_Texture* new_texture = NULL,
		int new_x = 0, int new_y = 0, int new_w = 32, int new_h = 32);
	Entity(vector2f new_pos, SDL_Texture* new_texture, SDL_Rect new_sprite);
	SDL_Texture* get_tex();
	SDL_RendererFlip get_flip();
	SDL_Rect get_rect();
	SDL_Rect get_sprite();
	vector2f get_pos();
	void set_flip(SDL_RendererFlip new_flip);
	void set_sprite(vector2f new_pos);
	bool collision_detection(SDL_Rect x, vector<SDL_Rect>& y);
	void move_x(int speed, SDL_Rect l_rect);
	void move_y(int speed, SDL_Rect l_rect);
protected:
	vector2f pos;
	float last_update;
	SDL_Texture* texture;
	SDL_Rect sprite;
	SDL_RendererFlip flip;
};







#endif