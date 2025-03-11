#include "map.hpp"
#include "player.hpp"
#include "object.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	Window main_window;
	main_window.before_render();

	Map main_map;
	main_map.map_init(main_window);

	Player main_player(main_window);

	Wall main_wall(main_window);

	Decorations decor(main_window);

	bool is_running = true;
	SDL_Event event;
	float delta_time = 0;
	while(is_running)
	{
		
		Uint32 frame_start = SDL_GetTicks();

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}
		main_window.before_render();
		
		float now = SDL_GetTicks() * 0.001f;
		main_player.player_update(delta_time, now);
		main_map.map_render(main_window);
		decor.render_behind(main_window, main_player.get_y());
		main_player.player_render(main_window);
		decor.render_front(main_window, main_player.get_y());
		main_wall.render_front(main_window, 0.0f);	



		main_window.present();

		Uint32 frame_end = SDL_GetTicks();
		delta_time = (frame_end - frame_start) * 0.001f;
		SDL_Delay(FRAME_DELAY - delta_time);
	}
	main_window.QuitSDL();
	return 0;
}
