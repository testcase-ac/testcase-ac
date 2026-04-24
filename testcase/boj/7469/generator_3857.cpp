#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<int> sampleDistinct(int cnt, int lo, int hi) {
    set<int> s;
    while ((int)s.size() < cnt) {
        int x = rnd.next(lo, hi);
        s.insert(x);
    }
    return vector<int>(s.begin(), s.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: array size
    int n = rnd.next(1, 10);
    // Hyper-parameter: number of queries
    int maxM = min(20, n * (n + 1) / 2);
    int m = rnd.next(1, maxM);

    // Build array a with several patterns
    vector<int> a;
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // random distinct in [-100,100]
        a = sampleDistinct(n, -100, 100);
    } else if (pattern == 1) {
        // almost sorted ascending 1..n
        a.resize(n);
        for (int i = 0; i < n; i++) a[i] = i + 1;
        int swaps = (n >= 2 ? rnd.next(0, n) : 0);
        for (int t = 0; t < swaps; t++) {
            int x = rnd.next(0, n - 2);
            swap(a[x], a[x + 1]);
        }
    } else if (pattern == 2) {
        // almost sorted descending n..1
        a.resize(n);
        for (int i = 0; i < n; i++) a[i] = n - i;
        int swaps = (n >= 2 ? rnd.next(0, n) : 0);
        for (int t = 0; t < swaps; t++) {
            int x = rnd.next(0, n - 2);
            swap(a[x], a[x + 1]);
        }
    } else {
        // cluster negatives and positives
        int negCnt = rnd.next(1, max(1, n - 1));
        int posCnt = n - negCnt;
        vector<int> negs = sampleDistinct(negCnt, -100, -1);
        vector<int> poss = sampleDistinct(posCnt, 1, 100);
        a = negs;
        a.insert(a.end(), poss.begin(), poss.end());
        shuffle(a.begin(), a.end());
    }

    // Output n, m and array
    println(n, m);
    println(a);

    // Generate queries
    for (int qi = 0; qi < m; qi++) {
        int qType = rnd.next(0, 2);
        int i, j, k;
        if (qType == 0) {
            // single element
            i = j = rnd.next(1, n);
            k = 1;
        } else if (qType == 1) {
            // full range
            i = 1; j = n;
            k = rnd.next(1, n);
        } else {
            // random subrange
            // choose a random length L in [1..n]
            int L = rnd.next(1, n);
            i = rnd.next(1, n - L + 1);
            j = i + L - 1;
            int kType = rnd.next(0, 2);
            if (kType == 0) k = 1;
            else if (kType == 1) k = L;
            else k = rnd.next(1, L);
        }
        println(i, j, k);
    }

    return 0;
}
