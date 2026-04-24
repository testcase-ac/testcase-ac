#include "testlib.h"
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // We must ensure C(N+M, N) <= 2^63-1, so enforce N+M <= 66
    int N, M;
    int type = rnd.next(0, 3);
    if (type == 0) {
        // One-dimensional path (thin grid)
        if (rnd.next(0,1) == 0) {
            N = 1;
            M = rnd.next(1, 65); // 1 + M <= 66
        } else {
            M = 1;
            N = rnd.next(1, 65);
        }
    } else if (type == 1) {
        // Small grid
        N = rnd.next(1, 10);
        M = rnd.next(1, min(10, 66 - N));
    } else if (type == 2) {
        // Medium grid
        N = rnd.next(5, 20);
        M = rnd.next(5, min(20, 66 - N));
    } else {
        // Larger but still safe
        N = rnd.next(1, 50);
        M = rnd.next(1, min(50, 66 - N));
    }
    // total edges in grid graph
    long long totalHoriz = (long long)N * (M + 1);
    long long totalVert  = (long long)M * (N + 1);
    long long totalEdges = totalHoriz + totalVert;
    int Kmax = (int)min<long long>(totalEdges, 50);
    int K = rnd.next(0, Kmax);
    // pick K distinct blocked roads
    set< tuple<int,int,int,int> > blocked;
    while ((int)blocked.size() < K) {
        bool horiz = rnd.next(0,1) == 0;
        int x1, y1, x2, y2;
        if (horiz) {
            // horizontal between (x, y) and (x+1, y)
            x1 = rnd.next(0, N-1);
            y1 = rnd.next(0, M);
            x2 = x1 + 1;
            y2 = y1;
        } else {
            // vertical between (x, y) and (x, y+1)
            x1 = rnd.next(0, N);
            y1 = rnd.next(0, M-1);
            x2 = x1;
            y2 = y1 + 1;
        }
        // normalize so (x1,y1) < (x2,y2)
        if (make_pair(x2,y2) < make_pair(x1,y1)) {
            swap(x1, x2);
            swap(y1, y2);
        }
        blocked.emplace(x1, y1, x2, y2);
    }
    // output
    println(N, M);
    println(K);
    for (auto &t : blocked) {
        int a,b,c,d;
        tie(a,b,c,d) = t;
        println(a, b, c, d);
    }
    return 0;
}
