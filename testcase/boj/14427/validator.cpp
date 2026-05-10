#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 100000;
    const int M_MIN = 1;
    const int M_MAX = 100000;
    const int A_MIN = 1;
    const int A_MAX = 1000000000;
    const int V_MIN = 1;
    const int V_MAX = 1000000000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, A_MIN, A_MAX, "A_i");
    inf.readEoln();

    int M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readEoln();

    for (int qi = 0; qi < M; ++qi) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int v = inf.readInt(V_MIN, V_MAX, "v");
            inf.readEoln();
        } else { // type == 2
            inf.readEoln();
        }
    }

    inf.readEof();
}
