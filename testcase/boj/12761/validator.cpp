#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read parameters
    int A = inf.readInt(2, 30, "A");
    inf.readSpace();
    int B = inf.readInt(2, 30, "B");
    inf.readSpace();
    int N = inf.readInt(0, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 100000, "M");
    inf.readEoln();

    // Check reachability using BFS on states [0..100000]
    const int MAXP = 100000;
    vector<char> vis(MAXP + 1, false);
    queue<int> q;
    vis[N] = true;
    q.push(N);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == M) break;
        // generate all 8 moves
        int candidates[6] = { u + 1, u - 1, u + A, u - A, u + B, u - B };
        for (int i = 0; i < 6; i++) {
            int v = candidates[i];
            if (v >= 0 && v <= MAXP && !vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
        // multiplication moves
        long long mulA = 1LL * u * A;
        if (mulA >= 0 && mulA <= MAXP && !vis[mulA]) {
            vis[mulA] = true;
            q.push((int)mulA);
        }
        long long mulB = 1LL * u * B;
        if (mulB >= 0 && mulB <= MAXP && !vis[mulB]) {
            vis[mulB] = true;
            q.push((int)mulB);
        }
    }

    ensuref(vis[M],
        "Position M=%d is not reachable from N=%d with A=%d, B=%d",
        M, N, A, B);

    inf.readEof();
    return 0;
}
