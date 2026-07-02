#include "testlib.h"

#include <array>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int n, m;
vector<string> board;

struct Answer {
    int count;
};

bool isLowerLetter(char ch) {
    return 'a' <= ch && ch <= 'z';
}

bool adjacent(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second) == 1;
}

Answer readAnswer(InStream& stream) {
    vector<string> output(n);
    for (int i = 0; i < n; ++i) {
        output[i] = stream.readToken(format("[*+.a-z]{%d,%d}", m, m),
                                     format("row[%d]", i + 1).c_str());
        for (int j = 0; j < m; ++j) {
            if (!isLowerLetter(output[i][j]) && output[i][j] != board[i][j]) {
                stream.quitf(_wa,
                             "row %d column %d is '%c', expected original '%c' or a lowercase letter",
                             i + 1,
                             j + 1,
                             output[i][j],
                             board[i][j]);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after board");
    }

    vector<vector<int>> seen(n, vector<int>(m, 0));
    int trominoes = 0;
    const array<int, 4> dr = {-1, 0, 1, 0};
    const array<int, 4> dc = {0, 1, 0, -1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (!isLowerLetter(output[r][c]) || seen[r][c]) {
                continue;
            }

            char label = output[r][c];
            vector<pair<int, int>> cells;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = 1;

            while (!q.empty()) {
                auto [vr, vc] = q.front();
                q.pop();
                cells.push_back({vr, vc});

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = vr + dr[dir];
                    int nc = vc + dc[dir];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m || seen[nr][nc] || output[nr][nc] != label) {
                        continue;
                    }
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }

            if ((int)cells.size() != 3) {
                stream.quitf(_wa,
                             "component labeled '%c' containing row %d column %d has size %d instead of 3",
                             label,
                             r + 1,
                             c + 1,
                             (int)cells.size());
            }

            int centerIndex = -1;
            for (int i = 0; i < 3; ++i) {
                int degree = 0;
                for (int j = 0; j < 3; ++j) {
                    if (i != j && adjacent(cells[i], cells[j])) {
                        ++degree;
                    }
                }
                if (degree == 2) {
                    centerIndex = i;
                }
            }

            if (centerIndex == -1) {
                stream.quitf(_wa,
                             "component labeled '%c' containing row %d column %d is not a tromino",
                             label,
                             r + 1,
                             c + 1);
            }

            vector<pair<int, int>> arms;
            for (int i = 0; i < 3; ++i) {
                if (i != centerIndex) {
                    arms.push_back(cells[i]);
                }
            }

            auto center = cells[centerIndex];
            bool straight = arms[0].first == arms[1].first || arms[0].second == arms[1].second;
            char centerCell = board[center.first][center.second];
            if (straight) {
                if (centerCell != '+') {
                    stream.quitf(_wa,
                                 "I-shaped tromino center at row %d column %d is on '%c', expected '+'",
                                 center.first + 1,
                                 center.second + 1,
                                 centerCell);
                }
            } else {
                if (centerCell != '*' && centerCell != '+') {
                    stream.quitf(_wa,
                                 "L-shaped tromino center at row %d column %d is on '%c', expected '*' or '+'",
                                 center.first + 1,
                                 center.second + 1,
                                 centerCell);
                }
            }

            for (auto arm : arms) {
                if (board[arm.first][arm.second] != '.') {
                    stream.quitf(_wa,
                                 "non-center square at row %d column %d is on '%c', expected '.'",
                                 arm.first + 1,
                                 arm.second + 1,
                                 board[arm.first][arm.second]);
                }
            }

            ++trominoes;
        }
    }

    return {trominoes};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    board.resize(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count < jury.count) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d", jury.count, participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d", jury.count, participant.count);
    }

    quitf(_ok, "answer=%d", participant.count);
}
