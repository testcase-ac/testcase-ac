#include "testlib.h"

#include <vector>

using namespace std;

int n, m;

struct Answer {
    int k;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(1, 1000000, "K");
    vector<vector<int>> board(n, vector<int>(m));
    vector<int> used(k + 1, 0);

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            board[y][x] = stream.readInt(1, k, format("paper[%d][%d]", y + 1, x + 1).c_str());
            used[board[y][x]] = 1;
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    for (int value = 1; value <= k; ++value) {
        if (!used[value]) {
            stream.quitf(_wa, "paper type %d is claimed but unused", value);
        }
    }

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dy == 0 && dx == 0) {
                        continue;
                    }
                    int ny = y + dy;
                    int nx = x + dx;
                    if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
                        continue;
                    }
                    if (board[y][x] == board[ny][nx]) {
                        stream.quitf(_wa,
                                     "adjacent cells (%d, %d) and (%d, %d) both use paper type %d",
                                     y + 1, x + 1, ny + 1, nx + 1, board[y][x]);
                    }
                }
            }
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "N");
    m = inf.readInt(1, 1000, "M");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.k > jury.k) {
        quitf(_wa, "participant uses more paper types than jury: jury=%d participant=%d", jury.k, participant.k);
    }
    if (participant.k < jury.k) {
        quitf(_fail, "participant found a better answer: jury=%d participant=%d", jury.k, participant.k);
    }
    quitf(_ok, "answer uses %d paper types", participant.k);
}
