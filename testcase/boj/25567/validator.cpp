#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_TOTAL = 200000;

    int n = inf.readInt(1, MAX_TOTAL, "N");
    inf.readEoln();

    vector<int> seen(MAX_TOTAL + 1, 0);
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        int len = inf.readInt(1, MAX_TOTAL, "L_i");
        ensuref(total + len <= MAX_TOTAL,
                "sum of L_i exceeds %d after line %d", MAX_TOTAL, i);
        total += len;

        for (int j = 1; j <= len; ++j) {
            inf.readSpace();
            int person = inf.readInt(1, MAX_TOTAL, "a_ij");
            ensuref(!seen[person], "duplicate person id %d", person);
            seen[person] = 1;
        }
        inf.readEoln();
    }

    for (int person = 1; person <= MAX_TOTAL; ++person) {
        if (seen[person]) {
            ensuref(person <= total,
                    "person id %d exceeds total number of people %d", person, total);
        }
    }

    int q = inf.readInt(1, MAX_TOTAL, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int op = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        int a = inf.readInt(1, total, "a");
        inf.readSpace();
        int b = inf.readInt(1, total, "b");
        inf.readEoln();
        (void)op;
        (void)a;
        (void)b;
    }

    inf.readEof();
}
