#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Vec3 {
    int x, y, z;
};

bool operator==(const Vec3& a, const Vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

int dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Rotate vector v by 90 degrees around axis 'axis' (unit axis, coordinates in {-1,0,1})
Vec3 rotate90(const Vec3& v, const Vec3& axis, int dir) {
    // dir = +1: 90 degrees, dir = -1: -90 degrees
    // Formula: v' = v * cos(90) + (axis x v) * sin(90) + axis * (axis·v) * (1 - cos(90))
    // cos(90)=0, sin(90)=dir
    // => v' = dir * (axis x v) + axis * (axis·v)
    Vec3 axv = cross(axis, v);
    int adv = dot(axis, v);
    Vec3 res{
        dir * axv.x + axis.x * adv,
        dir * axv.y + axis.y * adv,
        dir * axv.z + axis.z * adv
    };
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int H = 6, W = 6;
    int a[H][W];

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            a[i][j] = inf.readInt(0, 6, "cell");
            if (j + 1 < W) inf.readSpace();
        }
        inf.readEoln();
    }

    // Count occurrences of labels 1..6 and 0
    int cnt[7] = {0};
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            ++cnt[a[i][j]];

    // Exactly one of each 1..6 must exist
    for (int v = 1; v <= 6; ++v)
        ensuref(cnt[v] == 1, "Label %d occurs %d times, expected exactly 1", v, cnt[v]);

    // There must be exactly 6 non-zero cells (the faces of the net)
    int nonZero = 0;
    for (int v = 1; v <= 6; ++v) nonZero += cnt[v];
    ensuref(nonZero == 6, "There are %d non-zero cells, expected exactly 6", nonZero);

    // Identify positions of each face
    pair<int,int> pos[7];
    for (int v = 1; v <= 6; ++v) pos[v] = {-1, -1};
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            if (a[i][j] != 0)
                pos[a[i][j]] = {i, j};

    // Check all non-zero cells form a single 4-connected component.
    // Implementation convenience: BFS over all non-zero cells.
    vector<vector<int>> vis(H, vector<int>(W, 0));
    int sx = -1, sy = -1;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            if (a[i][j] != 0) {
                sx = i; sy = j;
                break;
            }
    ensuref(sx != -1, "No non-zero cell found, but we expect 6 faces");

    queue<pair<int,int>> q;
    q.push({sx, sy});
    vis[sx][sy] = 1;
    int visitedNonZero = 0;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        ++visitedNonZero;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (a[nx][ny] == 0) continue;
            if (vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            q.push({nx, ny});
        }
    }
    ensuref(visitedNonZero == nonZero,
            "Non-zero cells are not 4-connected (component size %d, expected %d)",
            visitedNonZero, nonZero);

    // Now simulate folding to check that:
    //  - the 6 squares can be mapped to 6 distinct faces of a cube
    //  - adjacency constraints are satisfied
    //
    // We don't need to match a particular net shape a priori; instead we:
    //  - place one face (pick the cell containing label 1) on the cube with a fixed orientation
    //  - perform DFS/BFS to assign orientations to neighboring faces
    //  - check for consistency and global cube properties.

    // Find grid coordinates of label 1
    int r1 = pos[1].first;
    int c1 = pos[1].second;
    ensuref(r1 != -1, "Face 1 not found, though counts said it should exist");

    // For each non-zero grid cell we will store whether it is used in DFS (it is, since we know component is single)
    // and its corresponding orientation on the cube: normal vector 'n' and local 'u' axis (right direction on the face).
    // 'v' axis (up on the face) can be derived as v = n x u (right-handed).
    struct Ori { bool assigned; Vec3 n, u; };
    Ori ori[H][W];
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            ori[i][j].assigned = false;

    // Initialize orientation of face at (r1,c1):
    // Let face 1's outward normal be (0,0,1) and its 'right' direction on grid (increasing column) be (1,0,0).
    ori[r1][c1].assigned = true;
    ori[r1][c1].n = {0, 0, 1};
    ori[r1][c1].u = {1, 0, 0};

    // DFS stack
    stack<pair<int,int>> st;
    st.push({r1, c1});

    // Track which cube normals are already occupied: map Vec3 -> label.
    map<tuple<int,int,int>, int> faceByNormal;

    auto normKey = [](const Vec3& v) {
        return make_tuple(v.x, v.y, v.z);
    };

    while (!st.empty()) {
        auto [x, y] = st.top(); st.pop();
        Ori cur = ori[x][y];
        Vec3 n = cur.n;
        Vec3 u = cur.u;
        Vec3 v = cross(n, u);

        int label = a[x][y];

        // Check that this face doesn't collide with another already-assigned cube face.
        auto key = normKey(n);
        auto it = faceByNormal.find(key);
        if (it == faceByNormal.end()) {
            faceByNormal[key] = label;
        } else {
            ensuref(it->second == label,
                    "Two different grid cells (including label %d and %d) map to the same cube face normal (%d,%d,%d)",
                    it->second, label, n.x, n.y, n.z);
        }

        // Explore neighbors
        for (int d = 0; d < 4; ++d) {
            int nxg = x + dx[d], nyg = y + dy[d];
            if (nxg < 0 || nxg >= H || nyg < 0 || nyg >= W) continue;
            if (a[nxg][nyg] == 0) continue;

            // Determine rotation axis and direction from current orientation and grid move.
            // Grid directions:
            //  up    (dx = -1, dy = 0) => fold around local 'u' axis; sign chosen so that
            //                              the neighbor ends up "above" current in 3D.
            //  down  (dx = +1, dy = 0)
            //  left  (dx = 0, dy = -1) => fold around local 'v' axis
            //  right (dx = 0, dy = +1)
            //
            // The pattern for a flat net lying in plane z=0, with n=(0,0,1), u=(1,0,0), v=(0,1,0):
            //  - cell above (row-1) has normal (0,-1,0)  (rotation +90 around u)
            //  - cell below (row+1) has normal (0,1,0)   (rotation -90 around u)
            //  - cell left  (col-1) has normal (-1,0,0)  (rotation -90 around v)
            //  - cell right (col+1) has normal (1,0,0)   (rotation +90 around v)
            Vec3 axis;
            int dirRot; // +1 or -1
            if (d == 0) { // up: (-1,0)
                axis = u;
                dirRot = +1;
            } else if (d == 1) { // down: (+1,0)
                axis = u;
                dirRot = -1;
            } else if (d == 2) { // left: (0,-1)
                axis = v;
                dirRot = -1;
            } else { // right: (0,+1)
                axis = v;
                dirRot = +1;
            }

            Vec3 nn = rotate90(n, axis, dirRot);
            Vec3 nu = rotate90(u, axis, dirRot);

            if (!ori[nxg][nyg].assigned) {
                ori[nxg][nyg].assigned = true;
                ori[nxg][nyg].n = nn;
                ori[nxg][nyg].u = nu;
                st.push({nxg, nyg});
            } else {
                // Already assigned: check consistency.
                ensuref(ori[nxg][nyg].n == nn &&
                        ori[nxg][nyg].u == nu,
                        "Orientation conflict at grid cell (%d,%d): multiple folding paths disagree",
                        nxg, nyg);
            }
        }
    }

    // After DFS, we must have exactly 6 distinct cube face normals.
    ensuref((int)faceByNormal.size() == 6,
            "Folding results in %d distinct cube faces, expected 6",
            (int)faceByNormal.size());

    // Also, all normals must be axis-aligned unit vectors with coordinates in {-1,0,1}
    // and form a valid cube: each axis appears with + and - once.
    set<tuple<int,int,int>> normals;
    for (auto &kv : faceByNormal) {
        Vec3 n{get<0>(kv.first), get<1>(kv.first), get<2>(kv.first)};
        int sq = n.x * n.x + n.y * n.y + n.z * n.z;
        ensuref(sq == 1,
                "Normal (%d,%d,%d) is not a unit axis vector",
                n.x, n.y, n.z);
        normals.insert(kv.first);
    }
    ensuref(normals.size() == 6, "Normals set size is %d, expected 6", (int)normals.size());

    // Check pair structure: for each axis, + and - must both exist.
    bool posX = normals.count({1,0,0});
    bool negX = normals.count({-1,0,0});
    bool posY = normals.count({0,1,0});
    bool negY = normals.count({0,-1,0});
    bool posZ = normals.count({0,0,1});
    bool negZ = normals.count({0,0,-1});
    ensuref(posX && negX && posY && negY && posZ && negZ,
            "Normals do not form a complete cube faces set");

    // Additionally, check that adjacency on net corresponds to adjacency on cube:
    // If two faces are neighbors in the grid (4-connected), their normals must be orthogonal (dot=0).
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (a[i][j] == 0) continue;
            Vec3 n1 = ori[i][j].n;
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
                if (a[ni][nj] == 0) continue;
                Vec3 n2 = ori[ni][nj].n;
                int dp = dot(n1, n2);
                ensuref(dp == 0,
                        "Adjacent faces at (%d,%d) and (%d,%d) are not orthogonal (dot=%d)",
                        i, j, ni, nj, dp);
            }
        }
    }

    // If we reach here, the net indeed folds into a cube, and face 1 normal is (0,0,1).
    // The opposite face has normal (0,0,-1); find its label.
    int oppositeLabel = 0;
    auto itOpp = faceByNormal.find({0,0,-1});
    ensuref(itOpp != faceByNormal.end(),
            "Could not find face opposite to face 1 (normal (0,0,-1) missing)");
    oppositeLabel = itOpp->second;

    // The problem statement guarantees in valid tests that this is the correct output.
    // The validator's role is only to ensure the net is foldable into a cube according
    // to the above simulation; solutions will compute and output the opposite face.

    inf.readEof();
}
