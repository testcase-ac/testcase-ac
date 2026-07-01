#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 40, "N");
    inf.readSpace();
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readEoln();

    ensuref(a != b, "A and B must be different: A=%d, B=%d", a, b);

    vector<string> friends(n);
    string rowPattern = "[NY]{" + to_string(n) + "}";
    for (int i = 0; i < n; ++i) {
        friends[i] = inf.readToken(rowPattern, "friend_row");
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        ensuref(friends[i][i] == 'N', "diagonal entry (%d, %d) must be N", i + 1, i + 1);
        for (int j = i + 1; j < n; ++j) {
            ensuref(friends[i][j] == friends[j][i],
                    "matrix must be symmetric at (%d, %d) and (%d, %d)",
                    i + 1, j + 1, j + 1, i + 1);
        }
    }

    ensuref(friends[a - 1][b - 1] == 'N', "A and B must not be friends");

    inf.readEof();
}
