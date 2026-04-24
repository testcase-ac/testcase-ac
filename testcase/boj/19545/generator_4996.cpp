#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of upper and lower cows
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Ensure enough distinct x-coordinates
    int mind = max(N, M);
    int t = rnd.any(vector<int>{-2, -1, 1, 2});
    int dx = rnd.wnext(20, t);       // biased in [0, 19]
    int maxX = mind + dx;            // so maxX >= mind

    // Prepare a pool of distinct x-coordinates [0..maxX]
    vector<int> xs(maxX + 1);
    iota(xs.begin(), xs.end(), 0);

    // Pick N distinct for upper, M distinct for lower
    shuffle(xs.begin(), xs.end());
    vector<int> U(xs.begin(), xs.begin() + N);
    shuffle(xs.begin(), xs.end());
    vector<int> D(xs.begin(), xs.begin() + M);

    sort(U.begin(), U.end());
    sort(D.begin(), D.end());

    // Road width L with some diversity
    int L;
    if (rnd.next() < 0.5)
        L = rnd.next(1, 5);
    else
        L = rnd.next(5, 20);

    // Output
    println(N, M, L);
    println(U);
    println(D);

    return 0;
}
