#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(2, 5); // Generate small N for readability
    vector<int> perm = rnd.perm(N, 1); // Generates a permutation of 1..N
    
    vector<vector<int>> W(N, vector<int>(N, 0));
    int MX = 9;
    if(rnd.next(0, 1)) {
        MX = 100;
    }
    
    // Fill the cycle edges with non-zero values
    for (int i = 0; i < N; i++) {
        int u = perm[i];
        int v = perm[(i + 1) % N];
        W[u - 1][v - 1] = rnd.next(1, MX);
    }
    
    // Fill other edges with 0 or non-zero values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && W[i][j] == 0) {
                if (rnd.next(0, 1)) {
                    W[i][j] = rnd.next(1, MX);
                }
            }
        }
    }
    
    // Print the generated test case
    println(N);
    for (int i = 0; i < N; i++) {
        vector<int> row;
        for (int j = 0; j < N; j++) {
            row.push_back(W[i][j]);
        }
        println(row);
    }
    
    return 0;
}
