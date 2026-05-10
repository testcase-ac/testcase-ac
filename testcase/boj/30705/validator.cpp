#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // For each day, read A_i and B_i
    for (int i = 1; i <= M; ++i) {
        int A = inf.readInt(1, N, "A_" + to_string(i));
        inf.readSpace();
        int B = inf.readInt(A, N, "B_" + to_string(i)); // A_i <= B_i
        inf.readEoln();
    }

    inf.readEof();
}
