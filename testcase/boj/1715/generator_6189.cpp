#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of piles
    int N = rnd.next(1, 12);
    println(N);

    // Decide if all sizes are equal
    bool all_equal = rnd.next(0, 3) == 0;
    vector<int> max_choices = {5, 10, 50, 100, 1000};
    int max_size = rnd.any(max_choices);

    if (all_equal) {
        int v = rnd.next(1, max_size);
        for (int i = 0; i < N; i++)
            println(v);
    } else {
        // Generate random sizes
        vector<int> a(N);
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, max_size);
        // Three modes: sorted asc, sorted desc, random order
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            sort(a.begin(), a.end());
        } else if (mode == 1) {
            sort(a.begin(), a.end(), greater<int>());
        } else {
            shuffle(a.begin(), a.end());
        }
        for (int x : a)
            println(x);
    }

    return 0;
}
