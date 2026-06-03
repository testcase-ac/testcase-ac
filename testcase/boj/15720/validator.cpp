#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int b = inf.readInt(1, 1000, "B");
    inf.readSpace();
    int c = inf.readInt(1, 1000, "C");
    inf.readSpace();
    int d = inf.readInt(1, 1000, "D");
    inf.readEoln();

    vector<int> counts = {b, c, d};
    for (int line = 0; line < 3; ++line) {
        int count = counts[line];
        for (int i = 0; i < count; ++i) {
            int price = inf.readInt(100, 10000, "price");
            ensuref(price % 100 == 0,
                    "price at menu line %d index %d is not a multiple of 100: %d",
                    line + 2, i + 1, price);
            if (i + 1 < count) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
