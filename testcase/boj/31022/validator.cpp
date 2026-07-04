#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static bool canSplitIntoGrades(const string& s, int g) {
    int n = static_cast<int>(s.size());
    vector<vector<int>> possible(n + 1, vector<int>(g + 1, 0));
    possible[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int used = 0; used < g; ++used) {
            if (!possible[i][used]) {
                continue;
            }
            for (int len = 1; len <= 3 && i + len <= n; ++len) {
                string token = s.substr(i, len);
                if (token.size() > 1 && token[0] == '0') {
                    continue;
                }
                int value = stoi(token);
                if (value <= 100) {
                    possible[i + len][used + 1] = 1;
                }
            }
        }
    }

    return possible[n][g] != 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        int g = inf.readInt(1, 25, "G");
        inf.readSpace();
        string s = inf.readToken("[0-9]{1,75}", "corrupted_grades");
        inf.readEoln();

        ensuref(static_cast<int>(s.size()) <= 3 * g,
                "corrupted grade string length %d exceeds 3 * G = %d",
                static_cast<int>(s.size()), 3 * g);
        ensuref(canSplitIntoGrades(s, g),
                "corrupted grade string cannot be split into exactly %d valid grades", g);
    }

    inf.readEof();
}
