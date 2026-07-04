#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> ticket = inf.readInts(n, 1, n, "t_i");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[ticket[i]],
                "duplicate ticket number at index %d: %d",
                i + 1,
                ticket[i]);
        seen[ticket[i]] = true;
    }

    inf.readEof();
}
