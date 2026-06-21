#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 11, "n");
    inf.readEoln();

    for (int box = 1; box <= 2; ++box) {
        for (int i = 1; i <= n; ++i) {
            int s = inf.readInt(-11, 11, "s");
            inf.readSpace();
            int e = inf.readInt(-11, 11, "e");
            ensuref(s < e, "box %d dimension %d must satisfy s < e, got %d >= %d",
                    box, i, s, e);

            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
