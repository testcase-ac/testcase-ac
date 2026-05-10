#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 250, "N");
    inf.readEoln();

    // Read V_i
    vector<int> V(N);
    for (int i = 0; i < N; ++i) {
        V[i] = inf.readInt(1, 2000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
}
