#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        string a = inf.readLine("[0-9?]{1,50}", "A");
        if (a == "0") {
            break;
        }

        ++datasets;
        setTestCase(datasets);
        ensuref(datasets < 100, "number of datasets must be less than 100");

        string b = inf.readLine("[0-9?]{1,50}", "B");
        string c = inf.readLine("[0-9?]{1,50}", "C");

        ensuref(a[0] != '0', "A must not start with 0");
        ensuref(b[0] != '0', "B must not start with 0");
        ensuref(c[0] != '0', "C must not start with 0");

        ensuref(a.size() == b.size() && b.size() == c.size(),
                "A, B, and C must have equal lengths");

        bool hasQuestion = false;
        for (char ch : a + b + c) {
            if (ch == '?') {
                hasQuestion = true;
                break;
            }
        }
        ensuref(hasQuestion, "each dataset must contain at least one question mark");
    }

    inf.readEof();
}
