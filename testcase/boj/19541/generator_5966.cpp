#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // 70% chance to generate a solvable case, otherwise an unsolvable small counterexample
    bool solvable = rnd.next() < 0.7;
    if (solvable) {
        int N = rnd.next(2, 10);
        int M = rnd.next(1, min(10, N * 2));
        // Generate meetings
        vector<vector<int>> meetings;
        for (int i = 0; i < M; i++) {
            int k = rnd.next(2, N);
            vector<int> p(N);
            iota(p.begin(), p.end(), 1);
            shuffle(p.begin(), p.end());
            p.resize(k);
            meetings.push_back(p);
        }
        // Random initial infection
        vector<int> init(N + 1);
        for (int i = 1; i <= N; i++) init[i] = rnd.next(0, 1);
        // Simulate to get final states
        vector<int> f = init;
        for (auto &m : meetings) {
            bool any = false;
            for (int x : m) if (f[x]) { any = true; break; }
            if (any) {
                for (int x : m) f[x] = 1;
            }
        }
        // Output
        println(N, M);
        for (auto &m : meetings) {
            printf("%d", (int)m.size());
            for (int x : m) printf(" %d", x);
            printf("\n");
        }
        for (int i = 1; i <= N; i++) {
            printf("%d%c", f[i], i == N ? '\n' : ' ');
        }
    } else {
        // Construct a small UNSOLVABLE instance on 3 persons: 1-2 then 2-3
        int N = rnd.next(3, 10);
        int M = 2;
        println(N, M);
        // First two meetings form the chain
        printf("2 1 2\n");
        printf("2 2 3\n");
        // Final states that break consistency: 1 and 3 are infected, 2 is not
        vector<int> f(N + 1);
        f[1] = 1; f[2] = 0; f[3] = 1;
        for (int i = 4; i <= N; i++) f[i] = rnd.next(0, 1);
        for (int i = 1; i <= N; i++) {
            printf("%d%c", f[i], i == N ? '\n' : ' ');
        }
    }
    return 0;
}
