#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Six types of test cases for diversity
    // 0: N=1 (edge)
    // 1: small random [2,10]
    // 2: tricky fixed values
    // 3: power of two
    // 4: power of three
    // 5: large random [1e5,1e6]
    int t = rnd.next(0, 5);
    int N;
    if (t == 0) {
        N = 1;
    } else if (t == 1) {
        N = rnd.next(2, 10);
    } else if (t == 2) {
        vector<int> v = {10, 18, 27, 28, 100};
        N = rnd.any(v);
    } else if (t == 3) {
        int k = rnd.next(1, 19);
        N = 1 << k;
    } else if (t == 4) {
        int k = rnd.next(1, 12);
        N = 1;
        for (int i = 0; i < k; i++) N *= 3;
    } else {
        N = rnd.next(100000, 1000000);
    }

    // Output single integer N
    println(N);
    return 0;
}
