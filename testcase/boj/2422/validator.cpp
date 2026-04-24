#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(0, 10000, "M");
    inf.readEoln();

    // Read forbidden pairs, ensure no loops or duplicates
    set<pair<int,int>> forbidden;
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Forbidden pair %d: loop detected (%d, %d)", i, u, v);

        int a = u, b = v;
        if (a > b) swap(a, b);
        pair<int,int> p = make_pair(a, b);
        ensuref(!forbidden.count(p),
                "Duplicate forbidden pair at index %d: (%d, %d)", i, a, b);
        forbidden.insert(p);
    }

    inf.readEof();
    return 0;
}
