#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N = 1;
    int M = 1;
    vector<int> t;

    if (mode == 0) {
        N = rnd.next(1, 6);
        M = rnd.next(1, 6);
        int cur = rnd.next(0, 2);
        for (int i = 0; i < N; ++i) {
            t.push_back(cur);
            cur += rnd.next(1, 2);
        }
    } else if (mode == 1) {
        N = rnd.next(2, 10);
        M = rnd.next(1, 4);
        int cur = rnd.next(2, 8);
        for (int i = 0; i < N; ++i) {
            t.push_back(cur);
            cur += 1;
        }
    } else if (mode == 2) {
        N = rnd.next(1, 10);
        M = rnd.next(3, 12);
        int cur = rnd.next(0, 6);
        for (int i = 0; i < N; ++i) {
            t.push_back(cur);
            cur += rnd.next(M + 1, M + 8);
        }
    } else if (mode == 3) {
        N = rnd.next(2, 14);
        M = rnd.next(1, 20);
        int cur = rnd.next(0, 10);
        for (int i = 0; i < N; ++i) {
            t.push_back(cur);
            cur += rnd.next(1, max(2, M + 3));
        }
    } else if (mode == 4) {
        N = rnd.next(1, 12);
        M = rnd.next(1, 1000000);
        int cur = 1000000 - N + 1 - rnd.next(0, 20);
        cur = max(0, cur);
        for (int i = 0; i < N; ++i) {
            t.push_back(cur + i);
        }
    } else {
        N = rnd.next(20, 60);
        M = rnd.next(1, 50);
        int cur = rnd.next(0, 30);
        for (int i = 0; i < N; ++i) {
            t.push_back(cur);
            cur += rnd.next(1, 8);
        }
    }

    for (int& x : t) {
        x = min(x, 1000000);
    }
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    N = int(t.size());

    println(N, M);
    println(t);
    return 0;
}
