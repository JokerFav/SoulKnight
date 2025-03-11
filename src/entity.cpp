#include "entity.hpp"
using namespace std;

Entity::Entity(SDL_Texture* new_texture, vector2f new_pos, int new_x, int new_y, int new_w, int new_h):
	texture(new_texture), pos(new_pos)
{
	
	sprite.x = new_x;
	sprite.y = new_y;
	sprite.w = new_w;
	sprite.h = new_h;
	flip = SDL_FLIP_NONE;
}

Entity::Entity(SDL_Texture* new_texture, vector2f new_pos, SDL_Rect new_sprite):
	texture(new_texture), pos(new_pos), sprite(new_sprite)
{

}

SDL_Texture* Entity::get_tex()
{
	return texture;
}

SDL_RendererFlip Entity::get_flip()
{
	return flip;
}

SDL_Rect Entity::get_rect()
{
	SDL_Rect real_pos;
	real_pos.x = pos.x + 8;
	real_pos.y = pos.y + 10;
	real_pos.w = 15;
	real_pos.h = 20;
	return real_pos;
}

SDL_Rect Entity::get_sprite()
{
	return sprite;
}

float Entity::get_y()
{
	return pos.y;
}

void Entity::set_flip(SDL_RendererFlip new_flip)
{
	flip = new_flip;
}

void Entity::set_sprite(vector2f new_pos)
{
	sprite.x = new_pos.y * sprite.h;
	sprite.y = new_pos.x * sprite.w;
}

bool Entity::collision_detection(SDL_Rect x, vector<SDL_Rect>& y)
{
	for(int i = 0; i < (int)y.size(); ++i)
		if(SDL_HasIntersection(&x, &y[i]) == SDL_TRUE)
			return true;
	return false;
}

void Entity::move_x(int speed, float delta_time)
{
	delta_time = FRAME_DELAY / 1000;
	pos.x += delta_time * speed;
	if(collision_detection(get_rect(), map_tiles))
		pos.x -= delta_time * speed;
}

void Entity::move_y(int speed, float delta_time)
{
	delta_time = FRAME_DELAY / 1000;
	pos.y += delta_time * speed;
	if(collision_detection(get_rect(), map_tiles))
		pos.y -= delta_time * speed;
}



