#include "testlib.h"

#include <cctype>
#include <cstdlib>
#include <set>
#include <string>
#include <utility>

using namespace std;

double readBoundedDecimal(double low, double high, const string& name) {
    string token = inf.readToken("[0-9][0-9.]*", name);

    int dotCount = 0;
    int dotPos = -1;
    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == '.') {
            ++dotCount;
            dotPos = i;
        } else {
            ensuref(isdigit((unsigned char)token[i]),
                    "%s contains a non-digit character: %s",
                    name.c_str(),
                    token.c_str());
        }
    }

    ensuref(dotCount <= 1, "%s has more than one decimal point: %s", name.c_str(), token.c_str());
    ensuref(dotPos != 0 && dotPos != (int)token.size() - 1,
            "%s has an invalid decimal form: %s",
            name.c_str(),
            token.c_str());

    int integerLength = dotPos == -1 ? (int)token.size() : dotPos;
    ensuref(integerLength == 1 || token[0] != '0',
            "%s has a leading zero in the integer part: %s",
            name.c_str(),
            token.c_str());

    char* end = nullptr;
    double value = strtod(token.c_str(), &end);
    ensuref(end != nullptr && *end == '\0', "%s is not a valid decimal: %s", name.c_str(), token.c_str());
    ensuref(low <= value && value <= high,
            "%s=%s is outside [%.10g, %.10g]",
            name.c_str(),
            token.c_str(),
            low,
            high);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int kDatasets = inf.readInt(1, 100000, "K");
    inf.readEoln();

    long long totalRows = 0;
    for (int tc = 1; tc <= kDatasets; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100, "n");
        inf.readSpace();
        int r = inf.readInt(0, n * n, "r");
        inf.readSpace();
        int m = inf.readInt(0, 10000, "m");
        inf.readSpace();
        int eraseLimit = inf.readInt(0, m, "k");
        (void)eraseLimit;
        inf.readEoln();

        totalRows += r + m;
        // CHECK: K has no statement upper bound; cap aggregate rows to one
        // largest dataset scale so validation cannot accept impractically huge input.
        ensuref(totalRows <= 20000, "sum of relationship and event rows exceeds 20000 at dataset %d", tc);

        set<pair<int, int>> relationships;
        for (int i = 1; i <= r; ++i) {
            int u = inf.readInt(1, n, "u_i");
            inf.readSpace();
            int v = inf.readInt(1, n, "v_i");
            inf.readSpace();
            readBoundedDecimal(0.0, 1.0, "p_i");
            inf.readEoln();

            ensuref(relationships.insert({u, v}).second,
                    "duplicate relationship pair in dataset %d at row %d: %d %d",
                    tc,
                    i,
                    u,
                    v);
        }

        for (int i = 1; i <= m; ++i) {
            inf.readInt(1, n, "u_i");
            inf.readSpace();
            inf.readInt(1, n, "v_i");
            inf.readSpace();
            readBoundedDecimal(0.0, 10000.0, "d_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
