#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of files
    int N = rnd.next(1, 10);

    // Cluster size hyper-parameter
    int typeC = rnd.next(0, 2);
    int C;
    if (typeC == 0) {
        C = 1;
    } else if (typeC == 1) {
        int k = rnd.next(0, 20);
        C = 1 << k; // power of two
    } else {
        C = rnd.next(1, 1048576);
    }

    // Probability of zero-size files
    double zeroProb = rnd.next(0.0, 0.5);

    // Distribution type for non-zero files
    string fileDist = rnd.next("small|mixed|large");

    // Generate file sizes
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < zeroProb) {
            a[i] = 0;
        } else if (fileDist == "small") {
            // around the cluster size
            a[i] = rnd.next(1, C * 2);
        } else if (fileDist == "mixed") {
            // full range
            a[i] = rnd.next(1, 1000000000);
        } else {
            // tend to be large
            a[i] = rnd.next(C, 1000000000);
        }
    }

    // Output
    println(N);
    println(a);
    println(C);

    return 0;
}
