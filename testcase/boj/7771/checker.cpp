#include "testlib.h"

#include <algorithm>
#include <array>
#include <queue>
#include <string>
#include <vector>

using namespace std;

array<array<int, 10>, 10> shotRound;

struct Answer {
    int complexity;
};

Answer readAnswer(InStream& stream) {
    vector<string> board(10);
    for (int r = 0; r < 10; ++r) {
        board[r] = stream.readToken("[.#]{10}", format("row[%d]", r + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after board");
    }

    vector<vector<int>> component(10, vector<int>(10, -1));
    vector<int> lengths;
    int complexity = 0;

    const int dr4[4] = {-1, 0, 1, 0};
    const int dc4[4] = {0, 1, 0, -1};

    for (int sr = 0; sr < 10; ++sr) {
        for (int sc = 0; sc < 10; ++sc) {
            if (board[sr][sc] != '#' || component[sr][sc] != -1) {
                continue;
            }

            int id = lengths.size();
            vector<pair<int, int>> cells;
            queue<pair<int, int>> q;
            q.push({sr, sc});
            component[sr][sc] = id;

            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                cells.push_back({r, c});
                complexity = max(complexity, shotRound[r][c]);

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr4[d];
                    int nc = c + dc4[d];
                    if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10) {
                        continue;
                    }
                    if (board[nr][nc] == '#' && component[nr][nc] == -1) {
                        component[nr][nc] = id;
                        q.push({nr, nc});
                    }
                }
            }

            bool sameRow = true;
            bool sameCol = true;
            for (auto [r, c] : cells) {
                sameRow = sameRow && (r == cells[0].first);
                sameCol = sameCol && (c == cells[0].second);
            }
            if (!sameRow && !sameCol) {
                stream.quitf(_wa, "ship containing row %d column %d is not straight", sr + 1, sc + 1);
            }
            if ((int)cells.size() > 4) {
                stream.quitf(_wa, "ship containing row %d column %d has length %d", sr + 1, sc + 1,
                             (int)cells.size());
            }

            if (sameRow) {
                vector<int> cols;
                for (auto [r, c] : cells) {
                    cols.push_back(c);
                }
                sort(cols.begin(), cols.end());
                for (int i = 1; i < (int)cols.size(); ++i) {
                    if (cols[i] != cols[i - 1] + 1) {
                        stream.quitf(_wa, "horizontal ship containing row %d column %d is not consecutive",
                                     sr + 1, sc + 1);
                    }
                }
            } else {
                vector<int> rows;
                for (auto [r, c] : cells) {
                    rows.push_back(r);
                }
                sort(rows.begin(), rows.end());
                for (int i = 1; i < (int)rows.size(); ++i) {
                    if (rows[i] != rows[i - 1] + 1) {
                        stream.quitf(_wa, "vertical ship containing row %d column %d is not consecutive",
                                     sr + 1, sc + 1);
                    }
                }
            }

            lengths.push_back((int)cells.size());
        }
    }

    array<int, 5> count{};
    for (int length : lengths) {
        if (length < 1 || length > 4) {
            stream.quitf(_wa, "ship has invalid length %d", length);
        }
        ++count[length];
    }
    if (count[1] != 4 || count[2] != 3 || count[3] != 2 || count[4] != 1) {
        stream.quitf(_wa, "fleet is invalid: length1=%d length2=%d length3=%d length4=%d",
                     count[1], count[2], count[3], count[4]);
    }

    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            if (board[r][c] != '#') {
                continue;
            }
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10 || board[nr][nc] != '#') {
                        continue;
                    }
                    if (component[nr][nc] != component[r][c]) {
                        stream.quitf(_wa, "ships at row %d column %d and row %d column %d touch",
                                     r + 1, c + 1, nr + 1, nc + 1);
                    }
                }
            }
        }
    }

    return {complexity};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            shotRound[r][c] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.complexity < jury.complexity) {
        quitf(_wa, "jury has better complexity: jury=%d participant=%d",
              jury.complexity, participant.complexity);
    }
    if (participant.complexity > jury.complexity) {
        quitf(_fail, "participant found better complexity: jury=%d participant=%d",
              jury.complexity, participant.complexity);
    }
    quitf(_ok, "complexity=%d", participant.complexity);
}
