#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

// Global data from input
int N;
int totalTiles;
// For each tile id 1..totalTiles:
// A[id] = number on left square, B[id] = number on right square
vector<int> A, B;
// For each tile id:
// row[id] = 0-based row index
// c0[id], c1[id] = 0-based column indices of its two squares
// r0[id], r1[id] = same row = row[id]
vector<int> row_of, c0, c1;

// Precompute geometry: rows 0..N-1, odd rows have N-1 tiles shifted by 1, even rows N tiles no shift
void build_geometry() {
    row_of.assign(totalTiles+1, 0);
    c0.assign(totalTiles+1, 0);
    c1.assign(totalTiles+1, 0);
    int id = 0;
    for (int r = 0; r < N; r++) {
        bool shifted = (r % 2 == 1);
        int cnt = shifted ? N-1 : N;
        int shift = shifted ? 1 : 0;
        for (int k = 0; k < cnt; k++) {
            ++id;
            row_of[id] = r;
            int base = shift + 2*k;
            c0[id] = base;
            c1[id] = base + 1;
        }
    }
}

// A helper to check if two squares (r1,c1,v1) and (r2,c2,v2) share a side and match number
inline bool squares_adj(int r1, int c1, int v1, int r2, int c2, int v2) {
    if (abs(r1 - r2) + abs(c1 - c2) != 1) return false;
    return v1 == v2;
}

// readAns: read a path from stream, verify it's a valid walk starting at 1 with matching adjacency.
// Returns pair<path_length, end_tile_id>.
// On ouf invalid => quitf(_wa, ...). On ans invalid => quitf(_fail, ...).
pair<int,int> readAns(InStream &stream) {
    // read path length
    int len = stream.readInt(1, totalTiles, "path length");
    if (len < 1) {
        stream.quitf(_wa, "path length must be >= 1, found %d", len);
    }
    vector<int> p(len);
    for (int i = 0; i < len; i++) {
        p[i] = stream.readInt(1, totalTiles, format("path[%d]", i+1).c_str());
    }
    // must start at tile 1
    if (p[0] != 1) {
        stream.quitf(_wa, "path must start at tile 1, found %d", p[0]);
    }
    // verify adjacency
    for (int i = 0; i+1 < len; i++) {
        int u = p[i], v = p[i+1];
        int ru = row_of[u], rv = row_of[v];
        bool ok = false;
        // try all square pairs of u and v
        // u has (ru,c0[u],A[u]) and (ru,c1[u],B[u])
        // v has (rv,c0[v],A[v]) and (rv,c1[v],B[v])
        if (squares_adj(ru, c0[u], A[u], rv, c0[v], A[v])) ok = true;
        if (squares_adj(ru, c0[u], A[u], rv, c1[v], B[v])) ok = true;
        if (squares_adj(ru, c1[u], B[u], rv, c0[v], A[v])) ok = true;
        if (squares_adj(ru, c1[u], B[u], rv, c1[v], B[v])) ok = true;
        if (!ok) {
            stream.quitf(_wa, "tiles %d and %d are not adjacent or numbers do not match", u, v);
        }
    }
    return make_pair(len, p[len-1]);
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    // compute total tiles: sum over rows: even r (0-based) N tiles, odd r N-1
    totalTiles = 0;
    for (int r = 0; r < N; r++) {
        totalTiles += (r % 2 == 0 ? N : N-1);
    }
    A.resize(totalTiles+1);
    B.resize(totalTiles+1);
    for (int i = 1; i <= totalTiles; i++) {
        A[i] = inf.readInt(1,6);
        B[i] = inf.readInt(1,6);
    }
    build_geometry();
    // read jury and participant answers
    pair<int,int> jans = readAns(ans);
    pair<int,int> pans = readAns(ouf);
    // must end at same tile
    if (pans.second != jans.second) {
        quitf(_wa, "path ends at tile %d but expected tile %d", pans.second, jans.second);
    }
    // compare path lengths
    if (pans.first > jans.first) {
        quitf(_wa, "path is longer than jury's: participant = %d, jury = %d",
              pans.first, jans.first);
    } else if (pans.first == jans.first) {
        quitf(_ok, "path length = %d", pans.first);
    } else {
        // participant found strictly shorter path => must be jury bug
        quitf(_fail, "participant's path is shorter than jury's: participant = %d, jury = %d",
              pans.first, jans.first);
    }
    return 0;
}
