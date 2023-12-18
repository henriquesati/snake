#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#define body 7
#define inc 10
#define azul al_map_rgb_f(0, 0, 1)
#define branco al_map_rgb_f(255,255,255)
#define dbb al_map_rgb_f(0,1,0)

const float FPS = 30;
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

	bool running = true;
	al_init();

	ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
 	ALLEGRO_TIMER* timer = al_create_timer(1.0/FPS);
	display = al_create_display(480, 600);
	al_clear_to_color(al_map_rgb(255, 255, 255)); //cor de fundo
	  al_flip_display();
	//addons
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
    ALLEGRO_BITMAP *snake = al_load_bitmap("snake.bmp");

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
	//
	int x=220;
	int y = 300;
    node* head = init_node(x,y);
	int state =83;
	void orch2(int x, int y, ALLEGRO_COLOR cor){
		
		al_draw_rectangle(x, y, x+body, y+body, cor, 5);
		al_flip_display();
	}
	void orch1(int x, int y, ALLEGRO_COLOR cor){
		
		al_draw_rectangle(x, y, x+body, y+body, cor, 5);
		al_flip_display();
	}
    while (running) {

        al_wait_for_event(queue, &event);
		// if(event.type == ALLEGRO_EVENT_TIMER) // dispara com o evento de timer, nao necessario nessa versao

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			// if (event.keyboard.keycode>81 && event.keyboard.keycode <86)
			switch (event.keyboard.keycode){
				case 84:
				y-=inc;
                head->y = y;
				orch1(head->x, head->y, azul);
                printf("headx %i -->heady %i", head->x, head->y);
				orch1(head->x,y+inc, branco);
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
				orch1(x+inc,y, branco);
				puts("left");
				break;
			case 83:
				x+=inc;
				// orch2(x, y, azul);
				// orch2(x-inc, y, branco);
                al_draw_bitmap(snake, x,y, 0);
                al_draw_bitmap(snake, x,y+200, 0);
                al_flip_display();
                al_clear_to_color(al_map_rgb(255, 255, 255));
				puts("right");
				break;
			
			default:
				printf("algo deu errado");
				break;
			}

        }

        // al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);

    return 0;
}