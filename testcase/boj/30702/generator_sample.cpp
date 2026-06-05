#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomColor(int alphabetSize) {
    return char('A' + rnd.next(alphabetSize));
}

vector<string> makeRandomGrid(int n, int m, int alphabetSize) {
    vector<string> grid(n, string(m, 'A'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = randomColor(alphabetSize);
        }
    }
    return grid;
}

vector<string> makeStripedGrid(int n, int m, int alphabetSize) {
    vector<string> grid(n, string(m, 'A'));
    int stripeMode = rnd.next(3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int key = 0;
            if (stripeMode == 0) {
                key = i / rnd.next(1, 3);
            } else if (stripeMode == 1) {
                key = j / rnd.next(1, 3);
            } else {
                key = (i / rnd.next(1, 2)) + (j / rnd.next(1, 2));
            }
            grid[i][j] = char('A' + key % alphabetSize);
        }
    }
    return grid;
}

vector<string> makeCheckerGrid(int n, int m) {
    vector<string> grid(n, string(m, 'A'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = char('A' + (i + j) % 2);
        }
    }
    return grid;
}

vector<vector<int>> componentIds(const vector<string>& grid) {
    int n = int(grid.size());
    int m = int(grid[0].size());
    vector<vector<int>> comp(n, vector<int>(m, -1));
    vector<int> qx(n * m), qy(n * m);
    int compCount = 0;
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    for (int si = 0; si < n; ++si) {
        for (int sj = 0; sj < m; ++sj) {
            if (comp[si][sj] != -1) {
                continue;
            }
            int head = 0, tail = 0;
            qx[tail] = si;
            qy[tail++] = sj;
            comp[si][sj] = compCount;
            while (head < tail) {
                int x = qx[head];
                int y = qy[head++];
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                        continue;
                    }
                    if (comp[nx][ny] == -1 && grid[nx][ny] == grid[x][y]) {
                        comp[nx][ny] = compCount;
                        qx[tail] = nx;
                        qy[tail++] = ny;
                    }
                }
            }
            ++compCount;
        }
    }
    return comp;
}

vector<string> makeComponentConsistentB(const vector<string>& a, int alphabetSize) {
    int n = int(a.size());
    int m = int(a[0].size());
    vector<vector<int>> comp = componentIds(a);
    int compCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            compCount = max(compCount, comp[i][j] + 1);
        }
    }

    vector<char> color(compCount);
    for (int id = 0; id < compCount; ++id) {
        color[id] = randomColor(alphabetSize);
    }

    vector<string> b(n, string(m, 'A'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            b[i][j] = color[comp[i][j]];
        }
    }
    return b;
}

vector<string> makeSplitB(const vector<string>& a, int alphabetSize) {
    vector<string> b = makeComponentConsistentB(a, alphabetSize);
    int n = int(a.size());
    int m = int(a[0].size());

    vector<pair<int, int>> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 1 < m; ++j) {
            if (a[i][j] == a[i][j + 1]) {
                candidates.push_back({i, j});
            }
        }
    }
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == a[i + 1][j]) {
                candidates.push_back({i, j});
            }
        }
    }

    if (candidates.empty()) {
        return b;
    }

    pair<int, int> cell = rnd.any(candidates);
    int x = cell.first;
    int y = cell.second;
    int nx = x;
    int ny = y + 1;
    if (ny >= m || a[x][y] != a[nx][ny]) {
        nx = x + 1;
        ny = y;
    }
    b[nx][ny] = char('A' + (b[x][y] - 'A' + rnd.next(1, alphabetSize - 1)) % alphabetSize);
    return b;
}

void printCase(const vector<string>& a, const vector<string>& b) {
    println(int(a.size()), int(a[0].size()));
    for (const string& row : a) {
        println(row);
    }
    for (const string& row : b) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(3, 10);
    int m = rnd.next(3, 12);
    int alphabetSize = rnd.next(2, 8);

    vector<string> a;
    if (mode == 0) {
        a = makeCheckerGrid(n, m);
    } else if (mode <= 3) {
        a = makeStripedGrid(n, m, alphabetSize);
    } else {
        a = makeRandomGrid(n, m, alphabetSize);
    }

    vector<string> b;
    if (mode == 2 || mode == 5) {
        b = makeSplitB(a, alphabetSize);
    } else if (mode == 4) {
        b = makeRandomGrid(n, m, alphabetSize);
    } else {
        b = makeComponentConsistentB(a, alphabetSize);
    }

    printCase(a, b);
    return 0;
}
