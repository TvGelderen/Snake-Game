#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int *bodyX = (int*)malloc(100*sizeof(int));
int *bodyY = (int*)malloc(100*sizeof(int));
enum direction {STOP=0, UP, DOWN, LEFT, RIGHT};
direction dir;

void initialize() {
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void draw() {
    system("cls");

    for (int i=0; i<width+2; i++)
        cout << "#";
    cout << endl;

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (j==0) {
                cout << "#";
            } else if (i==y && j==x) {
                cout << "O";
            } else if (i==foodY && j==foodX) {
                cout << "+";
            } else {
                for (int k=0; k<score; k++) {
                    if (bodyX[k]==j && bodyY[k]==i)
                        cout << "o";
                }
                    cout << " ";
            } 
            
            if (j==width-1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i=0; i<width+2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            gameOver = true;
            break;
        default:
            break;
        }
    }

}

void mechanics() {
    int h1X,h1Y,h2X,h2Y;

    h1X = bodyX[0];
    h1Y = bodyY[0];
    bodyX[0] = x;
    bodyY[0] = y;

    for (int i=1; i <= score; i++) {
        h2X = bodyX[i];
        h2Y = bodyY[i];
        bodyX[i] = h1X;
        bodyY[i] = h1Y;
        h1X = h2X;
        h1Y = h2Y;
    }

    switch (dir) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    if (x > width)
        x = 0;
    if (x < 0) 
        x = width;
    if (y > height)
        y = 0;
    if (y < 0)
        y = height;
    
    for (int i=0; i<score; i++) {
        if (x==bodyX[i] && y==bodyY[i]) 
            gameOver = true;
    }

    if (x==foodX && y==foodY) {
        score++;
        foodX = rand() % width;
        foodY = rand() % height;
    }
}

int main() {
    initialize();

    while(!gameOver) {
        draw();
        input();
        mechanics();
    }

    return 0;
}
