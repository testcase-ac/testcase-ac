#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N (keep it readable and under ~500 chars total output)
    int N;
    if (rnd.next(0, 1) == 0) {
        N = rnd.next(5, 11);   // often smaller
    } else {
        N = rnd.next(12, 20);  // sometimes medium
    }

    vector<string> g(N, string(N, '0'));

    int scenario = rnd.next(0, 8); // 0..8 → 9 different patterns

    switch (scenario) {
        case 0: {
            // All zeros
            // g already initialized to '0'
            break;
        }
        case 1: {
            // All ones
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    g[i][j] = '1';
            break;
        }
        case 2: {
            // A few isolated single houses (no 4-neighbour adjacency)
            int maxK = min(5, N * N);
            int K = rnd.next(1, maxK);
            int placed = 0;
            while (placed < K) {
                int x = rnd.next(0, N - 1);
                int y = rnd.next(0, N - 1);
                if (g[x][y] == '1') continue;
                bool ok = true;
                const int dx[4] = {1, -1, 0, 0};
                const int dy[4] = {0, 0, 1, -1};
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                        if (g[nx][ny] == '1') {
                            ok = false;
                            break;
                        }
                    }
                }
                if (!ok) continue;
                g[x][y] = '1';
                ++placed;
            }
            break;
        }
        case 3: {
            // Random Bernoulli grid with random density
            vector<double> probs = {0.15, 0.25, 0.35, 0.5, 0.7, 0.85};
            double p = probs[rnd.next((int)probs.size())];
            int cnt = 0;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j) {
                    if (rnd.next() < p) {
                        g[i][j] = '1';
                        ++cnt;
                    }
                }
            // Ensure not completely empty or completely full
            if (cnt == 0) {
                int x = rnd.next(0, N - 1);
                int y = rnd.next(0, N - 1);
                g[x][y] = '1';
            } else if (cnt == N * N) {
                int x = rnd.next(0, N - 1);
                int y = rnd.next(0, N - 1);
                g[x][y] = '0';
            }
            break;
        }
        case 4: {
            // A few compact clusters (using Manhattan-radius "blobs")
            int maxClusters = max(1, N / 4);
            maxClusters = min(maxClusters, 4);
            int k = rnd.next(1, maxClusters);
            vector<double> qs = {0.5, 0.7, 0.9, 1.0};

            int total = 0;
            for (int c = 0; c < k; ++c) {
                int cx = rnd.next(0, N - 1);
                int cy = rnd.next(0, N - 1);
                int R = rnd.next(1, min(3, N / 2));
                double q = qs[rnd.next((int)qs.size())];
                bool anyHere = false;
                for (int dx = -R; dx <= R; ++dx) {
                    for (int dy = -R; dy <= R; ++dy) {
                        if (abs(dx) + abs(dy) > R) continue;
                        int nx = cx + dx;
                        int ny = cy + dy;
                        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                        if (rnd.next() < q) {
                            if (g[nx][ny] == '0') {
                                g[nx][ny] = '1';
                                ++total;
                            }
                            anyHere = true;
                        }
                    }
                }
                if (!anyHere) {
                    if (g[cx][cy] == '0') {
                        g[cx][cy] = '1';
                        ++total;
                    }
                }
            }
            if (total == 0) {
                int x = rnd.next(0, N - 1);
                int y = rnd.next(0, N - 1);
                g[x][y] = '1';
            }
            break;
        }
        case 5: {
            // Diagonal patterns (main and optionally anti-diagonal)
            bool addAnti = rnd.next(0, 1);
            for (int i = 0; i < N; ++i) {
                g[i][i] = '1';
                if (addAnti) g[i][N - 1 - i] = '1';
            }
            break;
        }
        case 6: {
            // Checkerboard pattern (each house isolated by diagonals)
            bool onesOnEven = rnd.next(0, 1); // whether (i+j)%2==0 is '1'
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    bool even = ((i + j) & 1) == 0;
                    if (even == onesOnEven) g[i][j] = '1';
                }
            }
            break;
        }
        case 7: {
            // Stripes (rows/columns), maybe intersecting
            bool vertical = rnd.next(0, 1);
            if (vertical) {
                int num = rnd.next(1, min(3, N));
                vector<int> cols(N);
                for (int i = 0; i < N; ++i) cols[i] = i;
                shuffle(cols.begin(), cols.end());
                for (int t = 0; t < num; ++t) {
                    int c = cols[t];
                    for (int r = 0; r < N; ++r) g[r][c] = '1';
                }
                if (rnd.next(0, 1)) {
                    int numRows = rnd.next(1, min(2, N));
                    vector<int> rows(N);
                    for (int i = 0; i < N; ++i) rows[i] = i;
                    shuffle(rows.begin(), rows.end());
                    for (int t = 0; t < numRows; ++t) {
                        int r = rows[t];
                        for (int c = 0; c < N; ++c) g[r][c] = '1';
                    }
                }
            } else {
                int num = rnd.next(1, min(3, N));
                vector<int> rows(N);
                for (int i = 0; i < N; ++i) rows[i] = i;
                shuffle(rows.begin(), rows.end());
                for (int t = 0; t < num; ++t) {
                    int r = rows[t];
                    for (int c = 0; c < N; ++c) g[r][c] = '1';
                }
                if (rnd.next(0, 1)) {
                    int numCols = rnd.next(1, min(2, N));
                    vector<int> cols(N);
                    for (int i = 0; i < N; ++i) cols[i] = i;
                    shuffle(cols.begin(), cols.end());
                    for (int t = 0; t < numCols; ++t) {
                        int c = cols[t];
                        for (int r = 0; r < N; ++r) g[r][c] = '1';
                    }
                }
            }
            // Small random noise to break perfect regularity
            if (rnd.next(0, 1)) {
                double p = 0.08;
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < N; ++j)
                        if (rnd.next() < p)
                            g[i][j] = (g[i][j] == '1' ? '0' : '1');
            }
            break;
        }
        case 8: {
            // Single connected "snake" via random walk
            int maxSteps = max(N * N / 2, N);
            int steps = rnd.next(N, maxSteps);
            int x = rnd.next(0, N - 1);
            int y = rnd.next(0, N - 1);
            g[x][y] = '1';
            for (int s = 0; s < steps; ++s) {
                while (true) {
                    int dir = rnd.next(0, 3);
                    int dx = 0, dy = 0;
                    if (dir == 0) dx = 1;
                    if (dir == 1) dx = -1;
                    if (dir == 2) dy = 1;
                    if (dir == 3) dy = -1;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                    x = nx;
                    y = ny;
                    g[x][y] = '1';
                    break;
                }
            }
            break;
        }
    }

    // Randomly apply simple transformations for extra variety
    if (rnd.next(0, 1)) {
        // Horizontal flip
        for (int i = 0; i < N; ++i)
            reverse(g[i].begin(), g[i].end());
    }
    if (rnd.next(0, 1)) {
        // Vertical flip
        for (int i = 0; i < N / 2; ++i)
            swap(g[i], g[N - 1 - i]);
    }
    if (rnd.next(0, 1)) {
        // Transpose (since map is square)
        vector<string> t(N, string(N, '0'));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                t[j][i] = g[i][j];
        g.swap(t);
    }

    // Output
    println(N);
    for (int i = 0; i < N; ++i)
        println(g[i]);

    return 0;
}
