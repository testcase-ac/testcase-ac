#include "testlib.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Choose grid dimensions; note that M is the number of columns (width) and N is the number of rows (height)
    // We use a small upper bound (10) so that the grid is easy to inspect manually.
    int M = rnd.next(1, 10); 
    int N = rnd.next(1, 10); 

    // Hyperparameter: probability that a cell is a wall (value '1')
    // We choose it uniformly from [0.0, 1.0) so that we get a variety of maze densities.
    double wallProb = rnd.next(0.0, 1.0);

    // Print the grid dimensions: first M (width), then N (height)
    println(M, N);
    
    // Generate each row of the maze.
    // The maze is represented as N strings of length M.
    // Ensure that the start cell (top-left) and the goal cell (bottom-right) are always open ('0').
    for (int i = 0; i < N; i++) {
        string row = "";
        for (int j = 0; j < M; j++) {
            // Force the starting cell (0,0) and ending cell (N-1, M-1) to be open.
            if ((i == 0 && j == 0) || (i == N - 1 && j == M - 1)) {
                row.push_back('0');
            } else {
                // With probability wallProb, the cell is a wall ('1'); otherwise, it's open ('0')
                row.push_back(rnd.next(0.0, 1.0) < wallProb ? '1' : '0');
            }
        }
        println(row);
    }
    
    return 0;
}
