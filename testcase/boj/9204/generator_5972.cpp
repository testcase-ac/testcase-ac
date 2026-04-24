#include "testlib.h"
#include <vector>
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    set<string> used;
    for (int tc = 0; tc < T; ++tc) {
        int rx, cx, ry, cy;
        string key;
        // regenerate until we get a unique test case
        do {
            // start position
            rx = rnd.next(1, 8);
            cx = rnd.next(1, 8);

            // choose scenario type by weighted probability
            double d = rnd.next();
            int type;
            if (d < 0.10) type = 0;      // same square
            else if (d < 0.40) type = 1; // one move
            else if (d < 0.75) type = 2; // two moves
            else type = 3;               // impossible

            if (type == 0) {
                ry = rx; cy = cx;
            }
            else if (type == 1) {
                // all reachable diagonal squares except the same
                vector<pair<int,int>> cand;
                for (int r = 1; r <= 8; ++r) {
                    for (int c = 1; c <= 8; ++c) {
                        if (r == rx && c == cx) continue;
                        if (abs(r - rx) == abs(c - cx))
                            cand.emplace_back(r, c);
                    }
                }
                if (cand.empty()) {
                    type = 2; // fallback
                } else {
                    auto p = rnd.any(cand);
                    ry = p.first; cy = p.second;
                }
            }
            if (type == 2) {
                // two moves: same color, not on same diagonal or same
                do {
                    ry = rnd.next(1, 8);
                    cy = rnd.next(1, 8);
                } while ((ry == rx && cy == cx)
                         || ((ry + cy) % 2 != (rx + cx) % 2)
                         || (abs(ry - rx) == abs(cy - cx)));
            }
            if (type == 3) {
                // impossible: different color
                do {
                    ry = rnd.next(1, 8);
                    cy = rnd.next(1, 8);
                } while ((ry + cy) % 2 == (rx + cx) % 2);
            }

            // build a key to ensure uniqueness
            key = to_string(cx) + "," + to_string(rx) + "-" +
                  to_string(cy) + "," + to_string(ry);
        } while (used.count(key));
        used.insert(key);

        // output in chess notation: column letter, row number, ...
        char cxs = char('A' + cx - 1);
        char cys = char('A' + cy - 1);
        println(string(1, cxs), rx, string(1, cys), ry);
    }

    return 0;
}
