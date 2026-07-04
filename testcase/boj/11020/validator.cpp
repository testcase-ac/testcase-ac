#include "testlib.h"

#include <cmath>
#include <set>
#include <string>

using namespace std;

string readDecimalToken(const char* name) {
    string token = inf.readToken("[0-9]{1,32}|[0-9]{1,32}\\.[0-9]{1,32}", name);

    size_t dot = token.find('.');
    string integerPart = dot == string::npos ? token : token.substr(0, dot);
    ensuref(integerPart == "0" || integerPart[0] != '0',
            "%s has leading zeroes: %s", name, token.c_str());

    return token;
}

long double parseDecimal(const string& token) {
    return stold(token);
}

string normalizeDecimal(string token) {
    size_t dot = token.find('.');
    if (dot != string::npos) {
        while (!token.empty() && token.back() == '0') {
            token.pop_back();
        }
        if (!token.empty() && token.back() == '.') {
            token.pop_back();
        }
    }
    return token;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200, "N");
        inf.readEoln();

        // CHECK: K has no stated upper bound; cap aggregate nuggets at one largest data set.
        totalN += n;
        ensuref(totalN <= 200, "sum of N exceeds practical cap: %d", totalN);

        set<pair<string, string>> points;
        for (int i = 1; i <= n; ++i) {
            string alphaToken = readDecimalToken("alpha");
            inf.readSpace();
            string radiusToken = readDecimalToken("r");
            inf.readEoln();

            long double alpha = parseDecimal(alphaToken);
            long double radius = parseDecimal(radiusToken);
            long double twoPi = 2.0L * acosl(-1.0L);

            ensuref(0.0L <= alpha && alpha < twoPi,
                    "alpha out of range at nugget %d: %s", i, alphaToken.c_str());
            ensuref(0.0L < radius && radius <= 1.0L,
                    "r out of range at nugget %d: %s", i, radiusToken.c_str());

            pair<string, string> point = {
                normalizeDecimal(alphaToken),
                normalizeDecimal(radiusToken),
            };
            ensuref(points.insert(point).second,
                    "duplicate nugget position at nugget %d: %s %s",
                    i, alphaToken.c_str(), radiusToken.c_str());
        }
    }

    inf.readEof();
}
