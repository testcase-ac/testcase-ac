#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

// Check connectivity of cells with value 1 using BFS/DFS on 4-neighbors.
bool isConnected(const vector<vector<int>>& g) {
    int h = 6, w = 6;
    int total = 0;
    int sr = -1, sc = -1;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            if (g[i][j] == 1) {
                total++;
                if (sr == -1) { sr = i; sc = j; }
            }
    if (total == 0) return false; // but we will enforce total==6 elsewhere

    vector<vector<int>> vis(h, vector<int>(w, 0));
    queue<pair<int,int>> q;
    q.push({sr, sc});
    vis[sr][sc] = 1;
    int cnt = 0;
    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        cnt++;
        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (0 <= nr && nr < h && 0 <= nc && nc < w &&
                g[nr][nc] == 1 && !vis[nr][nc]) {
                vis[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
    return cnt == total;
}

// Try to simulate folding the net into a cube and ensure it yields a valid cube net.
// We check that the 6 squares can be embedded on distinct faces of a cube consistently.
bool isValidCubeNet(const vector<vector<int>>& g) {
    int h = 6, w = 6;
    // Locate all cells with 1
    vector<pair<int,int>> cells;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            if (g[i][j] == 1)
                cells.push_back({i,j});

    if ((int)cells.size() != 6) return false;

    // directions on grid
    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    // For 3D orientation, we represent a face by its normal vector (nx, ny, nz)
    // where each component is in {-1,0,1}, and |n|=1.
    struct Vec3 { int x,y,z; };

    auto cross = [](Vec3 a, Vec3 b)->Vec3 {
        return {a.y*b.z - a.z*b.y,
                a.z*b.x - a.x*b.z,
                a.x*b.y - a.y*b.x};
    };

    auto eq = [](Vec3 a, Vec3 b)->bool {
        return a.x==b.x && a.y==b.y && a.z==b.z;
    };

    // For rolling the cube from a face with normal n, with "up" vector u,
    // when we move on the net in some direction, we rotate in 3D.
    // We track for each visited cell its (normal, up) orientation.
    struct Ori {
        Vec3 n; // normal
        Vec3 u; // "up" direction on that face
    };

    // Precompute neighbor relations for the 4 grid directions.
    // For a move from cell A to B:
    // dir 0: up    (-1,0) --> rotate around local X-axis? Actually, we can reason:
    // If we stand on face with normal n and up u, we can define:
    // right r = cross(n, u) (assuming right-handed coordinates).
    // Moving on the net in grid directions corresponds to rotating so that
    // shared edge becomes hinge. Specifically:
    // move up    : new normal n' = u,          new up u' = -n
    // move down  : new normal n' = -u,         new up u' = n
    // move left  : new normal n' = r,          new up u' = u
    // move right : new normal n' = -r,         new up u' = u
    auto negate = [](Vec3 v)->Vec3 { return {-v.x,-v.y,-v.z}; };

    // We will BFS from an arbitrary cell with an arbitrary starting orientation,
    // e.g., first 1-cell has normal (0,0,1) (front), up (0,1,0).
    // During BFS, if we revisit a cell, we must enforce consistent orientation.
    // Also, we ensure all 6 normals are distinct.
    int sr = cells[0].first;
    int sc = cells[0].second;

    vector<vector<int>> vis(6, vector<int>(6, 0));
    vector<vector<Ori>> ori(6, vector<Ori>(6));
    queue<pair<int,int>> q;

    Ori start;
    start.n = {0,0,1};
    start.u = {0,1,0}; // arbitrary consistent basis

    vis[sr][sc] = 1;
    ori[sr][sc] = start;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        Ori cur = ori[r][c];
        Vec3 n = cur.n;
        Vec3 u = cur.u;
        Vec3 rdir = cross(n, u); // right

        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (!(0 <= nr && nr < h && 0 <= nc && nc < w)) continue;
            if (g[nr][nc] != 1) continue;

            Vec3 nn, uu;
            if (k == 0) { // up
                nn = u;
                uu = negate(n);
            } else if (k == 1) { // down
                nn = negate(u);
                uu = n;
            } else if (k == 2) { // left
                nn = rdir;
                uu = u;
            } else { // right
                nn = negate(rdir);
                uu = u;
            }

            if (!vis[nr][nc]) {
                vis[nr][nc] = 1;
                ori[nr][nc] = {nn, uu};
                q.push({nr, nc});
            } else {
                // Already assigned orientation; must be consistent
                Ori prev = ori[nr][nc];
                if (!eq(prev.n, nn) || !eq(prev.u, uu)) {
                    return false;
                }
            }
        }
    }

    // All 6 squares reachable?
    int cnt = 0;
    for (auto [r, c] : cells)
        if (vis[r][c]) cnt++;
    if (cnt != 6) return false;

    // All normals must be distinct (no two cells on same cube face).
    vector<Vec3> normals;
    for (auto [r, c] : cells)
        normals.push_back(ori[r][c].n);

    for (int i = 0; i < 6; ++i)
        for (int j = i+1; j < 6; ++j)
            if (eq(normals[i], normals[j]))
                return false;

    // A proper cube has exactly 6 faces; normals must be one of 6 orthogonal directions.
    // Check each normal has length 1 and components in {-1,0,1}.
    auto len2 = [](Vec3 v)->int { return v.x*v.x + v.y*v.y + v.z*v.z; };
    for (auto v : normals) {
        if (!(len2(v) == 1 &&
              v.x >= -1 && v.x <= 1 &&
              v.y >= -1 && v.y <= 1 &&
              v.z >= -1 && v.z <= 1))
            return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int TESTS = 3;
    const int H = 6;
    const int W = 6;

    for (int tc = 0; tc < TESTS; ++tc) {
        setTestCase(tc + 1);

        vector<vector<int>> g(H, vector<int>(W));
        int ones = 0;

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                g[i][j] = inf.readInt(0, 1, "cell");
                if (j + 1 < W) inf.readSpace();
            }
            inf.readEoln();
        }

        // Exactly six ones overall
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (g[i][j] == 1) ones++;

        ensuref(ones == 6, "Test case %d: number of ones must be exactly 6, got %d", tc + 1, ones);

        // "정사각형들이 서로 떨어져 있는 경우는 없다." => connectivity of 1-cells
        ensuref(isConnected(g), "Test case %d: squares (1-cells) are not 4-connected", tc + 1);

        // Problem guarantees that "정육면체의 전개도이면 yes, 아니면 no" and always answer exists.
        // That is simply true by definition; both yes and no are always possible.
        // There is no extra global guarantee about always being foldable,
        // so we do NOT enforce isValidCubeNet here.
        // However, the statement does not guarantee that the input is always
        // a cube net, only that squares are connected and count is 6,
        // which we already enforced.
    }

    inf.readEof();
}
