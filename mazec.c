#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 10
#define HEIGHT 10

#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define DOOR 'D'

#define DEFAULT_X 8 //player start position
#define DEFAULT_Y 1

int currentX = 8;
int currentY = 1;
char** currentMaze = NULL;
int currentMazeNum = 0;

/* MazeC - A simple maze game in C

The game's goal is to be least resource intensive and have good performance.

*/


/*char maze0[HEIGHT][WIDTH] = {
    "##########",
    "#        #",
    "#  #     #",
    "#  ## ## #",
    "#  #     #",
    "#  # ##  #",
    "#  #  #  #",
    "#     ## #",
    "#       D#",
    "##########"
};

char maze1[HEIGHT][WIDTH]= {
    "##########",
    "#        #",
    "#  #     #",
    "#  ## ## #",
    "#  #     #",
    "#  # ##  #",
    "#  #  #  #",
    "#     ## #",
    "#       D#",
    "##########"
};*/

char* maze0[HEIGHT] = {
    "##########",
    "#        #",
    "#  #     #",
    "#  ## ## #",
    "#  #     #",
    "#  # ##  #",
    "#  #  #  #",
    "#     ## #",
    "#       D#",
    "##########"
};

char* maze1[HEIGHT] = {
    "##########",
    "#  #     #",
    "#  #     #",
    "#  ## ## #",
    "#  #     #",
    "#  # ##  #",
    "#  #  #  #",
    "#     ## #",
    "#       D#",
    "##########"
};


void MazeSetup(int maze, bool operation) {
    switch (maze) {
        case 0:
            if (operation) {
                currentMaze = (char**)malloc(sizeof(char*) * HEIGHT);
                for (int i = 0; i < HEIGHT; i++) {
                    currentMaze[i] = (char*)malloc(sizeof(char) * (WIDTH + 1));
                    for (int j = 0; j < WIDTH; j++) {
                        currentMaze[i][j] = maze0[i][j];
                    }
                    currentMaze[i][WIDTH] = '\0';
                }
                currentMaze[currentY][currentX] = PLAYER;
            } else {
                for (int i = 0; i < HEIGHT; i++) {
                    free(currentMaze[i]);
                }
                free(currentMaze);
                currentMaze = NULL;
            }
            break;
        case 1:
            if (operation) {
                currentMaze = (char**)malloc(sizeof(char*) * HEIGHT);
                for (int i = 0; i < HEIGHT; i++) {
                    currentMaze[i] = (char*)malloc(sizeof(char) * (WIDTH + 1));
                    for (int j = 0; j < WIDTH; j++) {
                        currentMaze[i][j] = maze1[i][j];
                    }
                    currentMaze[i][WIDTH] = '\0';
                }
                currentMaze[currentY][currentX] = PLAYER;
            } else {
                for (int i = 0; i < HEIGHT; i++) {
                    free(currentMaze[i]);
                }
                free(currentMaze);
                currentMaze = NULL;
            }
            break;
    }
}

void generateMaze() {

}

void renderMaze(char** maze) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(maze[i][j]);
        }
        printf("\n");
    }
}


void movePlayer(char** maze) {
    char input = getc(stdin);
    switch (input){
        case 'w':
            //down 
            if (maze[currentY - 1][currentX] == PATH) {
                maze[currentY][currentX] = PATH;
                currentY--;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 'a':
            //left
            if (maze[currentY][currentX - 1] == PATH) {
                maze[currentY][currentX] = PATH;
                currentX--;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 's':
            //up
            if (maze[currentY + 1][currentX] == PATH) {
                maze[currentY][currentX] = PATH;
                currentY++;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 'd':
            //right
            if (maze[currentY][currentX + 1] == PATH) {
                maze[currentY][currentX] = PATH;
                currentX++;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        default:
            break;
    }
}

void load_new_level() {
    currentX, currentY = DEFAULT_X, DEFAULT_Y;
    MazeSetup(currentMazeNum, false);
    currentMazeNum++;
    MazeSetup(currentMazeNum, true);
}


void game_loop() {
    while (1) {
        system("cls");
        printf("Current level: %d\n", currentMazeNum,"\n");
        renderMaze(currentMaze);
        movePlayer(currentMaze);
        if (currentMaze[currentY][currentX] == DOOR) {
            
        }
    }
}

int main() {
    MazeSetup(currentMazeNum, true);
    game_loop();
    MazeSetup(currentMazeNum, false); // Free the maze
    return 0;
}
