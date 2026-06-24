#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, k;

struct Answer {
    bool possible;
};

string readDecision(InStream& stream, TResult verdict) {
    string token = stream.readToken("[A-Z]+", "decision");
    if (token != "YES" && token != "NO") {
        stream.quitf(verdict, "decision must be YES or NO, found '%s'", token.c_str());
    }
    return token;
}

Answer readAnswer(InStream& stream, TResult verdict) {
    string decision = readDecision(stream, verdict);
    if (decision == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(verdict, "extra output after NO");
        }
        return {false};
    }

    vector<string> grid(n);
    int filled = 0;
    vector<int> row(n, 0), col(n, 0);
    int diagDown = 0, diagUp = 0;

    for (int i = 0; i < n; ++i) {
        grid[i] = stream.readToken(format("[.#]{%d}", n), format("row[%d]", i + 1).c_str());
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#') {
                ++filled;
                ++row[i];
                ++col[j];
                if (i == j) {
                    ++diagDown;
                }
                if (i + j == n - 1) {
                    ++diagUp;
                }
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after grid");
    }

    if (filled != k) {
        stream.quitf(verdict, "expected exactly %d filled cells, found %d", k, filled);
    }
    for (int i = 0; i < n; ++i) {
        if (row[i] == n) {
            stream.quitf(verdict, "row %d is a bingo line", i + 1);
        }
        if (col[i] == n) {
            stream.quitf(verdict, "column %d is a bingo line", i + 1);
        }
    }
    if (diagDown == n) {
        stream.quitf(verdict, "main diagonal is a bingo line");
    }
    if (diagUp == n) {
        stream.quitf(verdict, "anti-diagonal is a bingo line");
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (jury.possible == participant.possible) {
        quitf(_ok, "%s", participant.possible ? "valid grid" : "impossible");
    }
    if (jury.possible) {
        quitf(_wa, "jury provides a valid grid, but participant answered NO");
    }
    quitf(_fail, "participant provides a valid grid, but jury answered NO");
}
