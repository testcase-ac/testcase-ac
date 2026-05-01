#include "testlib.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;

bool containsCell(const vector<pair<int,int>>& v, int x, int y) {
    for (auto &p : v)
        if (p.first == x && p.second == y)
            return true;
    return false;
}

vector<pair<int,int>> allCellsExceptEndpoints() {
    vector<pair<int,int>> cells;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            if ((i == 1 && j == 1) || (i == 5 && j == 5)) continue;
            cells.emplace_back(i, j);
        }
    }
    return cells;
}

// Check that:
//  - (1,1) is a tree cell
//  - (5,5) is reachable from (1,1)
//  - all tree cells are reachable from (1,1)
bool isValidStones(const vector<pair<int,int>>& stones) {
    bool blocked[6][6] = {};
    for (auto &p : stones) {
        blocked[p.first][p.second] = true;
    }

    if (blocked[1][1]) return false;
    if (blocked[5][5]) return false;

    bool vis[6][6] = {};
    queue<pair<int,int>> q;
    q.push({1,1});
    vis[1][1] = true;

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while (!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 1 || nx > 5 || ny < 1 || ny > 5) continue;
            if (blocked[nx][ny] || vis[nx][ny]) continue;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    if (!vis[5][5]) return false;

    // Ensure all tree cells are reachable
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            if (!blocked[i][j] && !vis[i][j]) return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int,int>> finalStones;

    // Try multiple times to obtain a valid configuration
    for (int attempt = 0; attempt < 1000; ++attempt) {
        vector<pair<int,int>> stones;
        int scenario = rnd.next(0, 7); // 8 different styles

        switch (scenario) {
            case 0: {
                // Example from the statement
                stones.push_back({3, 2});
                stones.push_back({3, 3});
                stones.push_back({3, 4});
                stones.push_back({3, 1});
                break;
            }
            case 1: {
                // No stones at all
                break;
            }
            case 2: {
                // Small random K in {0,2,4,6}
                int Ks[4] = {0, 2, 4, 6};
                int K = Ks[rnd.next(0, 3)];
                vector<pair<int,int>> cells = allCellsExceptEndpoints();
                shuffle(cells.begin(), cells.end());
                for (int i = 0; i < K; ++i) stones.push_back(cells[i]);
                break;
            }
            case 3: {
                // Medium random K in {8,10,12,14}
                int Ks[4] = {8, 10, 12, 14};
                int K = Ks[rnd.next(0, 3)];
                vector<pair<int,int>> cells = allCellsExceptEndpoints();
                shuffle(cells.begin(), cells.end());
                for (int i = 0; i < K; ++i) stones.push_back(cells[i]);
                break;
            }
            case 4: {
                // Larger random K, but will later cap at 16
                int Ks[4] = {16, 18, 20, 22};
                int K = Ks[rnd.next(0, 3)];
                vector<pair<int,int>> cells = allCellsExceptEndpoints();
                shuffle(cells.begin(), cells.end());
                for (int i = 0; i < K && i < (int)cells.size(); ++i) stones.push_back(cells[i]);
                break;
            }
            case 5: {
                // Barrier row or column with a single hole, plus optional extra stones
                bool rowBarrier = rnd.next(0, 1); // 0: row, 1: column
                stones.clear();
                if (!rowBarrier) {
                    int r = rnd.next(2, 4); // avoid rows 1 and 5
                    for (int c = 1; c <= 5; ++c) {
                        stones.emplace_back(r, c);
                    }
                } else {
                    int c = rnd.next(2, 4); // avoid columns 1 and 5
                    for (int r = 1; r <= 5; ++r) {
                        stones.emplace_back(r, c);
                    }
                }
                // Remove one stone to create a "hole"
                int remIdx = rnd.next(0, (int)stones.size() - 1);
                stones.erase(stones.begin() + remIdx); // now K = 4

                // With probability 1/2, add 2 more random stones elsewhere (K = 6)
                if (rnd.next(0, 1) == 1) {
                    vector<pair<int,int>> avail;
                    for (int i = 1; i <= 5; ++i) {
                        for (int j = 1; j <= 5; ++j) {
                            if ((i == 1 && j == 1) || (i == 5 && j == 5)) continue;
                            if (!containsCell(stones, i, j)) {
                                avail.emplace_back(i, j);
                            }
                        }
                    }
                    shuffle(avail.begin(), avail.end());
                    int addCnt = min(2, (int)avail.size());
                    for (int i = 0; i < addCnt; ++i) stones.push_back(avail[i]);
                }
                break;
            }
            case 6: {
                // Checkerboard: stones only on cells with (i+j) even (subset), excluding endpoints
                vector<pair<int,int>> cells;
                for (int i = 1; i <= 5; ++i) {
                    for (int j = 1; j <= 5; ++j) {
                        if ((i == 1 && j == 1) || (i == 5 && j == 5)) continue;
                        if ((i + j) % 2 == 0) cells.emplace_back(i, j);
                    }
                }
                shuffle(cells.begin(), cells.end());
                int maxPairs = (int)cells.size() / 2;
                int pairCount = rnd.next(1, maxPairs); // 1..maxPairs
                int K = 2 * pairCount;
                for (int i = 0; i < K; ++i) stones.push_back(cells[i]);
                break;
            }
            case 7: {
                // Symmetric with respect to the center (3,3), using pairs of symmetric cells
                typedef pair<int,int> pii;
                vector<pair<pii,pii>> pairs;
                for (int i = 1; i <= 5; ++i) {
                    for (int j = 1; j <= 5; ++j) {
                        pii p = {i, j};
                        pii q = {6 - i, 6 - j};
                        if (p > q) continue; // handle each pair only once
                        if (p == q) continue; // skip center (3,3) to keep even count
                        if ((p.first == 1 && p.second == 1) || (p.first == 5 && p.second == 5) ||
                            (q.first == 1 && q.second == 1) || (q.first == 5 && q.second == 5)) {
                            continue; // skip pair involving endpoints
                        }
                        pairs.push_back({p, q});
                    }
                }
                // Randomly choose some pairs
                for (auto &pq : pairs) {
                    if (rnd.next(0, 1) == 1) {
                        stones.push_back(pq.first);
                        stones.push_back(pq.second);
                    }
                }
                // Ensure we have at least one symmetric pair
                if (stones.empty() && !pairs.empty()) {
                    int idx = rnd.next(0, (int)pairs.size() - 1);
                    stones.push_back(pairs[idx].first);
                    stones.push_back(pairs[idx].second);
                }
                break;
            }
        }

        // Remove any accidental stones on endpoints (safety)
        stones.erase(
            remove_if(stones.begin(), stones.end(),
                      [](const pair<int,int>& p) {
                          return (p.first == 1 && p.second == 1) ||
                                 (p.first == 5 && p.second == 5);
                      }),
            stones.end()
        );

        // Cap K at 16 (otherwise (5,5) cannot be reachable)
        while ((int)stones.size() > 16) {
            int idx = rnd.next(0, (int)stones.size() - 1);
            stones.erase(stones.begin() + idx);
        }

        // Ensure K is even (0 ≤ K ≤ 16, K even)
        int K = (int)stones.size();
        if (K % 2 == 1) {
            vector<pair<int,int>> cells = allCellsExceptEndpoints();
            vector<pair<int,int>> freeCells;
            for (auto &c : cells) {
                if (!containsCell(stones, c.first, c.second))
                    freeCells.push_back(c);
            }
            if (K < 16 && !freeCells.empty()) {
                // Add one more stone to make K even
                stones.push_back(rnd.any(freeCells));
            } else {
                // Fallback: remove one stone to make K even
                int idx = rnd.next(0, (int)stones.size() - 1);
                stones.erase(stones.begin() + idx);
            }
        }

        shuffle(stones.begin(), stones.end());

        if (isValidStones(stones)) {
            finalStones = stones;
            break;
        }
    }

    // Fallback to a known-good example if generation somehow failed
    if (finalStones.empty()) {
        finalStones.push_back({3, 2});
        finalStones.push_back({3, 3});
        finalStones.push_back({3, 4});
        finalStones.push_back({3, 1});
    }

    println((int)finalStones.size());
    for (auto &p : finalStones) {
        println(p.first, p.second);
    }

    return 0;
}
