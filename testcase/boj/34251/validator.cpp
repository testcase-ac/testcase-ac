#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2;
    const int N_MAX = 200000;
    const int Q_MIN = 1;
    const int Q_MAX = 200000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int Q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readEoln();

    vector<int> A(N + 1);

    for (int i = 0; i <= N; ++i) {
        int low = 0;
        int high = min(N - i, i);
        A[i] = inf.readInt(low, high, ("A_" + to_string(i)).c_str());
        if (i != N) inf.readSpace();
    }
    inf.readEoln();

    for (int qi = 1; qi <= Q; ++qi) {
        int x = inf.readInt(0, N, ("x_" + to_string(qi)).c_str());
        inf.readSpace();
        int ymax = min(N - x, x);
        int y = inf.readInt(0, ymax, ("y_" + to_string(qi)).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
