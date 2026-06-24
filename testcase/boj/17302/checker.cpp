#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m;
vector<string> initialGrid;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string status = stream.readToken();
    if (status == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {false};
    }
    if (status != "1") {
        stream.quitf(_wa, "answer status must be -1 or 1, found '%s'", status.c_str());
    }

    vector<string> ops(n);
    string pattern = "[123]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        ops[i] = stream.readToken(pattern, format("operations row %d", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operations grid");
    }

    vector<vector<unsigned char>> flipped(n, vector<unsigned char>(m, 0));
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            char op = ops[r][c];
            if (op == '3') {
                flipped[r][c] ^= 1;
            }
            if (op == '2' || op == '3') {
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (0 <= nr && nr < n && 0 <= nc && nc < m) {
                        flipped[nr][nc] ^= 1;
                    }
                }
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            bool black = initialGrid[r][c] == 'B';
            if (flipped[r][c]) {
                black = !black;
            }
            if (black) {
                stream.quitf(_wa, "cell (%d, %d) remains black", r + 1, c + 1);
            }
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    initialGrid.resize(n);
    for (int i = 0; i < n; ++i) {
        initialGrid[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provided a valid witness while jury says impossible");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid witness but participant says impossible");
    }

    quitf(_ok, "%s", participant.possible ? "valid witness" : "both answers are impossible");
}
