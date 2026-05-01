#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int maxN = 14;

    // Choose N with bias towards small/medium sizes
    int N;
    int choice = rnd.next(0, 9);
    if (choice < 3) {
        N = rnd.next(1, 4);          // small
    } else if (choice < 8) {
        N = rnd.next(5, 10);         // medium
    } else {
        N = rnd.next(11, maxN);      // larger but still readable
    }

    // Choose K with bias towards small/moderate, sometimes multiple of 4
    int maxK = 20;
    if (rnd.next(0, 9) == 0) maxK = 40; // 10% chance of larger K
    int K;
    bool multipleOf4 = (rnd.next(0, 3) == 0); // 1/4 chance
    if (multipleOf4) {
        int m = rnd.next(1, maxK / 4);
        K = 4 * m;
    } else {
        K = rnd.next(1, maxK);
    }

    // Initialize empty board
    vector<string> grid(N, string(N, '.'));

    // Choose board pattern type
    int boardType = rnd.next(0, 5);
    if (boardType == 4 && N < 3) boardType = 1; // cross pattern needs N>=3

    // Generate walls according to boardType
    switch (boardType) {
        case 0: { // a few horizontal floors
            int floors = rnd.next(1, max(1, N / 2));
            for (int i = 0; i < floors; i++) {
                int r = (N == 1 ? 0 : rnd.wnext(N, 2)); // bias towards bottom
                int minLen = 1;
                int maxLenSeg = N;
                int len = rnd.next(minLen, maxLenSeg);
                int start = rnd.next(0, N - len);
                for (int c = start; c < start + len; c++)
                    grid[r][c] = 'X';
            }
            break;
        }
        case 1: { // random scatter
            int density = rnd.next(15, 50); // percent
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (rnd.next(100) < density)
                        grid[r][c] = 'X';
                }
            }
            break;
        }
        case 2: { // horizontal segments on many rows
            for (int r = 0; r < N; r++) {
                if (rnd.next(100) < 60) {
                    int segs = (N == 1 ? 1 : rnd.next(1, 2));
                    for (int s = 0; s < segs; s++) {
                        int len = rnd.next(1, N);
                        int start = rnd.next(0, N - 1);
                        int end = start + len - 1;
                        if (end >= N) end = N - 1;
                        for (int c = start; c <= end; c++)
                            grid[r][c] = 'X';
                    }
                }
            }
            break;
        }
        case 3: { // vertical walls
            int numCols = rnd.next(1, max(1, N / 2));
            vector<int> cols(N);
            for (int i = 0; i < N; i++) cols[i] = i;
            shuffle(cols.begin(), cols.end());
            for (int i = 0; i < numCols; i++) {
                int col = cols[i];
                for (int r = 0; r < N; r++) {
                    if (rnd.next(100) < 80)
                        grid[r][col] = 'X';
                }
            }
            break;
        }
        case 4: { // cross in the middle + some random walls
            int mid = N / 2;
            for (int c = 0; c < N; c++)
                grid[mid][c] = 'X';
            for (int r = 0; r < N; r++)
                grid[r][mid] = 'X';
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (grid[r][c] == '.' && rnd.next(100) < 10)
                        grid[r][c] = 'X';
                }
            }
            break;
        }
        case 5: { // empty board (no walls)
            // already all '.'
            break;
        }
    }

    // Find candidate positions for the ball ('.' with support below or at bottom)
    vector< pair<int,int> > cand;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (grid[r][c] == '.' && (r == N - 1 || grid[r + 1][c] == 'X')) {
                cand.push_back(make_pair(r, c));
            }
        }
    }

    // Ensure at least one valid position by forcing a bottom cell to be empty if needed
    if (cand.empty()) {
        int col = rnd.next(0, N - 1);
        grid[N - 1][col] = '.';
        // recompute candidates
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (grid[r][c] == '.' && (r == N - 1 || grid[r + 1][c] == 'X')) {
                    cand.push_back(make_pair(r, c));
                }
            }
        }
    }

    // Place the single ball 'L'
    int idx = rnd.next(0, (int)cand.size() - 1);
    int br = cand[idx].first;
    int bc = cand[idx].second;
    grid[br][bc] = 'L';

    // Generate rotation sequence
    string ops(K, 'L');
    int dirType = rnd.next(0, 4);
    if (dirType == 0) {
        // Completely random directions
        for (int i = 0; i < K; i++) {
            ops[i] = (rnd.next(0, 1) == 0 ? 'L' : 'D');
        }
    } else if (dirType == 1) {
        // All 'L'
        for (int i = 0; i < K; i++) ops[i] = 'L';
    } else if (dirType == 2) {
        // All 'D'
        for (int i = 0; i < K; i++) ops[i] = 'D';
    } else if (dirType == 3) {
        // Alternating pattern
        char first = (rnd.next(0, 1) == 0 ? 'L' : 'D');
        char second = (first == 'L' ? 'D' : 'L');
        for (int i = 0; i < K; i++) {
            ops[i] = (i % 2 == 0 ? first : second);
        }
    } else {
        // Repeated 3-length pattern
        vector<string> patterns;
        patterns.push_back("LLD");
        patterns.push_back("LDD");
        patterns.push_back("LDL");
        patterns.push_back("DLL");
        string pat = rnd.any(patterns);
        int plen = (int)pat.size();
        for (int i = 0; i < K; i++) {
            ops[i] = pat[i % plen];
        }
    }

    // Output
    println(N, K);
    for (int r = 0; r < N; r++) {
        println(grid[r]);
    }
    for (int i = 0; i < K; i++) {
        println(ops[i]);
    }

    return 0;
}
