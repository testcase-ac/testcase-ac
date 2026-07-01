#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string label(int id, int sign) {
    string s;
    s += char('A' + id);
    s += sign ? '+' : '-';
    return s;
}

string opposite(const string& s) {
    if (s == "00") {
        return s;
    }
    string t = s;
    t[1] = (t[1] == '+') ? '-' : '+';
    return t;
}

string molecule(const vector<string>& sides) {
    string s;
    for (const string& side : sides) {
        s += side;
    }
    return s;
}

string randomLabel(int letters, int zeroPercent) {
    if (rnd.next(1, 100) <= zeroPercent) {
        return "00";
    }
    return label(rnd.next(0, letters - 1), rnd.next(0, 1));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int letters = rnd.next(1, 8);
    vector<string> molecules;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            vector<string> sides(4, "00");
            int filled = rnd.next(0, 3);
            for (int j = 0; j < filled; ++j) {
                sides[j] = label(rnd.next(0, letters - 1), 0);
            }
            shuffle(sides.begin(), sides.end());
            molecules.push_back(molecule(sides));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            vector<string> sides;
            for (int j = 0; j < 4; ++j) {
                sides.push_back(randomLabel(letters, rnd.next(15, 60)));
            }
            molecules.push_back(molecule(sides));
        }
    } else if (mode == 2) {
        int cycleLen = rnd.next(1, min(letters, 6));
        for (int i = 0; i < cycleLen; ++i) {
            string from = label(i, rnd.next(0, 1));
            string to = opposite(label((i + 1) % cycleLen, rnd.next(0, 1)));
            vector<string> sides = {from, to, "00", randomLabel(letters, 70)};
            shuffle(sides.begin(), sides.end());
            molecules.push_back(molecule(sides));
        }
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            vector<string> sides;
            for (int j = 0; j < 4; ++j) {
                sides.push_back(randomLabel(letters, rnd.next(20, 80)));
            }
            molecules.push_back(molecule(sides));
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 24);
        for (int i = 0; i < n; ++i) {
            int first = rnd.next(0, letters - 1);
            int second = rnd.next(0, letters - 1);
            vector<string> sides = {
                label(first, rnd.next(0, 1)),
                opposite(label(second, rnd.next(0, 1))),
                randomLabel(letters, 45),
                randomLabel(letters, 45),
            };
            shuffle(sides.begin(), sides.end());
            molecules.push_back(molecule(sides));
        }
    } else {
        int n = rnd.next(16, 40);
        letters = rnd.next(12, 26);
        for (int i = 0; i < n; ++i) {
            vector<string> sides;
            for (int j = 0; j < 4; ++j) {
                sides.push_back(randomLabel(letters, rnd.next(0, 35)));
            }
            molecules.push_back(molecule(sides));
        }
    }

    shuffle(molecules.begin(), molecules.end());
    println(int(molecules.size()));
    println(molecules);
    return 0;
}
