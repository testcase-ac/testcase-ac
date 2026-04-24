#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    double pi = acos(-1.0);
    for (int t = 0; t < T; t++) {
        int N = rnd.next(1, 10);
        int K = rnd.next(1, min(N, 3));
        int Rbound = rnd.next(0, 1000);
        // partition N into K positive sizes
        vector<int> sz(K, 1);
        for (int i = 0; i < N - K; i++)
            sz[rnd.next(0, K - 1)]++;
        // compute well-separated cluster centers
        vector<pair<int,int>> centers(K);
        for (int i = 0; i < K; i++) {
            double ang = 2 * pi * i / K;
            int cx = 2500 + int(2000 * cos(ang));
            int cy = 2500 + int(2000 * sin(ang));
            cx += rnd.next(-100, 100);
            cy += rnd.next(-100, 100);
            cx = max(0, min(5000, cx));
            cy = max(0, min(5000, cy));
            centers[i] = {cx, cy};
        }
        vector<tuple<int,int,int>> circles;
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < sz[i]; j++) {
                int x = centers[i].first;
                int y = centers[i].second;
                int r = rnd.next(0, Rbound);
                circles.emplace_back(x, y, r);
            }
        }
        shuffle(circles.begin(), circles.end());
        println(N);
        for (auto &c : circles) {
            int x, y, r;
            tie(x, y, r) = c;
            println(x, y, r);
        }
    }
    return 0;
}
