#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of holes/balls
    int n = rnd.next(3, 10);
    vector<long long> c(n);
    // choose a pattern for diversity
    int mode = rnd.next(0, 6);
    switch (mode) {
        case 0: {
            // fully random in [-A, A]
            int A = rnd.next(0, 20);
            for (int i = 0; i < n; i++)
                c[i] = rnd.next(-A, A);
            break;
        }
        case 1: {
            // all non-negative
            for (int i = 0; i < n; i++)
                c[i] = rnd.next(0, 20);
            break;
        }
        case 2: {
            // all non-positive
            for (int i = 0; i < n; i++)
                c[i] = rnd.next(-20, 0);
            break;
        }
        case 3: {
            // sorted ascending random
            for (int i = 0; i < n; i++)
                c[i] = rnd.next(-10, 10);
            sort(c.begin(), c.end());
            break;
        }
        case 4: {
            // sorted descending random
            for (int i = 0; i < n; i++)
                c[i] = rnd.next(-10, 10);
            sort(c.rbegin(), c.rend());
            break;
        }
        case 5: {
            // spike pattern
            for (int i = 0; i < n; i++)
                c[i] = rnd.next(-5, 5);
            int idx = rnd.next(0, n - 1);
            // positive or negative spike
            if (rnd.next(0, 1) == 0)
                c[idx] = rnd.next(6, 20);
            else
                c[idx] = rnd.next(-20, -6);
            break;
        }
        case 6: {
            // alternating high/low
            long long high = rnd.next(1, 20);
            long long low = -rnd.next(1, 20);
            for (int i = 0; i < n; i++)
                c[i] = (i % 2 == 0 ? high : low);
            break;
        }
    }
    // small random shuffle to break strict patterns
    shuffle(c.begin(), c.end());
    // output
    println(n);
    println(c);
    return 0;
}
