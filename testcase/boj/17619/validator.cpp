#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Log {
    int idx;
    long long x1, x2, y;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read logs
    vector<Log> logs;
    logs.reserve(N);
    for (int i = 0; i < N; i++) {
        long long x1 = inf.readLong(0LL, 1000000000LL, "x1");
        inf.readSpace();
        long long x2 = inf.readLong(0LL, 1000000000LL, "x2");
        inf.readSpace();
        long long y  = inf.readLong(0LL, 1000000000LL, "y");
        inf.readEoln();

        ensuref(x1 < x2,
                "Log %d: x1 must be < x2, got x1=%lld, x2=%lld",
                i+1, x1, x2);

        logs.push_back({i+1, x1, x2, y});
    }

    // Check that no two logs touch or overlap at the same y
    sort(logs.begin(), logs.end(), [](const Log &a, const Log &b) {
        if (a.y != b.y) return a.y < b.y;
        return a.x1 < b.x1;
    });
    for (int i = 1; i < N; i++) {
        const Log &prev = logs[i-1];
        const Log &cur  = logs[i];
        if (prev.y == cur.y) {
            ensuref(prev.x2 < cur.x1,
                    "Logs %d and %d at y=%lld overlap or touch: [%lld, %lld] vs [%lld, %lld]",
                    prev.idx, cur.idx, prev.y,
                    prev.x1, prev.x2, cur.x1, cur.x2);
        }
    }

    // Read queries
    for (int i = 0; i < Q; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        ensuref(u != v,
                "Query %d: endpoints must be distinct, got (%d, %d)",
                i+1, u, v);
    }

    inf.readEof();
    return 0;
}
