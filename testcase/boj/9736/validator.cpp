#include "testlib.h"

#include <string>

using namespace std;

struct Element {
    int a;
    int b;
};

Element readElement(const string& name, int m, int n) {
    string token = inf.readToken("a[0-9]{1,4}b[0-9]{1,4}", name);
    size_t bPos = token.find('b');
    string aPart = token.substr(1, bPos - 1);
    string bPart = token.substr(bPos + 1);

    ensuref(aPart == "0" || aPart[0] != '0',
            "%s has leading zero in a exponent: %s", name.c_str(), token.c_str());
    ensuref(bPart == "0" || bPart[0] != '0',
            "%s has leading zero in b exponent: %s", name.c_str(), token.c_str());

    int a = stoi(aPart);
    int b = stoi(bPart);
    ensuref(0 <= a && a < m, "%s has a exponent %d outside [0, %d)",
            name.c_str(), a, m);
    ensuref(0 <= b && b < n, "%s has b exponent %d outside [0, %d)",
            name.c_str(), b, n);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int setCount = 0;
    long long totalQueries = 0;
    while (true) {
        // CHECK: The statement names problemID as a token but gives no length
        // or alphabet; accept printable non-whitespace IDs with a practical cap.
        string problemId = inf.readToken("[!-~]{1,20}", "problemID");
        inf.readSpace();

        if (problemId == "ZZ") {
            inf.readInt(0, 0, "terminator_m");
            inf.readSpace();
            inf.readInt(0, 0, "terminator_n");
            inf.readSpace();
            inf.readInt(0, 0, "terminator_p");
            inf.readEoln();
            break;
        }

        ++setCount;
        setTestCase(setCount);
        int m = inf.readInt(2, 1000, "m");
        inf.readSpace();
        int n = inf.readInt(2, 1000, "n");
        inf.readSpace();
        // CHECK: The statement does not bound p; cap each set and total input
        // size to keep validator-backed generated tests practical.
        int p = inf.readInt(1, 100000, "p");
        inf.readEoln();

        totalQueries += p;
        // CHECK: The statement does not bound the number of problem sets; cap
        // aggregate multiplication problems to a practical input size.
        ensuref(totalQueries <= 100000, "too many multiplication problems: %lld",
                totalQueries);

        for (int i = 0; i < p; ++i) {
            string lhsName = "lhs_" + to_string(i + 1);
            string rhsName = "rhs_" + to_string(i + 1);
            readElement(lhsName, m, n);
            inf.readSpace();
            readElement(rhsName, m, n);
            inf.readEoln();
        }
    }

    ensuref(setCount > 0, "input must contain at least one problem set before ZZ");
    inf.readEof();
}
