#include <stdio.h>
#include <stdlib.h>

int build_maze(char **maze){
    int N = 0;
    int M = 0;
    int c;
    while((c = getchar()) != EOF){
        if(c != '\n'){
            if(M == 0){
                maze[N] = malloc(sizeof(char));
            }else{
                maze[N] = realloc(maze[N], sizeof(char));
            }
            maze[N][M] = (char)c;
            M++;
        }else{
            N++;
            M = 0;
        }
    }
    return N;
}

int solvable(int row, int col, int ** maze, int ** visited){
    int N = sizeof(maze) / sizeof(maze[0]);
    int M = sizeof(maze[0])/N;
    if(row == (N-1) && col == (M-1)){
        return 1;
    }
    visited[row][col] = 1;
    if((col != 0) && visited[row][col-1] != 1){
        if(maze[row][col-1] != 1){
            if(solvable(row, col-1, maze, visited)){
                return 1;
            }
        }
    }
    if((col != (M-1)) && visited[row][col+1] != 1){
        if(maze[row][col+1] != 1){
            if(solvable(row, col+1, maze, visited)){
                return 1;
            }
        }
    }
    if((row != 0) && visited[row-1][col] != 1){
        if(maze[row-1][col] != 1){
            if(solvable(row-1, col, maze, visited)){
                return 1;
            }
        }
    }
    if((row != (N-1)) && visited[row+1][col] != 1){
        if(maze[row+1][col] != 1){
            if(solvable(row+1, col, maze, visited)){
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char ** maze = (char **) malloc(sizeof(char));
    int row = build_maze(maze);
    int col = sizeof(maze)/row;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0; j < col ; j++){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}