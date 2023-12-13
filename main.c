#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>
#define body 7
#define inc 10
#define azul al_map_rgb_f(0, 0, 1)
#define branco al_map_rgb_f(255,255,255)
#define dbb al_map_rgb_f(0,1,0)

const float FPS = 40;

int main(int argc, char *argv[]){   
	bool running = true;
	bool redraw = true;
	al_init();


	ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
 	ALLEGRO_TIMER* timer = al_create_timer(1.0/20);
	ALLEGRO_BITMAP  *background= NULL;
	display = al_create_display(480, 600);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	//addons
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
	//
	int x=220;
	int y = 300;
	int state =83;
	int eixo;
	void orch2(int x, int y, ALLEGRO_COLOR cor){
		
		al_draw_rectangle(x, y, x+body, y+body, cor, 5);
		al_flip_display();
	}
	void orch1(int x, int y, ALLEGRO_COLOR cor){
		
		al_draw_rectangle(x, y, x+body, y+body, cor, 5);
		al_flip_display();
	}
	
	bool valid(int num){

		if (state == 84 && num == 85)
			return 0;
		if(state == 82 && num == 83)
			return 0;
		if (state == 85 && num == 84)
			return 0;
		if(state == 83 && num == 82)
			return 0;
	return 1;
	}

    while (running) {

        al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER)
			switch (state){
				case 84:
				y-=inc;
				orch1(x, y, azul);
				orch1(x,y+inc, dbb);
				puts("up");
				break;
			case 85:
				y+=inc;
				orch2(x, y, azul);
				orch2(x, y-inc, branco);
				puts("down");
				break;
			case 82:
				x-=inc;
				orch1(x, y, azul);
				orch1(x+inc,y, dbb);
				puts("left");
				break;
			case 83:
				x+=inc;
				orch2(x, y, azul);
				orch2(x-inc, y, branco);
				puts("right");
				break;
			
			default:
				printf("algo deu errado");
				break;
			}


        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode>81 && event.keyboard.keycode <86)
				if (valid(event.keyboard.keycode))
					state = event.keyboard.keycode;
        }
			printf("x: %i, y:%i\n",x,y);

        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);

    return 0;
}
