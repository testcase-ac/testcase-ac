#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 400, "N");
    inf.readEoln();

    // Read Coca-Cola Zero counts c[i][j]
    vector<vector<long long>> c(N, vector<long long>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j > 0) inf.readSpace();
            c[i][j] = inf.readLong(0LL, 1000000000LL, "c");
        }
        inf.readEoln();
    }

    // Read Pepsi Zero counts p[i][j]
    vector<vector<long long>> p(N, vector<long long>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j > 0) inf.readSpace();
            p[i][j] = inf.readLong(0LL, 1000000000LL, "p");
        }
        inf.readEoln();
    }

    // Validate that starting and ending cells have zero cola
    ensuref(c[0][0] == 0, "c[1][1] must be 0, found %lld", c[0][0]);
    ensuref(c[N-1][N-1] == 0, "c[N][N] must be 0, found %lld", c[N-1][N-1]);
    ensuref(p[0][0] == 0, "p[1][1] must be 0, found %lld", p[0][0]);
    ensuref(p[N-1][N-1] == 0, "p[N][N] must be 0, found %lld", p[N-1][N-1]);

    inf.readEof();
    return 0;
}
