#include "map.hpp"
#include "player.hpp"
#include "object.hpp"
#include "fantasy.hpp"
#include "enemy.hpp"
#include "window.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	main_window.before_render();
	Map main_map;
	main_map.map_init();
	Player main_player;
	Wall main_wall;
	Decorations decor;
	Sword sword;
	
	spawn_enemies();






	
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
		main_player.player_update(now, sword.is_attacking());
		sword.attack(now, main_player.get_pos(), main_player.get_flip());









		main_map.map_render();
		decor.render_behind(main_player.get_leg_rect().y);
		main_wall.render_behind(main_player.get_leg_rect().y);
		sword.sword_render();
		main_player.player_render();
		decor.render_front(main_player.get_leg_rect().y);
		main_wall.render_front(main_player.get_leg_rect().y);	

		/*for(Enemy* e: enemies)
		{
			if(Slime* enemy = dynamic_cast<Slime*>(e))
				enemy->update(now);
		}

		for()*/


		main_window.present();

		Uint32 frame_end = SDL_GetTicks();
		delta_time = (frame_end - frame_start) * 0.001f;
		SDL_Delay(FRAME_DELAY - delta_time);
	}
	main_window.QuitSDL();
	return 0;
}