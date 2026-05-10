#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of seniors
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Read each senior's answer Ai
    for (int i = 1; i <= N; i++) {
        // Each Ai must be between 1 and N
        inf.readInt(1, N, "A_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
