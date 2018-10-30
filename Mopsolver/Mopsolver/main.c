//
//  main.c
//  Mopsolver
//
//  Created by Giovana Puccini on 10/29/18.
//  Copyright © 2018 Giovana Puccini. All rights reserved.
//

//
//file: Mopsolver.c
// @author: Giovana Puccini
// @email: gxp6079@rit.edu
// ________________________________________________________

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

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
                maze[N] = malloc(sizeof(char)+1);
            }else{
                maze[N] = realloc(maze[N], (M+2)*sizeof(char));
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
 * @param N - max row value
 * @param M - max col value
 * @param **maze - a 2D array where the maze information is stored
 * @return 1 if solvable 0 otherwise
 */
int solvable(int row, int col, int N, int M, char ** maze, int visited[N][M]){
    if(row == (N-1) && col == (M-1)){
        return 1;
    }
    visited[row][col] = 1;
    if(maze[row][col] != '1'){
        if((col != 0) && !visited[row][col-1] && solvable(row, col-1, N, M, maze, visited)){
            return 1;
        }
        if((row != (N-1)) && !visited[row+1][col] && solvable(row+1, col, N, M, maze, visited)){
            return 1;
        }
        if((col != M-1) && !visited[row][col+1] && solvable(row, col+1, N, M, maze, visited)){
            return 1;
        }
        if((row != 0) && !visited[row-1][col] && solvable(row-1, col, N, M, maze, visited)){
            return 1;
        }
        return 0;
    }
    return 0;
}

/*
 * smallPath prints the smallest path to solve the maze
 * @param row - initial row value
 * @param col - initial col value
 * @param N - max row value
 * @param M - max col value
 * @param **maze - a 2D array where the maze information is stored
 * @return 1 if solvable 0 otherwise
 */

int smallPath(int row, int col, int N, int M, char ** maze, int visited[N][M]){
    return 0;
}

/*
 * prettyPrints prints the maze
 * @param **maze - a 2D array where the maze information is stored
 * @return 1 if solvable 0 otherwise
 */
void prettyPrints(char ** maze, int row, int col){
    printf("|");
    for(int i = 0 ; i <= 2*col ; i ++){
        printf("-");
    }
    printf("|\n");
    for(int j = 0; j < row ; j++){
        printf("|");
        for(int i = 0 ; i < col ; i++){
            printf(" %c", maze[j][i]);
        }
        printf(" |\n");
    }
    printf("|");
    for(int i = 0 ; i <= 2*col ; i ++){
        printf("-");
    }
    printf("|\n");
}

int main() {
    char ** maze = (char **) malloc(sizeof(char));;
    int row = build_maze(maze);
    int col = (int) strlen(maze[0]);
    int visited[row][col];
    build_visited(row, col, visited);
    printf("\n");
    prettyPrints(maze, row, col);
    printf("%d", solvable(0, 0, row, col, maze, visited));
    return 0;
}



