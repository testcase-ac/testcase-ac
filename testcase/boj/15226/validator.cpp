#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string h0 = inf.readToken("[0-9]{1,1001}", "h0");
    inf.readEoln();

    ensuref(h0 != "0", "h0 must be at least 1");
    ensuref(h0.size() == 1 || h0[0] != '0', "h0 has a leading zero");
    if (h0.size() == 1001) {
        ensuref(h0[0] == '1', "h0 exceeds 10^1000");
        for (int i = 1; i < 1001; ++i) {
            ensuref(h0[i] == '0', "h0 exceeds 10^1000");
        }
    }

    inf.readEof();
}
