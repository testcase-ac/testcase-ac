#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Height of the tree
    int k = rnd.next(1, 4);
    // Number of edges in a perfect binary tree of height k
    int E = (1 << (k + 1)) - 2;
    // Hyper-parameter for maximum weight
    vector<int> choices = {5, 10, 20, 1000};
    int maxW = rnd.any(choices);
    // Generate weights with possible high/low clustering
    vector<int> w(E);
    double highProb = 0.3;
    for (int i = 0; i < E; i++) {
        if (maxW == 1000 && rnd.next() < highProb) {
            w[i] = rnd.next(500, 1000);
        } else {
            w[i] = rnd.next(1, maxW);
        }
    }
    // Output
    println(k);
    println(w);
    return 0;
}
