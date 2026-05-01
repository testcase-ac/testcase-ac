#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_VAL = -1000000;
    const int MAX_VAL = 1000000;

    int scenarioCount = 12;
    int scenario = rnd.next(0, scenarioCount - 1);

    vector<int> a;
    int N = 0;

    switch (scenario) {
        case 0: {
            // Single element
            N = 1;
            a.push_back(rnd.next(MIN_VAL, MAX_VAL));
            break;
        }
        case 1: {
            // Already sorted ascending, small N
            N = rnd.next(2, 15);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(-50, 50);
            sort(a.begin(), a.end());
            break;
        }
        case 2: {
            // Already sorted descending, small N
            N = rnd.next(2, 15);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(-50, 50);
            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
            break;
        }
        case 3: {
            // All equal
            N = rnd.next(10, 30);
            int choice = rnd.next(0, 5);
            int val;
            if (choice == 0) val = 0;
            else if (choice == 1) val = 1;
            else if (choice == 2) val = -1;
            else if (choice == 3) val = MAX_VAL;
            else if (choice == 4) val = MIN_VAL;
            else val = rnd.next(-5, 5);
            a.assign(N, val);
            break;
        }
        case 4: {
            // Many duplicates in a narrow range
            N = rnd.next(10, 40);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(-3, 3);
            break;
        }
        case 5: {
            // Random in full range
            N = rnd.next(10, 40);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(MIN_VAL, MAX_VAL);
            break;
        }
        case 6: {
            // Only negative numbers
            N = rnd.next(10, 40);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(MIN_VAL, -1);
            break;
        }
        case 7: {
            // Only non-negative numbers
            N = rnd.next(10, 40);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(0, MAX_VAL);
            break;
        }
        case 8: {
            // Almost sorted ascending (few elements out of place)
            N = rnd.next(10, 40);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(-100, 100);
            sort(a.begin(), a.end());
            int swaps = rnd.next(1, 3);
            for (int s = 0; s < swaps; ++s) {
                int i = rnd.next(0, N - 1);
                int j = rnd.next(0, N - 1);
                if (i != j) swap(a[i], a[j]);
            }
            break;
        }
        case 9: {
            // Alternating low/high values
            N = rnd.next(10, 40);
            int low, high;
            if (rnd.next(0, 3) == 0) {
                // Extreme alternation
                low = MIN_VAL;
                high = MAX_VAL;
            } else {
                low = rnd.next(-10, 0);
                high = rnd.next(1, 10);
                if (high <= low) high = low + 1;
            }
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = (i % 2 == 0 ? high : low);
            // Slight shuffle to avoid trivial pattern
            shuffle(a.begin(), a.end());
            break;
        }
        case 10: {
            // Must include both extremes -1e6 and 1e6
            N = rnd.next(5, 25);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(-100, 100);
            if (N >= 2) {
                a[0] = MIN_VAL;
                a[1] = MAX_VAL;
            } else if (N == 1) {
                a[0] = MIN_VAL;
            }
            shuffle(a.begin(), a.end());
            break;
        }
        case 11: {
            // Mix of negatives, zeros, positives with duplicates
            N = rnd.next(15, 40);
            a.clear();
            // Ensure presence of -2, -1, 0, 1, 2
            a.push_back(-2);
            a.push_back(-1);
            a.push_back(0);
            a.push_back(1);
            a.push_back(2);
            while ((int)a.size() < N) {
                a.push_back(rnd.next(-5, 5));
            }
            shuffle(a.begin(), a.end());
            break;
        }
    }

    println(N);
    for (int x : a) println(x);

    return 0;
}
