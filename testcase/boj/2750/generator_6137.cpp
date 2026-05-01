#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a manageable N for manual verification
    int N = rnd.next(1, 15);
    int pattern = rnd.next(0, 4);
    vector<int> v;

    if (pattern == 0) {
        // Already sorted ascending sequence 1..N
        for (int i = 1; i <= N; i++) v.push_back(i);
    }
    else if (pattern == 1) {
        // Sorted descending sequence N..1
        for (int i = N; i >= 1; i--) v.push_back(i);
    }
    else if (pattern == 2) {
        // Pure random unique ints in [-1000,1000]
        set<int> s;
        while ((int)s.size() < N) {
            s.insert(rnd.next(-1000, 1000));
        }
        for (int x : s) v.push_back(x);
        // shuffle the set order to make it arbitrary
        shuffle(v.begin(), v.end());
    }
    else if (pattern == 3) {
        // Almost sorted: generate sorted random, then swap some pairs
        set<int> s;
        while ((int)s.size() < N) {
            s.insert(rnd.next(-1000, 1000));
        }
        for (int x : s) v.push_back(x);
        // perform a few random swaps
        int swaps = rnd.next(1, N/2 + 1);
        for (int i = 0; i < swaps; i++) {
            int a = rnd.next(0, N-1);
            int b = rnd.next(0, N-1);
            swap(v[a], v[b]);
        }
    }
    else {
        // pattern == 4: include extremes -1000 and 1000 if possible
        if (N >= 2) {
            v.push_back(-1000);
            v.push_back(1000);
            set<int> s;
            while ((int)s.size() < N-2) {
                int x = rnd.next(-999, 999);
                if (x != -1000 && x != 1000) s.insert(x);
            }
            for (int x : s) v.push_back(x);
            shuffle(v.begin(), v.end());
        } else {
            // fallback to pure random if N == 1
            v.push_back(rnd.next(-1000, 1000));
        }
    }

    // Output format
    println(N);
    for (int x : v) println(x);
    return 0;
}
