#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
extern bool game_over = false;
int candy_coord_i = 0;
int gen() {
    return (rand() % 10) + 1;
}

int gen_cord(){
    return (rand() %500) +1;
}
typedef struct{
    int x;
    int y;
} coord;
extern coord candy_array[50];


void add_candy(){
    int x = gen_cord();
    int y = x;
    candy_array[candy_coord_i].x = x;
    candy_array[candy_coord_i].y = y;
    candy_coord_i++;
}

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


typedef struct candy_node{
    int x;
    int y;
    struct candy_node *next;
}candy_node;


void rm_candy(int index){
    candy_array[index].x = 999;
    candy_array[index].y = 999;

}