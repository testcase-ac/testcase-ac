#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a small size for hand-checkable cases
    int N = rnd.next(1, 10);

    // Start with the sorted stack [1, 2, ..., N]
    vector<int> a(N);
    iota(a.begin(), a.end(), 1);

    if (N >= 2) {
        // Hyper-parameter: choose a pattern
        int s = rnd.next(0, 4);
        switch (s) {
            case 0:
                // Completely random permutation
                shuffle(a.begin(), a.end());
                break;
            case 1:
                // Already sorted
                break;
            case 2:
                // Fully reversed
                reverse(a.begin(), a.end());
                break;
            case 3: {
                // Almost sorted: shuffle a random prefix
                int k = rnd.next(1, N - 1);
                shuffle(a.begin(), a.begin() + k);
                break;
            }
            case 4: {
                // Random suffix sorted: keep the last l elements in order
                int l = rnd.next(1, N - 1);
                shuffle(a.begin(), a.begin() + (N - l));
                break;
            }
        }
    }

    // Output in the required format
    println(N);
    for (int x : a) {
        println(x);
    }

    return 0;
}
