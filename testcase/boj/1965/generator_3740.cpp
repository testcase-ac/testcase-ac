#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small size for hand-checkable
    int n = rnd.next(1, 10);
    // choose distribution type
    int dist = rnd.next(0, 3);
    vector<int> a(n);
    switch (dist) {
        case 0: { // strictly increasing
            int start = rnd.next(1, 1000 - n + 1);
            for (int i = 0; i < n; i++) {
                a[i] = start + i;
            }
            break;
        }
        case 1: { // strictly decreasing
            int start = rnd.next(n, 1000);
            for (int i = 0; i < n; i++) {
                a[i] = start - i;
            }
            break;
        }
        case 2: // totally random
            for (int i = 0; i < n; i++) {
                a[i] = rnd.next(1, 1000);
            }
            break;
        case 3: { // random walk (local variations, with duplicates)
            a[0] = rnd.next(1, 1000);
            for (int i = 1; i < n; i++) {
                int delta = rnd.next(-50, 50);
                int v = a[i-1] + delta;
                if (v < 1) v = 1;
                if (v > 1000) v = 1000;
                a[i] = v;
            }
            break;
        }
    }
    // maybe shuffle a bit for random mixing but keep some order
    if (rnd.next(0, 1)) {
        // reverse with some probability
        reverse(a.begin(), a.end());
    }
    // output
    println(n);
    println(a);
    return 0;
}
