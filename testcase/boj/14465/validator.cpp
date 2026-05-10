#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, B
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    set<int> broken;
    for (int i = 0; i < B; ++i) {
        int x = inf.readInt(1, N, "broken_signal_number");
        inf.readEoln();
        ensuref(broken.insert(x).second, 
            "Duplicate broken signal number at line %d: %d", i+2, x);
    }

    inf.readEof();
}
