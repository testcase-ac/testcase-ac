#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int K;
    if (mode == 0) {
        K = rnd.next(1, 3);
    } else if (mode == 1) {
        K = rnd.next(4, 6);
    } else if (mode == 2) {
        K = rnd.next(7, 10);
    } else {
        K = rnd.wnext(10, 2) + 1;
    }

    int N = (1 << K) - 1;
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);

    if (mode == 1) {
        reverse(order.begin(), order.end());
    } else if (mode == 2) {
        shuffle(order.begin(), order.end());
    } else if (mode == 3) {
        vector<int> centered;
        centered.reserve(N);
        for (int len = N; len > 0; len /= 2) {
            int block = (N + 1) / len;
            for (int start = block / 2; start < N; start += block) {
                if (1 <= order[start] && order[start] <= N) {
                    centered.push_back(order[start]);
                }
            }
        }
        vector<char> used(N + 1, 0);
        order.clear();
        for (int x : centered) {
            if (!used[x]) {
                used[x] = 1;
                order.push_back(x);
            }
        }
        for (int x = 1; x <= N; ++x) {
            if (!used[x]) order.push_back(x);
        }
    } else if (rnd.next(0, 1) == 1) {
        vector<int> extremes;
        extremes.reserve(N);
        for (int lo = 1, hi = N; lo <= hi; ++lo, --hi) {
            extremes.push_back(lo);
            if (lo != hi) extremes.push_back(hi);
        }
        order = extremes;
    }

    println(K);
    println(order);
    return 0;
}
