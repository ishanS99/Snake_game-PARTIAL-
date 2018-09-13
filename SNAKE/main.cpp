#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;

struct food
{
    int x,y;
    char value;
};
struct snake
{
    int x,y;
    char value;
    snake *next;
    //snake *last;
};
struct poision
{
    int x,y;
    char value;
};

food f;
poision p;
snake *head = NULL;
//snake *last = NULL;
char area[30][80];

void create_area()//just creating the initial area for game
{
    int i,j;
    for(i=1;i<29;i++)
    {
        for(j=1;j<79;j++)
            area[i][j]=' ';
    }
    for(i=1;i<29;i++)
    {
        area[i][0]='|';
        area[i][79]='|';
    }
    for(i=1;i<79;i++)
    {
        area[0][i]='_';
        area[29][i]='-';
    }
}

void create_food(int max_x , int max_y , char val)//creating food for the game
{
    f.value = val;
    f.x = (rand() % (max_x - 1 + 1)) + 1;;
    f.y = (rand() % (max_y - 1 + 1)) + 1;
}

void create_poision(int max_x , int max_y , char val)//creating poision for the game
{
    p.value = val;
    p.x = (rand() % (max_x - 1 + 1)) + 1;;
    p.y = (rand() % (max_y - 1 + 1)) + 1;
}

snake* create_node(int p, int q,char val)//create a node for snake body
{
    snake *ptr = new snake;
    ptr->value = val;
    ptr->x = p;
    ptr->y = q;
    ptr->next = NULL;
}

void create_snake(int p, int q, char val)//adding node to the snake
{
    snake *temp, *t;
    temp = create_node(p,q,val);
    if(head==NULL)
        head = temp;
    else
    {
        t=head;
        while(t->next != NULL)
            t=t->next;
        t->next=temp;
        temp->next=NULL;
    }
}

void print_area()//just prints the 2D matrix
{
    int i,j;
    for(i=0;i<30;i++)
    {
        for(j=0;j<80;j++)
        {
            printf("%c",area[i][j]);
        }
        printf("\n");
    }
}

void build_init_snake(int l)//using length for initial snake and start
{
    int p=20,q=20;
    create_snake(p,q,'H');
    l=l-2;
    q++;
    while(l--)
        create_snake(p,q++,'X');
    create_snake(p,q,'T');
}

void put_snake_to_area()//copying data of linked list to the 2D matrix
{
    snake * t;
    t=head;
    while(t!=NULL)
    {
        area[t->x][t->y] = t->value;
        t=t->next;
    }
}

void put_food_to_area()//copy data of food in 2D matrix
{
    area[f.x][f.y] = f.value;
}

void put_poision_to_area()//copy data of poision in 2D matrix
{
    area[p.x][p.y] = p.value;
}

void move_snake(char d)//to move snake in desired direction
{
    /*snake *t , *temp;
    t=head;
    temp= head;
    while(t->next->next!=NULL)
        t=t->next;
    snake * last;
    last = t->next;
    t->value = 'T';
    t->next = NULL;
    last->next = temp;
    head = last;
    head->value = 'H';
    head->next->value = 'X';*/
    snake *t , *temp;
    t=head;
    int j,h;
    j=t->x;
    h=t->y;
    while(t->next!=NULL)
    {
        temp=t;
        t=t->next;
    }
    temp->next=NULL;
    t->next=head;
    head=t;
    t=head;
    t->x=j;
    t->y=h;
    t->value='H';
    t=t->next;
    t->value='X';
    temp->value='T';
    switch (d)
    {
    case 'a':
        (head->y)--;
        if(head->y <1)
            head->y += 78;
        break;
    case 's':
        (head->x)++;
        if(head->x >28)
            head->x -= 28;
        break;
    case 'w':
        (head->x)--;
        if(head->x <1)
            head->x += 28;
        break;
    case 'd':
        (head->y)++;
        if(head->y >78)
            head->y -= 78;
        break;
    }
}

int when_eats_food()//if snake consumes the food increase length by 1
{
    if((head->x == f.x) && (head->y == f.y))
    {
        snake *t;
        t=head;
        while(t->next!=NULL)
            t=t->next;
        snake *n;
        n = create_node(t->x , t->y , 'T');
        t->next = n;
        n->next = NULL;
        t->value = 'X';
        return 1;
    }
    return 0;
}

int when_eats_poision()//if snake consumes the poision decrease length by 1
{
    if((head->x == p.x) && (head->y == p.y))
    {
        snake *t;
        t=head;
        while(t->next->next!=NULL)
            t=t->next;
        snake *temp = t->next;
        t->next=NULL;
        t->value = 'T';
        delete temp;
        return 1;
    }
    return 0;
}

void when_touches_itself()//if snake touches its own body
{
    snake* t;
    t=head->next;
    while(t->next!=NULL){
        if(head->x == t->x  && head->y == t->y)
        {
            t->value = 'T';
            t->next = NULL;
            break;
        }
        t=t->next;
    }

}
int main()
{
    //making initial stage of game
    create_area();
    create_food(28,78,'O');
    put_food_to_area();
    create_poision(28,78,'!');
    put_poision_to_area();
    build_init_snake(5);
    put_snake_to_area();
    print_area();

    //now the player starts playing
    char ch='a';
    //cin>>ch;
    //if(kbhit())
      //  ch=getch();
    while(ch!='q')
    {
        create_area();//cleans the board
        move_snake(ch);
        if(when_eats_food())
        {
            create_food(28,78,'O');
        }
        if(when_eats_poision())
            create_poision(28,78,'!');
        when_touches_itself();
        put_snake_to_area();
        put_food_to_area();
        put_poision_to_area();
        system("cls");
        print_area();
        //cin>>ch;
        if(kbhit())
            ch=getch();
    }
    system("cls");
    cout<<"DO YOU WANT TO SAVE THE GAME (Y/N): ";
    cin>>ch;
    return 0;
}
