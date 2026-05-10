#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, K, C
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readSpace();
    int K = inf.readInt(0, 50, "K");
    inf.readSpace();
    int C = inf.readInt(0, 1000000, "C");
    inf.readEoln();

    // Next N lines: M integers P_i,j
    for (int i = 0; i < N; ++i) {
        vector<long long> row = inf.readLongs(M, 0LL, 1000000LL, "P_i_j");
        inf.readEoln();
    }

    // Next K lines: friend pairs a_i, b_i
    set<pair<int,int>> edges;
    for (int i = 0; i < K; ++i) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();

        ensuref(a < b, "Friend pair index %d must satisfy 1 <= a_i < b_i <= N, but got (%d, %d)", i, a, b);
        auto e = make_pair(a, b);
        ensuref(!edges.count(e), "Duplicate friend pair at index %d: (%d, %d)", i, a, b);
        edges.insert(e);
    }

    inf.readEof();
}
