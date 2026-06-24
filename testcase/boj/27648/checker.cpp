#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m, k;

struct Answer {
    bool possible;
    vector<vector<int>> a;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("YES|NO", "verdict");

    Answer result;
    result.possible = verdict == "YES";

    if (!result.possible) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return result;
    }

    result.a.assign(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result.a[i][j] = stream.readInt(1, k, format("a[%d][%d]", i + 1, j + 1).c_str());
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after array");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n && result.a[i][j] >= result.a[i + 1][j]) {
                stream.quitf(_wa,
                             "a[%d][%d]=%d is not less than a[%d][%d]=%d",
                             i + 1,
                             j + 1,
                             result.a[i][j],
                             i + 2,
                             j + 1,
                             result.a[i + 1][j]);
            }
            if (j + 1 < m && result.a[i][j] >= result.a[i][j + 1]) {
                stream.quitf(_wa,
                             "a[%d][%d]=%d is not less than a[%d][%d]=%d",
                             i + 1,
                             j + 1,
                             result.a[i][j],
                             i + 1,
                             j + 2,
                             result.a[i][j + 1]);
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible) {
        if (participant.possible) {
            quitf(_fail, "participant found a valid array but jury says NO");
        }
        quitf(_ok, "both answers are NO");
    }

    if (!participant.possible) {
        quitf(_wa, "jury has a valid array but participant says NO");
    }

    quitf(_ok, "valid increasing array");
}
