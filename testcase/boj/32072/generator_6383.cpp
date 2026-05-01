#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small-to-medium N
    int N = rnd.next(2, 15);
    vector<int> P(N+1);
    // Hyper-parameter: tree shape
    int shape = rnd.next(0, 3);
    if (shape == 0) {
        // Chain
        for (int i = 2; i <= N; i++) P[i] = i-1;
    } else if (shape == 1) {
        // Star
        for (int i = 2; i <= N; i++) P[i] = 1;
    } else if (shape == 2) {
        // Balanced-like
        for (int i = 2; i <= N; i++) P[i] = i/2;
    } else {
        // Random tree
        for (int i = 2; i <= N; i++) P[i] = rnd.next(1, i-1);
    }
    // Compute depths
    vector<int> depth(N+1);
    depth[1] = 0;
    for (int i = 2; i <= N; i++) {
        depth[i] = depth[P[i]] + 1;
    }
    // Hyper-parameter: weight assignment
    int wtype = rnd.next(0, 3);
    vector<int> A(N+1);
    if (wtype == 0) {
        // Random permutation
        vector<int> vals(N);
        for (int i = 0; i < N; i++) vals[i] = i+1;
        shuffle(vals.begin(), vals.end());
        for (int i = 1; i <= N; i++) A[i] = vals[i-1];
    } else if (wtype == 1) {
        // Ascending by index
        for (int i = 1; i <= N; i++) A[i] = i;
    } else if (wtype == 2) {
        // Descending by index
        for (int i = 1; i <= N; i++) A[i] = N - i + 1;
    } else {
        // Increasing along depth
        vector<int> nodes(N);
        for (int i = 0; i < N; i++) nodes[i] = i+1;
        shuffle(nodes.begin(), nodes.end());
        stable_sort(nodes.begin(), nodes.end(), [&](int a, int b){
            return depth[a] < depth[b];
        });
        for (int i = 0; i < N; i++) {
            A[nodes[i]] = i+1;
        }
    }
    // Output
    printf("%d\n", N);
    for (int i = 2; i <= N; i++) {
        printf("%d%c", P[i], (i==N? '\n':' '));
    }
    // Print weights
    vector<int> Aout(N);
    for (int i = 0; i < N; i++) Aout[i] = A[i+1];
    println(Aout);
    return 0;
}
