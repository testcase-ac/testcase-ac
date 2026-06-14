#include "testlib.h"

#include <cstdlib>
#include <string>

using namespace std;

long double readProbability(const string& name) {
    string token = inf.readToken("[0-9]{1,32}|[0-9]{1,32}\\.[0-9]{1,32}", name.c_str());

    size_t dot = token.find('.');
    string whole = dot == string::npos ? token : token.substr(0, dot);
    string frac = dot == string::npos ? "" : token.substr(dot + 1);

    ensuref(whole == "0" || whole == "1", "%s integer part is outside [0, 1]: %s",
            name.c_str(), token.c_str());
    ensuref(whole.size() == 1, "%s has a leading zero: %s", name.c_str(), token.c_str());

    if (whole == "1") {
        for (char c : frac) {
            ensuref(c == '0', "%s is greater than 1: %s", name.c_str(), token.c_str());
        }
    }

    return strtold(token.c_str(), nullptr);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean statement omits P's bound, while the English original gives 1 <= P <= 15.
    int p = inf.readInt(1, 15, "P");
    inf.readEoln();

    for (int tc = 1; tc <= p; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        long double l = readProbability("L");
        inf.readSpace();
        long double r = readProbability("R");
        inf.readEoln();

        ensuref(l + r <= 1.0L + 1e-18L, "L + R must be at most 1, got %.21Lf", l + r);
    }

    inf.readEof();
}
