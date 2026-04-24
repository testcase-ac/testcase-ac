#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 20, "K");
    inf.readEoln();

    // Read the sequence of N gestures, each must be exactly 'H', 'P', or 'S'
    for (int i = 0; i < N; i++) {
        // Read the entire line and ensure it's exactly one of H, P, S
        inf.readLine("[HPS]", "gesture");
    }

    inf.readEof();
    return 0;
}
