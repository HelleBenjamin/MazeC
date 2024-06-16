#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze_levels.h"

#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define DOOR 'D'

#define clear() printf("\033[H\033[J") //clear screen

#define DEFAULT_X 8 //player start position
#define DEFAULT_Y 1

int currentX = 8;
int currentY = 1;
char** currentMaze = NULL;
int currentMazeNum = 0;

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
            //up
            if (maze[currentY - 1][currentX] != WALL) {
                maze[currentY][currentX] = PATH;
                currentY--;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 'a':
            //left
            if (maze[currentY][currentX - 1] != WALL) {
                maze[currentY][currentX] = PATH;
                currentX--;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 's':
            //down
            if (maze[currentY + 1][currentX] != WALL) {
                maze[currentY][currentX] = PATH;
                currentY++;
                maze[currentY][currentX] = PLAYER;
            }
            break;
        case 'd':
            //right
            if (maze[currentY][currentX + 1] != WALL) {
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
        if (currentMaze[currentY + 1][currentX] == DOOR || currentMaze[currentY - 1][currentX] == DOOR || currentMaze[currentY][currentX + 1] == DOOR || currentMaze[currentY][currentX - 1] == DOOR) {
            load_new_level();
        }
        clear();
        printf("Current level: %d\n", currentMazeNum,"\n");
        renderMaze(currentMaze);
        movePlayer(currentMaze);
    }
}

void start_menu() {
    printf("MazeC 0.1\n");
    printf("1. Start\n2. Keyboard controls\n3. Exit\n");
    while (true) {
        char input = getc(stdin);
        if (input == '1') {
            MazeSetup(currentMazeNum, true);
            game_loop();
        } else if (input == '2') {
            printf("Keyboard controls: ");
            printf("w = up, a = left, s = down, d = right\n");
        } else if (input == '3') {
            break;
        }
    }
}

int main() {
    currentMazeNum = 0;
    start_menu();
    MazeSetup(currentMazeNum, false); //free the current maze
    return 0;
}
