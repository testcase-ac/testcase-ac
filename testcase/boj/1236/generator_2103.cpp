#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    // Initialize testlib and set the random seed.
    registerGen(argc, argv, 1);

    // Define bounds for the castle dimensions.
    // We choose small dimensions (between 1 and 10) so the testcase is easy to verify.
    int minN = 1, maxN = 10;
    int minM = 1, maxM = 10;
    int N = rnd.next(minN, maxN);
    int M = rnd.next(minM, maxM);
    
    // Create a grid (castle) with N rows and M columns.
    vector<string> castle(N, string(M, '.'));
    
    // Randomly choose one of four modes for filling the grid.
    // Mode 0: All cells are empty ('.').
    // Mode 1: All cells have a guard ('X').
    // Mode 2: Random fill with a moderate guard density.
    // Mode 3: Random fill with a sparse guard density.
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // All empty: Do nothing (castle already filled with '.')
    } else if (mode == 1) {
        // All guard: Fill every cell with 'X'.
        for (int i = 0; i < N; i++) {
            castle[i] = string(M, 'X');
        }
    } else if (mode == 2) {
        // Moderate density: Choose a guard probability between 30% and 70%.
        int p = rnd.next(30, 70);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // rnd.next(1, 100) <= p gives probability p%
                castle[i][j] = (rnd.next(1, 100) <= p ? 'X' : '.');
            }
        }
    } else { // mode == 3
        // Sparse density: Choose a guard probability between 10% and 40%.
        int p = rnd.next(10, 40);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                castle[i][j] = (rnd.next(1, 100) <= p ? 'X' : '.');
            }
        }
    }
    
    // Output the dimensions followed by the grid rows.
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(castle[i]);
    }
    
    return 0;
}
