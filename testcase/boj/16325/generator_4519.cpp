#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter: size of tree
    int N = rnd.next(2, 10);
    // Hyperparameter: choice of k
    int kType = rnd.next(0, 2);
    int K;
    if (kType == 0) {
        K = 2;            // minimum colors
    } else if (kType == 1) {
        K = N;            // maximum colors
    } else {
        K = rnd.next(2, N); // random in [2, N]
    }
    // Hyperparameter: shape of tree
    int treeType = rnd.next(0, 2);
    vector<int> parent(N);
    parent[0] = -1; // root has no parent
    if (treeType == 0) {
        // chain
        for (int i = 1; i < N; i++)
            parent[i] = i - 1;
    } else if (treeType == 1) {
        // star
        for (int i = 1; i < N; i++)
            parent[i] = 0;
    } else {
        // random with skew parameter t
        int t = rnd.next(-3, 3);
        for (int i = 1; i < N; i++) {
            // choose parent in [0, i-1] with skew
            parent[i] = rnd.wnext(i, t);
        }
    }
    // Output
    println(N, K);
    for (int i = 1; i < N; i++) {
        println(parent[i]);
    }
    return 0;
}
