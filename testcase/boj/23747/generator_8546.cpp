#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // --- Choose grid size (keep small but varied) ---
    int maxSide = 12;
    int R = rnd.next(1, maxSide);
    int C = rnd.next(1, maxSide);

    // With some probability, make the grid 1D (row or column)
    int shapeType = rnd.next(0, 3);
    if (shapeType == 0) {
        R = 1;
        C = rnd.next(1, maxSide);
    } else if (shapeType == 1) {
        C = 1;
        R = rnd.next(1, maxSide);
    }
    // R, C are between 1 and 12, so R*C <= 144

    // --- Generate grid pattern ---
    vector<string> g(R, string(C, 'a'));

    int patternType = rnd.next(0, 4);
    if (patternType == 0) {
        // All same letter: single huge region
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                g[i][j] = 'a';
    } else if (patternType == 1) {
        // No orthogonally adjacent equal letters (many tiny regions)
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                vector<char> options;
                for (char ch = 'a'; ch <= 'd'; ++ch) {
                    if (i > 0 && g[i - 1][j] == ch) continue;
                    if (j > 0 && g[i][j - 1] == ch) continue;
                    options.push_back(ch);
                }
                g[i][j] = rnd.any(options);
            }
        }
    } else if (patternType == 2) {
        // Completely random letters from a small alphabet
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                g[i][j] = char('a' + rnd.next(0, 3)); // a-d
    } else if (patternType == 3) {
        // Stripes (horizontal or vertical)
        bool horizontal = rnd.next(0, 1);
        vector<char> letters = {'a', 'b', 'c', 'd'};
        shuffle(letters.begin(), letters.end());
        int K = rnd.next(2, 4); // use first K letters
        if (horizontal) {
            for (int i = 0; i < R; ++i) {
                char ch = letters[i % K];
                for (int j = 0; j < C; ++j)
                    g[i][j] = ch;
            }
        } else {
            for (int j = 0; j < C; ++j) {
                char ch = letters[j % K];
                for (int i = 0; i < R; ++i)
                    g[i][j] = ch;
            }
        }
    } else {
        // Big rectangular block of a unique letter inside other letters
        // First fill with non-'a' letters avoiding equal neighbors (up/left)
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                vector<char> options;
                for (char ch = 'b'; ch <= 'e'; ++ch) {
                    if (i > 0 && g[i - 1][j] == ch) continue;
                    if (j > 0 && g[i][j - 1] == ch) continue;
                    options.push_back(ch);
                }
                g[i][j] = rnd.any(options);
            }
        }
        // Overlay a random rectangle of 'a'
        int r1 = rnd.next(0, R - 1);
        int r2 = rnd.next(r1, R - 1);
        int c1 = rnd.next(0, C - 1);
        int c2 = rnd.next(c1, C - 1);
        for (int i = r1; i <= r2; ++i)
            for (int j = c1; j <= c2; ++j)
                g[i][j] = 'a';
    }

    // --- Choose starting position ---
    int HR = rnd.next(1, R);
    int HC = rnd.next(1, C);

    // --- Generate movement / ward log ---
    int moveScenario = rnd.next(0, 4);
    int L = 0;
    double pWard = 0.0;
    bool requireWard = false;

    if (moveScenario == 0) {
        // Very short path, maybe few wards
        L = rnd.next(1, 5);
        pWard = 0.3;
        requireWard = false;
    } else if (moveScenario == 1) {
        // Mostly movement, possibly no wards
        L = rnd.next(1, 40);
        pWard = 0.0;
        requireWard = false;
    } else if (moveScenario == 2) {
        // Many wards
        L = rnd.next(1, 60);
        pWard = 0.7;
        requireWard = true;
    } else if (moveScenario == 3) {
        // Longer mixed walk
        L = rnd.next(30, 120);
        pWard = 0.3;
        requireWard = true;
    } else {
        // Mostly wards, little movement
        L = rnd.next(1, 40);
        pWard = 0.9;
        requireWard = false;
    }

    string s;
    s.reserve(L > 0 ? L : 1);
    int r = HR, c = HC;
    bool hasWard = false;

    for (int i = 0; i < L; ++i) {
        // Determine possible move directions
        vector<char> dirs;
        if (r > 1) dirs.push_back('U');
        if (r < R) dirs.push_back('D');
        if (c > 1) dirs.push_back('L');
        if (c < C) dirs.push_back('R');

        bool mustWard = dirs.empty();
        bool doWard = false;

        if (!mustWard && pWard > 0.0) {
            int threshold = int(pWard * 1000.0 + 0.5);
            if (rnd.next(0, 999) < threshold)
                doWard = true;
        }

        if (doWard || mustWard) {
            s.push_back('W');
            hasWard = true;
        } else {
            char d = rnd.any(dirs);
            s.push_back(d);
            if (d == 'U') --r;
            else if (d == 'D') ++r;
            else if (d == 'L') --c;
            else if (d == 'R') ++c;
        }
    }

    // Ensure at least one ward in scenarios that require it
    if (requireWard && L > 0 && !hasWard) {
        s[L - 1] = 'W';
        hasWard = true;
    }

    // Just in case (defensive): guarantee non-empty log and valid characters
    if (s.empty()) {
        s = "W";
        L = 1;
    }

    // --- Output ---
    println(R, C);
    for (int i = 0; i < R; ++i)
        println(g[i]);
    println(HR, HC);
    println(s);

    return 0;
}
