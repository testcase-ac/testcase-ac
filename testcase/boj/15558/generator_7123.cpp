#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter t for N size skew
    int tN = rnd.next(-2, 2);
    int maxN = 30;
    int N = rnd.wnext(maxN, tN) + 1; // 1..30, weighted
    // Hyper-parameter tk for k skew
    int tk = rnd.next(-1, 1);
    int k = rnd.wnext(N, tk) + 1;    // 1..N, weighted

    // Generate safe probabilities
    double safeProbL = rnd.next();
    double safeProbR = rnd.next();

    string left(N, '0'), right(N, '0');
    for (int i = 0; i < N; i++) {
        if (rnd.next() < safeProbL) left[i] = '1';
        if (rnd.next() < safeProbR) right[i] = '1';
    }
    // Ensure starting cell is safe
    left[0] = '1';

    // Output
    println(N, k);
    println(left);
    println(right);
    return 0;
}
