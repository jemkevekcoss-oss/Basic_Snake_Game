#include <iostream>
#include <ctime>
#include "kmin_console.h"
//#include "snake_constructor.h"
using namespace std;

#define KEY_UP		1072
#define KEY_DOWN	1080
#define KEY_LEFT	1075
#define KEY_RIGHT	1077
#define KEY_NONE	-1

#define TOP_WALL 1
#define BOTTOM_WALL 25
#define LEFT_WALL 0
#define RIGHT_WALL 79

#define DOWN 1
#define UP 2
#define RIGHT 3
#define LEFT 4

#define MAX 10000

struct ToaDo {
    int x;
    int y;
    friend bool operator == (ToaDo& a, ToaDo& b) {
        return a.x == b.x && a.y == b.y;
    }
};

int SoDot = 3;
ToaDo snake[MAX];
void init_snake() {
    snake[0].x = 3; snake[0].y = 2;
    snake[1].x = 2; snake[1].y = 2;
    snake[2].x = 1; snake[2].y = 2;

}

void display_snake() {
    //Duyệt từng đốt:
    for (int i = 0; i < SoDot; i++) {
        gotoXY(snake[i].x, snake[i].y);
        if (i == 0) { //Đầu rắn
            setTextColor(14);
            cout << "O";
        }
        else {
            setTextColor(10);
            cout << (char)254;
        }
    }
}

void key_board_hit(int &direction,int pre_move) { 
    
    int key = inputKey();
    switch (key) {
    case KEY_UP:
        if(pre_move != DOWN) direction = UP;
        break;
    case KEY_DOWN:
        if (pre_move != UP) direction = DOWN;
        break;
    case KEY_LEFT:
        if (pre_move != RIGHT) direction = LEFT;
        break;
    case KEY_RIGHT:
        if (pre_move != LEFT) direction = RIGHT;
        break;
    }
}

void move(int direction) {
    //Xử lý phần thân:
    for (int i = SoDot - 1; i >= 1; i--) {
        if (i == SoDot - 1) {
            gotoXY(snake[i].x,snake[i].y);
            cout << ' ';
        }
        snake[i] = snake[i - 1];
    }
    /*if (SoDot == 1) {
        gotoXY(snake[0].x, snake[0].y); cout << " ";
    }*/
    switch (direction) {
    case UP:
            snake[0].y--; break;
    case DOWN:
            snake[0].y++; break;
    case LEFT:
            snake[0].x--; break;
    case RIGHT:
            snake[0].x++; break;
    }
}

bool touch_body() {
    //Linear search:
    for (int i = 1; i < SoDot; i++) {
        if (snake[0] == snake[i]) return true;
    }
    return false;
}

int score = 0;
void display_score() {
    gotoXY(RIGHT_WALL + 3, TOP_WALL); setTextColor(9);
    cout << "************************";
    gotoXY(RIGHT_WALL + 3, TOP_WALL + 1); setTextColor(9);
    cout << "* YOUR SCORE: " << score << "        *";
    gotoXY(RIGHT_WALL + 3, TOP_WALL + 2); setTextColor(9);
    cout << "************************";
    setTextColor(15); // Trả lại màu trắng!
}

bool Game_over() {
    if (touch_body()) return true;

    return (snake[0].y == TOP_WALL || snake[0].y == BOTTOM_WALL
        || snake[0].x == LEFT_WALL || snake[0].x == RIGHT_WALL);
}
void dealing_GameOver() {
    if (Game_over()) {
        clrscr();
        gotoXY(53, 13); 
        setTextColor(12);
        cout << "GAME OVER";
        gotoXY(53, 14);
        cout << "YOUR SCORE: " << score;
        char tmp = _getch();
    }
}

void set_walls() {
    for (int i = LEFT_WALL; i <= RIGHT_WALL; i++) {
        gotoXY(i, TOP_WALL);
        cout << (char)220;
    }
    for (int i = TOP_WALL+1; i <= BOTTOM_WALL; i++) {
        gotoXY(LEFT_WALL, i);
        cout << (char)221;
    }
    for (int i = LEFT_WALL; i <= RIGHT_WALL; i++) {
        gotoXY(i, BOTTOM_WALL);
        cout << (char)223;
    }
    for (int i = TOP_WALL+1; i < BOTTOM_WALL; i++) {
        gotoXY(RIGHT_WALL,i );
        cout << (char)222;
    }

}
int foodX, foodY;
void spawn_food() {
    srand(time(NULL));
    foodX = LEFT_WALL + 1 + rand() % (RIGHT_WALL - 1 - (LEFT_WALL + 1) + 1);
    foodY = TOP_WALL + 1 + rand() % (BOTTOM_WALL - 1 - (TOP_WALL + 1) + 1);
    gotoXY(foodX, foodY);
    setTextColor(12);
    cout << "$";
}

void lengthen() {
    snake[SoDot] = snake[SoDot - 1];
    ++SoDot;
}

void init_game() {
    display_score();
    //Khởi tạo map:
    set_walls();
    //Khoi tao ran:
    init_snake();
    //Sinh ra FOOD:
    spawn_food();
}

int main() {
 
        init_game();

        display_snake();
        //Game Loop:
        int x = 0, y = 0;
        int direc = RIGHT;
        
        while (true) {

            move(direc);
            int pre_move = direc;
            key_board_hit(direc, pre_move);
            
            noCursorType();
            display_snake();
            if (snake[0].x == foodX && snake[0].y == foodY) {
                ++score;
                display_score(); //Đỡ phải hiện thị liên tục
                spawn_food();
                lengthen();
            }
            //Lưu ý: pre_move nhận các gtri:UP DOWN LEFT RIGHT chứ ko phải a s d w
            

            if (Game_over()) {
                break;
            }

            Sleep(125);

        }
        Sleep(1000);
        dealing_GameOver();

}













