#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int parseMass(const string& token) {
    ensuref(token.size() >= 3, "mass token too short: %s", token.c_str());

    string digits = token.substr(2);
    while (digits.size() < 5) {
        digits.push_back('0');
    }

    int value = 0;
    for (char digit : digits) {
        value = value * 10 + (digit - '0');
    }
    ensuref(1 <= value && value <= 99999,
            "mass must be between 0.0 and 1.0 exclusive: %s", token.c_str());
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        set<int> masses;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            string mass = inf.readToken("0[.][0-9]{1,5}", "naomi_mass");
            int value = parseMass(mass);
            ensuref(masses.insert(value).second,
                    "duplicate mass in case %d: %s", tc, mass.c_str());
        }
        inf.readEoln();

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            string mass = inf.readToken("0[.][0-9]{1,5}", "ken_mass");
            int value = parseMass(mass);
            ensuref(masses.insert(value).second,
                    "duplicate mass in case %d: %s", tc, mass.c_str());
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
