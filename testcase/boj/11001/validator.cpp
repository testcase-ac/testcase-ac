#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and D
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int D = inf.readInt(1, N, "D"); // 1 ≤ D ≤ N
    inf.readEoln();

    // Read temperatures T_i: non-increasing, 1 ≤ T_i ≤ 1e9
    vector<long long> T = inf.readLongs(N, 1LL, 1000000000LL, "T_i");
    inf.readEoln();
    for (int i = 0; i + 1 < N; i++) {
        ensuref(T[i] >= T[i+1],
                "Temperatures must be non-increasing: T_%d=%lld < T_%d=%lld",
                i+1, T[i], i+2, T[i+1]);
    }

    // Read values V_i: 1 ≤ V_i ≤ 1e9
    vector<long long> V = inf.readLongs(N, 1LL, 1000000000LL, "V_i");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
