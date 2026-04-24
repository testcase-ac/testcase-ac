#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of plants
    int N = rnd.next(2, 10);
    // Choose generation pattern
    int pattern = rnd.next(0, 3);
    vector<pair<int,int>> pts;
    set<pair<int,int>> used;

    if (pattern == 0) {
        // Uniform random
        while ((int)pts.size() < N) {
            int x = rnd.next(0, 10);
            int y = rnd.next(0, 10);
            auto p = make_pair(x, y);
            if (used.insert(p).second) {
                pts.push_back(p);
            }
        }
    }
    else if (pattern == 1) {
        // Diagonal heavy: a long increasing chain plus some noise
        int L = rnd.next(1, N);
        int base = rnd.next(0, 10 - L);
        for (int i = 0; i < L; i++) {
            auto p = make_pair(base + i, base + i);
            used.insert(p);
            pts.push_back(p);
        }
        while ((int)pts.size() < N) {
            int x = rnd.next(0, 10);
            int y = rnd.next(0, 10);
            auto p = make_pair(x, y);
            if (used.insert(p).second) {
                pts.push_back(p);
            }
        }
    }
    else if (pattern == 2) {
        // Many points share same x
        int Kx = rnd.next(1, min(N, 3));
        vector<int> xs;
        while ((int)xs.size() < Kx) {
            int x = rnd.next(0, 10);
            if (find(xs.begin(), xs.end(), x) == xs.end())
                xs.push_back(x);
        }
        while ((int)pts.size() < N) {
            int x = rnd.any(xs);
            int y = rnd.next(0, 10);
            auto p = make_pair(x, y);
            if (used.insert(p).second) {
                pts.push_back(p);
            }
        }
    }
    else {
        // Clustered around K centers
        int K = rnd.next(2, 3);
        vector<int> sz(K, N / K);
        int rem = N - (N / K) * K;
        for (int i = 0; i < rem; i++) sz[i]++;
        for (int i = 0; i < K; i++) {
            int cx = rnd.next(1, 9);
            int cy = rnd.next(1, 9);
            for (int j = 0; j < sz[i]; j++) {
                int x, y;
                pair<int,int> p;
                do {
                    int dx = rnd.next(-1, 1);
                    int dy = rnd.next(-1, 1);
                    x = cx + dx;
                    y = cy + dy;
                    if (x < 0) x = 0;
                    if (x > 10) x = 10;
                    if (y < 0) y = 0;
                    if (y > 10) y = 10;
                    p = make_pair(x, y);
                } while (!used.insert(p).second);
                pts.push_back(p);
            }
        }
    }

    // Shuffle so input order is random
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
