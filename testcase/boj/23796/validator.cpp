#include "testlib.h"
#include <cmath>
using namespace std;

// Helper function to check if x is a power of two
bool is_power_of_two(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

// Helper function to check if x is 2^k for 1 <= k <= 30
bool is_valid_tile(int x) {
    if (x == 0) return true;
    if (!is_power_of_two(x)) return false;
    int k = 0;
    while (x > 1) {
        x >>= 1;
        ++k;
    }
    return 1 <= k && k <= 30;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 8;
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            int x = inf.readInt(0, 1073741824, format("tile[%d][%d]", row+1, col+1).c_str());
            ensuref(is_valid_tile(x),
                "tile[%d][%d] = %d is not 0 or 2^k for 1 <= k <= 30", row+1, col+1, x);
            if (col < N-1)
                inf.readSpace();
            else
                inf.readEoln();
        }
    }
    string dir = inf.readToken("[UDLR]", "direction");
    inf.readEoln();

    inf.readEof();
}
