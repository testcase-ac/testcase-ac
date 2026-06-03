#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 70, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string p = inf.readLine("[^]{1,20}", "P_i");
        for (char c : p) {
            ensuref(!isspace(static_cast<unsigned char>(c)),
                    "P_%d contains whitespace", i);
        }

        int k = inf.readInt(12, 400, "K_i");
        inf.readSpace();
        int m = inf.readInt(1, 10000, "M_i");
        inf.readEoln();

        (void)p;
        (void)k;
        (void)m;
    }

    inf.readEof();
}
