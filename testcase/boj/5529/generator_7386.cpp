#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 3);
    int M, N;
    vector<pair<int,int>> sw;
    if (type == 0) {
        // Unreachable with one useless switch
        M = rnd.next(2, 5);
        N = rnd.next(2, 10);
        int xi = rnd.next(1, M);
        int yi = rnd.next(1, N);
        // avoid the single helpful switch at (1,N)
        if (xi == 1 && yi == N) {
            if (xi < M) xi++;
            else xi--;
        }
        sw.emplace_back(xi, yi);
    } else if (type == 1) {
        // One-switch reachable: flip at (1,N)
        M = rnd.next(2, 10);
        N = rnd.next(2, 10);
        sw.emplace_back(1, N);
    } else if (type == 2) {
        // Two-switch path: need two flips
        M = rnd.next(2, 10);
        N = rnd.next(3, 10);
        int y = rnd.next(2, N-1);
        sw.emplace_back(1, y);
        sw.emplace_back(M, y);
    } else {
        // Complex: scatter plus guaranteed two-switch path
        M = rnd.next(3, 15);
        N = rnd.next(3, 15);
        int y = rnd.next(2, N-1);
        set<pair<int,int>> s;
        // guaranteed path switches
        s.emplace(1, y);
        s.emplace(M, y);
        // extra random switches
        int maxExtra = min(15, M*N - 2);
        int extra = rnd.next(3, maxExtra);
        while ((int)s.size() < 2 + extra) {
            int xi = rnd.next(1, M);
            int yi = rnd.next(1, N);
            // allow switches anywhere except duplicates
            s.emplace(xi, yi);
        }
        for (auto &p : s) sw.push_back(p);
    }
    // Shuffle order
    shuffle(sw.begin(), sw.end());
    int K = sw.size();
    println(M, N, K);
    for (auto &p : sw) println(p.first, p.second);
    return 0;
}
