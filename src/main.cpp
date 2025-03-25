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
	Wall main_wall;
	Decorations decor;
	
	spawn_enemies();






	
	bool is_running = true;
	SDL_Event event;
	float delta_time = 0;
	Uint32 last_counter = 0;
	while(is_running)
	{
		Uint32 frame_start = SDL_GetPerformanceCounter();


		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}
		main_window.before_render();
		
		Uint32 current_counter = SDL_GetPerformanceCounter();
		float current_time = current_counter / (float)SDL_GetPerformanceFrequency();
		delta_time = (current_counter - last_counter)
			/ (float)SDL_GetPerformanceFrequency();
		last_counter = current_counter;



		main_player.update(current_time, sword.is_attack(), delta_time);
		sword.attack(current_time, main_player.get_pos(), main_player.get_flip());








		main_map.map_render();
		decor.render_behind(main_player.get_leg_rect().y);
		main_wall.render_behind(main_player.get_leg_rect().y);
		sword.sword_render();
		main_player.player_render();
		decor.render_front(main_player.get_leg_rect().y);
		main_wall.render_front(main_player.get_leg_rect().y);	

		for(Enemy *e: enemies)
		{
			if(Slime* enemy = dynamic_cast<Slime*>(e))
				enemy->update(current_time, delta_time);
			if(Troll* enemy = dynamic_cast<Troll*>(e))
				enemy->update(current_time, delta_time);
			if(Orc* enemy = dynamic_cast<Orc*>(e))
				enemy->update(current_time, delta_time);
		}

		for(int i = 0; i < (int)enemies.size(); i++)
			if((*enemies[i]).is_death())
			{
				swap(enemies[i], enemies.back());
				enemies.pop_back();
				i--;
			}

		for(Enemy *e: enemies) main_window.render_entity(*e);


		main_window.present();

		Uint32 frame_end = SDL_GetPerformanceCounter();
		delta_time = (frame_end - frame_start)
		/ (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(max(FRAME_DELAY - delta_time, 0.0f));
	}
	main_window.QuitSDL();
	return 0;
}