#include "testlib.h"
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int normalizeMod(int value) {
    int result = value % 7;
    if (result < 0) result += 7;
    return result;
}

int makeValue(int residue, set<int>& used, int mode) {
    vector<int> bases;
    if (mode == 0) {
        bases = {-14, -7, 0, 7, 14};
    } else if (mode == 1) {
        bases = {-100000, -99995, -35, 0, 35, 99995, 100000};
    } else {
        bases = {-210, -70, -21, 0, 21, 70, 210};
    }
    shuffle(bases.begin(), bases.end());

    for (int base : bases) {
        for (int delta = 0; delta < 7; ++delta) {
            int value = base + delta;
            if (value < -100000 || value > 100000) continue;
            if (normalizeMod(value) == residue && used.insert(value).second) {
                return value;
            }
        }
    }

    while (true) {
        int quotient = rnd.next(-14285, 14285);
        int value = quotient * 7 + residue;
        if (value < -100000 || value > 100000) continue;
        if (used.insert(value).second) return value;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> variables = {"B", "E", "S", "I", "G", "O", "M"};
    int mode = rnd.next(0, 3);

    vector<pair<string, int>> rows;
    for (const string& variable : variables) {
        int count;
        if (mode == 0) {
            count = 1;
        } else if (mode == 1) {
            count = rnd.next(1, 4);
        } else if (mode == 2) {
            count = rnd.next(2, 8);
        } else {
            count = rnd.next(1, 12);
        }

        set<int> used;
        int favoredResidue = rnd.next(0, 6);
        int valueMode = rnd.next(0, 2);
        for (int i = 0; i < count; ++i) {
            int residue;
            if (mode == 0) {
                residue = rnd.next(0, 6);
            } else if (i == 0 || rnd.next(0, 99) < 55) {
                residue = favoredResidue;
            } else {
                residue = rnd.next(0, 6);
            }
            rows.push_back({variable, makeValue(residue, used, valueMode)});
        }
    }

    shuffle(rows.begin(), rows.end());

    println((int)rows.size());
    for (const auto& row : rows) {
        println(row.first, row.second);
    }

    return 0;
}
