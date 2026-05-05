#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 250000, "M");
    inf.readEoln();

    // 2. Read N meats: s_i, e_i, t_i
    vector<tuple<int,int,int>> meats;
    for (int i = 0; i < N; ++i) {
        int s = inf.readInt(0, 1000000000, "s_i");
        inf.readSpace();
        int e = inf.readInt(0, 1000000000, "e_i");
        inf.readSpace();
        int t = inf.readInt(1, 1000000000, "t_i");
        inf.readEoln();

        ensuref(s < e, "s_i < e_i must hold for meat %d: got s_i=%d, e_i=%d", i+1, s, e);
        meats.emplace_back(s, e, t);
    }

    // 3. Read M people: a_j, b_j
    for (int j = 0; j < M; ++j) {
        int a = inf.readInt(0, 1000000000 - 1, "a_j");
        inf.readSpace();
        int b = inf.readInt(0, 1000000000 - 1, "b_j");
        inf.readEoln();

        ensuref(a <= b, "a_j <= b_j must hold for person %d: got a_j=%d, b_j=%d", j+1, a, b);
    }

    inf.readEof();
}
