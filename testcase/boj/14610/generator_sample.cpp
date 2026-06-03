#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeSolvedCounts(int n, int m, bool forceMiddle) {
    vector<int> counts(n);
    int hi = forceMiddle ? m - 1 : m;
    int lo = forceMiddle ? 1 : 0;

    counts[0] = rnd.next(lo, hi);
    for (int i = 1; i < n; ++i) {
        counts[i] = rnd.next(lo, counts[i - 1]);
    }

    return counts;
}

vector<vector<int>> makeBoard(const vector<int>& counts, int m, bool coverAllProblems) {
    int n = int(counts.size());
    vector<vector<int>> board(n, vector<int>(m, 0));
    vector<int> remaining = counts;

    if (coverAllProblems) {
        vector<int> problems(m);
        for (int j = 0; j < m; ++j) {
            problems[j] = j;
        }
        shuffle(problems.begin(), problems.end());

        for (int problem : problems) {
            vector<int> candidates;
            for (int i = 0; i < n; ++i) {
                if (remaining[i] > 0) {
                    candidates.push_back(i);
                }
            }
            if (candidates.empty()) {
                break;
            }
            int row = rnd.any(candidates);
            board[row][problem] = 1;
            --remaining[row];
        }
    }

    for (int i = 0; i < n; ++i) {
        vector<int> zeros;
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 0) {
                zeros.push_back(j);
            }
        }
        shuffle(zeros.begin(), zeros.end());
        for (int take = 0; take < remaining[i] && take < int(zeros.size()); ++take) {
            board[i][zeros[take]] = 1;
        }
    }

    return board;
}

vector<int> makeVisiblePrefixes(int n, int m) {
    vector<int> prefixes(n);
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int prefix = rnd.next(0, m);
        fill(prefixes.begin(), prefixes.end(), prefix);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            prefixes[i] = i * m / max(1, n - 1);
        }
    } else {
        prefixes[0] = rnd.next(0, m);
        for (int i = 1; i < n; ++i) {
            prefixes[i] = rnd.next(prefixes[i - 1], m);
        }
    }

    return prefixes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(2, 8);
    int n = rnd.next(2, 14);

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 4);
    } else if (mode == 5) {
        n = rnd.next(15, 35);
        m = rnd.next(6, 10);
    }

    bool forceMiddle = m > 1 && rnd.next(0, 99) < 70;
    vector<int> counts = makeSolvedCounts(n, m, forceMiddle);

    if (mode == 2 && m > 1) {
        counts[0] = m;
    } else if (mode == 3) {
        counts[n - 1] = 0;
    }
    sort(counts.rbegin(), counts.rend());

    bool coverAllProblems = mode != 4;
    vector<vector<int>> board = makeBoard(counts, m, coverAllProblems);
    vector<int> prefixes = makeVisiblePrefixes(n, m);

    println(n, m);
    for (int i = 0; i < n; ++i) {
        printf("%d", counts[i]);
        for (int j = 0; j < m; ++j) {
            printf(" %d", j < prefixes[i] ? board[i][j] : -1);
        }
        printf("\n");
    }

    return 0;
}
