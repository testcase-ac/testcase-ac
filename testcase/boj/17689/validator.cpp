#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read A_i
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = inf.readInt(1, 1000000000, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
