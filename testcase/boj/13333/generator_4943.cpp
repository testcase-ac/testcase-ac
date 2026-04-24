#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of papers
    int n = rnd.next(1, 10);
    vector<int> a(n);
    // Hyper-parameter: pick distribution type
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Ascending citations 0,1,2,...
        for (int i = 0; i < n; i++)
            a[i] = i;
    } else if (type == 1) {
        // Descending citations n, n-1, ..., 1
        for (int i = 0; i < n; i++)
            a[i] = n - i;
    } else if (type == 2) {
        // Uniform random in [0, H]
        int H = rnd.next(0, 20);
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(0, H);
    } else {
        // Mostly zeros, with k random positive citations
        for (int i = 0; i < n; i++)
            a[i] = 0;
        int k = rnd.next(1, n);
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < k; i++)
            a[idx[i]] = rnd.next(1, 20);
    }
    // Shuffle to mix the sequence
    shuffle(a.begin(), a.end());
    // Output
    println(n);
    println(a);
    return 0;
}
