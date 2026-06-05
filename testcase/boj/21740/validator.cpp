#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

bool hasOnlyRotatableDigits(int value) {
    string s = to_string(value);
    for (char c : s) {
        if (c == '3' || c == '4' || c == '7') {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000, "a");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        ensuref(hasOnlyRotatableDigits(a[i]),
                "a[%d]=%d contains a digit that is not valid after 180-degree rotation",
                i + 1,
                a[i]);
    }

    inf.readEof();
}
