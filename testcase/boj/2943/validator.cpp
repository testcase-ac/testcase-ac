#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each day's S and A
    for (int i = 0; i < M; i++) {
        int S = inf.readInt(1, N, "S");
        inf.readSpace();
        int A = inf.readInt(1, N, "A");
        inf.readEoln();

        // Ensure A + S - 1 does not exceed N
        ensuref((long long)A + S - 1 <= N,
                "On line %d: A + S - 1 = %lld > N = %d", 
                i + 2, // +2 because line 1 is N M, then lines start at 2
                (long long)A + S - 1, 
                N);
    }

    inf.readEof();
    return 0;
}
