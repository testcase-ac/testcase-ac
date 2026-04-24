#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int n = rnd.next(3, 8);
        int k = rnd.next(3, 8);
        int t = rnd.next(1, n);
        int m_min = max(n, 3);
        int m_max = min(n * k * 2, 20);
        if (m_max < m_min) m_max = m_min;
        int m = rnd.next(m_min, m_max);

        vector<tuple<int,int,int>> logs;
        // ensure each team has at least one submission
        for (int i = 1; i <= n; ++i) {
            int j = rnd.next(1, k);
            int w = rnd.any(vector<int>{-2, -1, 0, 1, 2});
            int s = rnd.wnext(101, w);
            logs.emplace_back(i, j, s);
        }
        // remaining submissions
        int rem = m - n;
        for (int i = 0; i < rem; ++i) {
            int team = rnd.next(1, n);
            int prob = rnd.next(1, k);
            int w = rnd.any(vector<int>{-2, -1, 0, 1, 2});
            int score = rnd.wnext(101, w);
            logs.emplace_back(team, prob, score);
        }
        shuffle(logs.begin(), logs.end());

        println(n, k, t, m);
        for (auto &e : logs) {
            int ti, pj, sc;
            tie(ti, pj, sc) = e;
            println(ti, pj, sc);
        }
    }
    return 0;
}
