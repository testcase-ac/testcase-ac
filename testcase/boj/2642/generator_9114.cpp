#include "testlib.h"
using namespace std;

struct Vec {
    int x, y, z;
};

Vec neg(const Vec &a) { return Vec{-a.x, -a.y, -a.z}; }

bool eq(const Vec &a, const Vec &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

// Check if a given set of 6 cells (has[r][c] == true) forms a valid cube net
bool isValidNet(const bool has[6][6]) {
    int total = 0;
    int sr = -1, sc = -1;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (has[i][j]) {
                total++;
                if (sr == -1) {
                    sr = i;
                    sc = j;
                }
            }
        }
    }
    if (total != 6) return false;

    bool vis[6][6] = {};
    Vec u[6][6], v[6][6], w[6][6];

    vector<pair<int,int>> q;
    int head = 0;

    // Initial orientation (orthonormal basis aligned to axes)
    vis[sr][sc] = true;
    u[sr][sc] = Vec{0, 1, 0};
    v[sr][sc] = Vec{1, 0, 0};
    w[sr][sc] = Vec{0, 0, 1};
    q.push_back({sr, sc});

    vector<Vec> normals;
    normals.push_back(w[sr][sc]);

    static int dr[4] = {-1, 0, 1, 0};
    static int dc[4] = {0, 1, 0, -1};

    int visited = 0;

    while (head < (int)q.size()) {
        int r = q[head].first;
        int c = q[head].second;
        head++;

        visited++;

        Vec cu = u[r][c];
        Vec cv = v[r][c];
        Vec cw = w[r][c];

        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr < 0 || nr >= 6 || nc < 0 || nc >= 6) continue;
            if (!has[nr][nc]) continue;

            // Fold 90 degrees along the shared edge
            Vec nu, nv, nw;
            if (dir == 0) { // up
                nu = neg(cw);
                nv = cv;
                nw = cu;
            } else if (dir == 1) { // right
                nu = cu;
                nv = cw;
                nw = neg(cv);
            } else if (dir == 2) { // down
                nu = cw;
                nv = cv;
                nw = neg(cu);
            } else { // left
                nu = cu;
                nv = neg(cw);
                nw = cv;
            }

            if (!vis[nr][nc]) {
                vis[nr][nc] = true;
                u[nr][nc] = nu;
                v[nr][nc] = nv;
                w[nr][nc] = nw;
                q.push_back({nr, nc});
                normals.push_back(nw);
            } else {
                // Orientation conflict -> not a valid net
                if (!(eq(nu, u[nr][nc]) && eq(nv, v[nr][nc]) && eq(nw, w[nr][nc])))
                    return false;
            }
        }
    }

    if (visited != total) return false; // not connected

    // All six normals must be distinct (one for each cube face)
    if ((int)normals.size() != 6) return false;
    for (int i = 0; i < 6; ++i)
        for (int j = i + 1; j < 6; ++j)
            if (eq(normals[i], normals[j]))
                return false;

    return true;
}

// Generate a connected 6-cell shape that is a valid cube net
vector<pair<int,int>> generateValidNet() {
    static int dr[4] = {-1, 0, 1, 0};
    static int dc[4] = {0, 1, 0, -1};

    while (true) {
        bool has[6][6] = {};
        vector<pair<int,int>> cells;

        // Random starting cell
        int sr = rnd.next(0, 5);
        int sc = rnd.next(0, 5);
        has[sr][sc] = true;
        cells.push_back({sr, sc});

        // Grow a random connected polyomino of size 6
        while ((int)cells.size() < 6) {
            auto base = rnd.any(cells);
            int dir = rnd.next(0, 3);
            int nr = base.first + dr[dir];
            int nc = base.second + dc[dir];
            if (nr < 0 || nr >= 6 || nc < 0 || nc >= 6) continue;
            if (has[nr][nc]) continue;
            has[nr][nc] = true;
            cells.push_back({nr, nc});
        }

        if (isValidNet(has))
            return cells;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Always generate a foldable cube net
    vector<pair<int,int>> cells = generateValidNet();

    // Prepare 6x6 grid, fill with 0
    int grid[6][6];
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            grid[i][j] = 0;

    // Assign labels 1..6 randomly to the 6 cells
    vector<int> labels = {1, 2, 3, 4, 5, 6};
    shuffle(labels.begin(), labels.end());
    for (int k = 0; k < 6; ++k) {
        int r = cells[k].first;
        int c = cells[k].second;
        grid[r][c] = labels[k];
    }

    // Output the 6x6 grid
    for (int i = 0; i < 6; ++i) {
        vector<int> row(6);
        for (int j = 0; j < 6; ++j)
            row[j] = grid[i][j];
        println(row);
    }

    return 0;
}
