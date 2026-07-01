#include "testlib.h"

#include <string>

using namespace std;

int digitValue(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 36, "N");
        inf.readSpace();
        string m = inf.readToken("[0-9A-Z]{1,12}", "M");
        inf.readEoln();

        if (n == 0) {
            ensuref(m == "0", "terminator must be exactly 0 0");
            break;
        }

        ensuref(8 <= n && n <= 36, "N must be between 8 and 36, got %d", n);
        ensuref(m == "0" || m[0] != '0', "M must not have leading zeroes: %s", m.c_str());

        for (int i = 0; i < (int)m.size(); ++i) {
            int digit = digitValue(m[i]);
            ensuref(0 <= digit && digit < n,
                    "M has digit outside base N at position %d: %c for base %d",
                    i + 1,
                    m[i],
                    n);
        }

        ++datasets;
        // CHECK: The statement gives no dataset count bound; cap total lines for practical validation.
        ensuref(datasets <= 100000, "too many datasets: %d", datasets);
    }

    inf.readEof();
}
