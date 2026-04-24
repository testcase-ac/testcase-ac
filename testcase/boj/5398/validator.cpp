#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Data structures to collect intervals
    static vector<pair<int,int>> hor[1001];
    static vector<int> used_h;
    static bool has_h[1001];
    static vector<pair<int,int>> ver[1001];
    static vector<int> used_v;
    static bool has_v[1001];

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read H and V
        int H = inf.readInt(1, 500, "H");
        inf.readSpace();
        int V = inf.readInt(1, 500, "V");
        inf.readEoln();

        // Read horizontal words
        for (int i = 0; i < H; i++) {
            int x = inf.readInt(0, 1000, "x_h");
            inf.readSpace();
            int y = inf.readInt(0, 1000, "y_h");
            inf.readSpace();
            // Word of uppercase letters, length 1..1000
            string W = inf.readToken("[A-Z]{1,1000}", "W_h");
            inf.readEoln();
            int len = (int)W.size();
            int x1 = x;
            int x2 = x + len - 1;
            ensuref(x2 <= 2000, "Horizontal word at case %d, line %d exceeds board bounds: start (%d,%d), len=%d", tc, i+1, x, y, len);
            // Collect interval on row y
            if (!has_h[y]) {
                has_h[y] = true;
                used_h.push_back(y);
            }
            hor[y].emplace_back(x1, x2);
        }

        // Read vertical words
        for (int i = 0; i < V; i++) {
            int x = inf.readInt(0, 1000, "x_v");
            inf.readSpace();
            int y = inf.readInt(0, 1000, "y_v");
            inf.readSpace();
            string W = inf.readToken("[A-Z]{1,1000}", "W_v");
            inf.readEoln();
            int len = (int)W.size();
            int y1 = y;
            int y2 = y + len - 1;
            ensuref(y2 <= 2000, "Vertical word at case %d, line %d exceeds board bounds: start (%d,%d), len=%d", tc, i+1, x, y, len);
            // Collect interval on column x
            if (!has_v[x]) {
                has_v[x] = true;
                used_v.push_back(x);
            }
            ver[x].emplace_back(y1, y2);
        }

        // Check no overlapping among horizontals
        for (int y : used_h) {
            auto &vec = hor[y];
            sort(vec.begin(), vec.end());
            for (int i = 1; i < (int)vec.size(); i++) {
                auto &prev = vec[i-1];
                auto &cur  = vec[i];
                // They overlap if prev.second >= cur.first
                ensuref(prev.second < cur.first,
                        "Overlap in horizontal words at case %d on row %d: intervals [%d,%d] and [%d,%d]",
                        tc, y, prev.first, prev.second, cur.first, cur.second);
            }
            // clear for next case
            vec.clear();
            has_h[y] = false;
        }
        used_h.clear();

        // Check no overlapping among verticals
        for (int x : used_v) {
            auto &vec = ver[x];
            sort(vec.begin(), vec.end());
            for (int i = 1; i < (int)vec.size(); i++) {
                auto &prev = vec[i-1];
                auto &cur  = vec[i];
                ensuref(prev.second < cur.first,
                        "Overlap in vertical words at case %d on column %d: intervals [%d,%d] and [%d,%d]",
                        tc, x, prev.first, prev.second, cur.first, cur.second);
            }
            vec.clear();
            has_v[x] = false;
        }
        used_v.clear();
    }

    inf.readEof();
    return 0;
}
