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
	
	spawn_enemies();
	spawn_objects();
	sort(objects.begin(), objects.end(), [](Entity* a, Entity* b)
	{
		return a->get_y() < b->get_y();
	});

	set_health_bar();
	set_pos_available();

	
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
		cout << current_time << endl;
		delta_time = (current_counter - last_counter)
			/ (float)SDL_GetPerformanceFrequency();
		last_counter = current_counter;

		main_player.update(current_time, sword.is_attack(), delta_time, rooms[2]);
		sword.attack(current_time, main_player.get_pos(), main_player.get_flip());
		for(int i = 0; i < (int)health_bar.size(); ++i)
		{
			if(main_player.get_health() <= i * 2) 
				health_bar[i]->update(2);
			if(main_player.get_health() == i * 2 + 1)
				health_bar[i]->update(1);
			if(main_player.get_health() >= (i + 1) * 2)
				health_bar[i]->update(0);
		}

		/*
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
		*/

		while(enemies.size()) 
		{
			rooms[2].emplace_back(enemies.back());
			enemies.pop_back();
		}

		for(Enemy *e: rooms[2])
			{
				if(Slime* enemy = dynamic_cast<Slime*>(e))
					enemy->update(current_time, delta_time);
				if(Troll* enemy = dynamic_cast<Troll*>(e))
					enemy->update(current_time, delta_time);
				if(Orc* enemy = dynamic_cast<Orc*>(e))
					enemy->update(current_time, delta_time);
				if(Skeleton* enemy = dynamic_cast<Skeleton*>(e))
					enemy->update(current_time, delta_time);
				if(Projectile* enemy = dynamic_cast<Projectile*>(e))
					enemy->update(current_time, delta_time);
				if(Neucromancer* enemy = dynamic_cast<Neucromancer*>(e))
					enemy->update(current_time, delta_time, enemies);
			}

		for(int i = 0; i < (int)rooms[2].size(); i++)
			if((*rooms[2][i]).is_death())
			{
				swap(rooms[2][i], rooms[2].back());
				rooms[2].pop_back();
				i--;
			}



		main_map.map_render();	
		/*
		bool r_player = 0;
		int lo = 0;

		sort(enemies.begin(), enemies.end(), [](Enemy* a, Enemy* b)
		{
			return a->get_y() < b->get_y();
		});

		for(Enemy *e: enemies) 
			if(e->is_spawn())
			{
				if(!r_player && e->get_y() >= main_player.get_y())
				{
					sword.sword_render();
					main_player.player_render();
					r_player = 1;
				}
				while(lo < (int)objects.size() && objects[lo]->get_y() <= e->get_y())
				{
					main_window.render_entity(*objects[lo]);
					lo++;
				}
				main_window.render_entity(*e);
			}
		if(!r_player)
		{
			while(lo < (int)objects.size() && objects[lo]->get_y() <= main_player.get_y())
			{
				main_window.render_entity(*objects[lo]);
				lo++;
			}
			sword.sword_render();
			main_player.player_render();
		}
		while(lo < (int)objects.size())
		{
			main_window.render_entity(*objects[lo]);
			lo++;
		}
		*/

		bool r_player = 0;
		int lo = 0;

		sort(rooms[2].begin(), rooms[2].end(), [](Enemy* a, Enemy* b)
		{
			return a->get_y() < b->get_y();
		});

		for(Enemy *e: rooms[2]) 
			if(e->is_spawn())
			{
				if(!r_player && e->get_y() >= main_player.get_y())
				{
					while(lo < (int)objects.size() && objects[lo]->get_y() <= main_player.get_y())
					{
						main_window.render_entity(*objects[lo]);
						lo++;
					}
					sword.sword_render();
					main_player.player_render();
					r_player = 1;
				}
				while(lo < (int)objects.size() && objects[lo]->get_y() <= e->get_y())
				{
					main_window.render_entity(*objects[lo]);
					lo++;
				}
				main_window.render_entity(*e);
			}
		if(!r_player)
		{
			while(lo < (int)objects.size() && objects[lo]->get_y() <= main_player.get_y())
			{
				main_window.render_entity(*objects[lo]);
				lo++;
			}
			sword.sword_render();
			main_player.player_render();
		}
		while(lo < (int)objects.size())
		{
			main_window.render_entity(*objects[lo]);
			lo++;
		}

		for(int i = 0; i < (int)health_bar.size(); ++i)
			main_window.render_entity(*health_bar[i]);


		main_window.present();

		Uint32 frame_end = SDL_GetPerformanceCounter();
		delta_time = (frame_end - frame_start)
		/ (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(max(FRAME_DELAY - delta_time, 0.0f));
	}
	main_window.QuitSDL();
	return 0;
}