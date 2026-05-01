#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool isSolvable(const vector<vector<int>>& board) {
    int N = (int)board.size();
    int inner = N - 2;
    if (inner <= 0) return false;
    int K = inner * inner; // number of interior cells (including interior walls)

    vector<bool> isWall(K, false);
    uint64_t startMask = 0;
    int marbleCnt = 0;

    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= N - 2; j++) {
            int id = (i - 1) * inner + (j - 1);
            if (board[i][j] == 1) {
                isWall[id] = true;
            } else if (board[i][j] == 2) {
                startMask |= (1ULL << id);
                marbleCnt++;
            }
        }
    }

    if (marbleCnt <= 1) return true;

    static const int dx[8] = {1,-1,0,0,1,1,-1,-1};
    static const int dy[8] = {0,0,1,-1,1,-1,1,-1};

    vector<vector<pair<int,int>>> moves(K);
    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= N - 2; j++) {
            int u = (i - 1) * inner + (j - 1);
            if (isWall[u]) continue;
            for (int d = 0; d < 8; d++) {
                int mi = i + dx[d], mj = j + dy[d];
                int di = i + 2 * dx[d], dj = j + 2 * dy[d];
                if (mi < 1 || mi > N - 2 || mj < 1 || mj > N - 2) continue;
                if (di < 1 || di > N - 2 || dj < 1 || dj > N - 2) continue;
                int midId = (mi - 1) * inner + (mj - 1);
                int destId = (di - 1) * inner + (dj - 1);
                if (isWall[midId] || isWall[destId]) continue;
                moves[u].push_back(make_pair(midId, destId));
            }
        }
    }

    queue<uint64_t> q;
    unordered_set<uint64_t> vis;
    q.push(startMask);
    vis.insert(startMask);

    while (!q.empty()) {
        uint64_t cur = q.front(); q.pop();
        if (__builtin_popcountll(cur) == 1) return true;

        uint64_t temp = cur;
        while (temp) {
            int u = __builtin_ctzll(temp);
            temp &= (temp - 1);
            if (isWall[u]) continue;
            const vector<pair<int,int>>& vec = moves[u];
            for (size_t idx = 0; idx < vec.size(); idx++) {
                int mid = vec[idx].first;
                int dest = vec[idx].second;
                if ( ((cur >> mid) & 1ULL) && !((cur >> dest) & 1ULL) ) {
                    uint64_t nxt = cur;
                    nxt &= ~(1ULL << u);
                    nxt &= ~(1ULL << mid);
                    nxt |= (1ULL << dest);
                    if (vis.insert(nxt).second) {
                        q.push(nxt);
                        if (vis.size() > 200000) // safety guard
                            return false;
                    }
                }
            }
        }
    }

    return false;
}

int sampleN() {
    int r = rnd.next(0, 99);
    if (r < 50) return rnd.next(3, 5);
    else if (r < 85) return rnd.next(6, 8);
    else return rnd.next(9, 10);
}

vector<vector<int>> makeEmptyBoard(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        board[0][i] = 1;
        board[N-1][i] = 1;
        board[i][0] = 1;
        board[i][N-1] = 1;
    }
    return board;
}

vector<vector<int>> getPredefined(int id) {
    if (id == 0) {
        // Example 1 from statement (Possible)
        vector<vector<int>> b = {
            {1,1,1,1,1},
            {1,2,2,0,1},
            {1,2,2,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}
        };
        return b;
    } else if (id == 1) {
        // Example 2 from statement (Impossible)
        vector<vector<int>> b = {
            {1,1,1,1,1},
            {1,2,2,0,1},
            {1,2,0,0,1},
            {1,0,0,2,1},
            {1,1,1,1,1}
        };
        return b;
    } else if (id == 2) {
        // Example 3 from statement (Possible, single marble)
        vector<vector<int>> b = {
            {1,1,1},
            {1,2,1},
            {1,1,1}
        };
        return b;
    } else {
        // Custom: requires a diagonal move to win
        // Only valid move is (1,1) -> (3,3) along diagonal
        vector<vector<int>> b = {
            {1,1,1,1,1},
            {1,2,1,1,1},
            {1,1,2,1,1},
            {1,1,1,0,1},
            {1,1,1,1,1}
        };
        return b;
    }
}

vector<vector<int>> generateBackwardSolvable(int N) {
    vector<vector<int>> board = makeEmptyBoard(N);
    int innerN = N - 2;
    int innerCells = innerN * innerN;

    // choose starting marble position
    int startIdx = rnd.next(0, innerCells - 1);
    int si = startIdx / innerN + 1;
    int sj = startIdx % innerN + 1;
    board[si][sj] = 2;

    int maxMarbles = min(7, innerCells);
    int targetMarbles = rnd.next(1, maxMarbles);
    int reverseSteps = targetMarbles - 1;

    static const int dx[8] = {1,-1,0,0,1,1,-1,-1};
    static const int dy[8] = {0,0,1,-1,1,-1,1,-1};

    for (int step = 0; step < reverseSteps; step++) {
        // collect current marbles
        vector<pair<int,int>> marbles;
        for (int i = 1; i <= N - 2; i++)
            for (int j = 1; j <= N - 2; j++)
                if (board[i][j] == 2)
                    marbles.push_back(make_pair(i, j));

        if (marbles.empty()) break;

        bool moved = false;
        for (int tries = 0; tries < 50 && !moved; tries++) {
            pair<int,int> p = rnd.any(marbles);
            int x = p.first, y = p.second; // current dest (forward)
            int dir = rnd.next(0, 7);
            int mx = x - dx[dir];
            int my = y - dy[dir];
            int sx = x - 2 * dx[dir];
            int sy = y - 2 * dy[dir];

            if (sx < 1 || sx > N - 2 || sy < 1 || sy > N - 2) continue;
            if (mx < 1 || mx > N - 2 || my < 1 || my > N - 2) continue;
            if (board[mx][my] != 0) continue;
            if (board[sx][sy] != 0) continue; // no internal walls in this generator

            // apply reverse move: dest -> empty, mid and src -> marbles
            board[x][y] = 0;
            board[mx][my] = 2;
            board[sx][sy] = 2;
            moved = true;
        }
        if (!moved) break;
    }

    return board;
}

vector<vector<int>> randomWallsAndMarbles(int N) {
    vector<vector<int>> board = makeEmptyBoard(N);
    int innerN = N - 2;

    // random internal walls
    double pWall;
    int wtype = rnd.next(0, 2);
    if (wtype == 0) pWall = 0.0;
    else if (wtype == 1) pWall = 0.15;
    else pWall = 0.30;

    int freeCells = 0;
    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= N - 2; j++) {
            if (rnd.next(0.0, 1.0) < pWall)
                board[i][j] = 1;
            else {
                board[i][j] = 0;
                freeCells++;
            }
        }
    }

    if (freeCells == 0) {
        // ensure at least one free interior cell
        int ri = rnd.next(1, N - 2);
        int rj = rnd.next(1, N - 2);
        board[ri][rj] = 0;
        freeCells = 1;
    }

    // collect free cells
    vector<pair<int,int>> empties;
    for (int i = 1; i <= N - 2; i++)
        for (int j = 1; j <= N - 2; j++)
            if (board[i][j] == 0)
                empties.push_back(make_pair(i, j));

    freeCells = (int)empties.size();
    int maxMarbles = min(7, freeCells);
    int M;

    if (maxMarbles == 1) {
        M = 1;
    } else if (maxMarbles == 2) {
        int r = rnd.next(0, 99);
        if (r < 50) M = 1;
        else M = 2;
    } else if (maxMarbles == 3) {
        int r = rnd.next(0, 99);
        if (r < 20) M = 1;
        else if (r < 60) M = 2;
        else M = 3;
    } else {
        int r = rnd.next(0, 99);
        if (r < 20) M = 1;
        else if (r < 50) M = 2;
        else if (r < 80) M = 3;
        else M = rnd.next(4, maxMarbles);
    }

    shuffle(empties.begin(), empties.end());
    for (int k = 0; k < M; k++) {
        int i = empties[k].first;
        int j = empties[k].second;
        board[i][j] = 2;
    }

    return board;
}

vector<vector<int>> generateRandomWithStatus(int N, bool wantSolvable) {
    vector<vector<int>> best;
    for (int tries = 0; tries < 100; tries++) {
        vector<vector<int>> board = randomWallsAndMarbles(N);
        bool solv = isSolvable(board);
        if (solv == wantSolvable)
            return board;
        best = board;
    }
    return best;
}

void outputBoard(const vector<vector<int>>& board) {
    int N = (int)board.size();
    println(N);
    for (int i = 0; i < N; i++) {
        println(board[i]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> board;
    int modeRand = rnd.next(0, 99);

    if (modeRand < 20) {
        // Predefined small, hand-crafted boards
        int exId = rnd.next(0, 3); // 0..3
        board = getPredefined(exId);
    } else if (modeRand < 60) {
        // Backward-generated solvable boards without internal walls
        int N = sampleN();
        board = generateBackwardSolvable(N);
    } else {
        // Random boards with walls, controlled solvable/impossible by BFS
        int N = sampleN();
        bool wantSolvable = (rnd.next(0, 1) == 1);
        board = generateRandomWithStatus(N, wantSolvable);
    }

    outputBoard(board);
    return 0;
}
