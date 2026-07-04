#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int T = 1;
    int N = 1;
    int D = 1;
    int K = 1;
    vector<int> a;

    if (mode == 0) {
        T = rnd.next(1, 8);
        N = 1;
        D = rnd.next(1, 20);
        K = rnd.next(1, 10);
        a.push_back(rnd.next(1, T));
    } else if (mode == 1) {
        T = rnd.next(3, 30);
        N = rnd.next(2, 18);
        D = rnd.next(1, 6);
        K = rnd.next(1, 10);
        int distinct = rnd.next(1, min(T, 4));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1, T));
        for (int i = 0; i < N; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 2) {
        T = rnd.next(20, 80);
        N = rnd.next(8, 30);
        D = rnd.next(2, 12);
        K = rnd.next(1, 4);
        int center = rnd.next(1, T);
        int radius = rnd.next(0, min(T - 1, D + 3));
        for (int i = 0; i < N; ++i) {
            int lo = max(1, center - radius);
            int hi = min(T, center + radius);
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        T = rnd.next(10, 100);
        N = rnd.next(2, 25);
        D = rnd.next(1, 15);
        K = rnd.next(1, 10);
        for (int i = 0; i < N; ++i) a.push_back(rnd.next(1, T));
        sort(a.begin(), a.end());
    } else if (mode == 4) {
        T = rnd.next(50, 200);
        N = rnd.next(10, 35);
        D = rnd.next(3, 25);
        K = rnd.next(2, 6);
        int clusters = rnd.next(2, 5);
        vector<int> starts;
        for (int i = 0; i < clusters; ++i) starts.push_back(rnd.next(1, T));
        for (int i = 0; i < N; ++i) {
            int start = rnd.any(starts);
            int offset = rnd.next(0, D + 2);
            a.push_back(min(T, start + offset));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        T = rnd.next(100000000, 1000000000);
        N = rnd.next(3, 20);
        D = rnd.next(1, 1000000000);
        K = rnd.next(1, 10);
        for (int i = 0; i < N; ++i) a.push_back(rnd.next(1, T));
    } else {
        T = rnd.next(1, 12);
        N = rnd.next(12, 36);
        D = rnd.next(1, 20);
        K = 10;
        for (int i = 0; i < N; ++i) a.push_back(rnd.next(1, T));
        shuffle(a.begin(), a.end());
    }

    println(T, N, D, K);
    println(a);
    return 0;
}
