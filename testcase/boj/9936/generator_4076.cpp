#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose number of rows
    int N = rnd.next(2, 10);
    // Maximum dominoes that can fit on N x 3 board
    int max_dom = (3 * N) / 2;
    // Choose K with bias towards small or large
    int K;
    if (rnd.next() < 0.5) {
        // bias small
        K = rnd.wnext(max_dom, -1) + 1; 
    } else {
        // bias large
        K = rnd.wnext(max_dom, 1) + 1;
    }
    // Choose range for cell values
    int a = rnd.next(-5, 5);
    int b = rnd.next(-5, 5);
    int L = min(a, b), R = max(a, b);
    // Generate board
    vector< vector<int> > A(N, vector<int>(3));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = rnd.next(L, R);
        }
    }
    // Output
    println(N, K);
    for (int i = 0; i < N; i++) {
        println(A[i]);
    }
    return 0;
}
