#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and q
    int n = inf.readInt(1, 500000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 250000, "q");
    inf.readEoln();

    // Read array a
    vector<int> a = inf.readInts(n, 0, n, "a_i");
    inf.readEoln();

    int update_cnt = 0;

    for (int op = 0; op < q; ++op) {
        std::string type = inf.readToken("[!?]", "operation type");
        if (type == "?") {
            inf.readSpace();
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(l, n, "r");
            inf.readEoln();
        } else if (type == "!") {
            inf.readSpace();
            int i = inf.readInt(1, n, "i");
            inf.readSpace();
            int x = inf.readInt(0, n, "x");
            inf.readEoln();
            update_cnt++;
        } else {
            ensuref(false, "Unknown operation type: %s", type.c_str());
        }
    }

    ensuref(update_cnt <= 50000, "Total number of update operations (!) is %d, which exceeds the limit 50000", update_cnt);

    inf.readEof();
}
