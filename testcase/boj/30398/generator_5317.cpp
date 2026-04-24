#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small bounds for hand-checking
    int N = rnd.next(2, 10);
    int d = rnd.next(1, 5);
    // Maximum intermediate points
    int P_max = (d == 1 ? max(0, N - 2) : 3);
    // Diverse P using weighted choice
    int t = rnd.next(-1, 1);
    int P = rnd.wnext(P_max + 1, t); // in [0..P_max]

    vector<vector<int>> pts;
    if (d == 1) {
        // 1D case: pick distinct P points in [2..N-1]
        vector<int> domain;
        for (int x = 2; x <= N - 1; ++x) domain.push_back(x);
        shuffle(domain.begin(), domain.end());
        domain.resize(P);
        sort(domain.begin(), domain.end());
        for (int x : domain) {
            pts.push_back(vector<int>(1, x));
        }
    } else {
        // d >= 2: build monotonic chain
        vector<int> prev(d, 1);
        for (int i = 0; i < P; ++i) {
            // find dimensions we can increase
            vector<int> avail;
            for (int j = 0; j < d; ++j) {
                if (prev[j] < N) avail.push_back(j);
            }
            if (avail.empty()) break;
            int j0 = rnd.any(avail);
            int diff = N - prev[j0];
            int t2 = rnd.next(-1, 1);
            // step in [1..diff]
            int step = rnd.wnext(diff, t2) + 1;
            vector<int> cur = prev;
            cur[j0] += step;
            // avoid reaching the final point
            bool isEnd = true;
            for (int j = 0; j < d; ++j) {
                if (cur[j] != N) { isEnd = false; break; }
            }
            if (isEnd) break;
            pts.push_back(cur);
            prev = cur;
        }
    }

    int realP = pts.size();
    println(N, d, realP);
    for (auto &v : pts) println(v);
    return 0;
}
