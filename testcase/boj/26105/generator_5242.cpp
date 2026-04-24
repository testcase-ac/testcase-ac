#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: choose N small or medium
    int N;
    if (rnd.next() < 0.3) {
        N = rnd.next(2, 4);
    } else {
        N = rnd.next(5, 10);
    }

    // Hyperparameter: choose maximum segment length category
    vector<int> maxChoices = {5, 1000, 20000};
    int max_len = rnd.any(maxChoices);

    // Hyperparameter: choose pattern for diversity
    int pattern = rnd.next(0, 4);

    vector<int> a(N);
    if (pattern == 0) {
        // fully random
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, max_len);
        }
    } else if (pattern == 1) {
        // ascending sorted
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, max_len);
        }
        sort(a.begin(), a.end());
    } else if (pattern == 2) {
        // descending sorted
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, max_len);
        }
        sort(a.begin(), a.end(), greater<int>());
    } else if (pattern == 3) {
        // all equal
        int c = rnd.next(1, max_len);
        for (int i = 0; i < N; i++) {
            a[i] = c;
        }
    } else {
        // alternating two values
        int x = rnd.next(1, max_len);
        int y = rnd.next(1, max_len);
        while (y == x) {
            y = rnd.next(1, max_len);
        }
        for (int i = 0; i < N; i++) {
            a[i] = (i % 2 == 0 ? x : y);
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
