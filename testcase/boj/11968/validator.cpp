#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    vector<bool> seen(2 * n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int card = inf.readInt(1, 2 * n, "elsie_card");
        inf.readEoln();

        ensuref(!seen[card], "duplicate Elsie card at index %d: %d", i, card);
        seen[card] = true;
    }

    inf.readEof();
}
