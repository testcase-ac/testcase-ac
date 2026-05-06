#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    const string faceColors = "WORBGY"; // White, Orange, Red, Blue, Green, Yellow

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read the three rows of the cube net
        // We'll store the 3x18 stickers in sticker[i][j]
        vector<vector<char>> sticker(3, vector<char>(18));
        for (int i = 0; i < 3; ++i) {
            string s = inf.readLine("[^]+", "cube_row");
            // No leading or trailing space
            ensuref(!s.empty(), "Case %d: cube row %d is empty", tc, i+1);
            ensuref(s.front() != ' ' && s.back() != ' ',
                    "Case %d: cube row %d has leading or trailing space", tc, i+1);
            // No consecutive spaces
            ensuref(s.find("  ") == string::npos,
                    "Case %d: cube row %d has consecutive spaces", tc, i+1);

            // Split on single spaces
            vector<string> tokens;
            size_t pos = 0;
            while (true) {
                size_t sp = s.find(' ', pos);
                if (sp == string::npos) {
                    tokens.push_back(s.substr(pos));
                    break;
                }
                tokens.push_back(s.substr(pos, sp - pos));
                pos = sp + 1;
            }
            ensuref(tokens.size() == 18,
                    "Case %d: cube row %d has %d tokens (expected 18)",
                    tc, i+1, (int)tokens.size());

            for (int j = 0; j < 18; ++j) {
                const string &tok = tokens[j];
                ensuref(tok.size() == 1,
                        "Case %d: cube row %d, token %d has length %d (expected 1)",
                        tc, i+1, j+1, (int)tok.size());
                char c = tok[0];
                ensuref(faceColors.find(c) != string::npos,
                        "Case %d: cube row %d, token %d is '%c' (invalid color)",
                        tc, i+1, j+1, c);
                sticker[i][j] = c;
            }
        }

        // Check that each color appears exactly 9 times
        vector<int> count(6, 0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 18; ++j) {
                char c = sticker[i][j];
                int idx = faceColors.find(c);
                count[idx]++;
            }
        }
        for (int k = 0; k < 6; ++k) {
            ensuref(count[k] == 9,
                    "Case %d: color '%c' appears %d times (expected 9)",
                    tc, faceColors[k], count[k]);
        }

        // Check that each face's center square has the fixed color
        // Face f spans token columns [3*f .. 3*f+2], center at token 3*f+1 on row 2 (index 1)
        for (int f = 0; f < 6; ++f) {
            int tokenIdx = 3 * f + 1;
            char actual = sticker[1][tokenIdx];
            char expected = faceColors[f];
            ensuref(actual == expected,
                    "Case %d: face %d center color is '%c' (expected '%c')",
                    tc, f+1, actual, expected);
        }

        // Read and validate the moves line
        string moves = inf.readLine("[^]+", "moves");
        int L = (int)moves.size();
        ensuref(L >= 1 && L <= 1000,
                "Case %d: number of moves must be between 1 and 1000, found %d",
                tc, L);
        // No spaces and only valid face letters
        ensuref(moves.find(' ') == string::npos,
                "Case %d: moves line contains spaces", tc);
        for (int i = 0; i < L; ++i) {
            char c = moves[i];
            ensuref(faceColors.find(c) != string::npos,
                    "Case %d: moves[%d] is '%c' (invalid move)", tc, i+1, c);
        }
    }

    inf.readEof();
    return 0;
}
