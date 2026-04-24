#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: n, b, a
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int b = inf.readInt(1, 1000000000, "b");
    inf.readSpace();
    int a = inf.readInt(0, n, "a");
    inf.readEoln();

    // Read prices
    vector<int> price = inf.readInts(n, 2, 1000000000, "price");
    for (int i = 0; i < n; i++) {
        ensuref(price[i] % 2 == 0,
                "price at index %d is not even: %d",
                i + 1, price[i]);
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
