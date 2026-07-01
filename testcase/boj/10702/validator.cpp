#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int parseFormationPart(const string& formation, int& pos, const char* name) {
    int start = pos;
    while (pos < int(formation.size()) && formation[pos] >= '0' && formation[pos] <= '9') {
        ++pos;
    }

    ensuref(start < pos, "%s is missing in formation: %s", name, formation.c_str());
    ensuref(pos - start == 1 || formation[start] != '0',
            "%s has a leading zero in formation: %s", name, formation.c_str());

    int value = 0;
    for (int i = start; i < pos; ++i) {
        value = value * 10 + (formation[i] - '0');
    }
    ensuref(0 <= value && value <= 10, "%s is outside [0, 10]: %d", name, value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string formation = inf.readToken("[0-9]{1,2}-[0-9]{1,2}-[0-9]{1,2}", "formation");
        inf.readEoln();

        int pos = 0;
        int o = parseFormationPart(formation, pos, "O");
        ensuref(pos < int(formation.size()) && formation[pos] == '-',
                "missing first hyphen in formation: %s", formation.c_str());
        ++pos;
        int v = parseFormationPart(formation, pos, "V");
        ensuref(pos < int(formation.size()) && formation[pos] == '-',
                "missing second hyphen in formation: %s", formation.c_str());
        ++pos;
        int offense = parseFormationPart(formation, pos, "N");
        ensuref(pos == int(formation.size()), "extra characters in formation: %s", formation.c_str());

        // CHECK: The statement says the three formation values are positive, but the official
        // samples contain 10-0-0, so zero is accepted for individual line counts.
        ensuref(o + v + offense == 10, "formation values must sum to 10: %s", formation.c_str());
    }

    int m = inf.readInt(10, 22, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        string lines = inf.readToken("[OVN]{1,3}", "player_lines");
        inf.readEoln();

        set<char> seen;
        for (char line : lines) {
            ensuref(seen.insert(line).second, "duplicate player line '%c' at player %d", line, i + 1);
        }
    }

    inf.readEof();
}
