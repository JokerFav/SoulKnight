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
	sprite.x = new_pos.y * sprite.w;
	sprite.y = new_pos.x * sprite.h;
}

bool Entity::collision_detection(SDL_Rect x, vector<SDL_Rect>& y)
{
	for(int i = 0; i < (int)y.size(); ++i)
		if(SDL_HasIntersection(&x, &y[i]) == SDL_TRUE)
			return true;
	return false;
}

void Entity::move_x(float speed, SDL_Rect l_rect)
{
	pos.x += speed;
	l_rect.x += max(round(speed), (speed > 0.0f ? 1.0f : -1.0f));
	if(collision_detection(l_rect, map_tiles))
	{
		pos.x -= speed;
		cout << "collision detected on x-axis" << endl;
	}
}

void Entity::move_y(float speed, SDL_Rect l_rect)
{
	pos.y += speed;
	l_rect.y += max(round(speed), (speed > 0.0f ? 1.0f : -1.0f));
	cout << "before: " << l_rect.y << endl;
	if(collision_detection(l_rect, map_tiles))
	{
		pos.y -= speed;
		cout << "collision detected on y-axis " << l_rect.y << endl;
	}
}


