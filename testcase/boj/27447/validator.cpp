#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // Read t_i
    vector<int> t(N);
    if (N > 0) {
        t = inf.readInts(N, 0, 1000000, "t_i");
        inf.readEoln();
    }

    // Check strictly increasing order (since "오름차순" and "각 시각에는 최대 한 명의 손님까지만 올 수 있다")
    for (int i = 1; i < N; ++i) {
        ensuref(t[i] > t[i-1], "t_i must be strictly increasing: t[%d]=%d, t[%d]=%d", i-1, t[i-1], i, t[i]);
    }

    inf.readEof();
}
