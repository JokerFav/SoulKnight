#include "entity.hpp"
using namespace std;

Entity::Entity(vector2f new_pos, SDL_Texture* new_texture, int new_x, int new_y, int new_w, int new_h):
	pos(new_pos), texture(new_texture)
{
	
	sprite.x = new_x;
	sprite.y = new_y;
	sprite.w = new_w;
	sprite.h = new_h;
	flip = SDL_FLIP_NONE;
}

Entity::Entity(vector2f new_pos, SDL_Texture* new_texture, SDL_Rect new_sprite):
	pos(new_pos), texture(new_texture), sprite(new_sprite)
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
	real_pos.x = pos.x + 9;
	real_pos.y = pos.y + 26;
	real_pos.w = 13;
	real_pos.h = 3;
	return real_pos;
}

SDL_Rect Entity::get_sprite()
{
	return sprite;
}

vector2f Entity::get_pos()
{
	return pos;
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

void Entity::move_x(int speed, SDL_Rect l_rect)
{
	float delta_time = FRAME_DELAY / 1000.0f;
	pos.x += delta_time * speed;
	l_rect.x += round(delta_time * speed);
	if(collision_detection(l_rect, map_tiles))
	{
		pos.x -= delta_time * speed;
		//cout << "collision detected on x-axis" << endl;
	}
}

void Entity::move_y(int speed, SDL_Rect l_rect)
{
	float delta_time = FRAME_DELAY / 1000.0f;
	pos.y += delta_time * speed;
	l_rect.y += round(delta_time * speed);
	if(collision_detection(l_rect, map_tiles))
	{
		pos.y -= delta_time * speed;
		//cout << "collision detected on x-axis" << endl;
	}
}


