#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "funcoes.h"
#define body 7
#define inc 10
const float FPS = 15;
#define show print_list(head)
coord candy_array[50];

void print_list(node* head){
	for (node* p  = head; p!=NULL; p = p->next){
		printf("node: %i\n", p->x);
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	bool running = true;
	al_init();

	ALLEGRO_EVENT event;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
 	ALLEGRO_TIMER* timer = al_create_timer(1.0/FPS);
	display = al_create_display(500, 600);
	al_clear_to_color(al_map_rgb(255, 255, 255)); //cor de fundo
	  al_flip_display();
	//addons
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	ALLEGRO_BITMAP *snake = al_load_bitmap("snaki.bmp");
	ALLEGRO_BITMAP *candy = al_load_bitmap("candy.bmp");

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	//
	int x=220;
	int y = 300;
	int count = 0;
	node* head = init_node(x,y);
	add(head, x-10, y);
	int state =83;
	void check_candy(int x, int y){
		int threshold = 4;
		for (int i=0; i<candy_coord_i; i++){
			int d_x = abs(x - candy_array[i].x);
			int d_y = abs(y - candy_array[i].y);
			
			if (d_x <= threshold && d_y <= threshold ){
				add(head, 0,0);    
				rm_candy(i);
			}
		}
	}

void att_coords(node* body_snake, int new_x, int new_y){
	node *cur = body_snake;
		while (cur!=NULL){
			if (cur->x == new_x && cur->y == new_y)
				game_over = true;
			cur = cur->next;
		}
	check_candy(new_x,new_y);
	cur = body_snake;
	int old_x = new_x;
	int old_y = new_y;
		while(cur !=NULL){
			int old_x_tmp = cur->x;
			int old_y_tmp = cur->y;
			cur->x = old_x;
			cur->y = old_y;
			old_x = old_x_tmp;
			old_y = old_y_tmp;
			cur = cur->next;
		}
}   
	void draw(node* head){
		node *cur = head;
		while (cur!= NULL){
			al_draw_bitmap(snake, cur->x, cur->y, 0);
			cur = cur->next;
		}
	}
	 void draw_candy(){
		for (int i = 0; i<candy_coord_i; i++){
			al_draw_bitmap(candy, candy_array[i].x, candy_array[i].y, 0);
		}
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
	void draws(){
		draw(head);
		draw_candy();
		al_flip_display();
		al_clear_to_color(al_map_rgb(255, 255, 255));

	}
	 while (running & !game_over) {

		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER){
			count +=20;
				if (count >500){
					add_candy();
					count = 0;
				}
			switch (state){
				case 84:
				y-=inc;
				att_coords(head, x,y);
				draws();
				break;
			case 85:
				y+=inc;
				att_coords(head, x, y);
				draws();
				break;
			case 82:
				x-=inc;
				att_coords(head,x,y);
				draws();          
				break;
			case 83:
				x+=inc;
				att_coords(head,x,y);
				draws();
			default:
				// printf("algo deu errado");
				break;
			}
		}

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			running = false;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode>81 && event.keyboard.keycode <86 && valid(event.keyboard.keycode))
				state = event.keyboard.keycode;
			if (event.keyboard.keycode == ALLEGRO_KEY_A)
				add(head, 0,0);
			if (event.keyboard.keycode == ALLEGRO_KEY_B)
				running = false;

		}
	
	}

	al_destroy_display(display);
	al_destroy_event_queue(queue);

	return 0;
}