#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper: sometimes minimal N
    int N;
    if (rnd.next(0, 4) == 0) {
        N = 1;
    } else {
        N = rnd.next(2, 10);
    }
    // Generate non-increasing a[i] >= 1
    int a1 = rnd.next(1, 20);
    vector<int> a(N);
    a[0] = a1;
    for (int i = 1; i < N; i++) {
        int maxDec = a[i-1] - 1; // ensure next >=1
        int dec = rnd.wnext(maxDec + 1, -1); // weighted to small dec
        a[i] = a[i-1] - dec;
    }
    // Hyper: maximum x-range
    int maxX = a1 + rnd.next(0, 5);
    // Hyper: Q size, sometimes minimal
    int Q;
    if (rnd.next(0, 4) == 0) {
        Q = 1;
    } else {
        Q = rnd.next(1, 20);
    }
    // Generate queries
    vector<pair<int,int>> qs;
    vector<int> tList = {-2, -1, 0, 1, 2};
    for (int i = 0; i < Q; i++) {
        int t = rnd.any(tList);
        int y = rnd.wnext(N, t) + 1; // 1..N with bias
        int ay = a[y-1];
        double prob = rnd.next();
        int x;
        if (prob < 0.6 || ay + 1 > maxX) {
            // x inside existing Nemos
            x = rnd.next(1, ay);
        } else {
            // x outside to test zero-removal
            x = rnd.next(ay + 1, maxX);
        }
        qs.emplace_back(x, y);
    }
    // Shuffle query order
    shuffle(qs.begin(), qs.end());
    // Output
    println(N, Q);
    println(a);
    for (auto &pr : qs) {
        println(pr.first, pr.second);
    }
    return 0;
}
