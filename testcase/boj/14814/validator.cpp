#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const int SCALE = 10000;

int readFixed4(const string& name, int upper) {
    string token = inf.readToken("[0-9]{1,2}\\.[0-9]{4}", name);

    ensuref(token.size() >= 6, "%s must have exactly four decimal places", name.c_str());
    size_t dot = token.find('.');
    ensuref(dot != string::npos, "%s must contain a decimal point", name.c_str());
    ensuref(token.size() == dot + 5, "%s must have exactly four decimal places", name.c_str());
    ensuref(dot == 1 || token[0] != '0', "%s has a leading zero: %s", name.c_str(), token.c_str());

    int whole = 0;
    for (size_t i = 0; i < dot; ++i) {
        ensuref('0' <= token[i] && token[i] <= '9', "%s has an invalid digit: %s", name.c_str(), token.c_str());
        whole = whole * 10 + (token[i] - '0');
    }

    int frac = 0;
    for (size_t i = dot + 1; i < token.size(); ++i) {
        ensuref('0' <= token[i] && token[i] <= '9', "%s has an invalid digit: %s", name.c_str(), token.c_str());
        frac = frac * 10 + (token[i] - '0');
    }

    int value = whole * SCALE + frac;
    ensuref(value <= upper, "%s is greater than the allowed maximum", name.c_str());
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50, "N");
        inf.readSpace();
        inf.readInt(1, n, "K");
        inf.readEoln();

        int u = readFixed4("U", n * SCALE);
        inf.readEoln();

        vector<int> probabilities;
        probabilities.reserve(n);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int p = readFixed4("P_i", SCALE);
            probabilities.push_back(p);
            sum += p;
        }
        inf.readEoln();

        ensuref(u <= 1LL * n * SCALE - sum,
                "test case %d has more training units than can be used", tc);
    }

    inf.readEof();
}
