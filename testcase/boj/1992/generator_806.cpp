#include "testlib.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate N as a power of 2 in the range [2, 16].
    int powersOfTwo[] = {2, 4, 8, 16, 32};
    int N = powersOfTwo[rnd.next(0, 4)];
    println(N);

    double density1 = rnd.next();
    double density2 = rnd.next();
    double density3 = rnd.next();
    double density4 = rnd.next();
    // Generate the N x N matrix with the given density.
    vector<string> matrix(N, string(N, '0'));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double densityUsed;
            if(i < N/2 && j < N/2) {
                densityUsed = density1;
            } else if(i < N/2 && j >= N/2) {
                densityUsed = density2;
            } else if(i >= N/2 && j < N/2) {
                densityUsed = density3;
            } else {
                densityUsed = density4;
            }
            // Generate a 1 with a probability equal to the density.
            matrix[i][j] = (rnd.next() < densityUsed) ? '1' : '0';
        }
        println(matrix[i]);
    }

    return 0;
}
