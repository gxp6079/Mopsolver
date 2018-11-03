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
#include <getopt.h>
#include "queue.h"

/*
 * build_maze builds the maze from stdin
 * @param **maze - a 2D array where the maze information will be added , input - input file
 * @return N - the row size of the maze
 */
int build_maze(char ***maze, FILE * input){
    int N = 0;
    int M = 0;
    int c;
    while((c = getc(input)) != EOF){
        if( c!= ' '){
            if(c != '\n'){
                if(M == 0 && N == 0){
                    *(maze) = (char**) malloc(sizeof(char*));
                    (*(maze))[N] = (char *) malloc(sizeof(char) + 1);
                }
                else{
                    if(M == 0){
                        *(maze) = (char **) realloc(*(maze), (N + 1) * sizeof(char *));
                        (*(maze))[N] = (char *) malloc(sizeof(char) + 1);
                    }
                    else{
                        (*(maze))[N] = (char *) realloc((*(maze))[N], ((M + 1) * sizeof(char)) + 1);
                    }
                }
                (*(maze))[N][M] = (char)c;
                M++;
            }else{
                (*(maze))[N][M] = '\0';
                N++;
                M = 0;
            }
        }
    }
    return N;
}

/*
 * build_visited builds the visited array with all initial values = 0;
 * @param row - row size of the array , col - column size of the array ,
 * visited - a 2D array where the information will be added;
 */
void build_visited(int row, int col, int visited[row][col]){
    for (int i = 0; i < row ; ++i) {
        for (int j = 0; j < col ; ++j) {
            visited[i][j] = 0;
        }
    }
}

/*
 * prettyPrints prints the maze
 * @param row - initial row value , col - initial col value , N - max row value , M - max col value ,
 * **maze - a 2D array where the maze information is stored , output - file where the output should be printed
 * path - an array conataining 1 if the node belongs to the path and 0 otherwise ,
 * with_path - 1 if the path is to be printed 0 otherwise
 */
void prettyPrints(char ** maze, int row, int col, FILE * output, int path[row][col], int with_path){
    fprintf(output, "|");
    for(int i = 0 ; i <= 2*col ; i ++){
        fprintf(output, "-");
    }
    fprintf(output, "|\n");
    for(int j = 0; j < row ; j++){
        if(j != 0){
            fprintf(output,"|");
        }
        else{
            fprintf(output," ");
        }
        for(int i = 0 ; i < col ; i++){
            if(maze[j][i] == '0'){
                if(path[j][i] && with_path){
                    fprintf(output, " +");
                }
                else{
                    fprintf(output, " .");
                }
            }
            else{
                fprintf(output, " #");
            }
        }
        if(j != row - 1){
            fprintf(output, " |\n");
        }else{
            fprintf(output, "\n");
        }
    }
    fprintf(output, "|");
    for(int i = 0 ; i <= 2*col ; i ++){
        fprintf(output, "-");
    }
    fprintf(output, "|\n");
}


/*
 * solvable returns weather or not the maze can be solved
 * @param row - initial row value , col - initial col value , N - max row value , M - max col value ,
 * **maze - a 2D array where the maze information is stored, visited - an array containing 0 for unvisited
 * noded and 1 for visited
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
 * countSize prints the size of the smallest solvable path and the path itself
 * @param t - the end tuple , **maze - a 2D array where the maze information is stored ,
 * row - initial row value , col - initial col value , p - 1 if the path is to be printed 0 otherwise ,
 * path_size - 1 if the path size is to be printed 0 otherwise , output - file where the output is to be printed
 */
void countSize(Tuple t, char ** maze, int row, int col, int p, int path_size, FILE * output){
    int size = 0;
    int path[row][col];
    build_visited(row, col, path);
    while(t != NULL){
        path[getVal1(t)][getVal2(t)] = 1;
        size ++;
        Tuple temp = getParent(t);
        free(t);
        t = temp;
    }
    if(path_size){
        fprintf(output, "Solution in %d steps.\n", size);
    }
    if(p){
        prettyPrints(maze, row, col, output, path, 1);
    }
}

/*
 * addToQueue adds a new Tuple to the queue
 * @param parent - the parent of the new tuple , row - row of the new Tuple , col - col of the new Tuple * N - max row , M - max col , visited - an array containing 0 for unvisited noded and 1 for visited ,
 * q - Queue where the new Tuple should be added
 */
void addToQueue(Tuple parent, int row, int col, int N, int M, int visited[N][M], Queue q){
    visited[row][col] = 1;
    Tuple new_tuple = createTuple(row, col );
    addParent(new_tuple, parent);
    enqueue(q, new_tuple);
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
void smallPath(int N, int M, char ** maze, int p, int path, FILE * output){
    int visited[N][M];
    build_visited(N, M, visited);
    Tuple coordinates = createTuple(0, 0);
    Queue q = createQueue();
    enqueue(q, coordinates);
    visited[0][0] = 1;
    while(sizeQueue(q) != 0){
        Tuple current = dequeue(q);
        if(getVal1(current) == (N-1) && getVal2(current) == (M-1)){
            destroyQueue(q);
            countSize(current, maze, N, M, p, path, output);
            return;
        }
        if(getVal2(current) != 0 && !visited[getVal1(current)][getVal2(current) - 1] &&
           maze[getVal1(current)][getVal2(current) - 1] != '1'){
            addToQueue(current, getVal1(current), getVal2(current) - 1, N, M, visited, q);
        }
        if(getVal1(current) != 0 && !visited[getVal1(current) - 1][getVal2(current)] &&
           maze[getVal1(current)- 1][getVal2(current)] != '1'){
            addToQueue(current, getVal1(current)- 1, getVal2(current), N, M, visited, q);
        }
        if(getVal2(current) != (M-1) && !visited[getVal1(current)][getVal2(current) + 1] &&
           maze[getVal1(current)][getVal2(current) + 1] != '1'){
            addToQueue(current, getVal1(current), getVal2(current) + 1, N, M, visited, q);
        }
        if(getVal1(current) != (N-1) && !visited[getVal1(current) + 1][getVal2(current)] &&
           maze[getVal1(current) + 1][getVal2(current)] != '1'){
            addToQueue(current, getVal1(current) + 1, getVal2(current), N, M, visited, q);
        }
    }
}

int main(int argc, char * argv[]) {
    char ** maze = (char **) malloc(sizeof(char*));;
    int opt;
    char * input_name;
    char * output_name;
    FILE * input = stdin;
    FILE * output = stdout;
    int solv = 0;
    int h = 0;
    int p = 0;
    int d = 0;
    int s = 0;
    int row = 0;
    int col = 0;
    int visited[row][col];
    while( (opt = getopt( argc, argv, "hdspi:o:")) != -1){
        switch (opt){
            case 'h':
                h = 1;
                break;
            case 'd':
                d = 1;
                break;
            case 's':
                s = 1;
                break;
            case 'p':
                p = 1;
                break;
            case 'i':
                input_name = optarg;
                input = fopen(input_name, "r");
                break;
            case  'o':
                output_name = optarg;
                output = fopen(output_name, "w");
                break;
        }
    }
    if(h){
        fprintf(output, "USAGE:\n");
        fprintf(output, "mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
        fprintf(output, "\nOptions:\n");
        fprintf(output, "\t-h\tPrint this helpful message to stdout and exit.\n");
        fprintf(output, "\t-d\tPretty print (display) the maze after reading (Default: off)\n");
        fprintf(output, "\t-s\tPrint shortest solution steps.                (Default: off)\n");
        fprintf(output, "\t-p\tPrint an optimal path.                        (Default: off)\n");
        fprintf(output, "\t-i INFILE       Read maze from INFILE.                (Default: stdin)\n");
        fprintf(output, "\t-o OUTFILE      Write all output to OUTFILE.          (Default: stdout)\n");
    }
    if(d || s || p){
        row = build_maze(&maze, input);
        col = strlen(maze[0]);
        int visited[row][col];
        build_visited(row, col, visited);
        solv = solvable(0, 0, row, col, maze, visited);
    }
    if(d){
        prettyPrints(maze, row, col, output, visited, 0);
    }
    if(solv){
        smallPath(row, col, maze, p, s, output);
    }
    else if (p || s){
        fprintf(output, "No solution.\n");
    }
    for(int i = 0 ; i < row ; i++){
        free(maze[i]);
    }
    free(maze);
    return 0;
}

