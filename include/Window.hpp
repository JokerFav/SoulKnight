#ifndef Window_HPP
#define Window_HPP

#include "entity.hpp"
using namespace std;


class Window
{
	public:
			Window();
			void before_render();
			SDL_Texture* load_texture(string path);
			void QuitSDL();
			void render_map(SDL_Rect &tile, SDL_Texture* &MapTexture);
			void present();
			void render_entity(Entity &entity);
		SDL_Window* window;
		SDL_Renderer* renderer;
	private:
};

extern Window main_window;


#endif