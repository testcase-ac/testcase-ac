#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> seen(n + 1);
    for (int i = 0; i < n; ++i) {
        int cow = inf.readInt(1, n, "c_i");
        ensuref(!seen[cow], "cow %d appears more than once", cow);
        seen[cow] = 1;
        inf.readEoln();
    }

    inf.readEof();
}
