#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base sample for n = 2, m = 2
    const vector<string> base2x2 = {
        "  +---+",
        " /     \\",
        "+   *   +---+",
        " \\     /     \\",
        "  +---+   *   +",
        " /           /",
        "+   *   +   +",
        " \\           \\",
        "  +---+   *   +",
        "       \\     /",
        "        +---+"
    };

    // Optionally also sometimes use the unmodified 2x3 sample
    const vector<string> base2x3 = {
        "  +---+       +---+",
        " /     \\     /     \\",
        "+   *   +---+       +",
        " \\           \\     /",
        "  +---+   *   +---+",
        " /                 \\",
        "+   *   +---+   *   +",
        " \\                 /",
        "  +---+   *   +---+",
        "       \\     /",
        "        +---+"
    };

    auto hasNonSpaceAfter = [](const string &s, int pos) -> bool {
        for (int k = pos + 1; k < (int)s.size(); ++k)
            if (s[k] != ' ')
                return true;
        return false;
    };

    int T = rnd.next(1, 2);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        bool use2x3 = (rnd.next(0, 5) == 0); // rarely use the fixed 2x3 case

        if (use2x3) {
            int n = 2, m = 3;
            println(n, m);
            for (const string &s : base2x3) println(s);
            continue;
        }

        // Work with 2x2 grid, but randomize edges
        vector<string> g = base2x2;
        int H = (int)g.size();

        // Edge randomization mode:
        // 0 - slight random changes around original
        // 1 - all edges blocked
        // 2 - all edges traversable
        // 3 - fully random
        int modeEdge = rnd.next(0, 3);

        auto decideTravFromCurr = [&](bool currTrav) -> bool {
            if (modeEdge == 1) return false;
            if (modeEdge == 2) return true;
            if (modeEdge == 3) return (rnd.next(0, 1) == 1);
            // modeEdge == 0 : keep most of the time, flip with small probability
            if (rnd.next(0, 3) == 0) return !currTrav; // 1/4 flip
            return currTrav;
        };

        // Randomize horizontal edges: "+---+" or "+   +" patterns
        for (int i = 0; i < H; ++i) {
            int W = (int)g[i].size();
            for (int j = 0; j + 4 < W; ++j) {
                if (g[i][j] == '+' && g[i][j + 4] == '+') {
                    char c1 = g[i][j + 1], c2 = g[i][j + 2], c3 = g[i][j + 3];
                    if (c1 == c2 && c2 == c3 && (c1 == ' ' || c1 == '-')) {
                        bool currTrav = (c1 == ' ');
                        bool trav = decideTravFromCurr(currTrav);
                        char newChar = trav ? ' ' : '-';
                        g[i][j + 1] = g[i][j + 2] = g[i][j + 3] = newChar;
                    }
                }
            }
        }

        // Randomize diagonal edges: '/' or '\' characters (but never the last non-space in a line)
        for (int i = 0; i < H; ++i) {
            int W = (int)g[i].size();
            for (int j = 0; j < W; ++j) {
                if (g[i][j] == '/' || g[i][j] == '\\') {
                    if (!hasNonSpaceAfter(g[i], j)) continue; // keep boundary edges solid
                    bool currTrav = false; // '/' or '\' means blocked
                    bool trav = decideTravFromCurr(currTrav);
                    g[i][j] = trav ? ' ' : g[i][j];
                }
            }
        }

        int n = 2, m = 2;
        println(n, m);
        for (const string &s : g) println(s);
    }

    return 0;
}
