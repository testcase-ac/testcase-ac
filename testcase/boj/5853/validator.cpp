#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        std::string type = inf.readToken("A|L", "event_type");
        inf.readSpace();

        if (type == "A") {
            inf.readInt(1, n, "p");
        } else {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(a, n, "b");
        }
        inf.readEoln();
    }

    inf.readEof();
}
