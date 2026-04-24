#include "testlib.h"
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 10000, "K");
    inf.readEoln();

    // Track current number of passengers
    long long cur = K;

    // For each station, read boarding A and alighting B
    for (int i = 1; i <= N; i++) {
        int A = inf.readInt(0, 10000, "A");
        inf.readSpace();
        int B = inf.readInt(0, 10000, "B");
        inf.readEoln();

        // Update and validate passenger count
        cur += A;
        ensuref(cur >= B,
                "At station %d: trying to alight %d passengers but only %lld on the bus",
                i, B, cur);
        cur -= B;
    }

    // No extra content
    inf.readEof();
    return 0;
}
