#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N
    int N = rnd.next(2, 10);

    // Generate stone values with varied distribution
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < 0.5) {
            // bias towards larger values
            v[i] = rnd.wnext(10, 2);
        } else {
            // bias towards smaller values
            v[i] = rnd.wnext(10, -2);
        }
        if (v[i] < 1) v[i] = 1;
    }

    // Choose distinct start and end
    int a = rnd.next(1, N);
    int b = rnd.next(1, N);
    while (b == a) {
        b = rnd.next(1, N);
    }

    // Output format
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%d%c", v[i], i + 1 < N ? ' ' : '\n');
    }
    println(a, b);

    return 0;
}
