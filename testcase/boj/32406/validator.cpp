#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    // Read array a
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = inf.readInt(1, 1000, "a_i");
        if (i + 1 < N)
            inf.readSpace();
        else
            inf.readEoln();
    }

    // Read array b
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
        b[i] = inf.readInt(1, 1000, "b_i");
        if (i + 1 < N)
            inf.readSpace();
        else
            inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
