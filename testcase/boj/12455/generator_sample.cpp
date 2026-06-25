#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(12, 30);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int N;
        int K;
        vector<tuple<int, int, int>> coffee;

        if (mode == 0) {
            N = rnd.next(1, 3);
            K = rnd.next(1, 3);
            for (int i = 0; i < N; ++i) {
                coffee.emplace_back(rnd.next(1, K), rnd.next(1, K), rnd.next(1, 20));
            }
        } else if (mode == 1) {
            N = rnd.next(4, 8);
            K = rnd.next(4, 8);
            int deadline = rnd.next(1, K);
            for (int i = 0; i < N; ++i) {
                int c = rnd.next(1, K);
                int t = rnd.next() < 0.75 ? deadline : rnd.next(1, K);
                int s = rnd.next(1, 1000);
                coffee.emplace_back(c, t, s);
            }
        } else if (mode == 2) {
            N = rnd.next(3, 8);
            K = rnd.next(3, 8);
            for (int i = 0; i < N; ++i) {
                int c = rnd.next(1, K);
                int t = rnd.next(1, min(K, 3));
                int s = (i < 2) ? rnd.next(700, 1000) : rnd.next(1, 400);
                coffee.emplace_back(c, t, s);
            }
        } else if (mode == 3) {
            N = rnd.next(3, 8);
            K = 8;
            for (int i = 0; i < N; ++i) {
                int c = rnd.next(max(1, K - 2), K);
                int t = rnd.next(1, K);
                int s = rnd.next(1, 1000);
                coffee.emplace_back(c, t, s);
            }
        } else if (mode == 4) {
            N = 8;
            K = 8;
            for (int i = 0; i < N; ++i) {
                int c = rnd.next(1, K);
                int t = i + 1;
                int s = rnd.next(1, 1000);
                coffee.emplace_back(c, t, s);
            }
        } else {
            N = rnd.next(4, 8);
            K = rnd.next(4, 8);
            for (int i = 0; i < N; ++i) {
                int c = rnd.next(1, K);
                int t = rnd.next(1, K);
                int s = rnd.next(1, 10) <= 3 ? rnd.next(950, 1000) : rnd.next(1, 200);
                coffee.emplace_back(c, t, s);
            }
        }

        shuffle(coffee.begin(), coffee.end());
        println(N, K);
        for (auto [c, t, s] : coffee) {
            println(c, t, s);
        }
    }

    return 0;
}
