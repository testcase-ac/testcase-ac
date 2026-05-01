#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N small or medium for hand-checkable size
    int N;
    if (rnd.next(0, 1) == 0) N = rnd.next(1, 10);
    else N = rnd.next(11, 30);

    // Select a pattern for diversity
    int pattern = rnd.next(0, 4);
    vector<int> a;
    if (pattern == 0) {
        // Uniform random sizes
        for (int i = 0; i < N; i++)
            a.push_back(rnd.next(1, 4));
    } else if (pattern == 1) {
        // Biased towards small items
        vector<int> vb = {1,1,1,1,1,2,2,2,3,4};
        for (int i = 0; i < N; i++)
            a.push_back(rnd.any(vb));
    } else if (pattern == 2) {
        // Biased towards large items
        vector<int> vb = {4,4,4,4,4,3,3,3,2,1};
        for (int i = 0; i < N; i++)
            a.push_back(rnd.any(vb));
    } else if (pattern == 3) {
        // All items same size
        int k = rnd.next(1, 4);
        a.assign(N, k);
    } else {
        // Nearly balanced counts of each size
        int base = N / 4;
        int rem = N - base * 4;
        vector<int> cnt(5, base);
        for (int i = 1; i <= rem; i++) cnt[i]++;
        for (int size = 1; size <= 4; size++)
            for (int j = 0; j < cnt[size]; j++)
                a.push_back(size);
        shuffle(a.begin(), a.end());
    }

    // Output
    println(N);
    println(a);

    return 0;
}
