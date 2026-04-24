#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate N in the range [5..10]
    int N = rnd.next(5, 10);

    // Generate M in the range [1..50] (just to keep it fairly small)
    int M = rnd.next(1, 40);

    // We'll pick distinct numbers for the materials from the range [1..50].
    // If you want them smaller or bigger, adjust accordingly.
    vector<int> candidates(20);
    iota(candidates.begin(), candidates.end(), 1);  // [1, 2, 3, ..., 50]
    shuffle(candidates.begin(), candidates.end());

    // Now pick the first N distinct numbers
    vector<int> materials(candidates.begin(), candidates.begin() + N);

    // Print N
    cout << N << "\n";
    // Print M
    cout << M << "\n";

    // Print the N distinct material numbers
    for (int i = 0; i < N; i++) {
        cout << materials[i];
        if (i + 1 < N) cout << " ";
    }
    cout << "\n";

    return 0;
}
