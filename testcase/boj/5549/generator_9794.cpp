#include "testlib.h"
using namespace std;

struct Query {
    int a, b, c, d;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<char> terrain = {'J', 'O', 'I'};

    int scenario = rnd.next(0, 6);
    int M, N;

    // Choose M, N based on scenario
    if (scenario == 0) {
        // Tiny grid
        M = rnd.next(1, 3);
        N = rnd.next(1, 3);
    } else if (scenario == 1) {
        // Single row or single column
        if (rnd.next(0, 1) == 0) {
            M = 1;
            N = rnd.next(1, 10);
        } else {
            M = rnd.next(1, 10);
            N = 1;
        }
    } else if (scenario == 6) {
        // Near-max compact grid
        M = rnd.next(8, 10);
        N = rnd.next(8, 10);
    } else {
        // General medium grid
        M = rnd.next(2, 10);
        N = rnd.next(2, 10);
    }

    vector<string> grid(M, string(N, 'J'));

    // Fill grid pattern based on scenario
    if (scenario == 2) {
        // Uniform terrain
        char ch = rnd.any(terrain);
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                grid[i][j] = ch;
    } else if (scenario == 3) {
        // Stripes (horizontal or vertical)
        char p[3];
        vector<char> perm = terrain;
        shuffle(perm.begin(), perm.end());
        for (int i = 0; i < 3; ++i) p[i] = perm[i];

        bool horizontal = (rnd.next(0, 1) == 0);
        if (horizontal) {
            for (int i = 0; i < M; ++i) {
                char ch = p[i % 3];
                for (int j = 0; j < N; ++j)
                    grid[i][j] = ch;
            }
        } else {
            for (int j = 0; j < N; ++j) {
                char ch = p[j % 3];
                for (int i = 0; i < M; ++i)
                    grid[i][j] = ch;
            }
        }
    } else if (scenario == 4) {
        // Checkerboard with two main terrains, optional third
        char c1 = rnd.any(terrain);
        char c2 = c1;
        while (c2 == c1) c2 = rnd.any(terrain);
        char c3 = 'X';
        for (char t : terrain)
            if (t != c1 && t != c2) c3 = t;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                char ch = ((i + j) % 2 == 0) ? c1 : c2;
                // Small chance to use third kind
                if (c3 != 'X' && rnd.next(0, 9) == 0)
                    ch = c3;
                grid[i][j] = ch;
            }
        }
    } else if (scenario == 5) {
        // Biased random: one terrain dominates
        char major = rnd.any(terrain);
        vector<char> minor;
        for (char t : terrain) if (t != major) minor.push_back(t);
        int majorProb = rnd.next(65, 90); // percentage

        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j) {
                int x = rnd.next(0, 99);
                if (x < majorProb) grid[i][j] = major;
                else grid[i][j] = rnd.any(minor);
            }
    } else {
        // 0,1,6: plain random
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                grid[i][j] = rnd.any(terrain);
    }

    // Determine K (number of queries), keeping input compact
    int area = M * N;
    int maxK;
    if (area <= 4) maxK = 6;
    else if (area <= 25) maxK = 15;
    else maxK = 20;
    if (maxK < 1) maxK = 1;
    int K = rnd.next(1, maxK);

    vector<Query> queries;

    // Helper to add a query
    auto addQuery = [&](int a, int b, int c, int d) {
        queries.push_back(Query{a, b, c, d});
    };

    // Basic structured queries
    if ((int)queries.size() < K) {
        // Whole map
        addQuery(1, 1, M, N);
    }
    if ((int)queries.size() < K) {
        // Single cell, random
        int x = rnd.next(1, M);
        int y = rnd.next(1, N);
        addQuery(x, y, x, y);
    }
    if (M > 1 && (int)queries.size() < K) {
        // Full random row
        int r = rnd.next(1, M);
        addQuery(r, 1, r, N);
    }
    if (N > 1 && (int)queries.size() < K) {
        // Full random column
        int c = rnd.next(1, N);
        addQuery(1, c, M, c);
    }
    if (M > 1 && N > 1 && (int)queries.size() < K) {
        // Random sub-rectangle
        int a = rnd.next(1, M);
        int c = rnd.next(a, M);
        int b = rnd.next(1, N);
        int d = rnd.next(b, N);
        addQuery(a, b, c, d);
    }

    // Fill remaining with diverse random rectangles (and some duplicates)
    while ((int)queries.size() < K) {
        if (!queries.empty() && rnd.next(0, 4) == 0) {
            // 20% chance: duplicate an existing query
            Query q = rnd.any(queries);
            addQuery(q.a, q.b, q.c, q.d);
            continue;
        }

        int a = 1, b = 1, c = M, d = N;
        int choice = rnd.next(0, 3);

        if (choice == 0 && M > 1) {
            // Row query (maybe partial)
            a = c = rnd.next(1, M);
            if (rnd.next(0, 1) == 0) {
                b = 1; d = N;
            } else {
                b = rnd.next(1, N);
                d = rnd.next(b, N);
            }
        } else if (choice == 1 && N > 1) {
            // Column query (maybe partial)
            b = d = rnd.next(1, N);
            if (rnd.next(0, 1) == 0) {
                a = 1; c = M;
            } else {
                a = rnd.next(1, M);
                c = rnd.next(a, M);
            }
        } else {
            // General rectangle, sometimes 1x1
            a = rnd.next(1, M);
            c = rnd.next(a, M);
            b = rnd.next(1, N);
            d = rnd.next(b, N);
            // Small chance to force a single cell
            if (rnd.next(0, 9) == 0) {
                a = c;
                b = d;
            }
        }

        addQuery(a, b, c, d);
    }

    // Shuffle queries for randomness
    shuffle(queries.begin(), queries.end());

    // Output
    println(M, N);
    println(K);
    for (int i = 0; i < M; ++i)
        println(grid[i]);
    for (const Query &q : queries)
        println(q.a, q.b, q.c, q.d);

    return 0;
}
