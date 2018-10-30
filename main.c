//
//file: Mopsolver.c
// @author: Giovana Puccini
// @email: gxp6079@rit.edu
// ________________________________________________________

#include <stdio.h>
#include <stdlib.h>

/*
 * build_maze builds the maze from stdin
 * @param **maze - a 2D array where the maze information will be added;
 * @return N - the row size of the maze
 */
int build_maze(char **maze){
    int N = 0;
    int M = 0;
    int c;
    while((c = getchar()) != EOF){
        if(c != '\n'){
            if(M == 0){
                maze[N] = malloc(sizeof(char) + 1);
            }else{
                maze[N] = realloc(maze[N], (M+1)*sizeof(char));
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

/*
 * build_visited builds the visited array with all initial values = 0;
 * @param row - row size of the array
 * @param col - column size of the array
 * @param ** visited - a 2D array where the information will be added;
 */
void build_visited(int row, int col, int visited[row][col]){
    for (int i = 0; i < row ; ++i) {
        for (int j = 0; j < col ; ++j) {
            visited[i][j] = 0;
        }
    }
}

/*
 * solvable returns weather or not the maze can be solved
 * @param row - initial row value
 * @param col - initial col value
 * @param **maze - a 2D array where the maze information is stored
 * @return 1 if solvable 0 otherwise
 */
int solvable(int row, int col, char maze[row][col], int visited[row][col]){
    int N = sizeof(maze) / sizeof(maze[0]);
    int M = sizeof(maze[0])/N;
    if(row == (N-1) && col == (M-1)){
        return 1;
    }
    visited[row][col] = 1;
    if((col != 0) && visited[row][col-1] != '1'){
        if(maze[row][col-1] != 1){
            if(solvable(row, col-1, maze, visited)){
                return 1;
            }
        }
    }
    if((col != (M-1)) && visited[row][col+1] != '1'){
        if(maze[row][col+1] != 1){
            if(solvable(row, col+1, maze, visited)){
                return 1;
            }
        }
    }
    if((row != 0) && visited[row-1][col] != '1'){
        if(maze[row-1][col] != 1){
            if(solvable(row-1, col, maze, visited)){
                return 1;
            }
        }
    }
    if((row != (N-1)) && visited[row+1][col] != '1'){
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
    int visited[row][col];
    build_visited(row, col, visited);
    for(int i = 0 ; i < row ; i++){
        for(int j = 0; j < col ; j++){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    printf("%d", solvable(0, 0, maze, visited));
    return 0;
}
