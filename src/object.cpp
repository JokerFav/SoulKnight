#include "object.hpp"
using namespace std;

Object::Object(SDL_Texture* new_tex):tex(new_tex)
{

}

void Object::render_behind(float y)
{
	SDL_Rect p_in, p_out;
	for(int i = 0; i < (int)pos.size(); ++i)
		if(pos[i].y + tiles[order[i]].h <= y + 3)
		{
			p_in = tiles[order[i]];
			p_out.x = pos[i].x - camera.x;
			p_out.y = pos[i].y - camera.y;
			p_out.w = p_in.w;
			p_out.h = p_in.h;
			SDL_RenderCopy(main_window.renderer, tex, &p_in, &p_out);
		}
}

void Object::render_front(float y)
{
	SDL_Rect p_in, p_out;
	for(int i = 0; i < (int)pos.size(); ++i)
		if(pos[i].y + tiles[order[i]].h > y + 3)
		{
			p_in = tiles[order[i]];
			p_out.x = pos[i].x - camera.x;
			p_out.y = pos[i].y - camera.y;
			p_out.w = p_in.w;
			p_out.h = p_in.h;
			SDL_RenderCopy(main_window.renderer, tex, &p_in, &p_out);
		}
}

Wall::Wall():
	Object(main_window.load_texture("res/wall_2.png"))
{
	order.emplace_back(0);
	tiles.emplace_back(SDL_Rect{6, 6, 175, 20});
	pos.emplace_back(vector2f{49, 96});

	order.emplace_back(1);
	tiles.emplace_back(SDL_Rect{3, 39, 235, 22});	
	pos.emplace_back(vector2f{262, 96});

	order.emplace_back(2);
	tiles.emplace_back(SDL_Rect{0, 74, 271, 32});
	pos.emplace_back(vector2f{53, 288});

	order.emplace_back(3);
	tiles.emplace_back(SDL_Rect{8, 119, 141, 19});
	pos.emplace_back(vector2f{65, 410});

	order.emplace_back(4);
	tiles.emplace_back(SDL_Rect{3, 150, 267, 22});
	pos.emplace_back(vector2f{206, 560});


}

Decorations::Decorations():
	Object(main_window.load_texture("res/decorations.png"))
{
	order.emplace_back(0);
	tiles.emplace_back(SDL_Rect{3, 2, 57, 28});
	pos.emplace_back(vector2f{142, 222});

	order.emplace_back(1);
	tiles.emplace_back(SDL_Rect{3, 34, 42, 28});
	pos.emplace_back(vector2f{321, 458});

	order.emplace_back(1);
	pos.emplace_back(vector2f{320, 507});

	order.emplace_back(2);
	tiles.emplace_back(SDL_Rect{52, 37, 8, 7});
	pos.emplace_back(vector2f{167, 212});

	order.emplace_back(2);
	pos.emplace_back(vector2f{137, 251});

	order.emplace_back(2);
	pos.emplace_back(vector2f{296, 504});

	order.emplace_back(2);
	pos.emplace_back(vector2f{407, 440});

	order.emplace_back(3);
	tiles.emplace_back(SDL_Rect{51, 52, 10, 7});
	pos.emplace_back(vector2f{192, 253});

	order.emplace_back(3);
	pos.emplace_back(vector2f{272, 232});

	order.emplace_back(3);
	pos.emplace_back(vector2f{304, 280});

	order.emplace_back(3);
	pos.emplace_back(vector2f{80, 248});

	order.emplace_back(3);
	pos.emplace_back(vector2f{223, 504});

	order.emplace_back(3);
	pos.emplace_back(vector2f{280, 534});

	order.emplace_back(3);
	pos.emplace_back(vector2f{391, 511});

	order.emplace_back(3);
	pos.emplace_back(vector2f{345, 490});

	order.emplace_back(4);
	tiles.emplace_back(SDL_Rect{4, 66, 8, 10});
	pos.emplace_back(vector2f{241, 262});

	order.emplace_back(4);
	pos.emplace_back(vector2f{145, 278});

	order.emplace_back(5);
	tiles.emplace_back(SDL_Rect{37, 70, 22, 19});
	pos.emplace_back(vector2f{437, 464});

	order.emplace_back(5);
	pos.emplace_back(vector2f{217, 521});

	order.emplace_back(6);
	tiles.emplace_back(SDL_Rect{3, 85, 26, 19});
	pos.emplace_back(vector2f{229, 281});

	order.emplace_back(6);
	pos.emplace_back(vector2f{66, 197});

	order.emplace_back(7);
	tiles.emplace_back(SDL_Rect{19, 65, 10, 14});
	pos.emplace_back(vector2f{436, 517});

	order.emplace_back(8);
	tiles.emplace_back(SDL_Rect{8, 110, 16, 24});
	pos.emplace_back(vector2f{276, 485});

	order.emplace_back(9);
	tiles.emplace_back(SDL_Rect{40, 101, 16, 24});
	pos.emplace_back(vector2f{388, 485});

}

