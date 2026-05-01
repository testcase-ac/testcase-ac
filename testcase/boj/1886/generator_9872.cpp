#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(3, 12);
    int M = rnd.next(3, 12);

    vector<string> g(N, string(M, 'X'));

    int scenario = rnd.next(0, 3); // 0..3

    if (scenario == 0) {
        // No exits, random interior
        double pDot = 0.3 + 0.4 * rnd.next(); // 0.3 ~ 0.7
        int dotCnt = 0;
        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < M - 1; ++j) {
                if (rnd.next() < pDot) {
                    g[i][j] = '.';
                    dotCnt++;
                }
            }
        }
        if (dotCnt == 0) {
            int ri = rnd.next(1, N - 2);
            int rj = rnd.next(1, M - 2);
            g[ri][rj] = '.';
        }
        // Borders remain 'X', no 'D'
    } else if (scenario == 1) {
        // Single exit, all interior empty
        for (int i = 1; i < N - 1; ++i)
            for (int j = 1; j < M - 1; ++j)
                g[i][j] = '.';

        // Choose one border cell as exit
        vector<pair<int,int>> border;
        for (int i = 0; i < N; ++i) {
            border.emplace_back(i, 0);
            border.emplace_back(i, M - 1);
        }
        for (int j = 1; j < M - 1; ++j) {
            border.emplace_back(0, j);
            border.emplace_back(N - 1, j);
        }
        shuffle(border.begin(), border.end());
        auto [ei, ej] = border[0];
        g[ei][ej] = 'D';
        // other borders remain 'X'
    } else if (scenario == 2) {
        // Random interior, multiple random exits
        double pDot = 0.4 + 0.2 * rnd.next(); // 0.4 ~ 0.6
        int dotCnt = 0;
        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < M - 1; ++j) {
                if (rnd.next() < pDot) {
                    g[i][j] = '.';
                    dotCnt++;
                }
            }
        }
        if (dotCnt == 0) {
            int ri = rnd.next(1, N - 2);
            int rj = rnd.next(1, M - 2);
            g[ri][rj] = '.';
        }

        // Borders: random D or X, ensure at least one D
        double pD = 0.3 + 0.2 * rnd.next(); // 0.3 ~ 0.5
        int Dcnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
                    if (rnd.next() < pD) {
                        g[i][j] = 'D';
                        Dcnt++;
                    } else {
                        g[i][j] = 'X';
                    }
                }
            }
        }
        if (Dcnt == 0) {
            // Force one random border to be D
            vector<pair<int,int>> border;
            for (int i = 0; i < N; ++i) {
                border.emplace_back(i, 0);
                border.emplace_back(i, M - 1);
            }
            for (int j = 1; j < M - 1; ++j) {
                border.emplace_back(0, j);
                border.emplace_back(N - 1, j);
            }
            auto pos = rnd.any(border);
            g[pos.first][pos.second] = 'D';
        }
    } else if (scenario == 3) {
        // Split region with a full wall: some '.' unreachable from any exit
        bool usedSpecial = false;
        if (M >= 5 || N >= 5) {
            bool doVertical;
            if (M >= 5 && N >= 5) {
                doVertical = (rnd.next(0, 1) == 0);
            } else {
                doVertical = (M >= 5);
            }

            if (doVertical && M >= 5) {
                int k = rnd.next(2, M - 3); // barrier column
                bool leftIsDeprived = (rnd.next(0, 1) == 0);
                double pLeft = 0.5 + 0.2 * rnd.next();
                double pRight = 0.5 + 0.2 * rnd.next();

                int cntLeft = 0, cntRight = 0;
                for (int i = 1; i < N - 1; ++i) {
                    for (int j = 1; j < M - 1; ++j) {
                        if (j == k) continue; // barrier stays 'X'
                        if (j < k) {
                            if (rnd.next() < pLeft) {
                                g[i][j] = '.';
                                cntLeft++;
                            }
                        } else { // j > k
                            if (rnd.next() < pRight) {
                                g[i][j] = '.';
                                cntRight++;
                            }
                        }
                    }
                }
                if (leftIsDeprived) {
                    if (cntLeft == 0) {
                        int ri = rnd.next(1, N - 2);
                        int rj = rnd.next(1, k - 1);
                        g[ri][rj] = '.';
                        cntLeft = 1;
                    }
                } else {
                    if (cntRight == 0) {
                        int ri = rnd.next(1, N - 2);
                        int rj = rnd.next(k + 1, M - 2);
                        g[ri][rj] = '.';
                        cntRight = 1;
                    }
                }

                // Place exits only on non-deprived side border
                vector<pair<int,int>> cand;
                if (leftIsDeprived) {
                    for (int i = 0; i < N; ++i)
                        for (int j = 0; j < M; ++j)
                            if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
                                if (j >= k + 1)
                                    cand.emplace_back(i, j);
                } else {
                    for (int i = 0; i < N; ++i)
                        for (int j = 0; j < M; ++j)
                            if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
                                if (j <= k - 1)
                                    cand.emplace_back(i, j);
                }

                shuffle(cand.begin(), cand.end());
                int maxD = (int)cand.size();
                if (maxD > 0) {
                    int wantD = rnd.next(1, min(3, maxD));
                    for (int t = 0; t < wantD; ++t) {
                        int i = cand[t].first;
                        int j = cand[t].second;
                        g[i][j] = 'D';
                    }
                }
                usedSpecial = true;
            } else if (!doVertical && N >= 5) {
                int r = rnd.next(2, N - 3); // barrier row
                bool topIsDeprived = (rnd.next(0, 1) == 0);
                double pTop = 0.5 + 0.2 * rnd.next();
                double pBottom = 0.5 + 0.2 * rnd.next();

                int cntTop = 0, cntBottom = 0;
                for (int i = 1; i < N - 1; ++i) {
                    if (i == r) continue; // barrier row
                    for (int j = 1; j < M - 1; ++j) {
                        if (i < r) {
                            if (rnd.next() < pTop) {
                                g[i][j] = '.';
                                cntTop++;
                            }
                        } else { // i > r
                            if (rnd.next() < pBottom) {
                                g[i][j] = '.';
                                cntBottom++;
                            }
                        }
                    }
                }
                if (topIsDeprived) {
                    if (cntTop == 0) {
                        int ri = rnd.next(1, r - 1);
                        int rj = rnd.next(1, M - 2);
                        g[ri][rj] = '.';
                        cntTop = 1;
                    }
                } else {
                    if (cntBottom == 0) {
                        int ri = rnd.next(r + 1, N - 2);
                        int rj = rnd.next(1, M - 2);
                        g[ri][rj] = '.';
                        cntBottom = 1;
                    }
                }

                // Place exits only on non-deprived side border
                vector<pair<int,int>> cand;
                if (topIsDeprived) {
                    for (int i = 0; i < N; ++i)
                        for (int j = 0; j < M; ++j)
                            if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
                                if (i >= r + 1)
                                    cand.emplace_back(i, j);
                } else {
                    for (int i = 0; i < N; ++i)
                        for (int j = 0; j < M; ++j)
                            if (i == 0 || i == N - 1 || j == 0 || j == M - 1)
                                if (i <= r - 1)
                                    cand.emplace_back(i, j);
                }

                shuffle(cand.begin(), cand.end());
                int maxD = (int)cand.size();
                if (maxD > 0) {
                    int wantD = rnd.next(1, min(3, maxD));
                    for (int t = 0; t < wantD; ++t) {
                        int i = cand[t].first;
                        int j = cand[t].second;
                        g[i][j] = 'D';
                    }
                }
                usedSpecial = true;
            }
        }

        if (!usedSpecial) {
            // Fallback to scenario 2 if dimensions too small
            double pDot = 0.4 + 0.2 * rnd.next();
            int dotCnt = 0;
            for (int i = 1; i < N - 1; ++i) {
                for (int j = 1; j < M - 1; ++j) {
                    if (rnd.next() < pDot) {
                        g[i][j] = '.';
                        dotCnt++;
                    }
                }
            }
            if (dotCnt == 0) {
                int ri = rnd.next(1, N - 2);
                int rj = rnd.next(1, M - 2);
                g[ri][rj] = '.';
            }

            double pD = 0.3 + 0.2 * rnd.next();
            int Dcnt = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
                        if (rnd.next() < pD) {
                            g[i][j] = 'D';
                            Dcnt++;
                        } else {
                            g[i][j] = 'X';
                        }
                    }
                }
            }
            if (Dcnt == 0) {
                vector<pair<int,int>> border;
                for (int i = 0; i < N; ++i) {
                    border.emplace_back(i, 0);
                    border.emplace_back(i, M - 1);
                }
                for (int j = 1; j < M - 1; ++j) {
                    border.emplace_back(0, j);
                    border.emplace_back(N - 1, j);
                }
                auto pos = rnd.any(border);
                g[pos.first][pos.second] = 'D';
            }
        }
    }

    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(g[i]);
    }

    return 0;
}
