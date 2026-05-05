#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(1, 5000, "k");
    inf.readEoln();

    int ship_lines = 0;
    int order_lines = 0;

    for (int i = 0; i < k; ++i) {
        int type = inf.readInt(0, 1, "type");
        inf.readSpace();
        if (type == 0) {
            // Order: 0 a b
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readEoln();

            ensuref(a != b, "Order line %d: a == b (%d == %d)", i+2, a, b);
            order_lines++;
        } else {
            // Ship: 1 c d e
            int c = inf.readInt(1, n, "c");
            inf.readSpace();
            int d = inf.readInt(1, n, "d");
            inf.readSpace();
            int e = inf.readInt(1, 1000000, "e");
            inf.readEoln();

            ensuref(c != d, "Ship line %d: c == d (%d == %d)", i+2, c, d);
            ship_lines++;
        }
    }

    ensuref(ship_lines <= 1000, "Number of ship lines (%d) exceeds 1000", ship_lines);

    inf.readEof();
}
