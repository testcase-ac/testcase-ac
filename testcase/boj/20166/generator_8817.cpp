#include "testlib.h"
using namespace std;

char randomCharFrom(const string &s) {
    return s[rnd.next((int)s.size() - 1)];
}

char randomCharExcept(char avoid) {
    while (true) {
        char c = 'a' + rnd.next(0, 25);
        if (c != avoid) return c;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 3);

    int N = 3, M = 3;
    vector<string> grid;
    vector<string> queries;

    if (scenario == 0) {
        // General random scenario with paths guaranteed by construction
        bool small = rnd.next(0, 99) < 70;
        if (small) {
            N = rnd.next(3, 5);
            M = rnd.next(3, 5);
        } else {
            N = rnd.next(6, 10);
            M = rnd.next(6, 10);
        }

        int alphabetSize = rnd.next(1, 5); // 1..5 letters
        char maxChar = 'a' + alphabetSize - 1;

        grid.assign(N, string(M, 'a'));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                grid[i][j] = 'a' + rnd.next(0, alphabetSize - 1);

        // Directions (8 neighbors)
        const int dr[8] = {-1,-1,-1,0,0,1,1,1};
        const int dc[8] = {-1,0,1,-1,1,-1,0,1};

        int baseQ = rnd.next(5, 15);
        // Queries that are guaranteed to exist (by walking on the grid)
        for (int qi = 0; qi < baseQ; ++qi) {
            int L = rnd.next(1, 5);
            int r = rnd.next(0, N - 1);
            int c = rnd.next(0, M - 1);
            string s;
            for (int step = 0; step < L; ++step) {
                s.push_back(grid[r][c]);
                if (step + 1 < L) {
                    int dir = rnd.next(0, 7);
                    r = (r + dr[dir] + N) % N;
                    c = (c + dc[dir] + M) % M;
                }
            }
            queries.push_back(s);
        }

        // Some random strings (may or may not be possible)
        int extraRandom = rnd.next(2, 5);
        for (int i = 0; i < extraRandom; ++i) {
            int L = rnd.next(1, 5);
            string s;
            for (int j = 0; j < L; ++j)
                s.push_back('a' + rnd.next(0, alphabetSize - 1));
            queries.push_back(s);
        }

        // Add duplicates
        int dups = rnd.next(0, baseQ / 2);
        for (int i = 0; i < dups; ++i) {
            int idx = rnd.next(0, (int)queries.size() - 1);
            queries.push_back(queries[idx]);
        }

        // Keep total K reasonable
        if ((int)queries.size() > 30)
            queries.resize(30);
        shuffle(queries.begin(), queries.end());
    } else if (scenario == 1) {
        // All-same-character grid scenario
        N = rnd.next(3, 7);
        M = rnd.next(3, 7);
        char c = randomCharFrom("abcde");

        grid.assign(N, string(M, c));

        // Strings of only the grid character
        for (int L = 1; L <= 5; ++L) {
            queries.push_back(string(L, c));
        }

        // Strings with other characters (impossible)
        char other = randomCharExcept(c);
        // Pure other char strings
        for (int i = 0; i < 3; ++i) {
            int L = rnd.next(1, 5);
            queries.push_back(string(L, other));
        }
        // Mixed strings containing both (also impossible because grid has only c)
        queries.push_back(string() + c + other);
        queries.push_back(string() + other + c);
        queries.push_back(string() + c + other + c);

        shuffle(queries.begin(), queries.end());
    } else if (scenario == 2) {
        // Checkerboard two-letter grid
        N = rnd.next(3, 8);
        M = rnd.next(3, 8);

        char a = randomCharFrom("abcde");
        char b = a;
        while (b == a) b = randomCharFrom("abcde");

        grid.assign(N, string(M, a));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                grid[i][j] = ((i + j) % 2 == 0 ? a : b);

        // Queries emphasizing parity and direction rules
        queries.push_back(string(1, a));
        queries.push_back(string(1, b));

        // Alternating patterns (need orth moves)
        queries.push_back("ab");
        queries.push_back("ba");
        queries.push_back("aba");
        queries.push_back("bab");
        queries.push_back("ababa");
        queries.push_back("babab");

        // Same-letter patterns (need diagonal moves)
        queries.push_back(string(2, a));
        queries.push_back(string(3, a));
        queries.push_back(string(4, a));
        queries.push_back(string(5, a));
        queries.push_back(string(2, b));
        queries.push_back(string(3, b));

        // A few random short strings from {a,b}
        int extra = rnd.next(2, 5);
        for (int i = 0; i < extra; ++i) {
            int L = rnd.next(1, 5);
            string s;
            for (int j = 0; j < L; ++j)
                s.push_back(rnd.next(0, 1) == 0 ? a : b);
            queries.push_back(s);
        }

        shuffle(queries.begin(), queries.end());
    } else if (scenario == 3) {
        // Corner wrap / diagonal wrap stress on 3x3
        N = 3; M = 3;
        // Fixed 3x3 grid with unique letters
        grid = {
            "abc",
            "def",
            "ghi"
        };
        // Corners: a(1,1), c(1,3), g(3,1), i(3,3)
        // Strings that require wrap adjacency between unique letters
        vector<string> base = {
            "ag", "ga", // vertical wrap
            "ac", "ca", // horizontal wrap
            "ai", "ia", // diagonal wrap
            "cg", "gc", // another diagonal wrap
            "ci", "ic", // non-wrap diagonal inside
            "bd", "db", // non-wrap adjacency, for comparison
            "af", "fa", // non-wrap diagonal (inside grid)
            "aei", "iga", "cag", "gca"
        };
        queries = base;

        // Add a few random single letters and pairs
        int extra = rnd.next(2, 5);
        for (int i = 0; i < extra; ++i) {
            int L = rnd.next(1, 3);
            string s;
            for (int j = 0; j < L; ++j) {
                char c = 'a' + rnd.next(0, 8);
                s.push_back(c);
            }
            queries.push_back(s);
        }

        shuffle(queries.begin(), queries.end());
    }

    int K = (int)queries.size();
    if (K == 0) {
        // Fallback safety: shouldn't happen, but ensure at least one query
        queries.push_back("a");
        K = 1;
    }

    println(N, M, K);
    for (int i = 0; i < N; ++i)
        println(grid[i]);
    for (int i = 0; i < K; ++i)
        println(queries[i]);

    return 0;
}
