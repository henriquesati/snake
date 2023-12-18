#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "funcoes.h"
#define body 7
#define inc 10
const float FPS = 10;
#define show print_list(head)

typedef struct node{
    int x;
    int y;
    struct node *next;
} node;



node* init_node(int x, int y){
    node *tmp = malloc(sizeof(node));
    tmp->x = x;
    tmp->y = y;
    tmp->next = NULL;
    return tmp;
}

void add(node* head, int x, int y){
    node *tmp = init_node(x,y);
    node *cur = head;
        while (cur->next != NULL){
            cur = cur->next;
        }
    cur->next = tmp;
}

void att_coords(node* body_snake, int new_x, int new_y){
    node *cur = body_snake;
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
    node* head = init_node(x,y);
    add(head, x-10, y);
    add(head, x-20, y);
	int state =83;
    void draw(node* head){
        node *cur = head;
        while (cur!= NULL){
            al_draw_bitmap(snake, cur->x, cur->y, 0);
            printf("curx: %i, cury:%i\n", cur->x, cur->y);
            cur = cur->next;
        }
        show;
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
    void gen_candy(){
        al_draw_bitmap(candy, gen_cord(), gen_cord(), 0);
    }
    while (running) {

        al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER){
            int random_number = gen();
                if (gen() >3 && gen()<7)
                    gen_candy();
            switch (state){
				case 84:
				y-=inc;
                att_coords(head, x,y);
                draw(head);
                al_flip_display();
                al_clear_to_color(al_map_rgb(255, 255, 255));
				break;
			case 85:
				y+=inc;
                att_coords(head, x, y);
                draw(head);
                al_flip_display();
                al_clear_to_color(al_map_rgb(255, 255, 255));
				puts("down");
				break;
			case 82:
				x-=inc;
                att_coords(head,x,y);
                draw(head);
                al_flip_display();
                al_clear_to_color(al_map_rgb(255, 255, 255));              
				puts("left");
				break;
			case 83:
				x+=inc;
                att_coords(head,x,y);
                draw(head);
                al_flip_display();
                al_clear_to_color(al_map_rgb(255, 255, 255));
				puts("right");
			
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
                puts("JJDHAKSJDGHKASYGDADYSG");
        }
	
    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);

    return 0;
}