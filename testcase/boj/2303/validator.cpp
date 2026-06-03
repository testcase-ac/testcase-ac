#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 5; ++j) {
            inf.readInt(1, 10, "card");
            if (j < 5) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
