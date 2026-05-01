#include "testlib.h"
#include <queue>
using namespace std;

bool beats(char a, char b) {
    return (a == 'R' && b == 'S') ||
           (a == 'S' && b == 'P') ||
           (a == 'P' && b == 'R');
}

char moveThatBeats(char f) {
    if (f == 'R') return 'P';
    if (f == 'P') return 'S';
    return 'R'; // f == 'S'
}

bool findSolution(const vector<string>& a, int N, int M, int K, int &bestP, string &bestMoves) {
    int SZ = 1 << N;
    int totalStates = (M + 1) * SZ;

    vector<int> dist(totalStates, -1);
    vector<int> prev(totalStates, -1);
    vector<char> prevMove(totalStates, '?');

    int startMask = SZ - 1;
    int startIndex = 0 * SZ + startMask;
    dist[startIndex] = 0;

    queue<int> q;
    q.push(startIndex);

    int successIndex = -1;
    int successR = -1;

    const char moves[3] = {'R', 'P', 'S'};

    while (!q.empty() && successIndex == -1) {
        int idx = q.front(); q.pop();
        int r = idx / SZ;
        int mask = idx % SZ;

        if (r == M) continue;

        for (int mi = 0; mi < 3; ++mi) {
            char f = moves[mi];
            int nextMask = 0;
            for (int i = 0; i < N; ++i) {
                if (mask & (1 << i)) {
                    if (beats(a[i][r], f)) {
                        nextMask |= (1 << i);
                    }
                }
            }
            int alive = __builtin_popcount(nextMask);
            int nr = r + 1;

            if (alive >= 1 && alive <= K) {
                successIndex = nr * SZ + nextMask;
                successR = nr;
                prev[successIndex] = idx;
                prevMove[successIndex] = f;
                break;
            } else if (alive == 0) {
                continue;
            } else { // alive > K
                if (nr <= M) {
                    int nidx = nr * SZ + nextMask;
                    if (dist[nidx] == -1) {
                        dist[nidx] = dist[idx] + 1;
                        prev[nidx] = idx;
                        prevMove[nidx] = f;
                        q.push(nidx);
                    }
                }
            }
        }
    }

    if (successIndex == -1) return false;

    string path;
    int cur = successIndex;
    int startIndexCheck = 0 * SZ + (SZ - 1);
    while (cur != startIndexCheck) {
        char f = prevMove[cur];
        path.push_back(f);
        cur = prev[cur];
    }
    reverse(path.begin(), path.end());

    bestP = successR;
    bestMoves = path;
    return true;
}

vector<string> generateIdenticalImpossible(int &N, int &M, int &K) {
    N = rnd.next(2, 15);
    M = rnd.next(1, 20);
    K = rnd.next(1, N - 1);

    vector<string> a(N, string(M, 'R'));
    string s(M, 'R');
    if (rnd.next(0, 1) == 0) {
        char c = rnd.any(string("RSP"));
        for (int i = 0; i < M; ++i) s[i] = c;
    } else {
        for (int i = 0; i < M; ++i) s[i] = rnd.any(string("RSP"));
    }
    for (int i = 0; i < N; ++i) a[i] = s;
    return a;
}

vector<string> generateConstructiveSolvable(int &N, int &M, int &K) {
    N = rnd.next(2, 15);
    M = rnd.next(1, 20);

    bool forceK1 = (rnd.next(0, 3) == 0);
    if (forceK1) {
        K = 1;
    } else {
        K = rnd.next(1, N - 1);
    }

    int P = rnd.next(1, M);
    int W = rnd.next(1, K);

    vector<string> a(N, string(M, 'R'));
    string F(P, 'R');

    const char moves[3] = {'R', 'P', 'S'};
    for (int r = 0; r < P; ++r) {
        char f = moves[rnd.next(0, 2)];
        F[r] = f;
        char winnerMove = moveThatBeats(f);
        for (int i = 0; i < W; ++i) {
            a[i][r] = winnerMove;
        }
    }
    for (int i = 0; i < W; ++i) {
        for (int r = P; r < M; ++r) {
            a[i][r] = rnd.any(string("RSP"));
        }
    }
    for (int i = W; i < N; ++i) {
        bool allBeat = true;
        for (int r = 0; r < P; ++r) {
            char c = rnd.any(string("RSP"));
            a[i][r] = c;
            if (!beats(c, F[r])) allBeat = false;
        }
        if (allBeat && P > 0) {
            int rr = rnd.next(0, P - 1);
            char f = F[rr];
            string opts = "RSP";
            string cand;
            for (char c : opts) {
                if (!beats(c, f)) cand.push_back(c);
            }
            a[i][rr] = rnd.any(cand);
        }
        for (int r = P; r < M; ++r) {
            a[i][r] = rnd.any(string("RSP"));
        }
    }
    return a;
}

vector<string> generateRandomGame(int N, int M) {
    vector<string> a(N, string(M, 'R'));
    int patternType = rnd.next(0, 2);

    if (patternType == 0) {
        for (int i = 0; i < N; ++i)
            for (int r = 0; r < M; ++r)
                a[i][r] = rnd.any(string("RSP"));
    } else if (patternType == 1) {
        for (int i = 0; i < N; ++i) {
            char c = rnd.any(string("RSP"));
            for (int r = 0; r < M; ++r) a[i][r] = c;
        }
    } else {
        for (int r = 0; r < M; ++r) {
            char c = rnd.any(string("RSP"));
            for (int i = 0; i < N; ++i) a[i][r] = c;
        }
    }
    return a;
}

vector<string> generateRandomSolvable(int &N, int &M, int &K) {
    for (int attempt = 0; attempt < 300; ++attempt) {
        N = rnd.next(2, 15);
        M = rnd.next(1, 20);
        K = rnd.next(1, N - 1);

        vector<string> a = generateRandomGame(N, M);

        int bestP; string bestMoves;
        if (findSolution(a, N, M, K, bestP, bestMoves)) {
            return a;
        }
    }
    return generateConstructiveSolvable(N, M, K);
}

vector<string> generateRandomImpossible(int &N, int &M, int &K) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        N = rnd.next(2, 15);
        M = rnd.next(1, 20);
        if (rnd.next(0, 2) == 0) K = 1;
        else K = rnd.next(1, N - 1);

        vector<string> a = generateRandomGame(N, M);

        int bestP; string bestMoves;
        if (!findSolution(a, N, M, K, bestP, bestMoves)) {
            return a;
        }
    }
    return generateIdenticalImpossible(N, M, K);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M, K;
    vector<string> a;

    int scenario = rnd.next(0, 3);

    if (scenario == 0) {
        a = generateIdenticalImpossible(N, M, K);
    } else if (scenario == 1) {
        a = generateConstructiveSolvable(N, M, K);
    } else if (scenario == 2) {
        a = generateRandomSolvable(N, M, K);
    } else {
        a = generateRandomImpossible(N, M, K);
    }

    println(N, M, K);
    for (int i = 0; i < N; ++i) {
        println(a[i]);
    }

    return 0;
}
