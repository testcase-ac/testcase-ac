#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Couch {
    vector<pair<int, int>> cells;
    vector<pair<int, int>> unfoldedCells;
};

struct Answer {
    int claimed;
    int unfolded;
};

int n, m;
vector<string> inputGrid;
vector<Couch> couches;

bool isLetter(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool isUpper(char c) {
    return 'A' <= c && c <= 'Z';
}

bool inside(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

vector<pair<int, int>> sortedUnique(vector<pair<int, int>> cells) {
    sort(cells.begin(), cells.end());
    cells.erase(unique(cells.begin(), cells.end()), cells.end());
    return cells;
}

vector<pair<int, int>> computeUnfoldedCells(const vector<pair<int, int>>& cells) {
    auto [r1, c1] = cells[0];
    auto [r2, c2] = cells[1];
    char ch = inputGrid[r1][c1];
    vector<pair<int, int>> result = cells;

    if (r1 == r2) {
        int nr = isUpper(ch) ? r1 + 1 : r1 - 1;
        result.push_back({nr, c1});
        result.push_back({nr, c2});
    } else {
        int nc = isUpper(ch) ? c1 + 1 : c1 - 1;
        result.push_back({r1, nc});
        result.push_back({r2, nc});
    }

    return sortedUnique(result);
}

void readInput() {
    n = inf.readInt();
    m = inf.readInt();
    inputGrid.resize(n);
    for (int i = 0; i < n; ++i) {
        inputGrid[i] = inf.readToken();
    }

    vector<vector<int>> seen(n, vector<int>(m, 0));
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (inputGrid[r][c] == '.' || seen[r][c]) {
                continue;
            }

            char ch = inputGrid[r][c];
            if (!isLetter(ch)) {
                quitf(_fail, "invalid input character '%c' at (%d,%d)", ch, r + 1, c + 1);
            }

            vector<pair<int, int>> component;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = 1;

            while (!q.empty()) {
                auto [vr, vc] = q.front();
                q.pop();
                component.push_back({vr, vc});

                for (int d = 0; d < 4; ++d) {
                    int nr = vr + dr[d];
                    int nc = vc + dc[d];
                    if (!inside(nr, nc) || seen[nr][nc] || inputGrid[nr][nc] != ch) {
                        continue;
                    }
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }

            component = sortedUnique(component);
            if (component.size() != 2) {
                quitf(_fail, "input couch at (%d,%d) has %d cells", r + 1, c + 1, int(component.size()));
            }
            if (component[0].first != component[1].first && component[0].second != component[1].second) {
                quitf(_fail, "input couch at (%d,%d) is not adjacent", r + 1, c + 1);
            }

            couches.push_back({component, computeUnfoldedCells(component)});
        }
    }
}

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(0, int(couches.size()), "unfolded count");
    vector<string> grid(n);
    for (int r = 0; r < n; ++r) {
        grid[r] = stream.readToken("[.0-9]+", format("row %d", r + 1).c_str());
        if (int(grid[r].size()) != m) {
            stream.quitf(_wa, "row %d has length %d instead of %d", r + 1, int(grid[r].size()), m);
        }
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] != '.' && !isdigit(static_cast<unsigned char>(grid[r][c]))) {
                stream.quitf(_wa, "invalid output character '%c' at (%d,%d)", grid[r][c], r + 1, c + 1);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after hall description");
    }

    vector<vector<int>> owner(n, vector<int>(m, -1));
    vector<char> digit(couches.size(), 0);
    int unfolded = 0;

    for (int id = 0; id < int(couches.size()); ++id) {
        const auto& couch = couches[id];
        char d = 0;
        for (auto [r, c] : couch.cells) {
            if (!isdigit(static_cast<unsigned char>(grid[r][c]))) {
                stream.quitf(_wa, "original couch cell (%d,%d) is empty", r + 1, c + 1);
            }
            if (d == 0) {
                d = grid[r][c];
            } else if (grid[r][c] != d) {
                stream.quitf(_wa, "couch original cells use different digits at (%d,%d)", r + 1, c + 1);
            }
        }

        bool canUnfold = couch.unfoldedCells.size() == 4;
        if (canUnfold) {
            for (auto [r, c] : couch.unfoldedCells) {
                bool isOriginalCell = find(couch.cells.begin(), couch.cells.end(), make_pair(r, c)) != couch.cells.end();
                if (!inside(r, c) || (inputGrid[r][c] != '.' && !isOriginalCell)) {
                    canUnfold = false;
                    break;
                }
            }
        }

        bool appearsUnfolded = canUnfold;
        if (appearsUnfolded) {
            for (auto [r, c] : couch.unfoldedCells) {
                if (grid[r][c] != d) {
                    appearsUnfolded = false;
                    break;
                }
            }
        }

        const auto& occupied = appearsUnfolded ? couch.unfoldedCells : couch.cells;
        if (appearsUnfolded) {
            ++unfolded;
        }
        digit[id] = d;

        for (auto [r, c] : occupied) {
            if (!inside(r, c)) {
                stream.quitf(_wa, "couch %d occupies out-of-bounds cell (%d,%d)", id + 1, r + 1, c + 1);
            }
            if (owner[r][c] != -1) {
                stream.quitf(_wa, "cell (%d,%d) is occupied by multiple couches", r + 1, c + 1);
            }
            if (grid[r][c] != d) {
                stream.quitf(_wa, "couch %d has inconsistent digit at (%d,%d)", id + 1, r + 1, c + 1);
            }
            owner[r][c] = id;
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '.') {
                if (owner[r][c] != -1) {
                    stream.quitf(_wa, "occupied cell (%d,%d) is printed empty", r + 1, c + 1);
                }
            } else if (owner[r][c] == -1) {
                stream.quitf(_wa, "printed digit at (%d,%d) is not part of any couch", r + 1, c + 1);
            }
        }
    }

    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (owner[r][c] == -1) {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (!inside(nr, nc) || owner[nr][nc] == -1 || owner[nr][nc] == owner[r][c]) {
                    continue;
                }
                if (grid[nr][nc] == grid[r][c]) {
                    stream.quitf(_wa, "adjacent couches share digit %c at (%d,%d) and (%d,%d)",
                                 grid[r][c], r + 1, c + 1, nr + 1, nc + 1);
                }
            }
        }
    }

    if (claimed != unfolded) {
        stream.quitf(_wa, "claimed %d unfolded couches but layout contains %d", claimed, unfolded);
    }

    return {claimed, unfolded};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    readInput();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.unfolded < jury.unfolded) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d", jury.unfolded, participant.unfolded);
    }
    if (participant.unfolded > jury.unfolded) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d", jury.unfolded, participant.unfolded);
    }
    quitf(_ok, "answer=%d", participant.unfolded);
}
