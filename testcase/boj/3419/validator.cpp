#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1, N_MAX = 100;
    const int E_MIN = 1, E_MAX = 100;

    while (true) {
        // Peek ahead to check for "0 0" line (end of input)
        int N = inf.readInt(0, N_MAX, "N");
        inf.readSpace();
        int E = inf.readInt(0, E_MAX, "E");
        inf.readEoln();

        if (N == 0 && E == 0) {
            inf.readEof();
            return 0;
        }

        // After 0 0, there must be no more test cases
        ensuref(N >= N_MIN && N <= N_MAX, "N = %d is out of bounds [%d, %d]", N, N_MIN, N_MAX);
        ensuref(E >= E_MIN && E <= E_MAX, "E = %d is out of bounds [%d, %d]", E, E_MIN, E_MAX);

        for (int i = 0; i < N; ++i) {
            std::string line = inf.readLine("[.X]{1,100}", "map row");
            ensuref((int)line.size() == E, "Line %d: Expected length %d, got %d", i+1, E, (int)line.size());
            for (int j = 0; j < E; ++j) {
                ensuref(line[j] == '.' || line[j] == 'X',
                    "Line %d, column %d: Invalid character '%c', expected '.' or 'X'", i+1, j+1, line[j]);
            }
        }
    }
}
