#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int N;
    vector<int> cnt;

    if (mode == 0) {
        N = rnd.next(1, 5);
        cnt.assign(N, rnd.next(1, 4));
    } else if (mode == 1) {
        N = rnd.next(1, 20);
        cnt.assign(N, 1);
    } else if (mode == 2) {
        N = rnd.next(2, 18);
        int current = rnd.next(1, 6);
        for (int i = 0; i < N; ++i) {
            current += rnd.next(0, 4);
            cnt.push_back(current);
        }
    } else if (mode == 3) {
        N = rnd.next(2, 18);
        int current = rnd.next(8, 35);
        for (int i = 0; i < N; ++i) {
            cnt.push_back(current);
            current = max(1, current - rnd.next(0, 4));
        }
    } else if (mode == 4) {
        N = rnd.next(3, 20);
        cnt.assign(N, rnd.next(1, 3));
        int spikes = rnd.next(1, min(N, 4));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, N - 1);
            cnt[pos] = rnd.next(20, 1000);
        }
    } else if (mode == 5) {
        N = rnd.next(4, 24);
        int low = rnd.next(1, 3);
        int high = rnd.next(4, 80);
        for (int i = 0; i < N; ++i) {
            cnt.push_back((i % 2 == 0) ? rnd.next(1, low) : rnd.next(high / 2, high));
        }
    } else if (mode == 6) {
        N = rnd.next(30, 50);
        for (int i = 0; i < N; ++i) {
            cnt.push_back(rnd.next(1, 10));
        }
    } else {
        N = rnd.next(1, 50);
        cnt.assign(N, 1000);
        for (int i = 0; i < N; ++i) {
            if (rnd.next(0, 3) == 0) cnt[i] = rnd.next(1, 20);
        }
    }

    println(N);
    println(cnt);
    return 0;
}
