#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "n");
    inf.readEoln();

    vector<int> count(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            int value = inf.readInt(1, n, "value");
            ++count[value];
        }
        inf.readEoln();
    }

    for (int value = 1; value <= n; ++value) {
        ensuref(count[value] == n,
                "value %d appears %d times, expected %d",
                value,
                count[value],
                n);
    }

    inf.readEof();
}
