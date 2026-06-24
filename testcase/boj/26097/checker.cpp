#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    explicit DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
};

int n, m;
vector<int> board;

struct Answer {
    bool possible;
};

void readNoExtraTokens(InStream& stream) {
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
}

int cellId(int r, int c) {
    return r * m + c;
}

bool adjacentCells(int a, int b) {
    int ar = a / m, ac = a % m;
    int br = b / m, bc = b % m;
    return abs(ar - br) + abs(ac - bc) == 1;
}

vector<int> adjacentEmptyRoots(int v, const vector<char>& empty, DSU& dsu) {
    int r = v / m, c = v % m;
    vector<int> roots;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nr = r + dr[dir], nc = c + dc[dir];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
        int u = cellId(nr, nc);
        if (!empty[u]) continue;
        int root = dsu.find(u);
        bool seen = false;
        for (int existing : roots) {
            if (existing == root) {
                seen = true;
                break;
            }
        }
        if (!seen) roots.push_back(root);
    }
    return roots;
}

bool shareAdjacentEmptyComponent(int a, int b, const vector<char>& empty, DSU& dsu) {
    vector<int> rootsA = adjacentEmptyRoots(a, empty, dsu);
    vector<int> rootsB = adjacentEmptyRoots(b, empty, dsu);
    for (int ra : rootsA) {
        for (int rb : rootsB) {
            if (ra == rb) return true;
        }
    }
    return false;
}

void addEmptyCell(int v, vector<char>& empty, DSU& dsu) {
    empty[v] = true;
    int r = v / m, c = v % m;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int dir = 0; dir < 4; ++dir) {
        int nr = r + dr[dir], nc = c + dc[dir];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
        int u = cellId(nr, nc);
        if (empty[u]) dsu.unite(v, u);
    }
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 1, "first token");
    if (first == 0) {
        stream.quitf(_wa, "first token must be -1 or 1");
    }
    if (first == -1) {
        readNoExtraTokens(stream);
        return {false};
    }

    int total = n * m;
    if (total % 2 != 0) {
        stream.quitf(_wa, "a witness cannot remove an odd number of cards");
    }

    vector<char> empty(total, false);
    DSU dsu(total);
    int removed = 0;

    for (int step = 0; step < total / 2; ++step) {
        int r1 = stream.readInt(1, n, format("r1[%d]", step + 1).c_str()) - 1;
        int c1 = stream.readInt(1, m, format("c1[%d]", step + 1).c_str()) - 1;
        int r2 = stream.readInt(1, n, format("r2[%d]", step + 1).c_str()) - 1;
        int c2 = stream.readInt(1, m, format("c2[%d]", step + 1).c_str()) - 1;
        int a = cellId(r1, c1);
        int b = cellId(r2, c2);

        if (a == b) {
            stream.quitf(_wa, "step %d removes the same initial card twice", step + 1);
        }
        if (empty[a] || empty[b]) {
            stream.quitf(_wa, "step %d removes an already removed card", step + 1);
        }
        if (board[a] != board[b]) {
            stream.quitf(_wa, "step %d removes cards with different numbers", step + 1);
        }
        if (!adjacentCells(a, b) && !shareAdjacentEmptyComponent(a, b, empty, dsu)) {
            stream.quitf(_wa, "step %d cards cannot be made adjacent", step + 1);
        }

        addEmptyCell(a, empty, dsu);
        addEmptyCell(b, empty, dsu);
        removed += 2;
    }

    readNoExtraTokens(stream);
    if (removed != total) {
        stream.quitf(_wa, "witness removes %d cards instead of %d", removed, total);
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    board.resize(n * m);
    for (int i = 0; i < n * m; ++i) {
        board[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible == participant.possible) {
        quitf(_ok, "answer is %s", participant.possible ? "possible" : "impossible");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant supplied a valid witness while jury says impossible");
    }
    quitf(_wa, "jury has a valid witness but participant says impossible");
}
