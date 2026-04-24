#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
using namespace std;

struct Ans {
    bool impossible;
    int H, W;
    vector<string> grid;
};

// Trim empty rows and columns from shape
vector<string> trimShape(const vector<string>& s) {
    int h = s.size(), w = s[0].size();
    int r1 = h, r2 = -1, c1 = w, c2 = -1;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (s[i][j] == '#') {
                r1 = min(r1, i);
                r2 = max(r2, i);
                c1 = min(c1, j);
                c2 = max(c2, j);
            }
    if (r2 < r1 || c2 < c1) // no blocks?
        return vector<string>();
    vector<string> t;
    for (int i = r1; i <= r2; i++) {
        t.emplace_back(s[i].substr(c1, c2 - c1 + 1));
    }
    return t;
}

// Read jury or contestant answer
Ans readAns(InStream& stream) {
    Ans a;
    // Peek first non-space token
    string tok = stream.readToken();
    if (tok == "impossible") {
        a.impossible = true;
        return a;
    }
    // Otherwise it's H
    a.impossible = false;
    // parse H
    int H = 0;
    try {
        H = stoi(tok);
    } catch (...) {
        stream.quitf(_wa, "expected 'impossible' or grid height, found '%s'", tok.c_str());
    }
    a.H = H;
    a.W = stream.readInt(1, 1000, "grid width");
    if (a.H < 1 || a.H > 1000)
        stream.quitf(_wa, "grid height %d is out of bounds", a.H);
    a.grid.resize(a.H);
    for (int i = 0; i < a.H; i++) {
        a.grid[i] = stream.readToken();
        if ((int)a.grid[i].size() != a.W)
            stream.quitf(_wa, "row %d has length %d, expected %d", i+1, (int)a.grid[i].size(), a.W);
        for (char c : a.grid[i])
            if (c != '#' && c != '.')
                stream.quitf(_wa, "invalid character '%c' in grid", c);
        // No fully filled rows
        bool full = true;
        for (char c : a.grid[i])
            if (c == '.') { full = false; break; }
        if (full)
            stream.quitf(_wa, "row %d is fully filled before placement", i+1);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input block
    int h = inf.readInt(1, 100, "block height");
    int w = inf.readInt(1, 100, "block width");
    vector<string> shape0(h);
    for (int i = 0; i < h; i++) {
        shape0[i] = inf.readToken();
        if ((int)shape0[i].size() != w)
            quitf(_fail, "invalid input shape line length");
    }
    // Precompute shape rotations
    vector<vector<string>> shapes;
    shapes.reserve(4);
    vector<string> cur = shape0;
    for (int rot = 0; rot < 4; rot++) {
        vector<string> t = trimShape(cur);
        shapes.push_back(t);
        // Rotate 90 deg CW
        int hh = cur.size(), ww = cur[0].size();
        vector<string> nxt(ww, string(hh, '.'));
        for (int i = 0; i < hh; i++)
            for (int j = 0; j < ww; j++)
                nxt[j][hh-1-i] = cur[i][j];
        cur = nxt;
    }
    // Read answers
    Ans jans = readAns(ans);
    Ans pans = readAns(ouf);
    // Both impossible?
    if (jans.impossible) {
        if (pans.impossible)
            quitf(_ok, "both impossible");
        else
            quitf(_wa, "expected impossible");
    }
    // Jury has grid; contestant must have grid
    if (pans.impossible)
        quitf(_wa, "expected a grid, found impossible");
    // Now verify contestant grid solves the task
    int H = pans.H, W = pans.W;
    auto& G = pans.grid;
    // Precompute for each column the rows with '#'
    vector<vector<int>> gcols(W);
    for (int j = 0; j < W; j++) {
        for (int i = 0; i < H; i++)
            if (G[i][j] == '#')
                gcols[j].push_back(i);
    }
    // Try each rotation and shift
    bool ok = false;
    for (auto& S : shapes) {
        int sh = S.size();
        int sw = S[0].size();
        if (sh == 0 || sw == 0) continue;
        if (sw > W || sh > H) {
            // shape taller than grid is allowed (will produce y<0), but skip heavy check
        }
        // Precollect shape cells per column
        vector<vector<int>> sc(sw);
        for (int i = 0; i < sh; i++)
            for (int j = 0; j < sw; j++)
                if (S[i][j] == '#')
                    sc[j].push_back(i);
        for (int sft = 0; sft + sw <= W; sft++) {
            // compute drop
            int d = H + 1; // minimal collision delta
            for (int j = 0; j < sw; j++) {
                int gj = j + sft;
                auto& col = gcols[gj];
                for (int i_s : sc[j]) {
                    // find first grid row r >= i_s
                    int d_cell;
                    auto it = std::lower_bound(col.begin(), col.end(), i_s);
                    if (it != col.end())
                        d_cell = *it - i_s;
                    else
                        d_cell = H - i_s;
                    d = min(d, d_cell);
                    if (d == 0) break;
                }
                if (d == 0) break;
            }
            int y = d - 1;
            if (y < 0) continue;
            // Check no overlap at y
            bool overlap = false;
            for (int i_s = 0; i_s < sh && !overlap; i_s++)
                for (int j = 0; j < sw; j++)
                    if (S[i_s][j] == '#') {
                        int gi = i_s + y, gj = j + sft;
                        if (gi < 0 || gi >= H || gj < 0 || gj >= W || G[gi][gj] == '#') {
                            overlap = true;
                            break;
                        }
                    }
            if (overlap) continue;
            // Check union covers entire grid
            bool covers = true;
            for (int i = 0; i < H && covers; i++) {
                for (int j = 0; j < W; j++) {
                    bool filled = (G[i][j] == '#');
                    int sj = j - sft;
                    int si = i - y;
                    if (!filled && sj >= 0 && sj < sw && si >= 0 && si < sh && S[si][sj] == '#')
                        filled = true;
                    if (!filled) {
                        covers = false;
                        break;
                    }
                }
            }
            if (covers) {
                ok = true;
                break;
            }
        }
        if (ok) break;
    }
    if (!ok)
        quitf(_wa, "no placement of the block clears all rows");
    quitf(_ok, "valid grid");
    return 0;
}
