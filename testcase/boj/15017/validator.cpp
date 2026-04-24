#include "testlib.h"
#include <string>
#include <set>
using namespace std;

static int parseTime100(const string &s) {
    // s matches [0-9]{1,2}\.[0-9]{2}
    int p = s.find('.');
    int ip = stoi(s.substr(0, p));
    int fp = stoi(s.substr(p+1));
    return ip * 100 + fp;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of runners
    int n = inf.readInt(4, 500, "n");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; i++) {
        // Read runner name
        string name = inf.readToken("[A-Z]{2,20}", "name");
        inf.readSpace();
        // Read a_i and b_i as tokens with exactly two decimals
        string a_s = inf.readToken("[0-9]{1,2}\\.[0-9]{2}", "a_i");
        inf.readSpace();
        string b_s = inf.readToken("[0-9]{1,2}\\.[0-9]{2}", "b_i");
        inf.readEoln();

        // Unique names
        auto res = names.insert(name);
        ensuref(res.second,
                "Duplicate name at line %d: %s",
                i + 2, name.c_str());

        // Parse times in hundredths of a second
        int a100 = parseTime100(a_s);
        int b100 = parseTime100(b_s);

        // Constraints: 8.00 <= b_i <= a_i < 20.00
        ensuref(b100 >= 800,
                "b_i too small at line %d (%s): got %.2f, expected >= 8.00",
                i + 2, name.c_str(), b100 / 100.0);
        ensuref(a100 < 2000,
                "a_i too large at line %d (%s): got %.2f, expected < 20.00",
                i + 2, name.c_str(), a100 / 100.0);
        ensuref(a100 >= b100,
                "a_i < b_i at line %d (%s): a_i=%.2f, b_i=%.2f",
                i + 2, name.c_str(),
                a100 / 100.0, b100 / 100.0);
    }

    inf.readEof();
    return 0;
}
