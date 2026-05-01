#include "testlib.h"
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N, M;

vector<vector<pair<int,int>>> buildComponents(const vector<vector<int>> &A, vector<int> &compVal) {
    vector<vector<pair<int,int>>> comps;
    compVal.clear();
    vector<vector<int>> id(N, vector<int>(M, -1));
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    int cid = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (id[i][j] != -1) continue;
            int v = A[i][j];
            queue<pair<int,int>> q;
            q.push({i,j});
            id[i][j] = cid;
            comps.push_back(vector<pair<int,int>>());
            comps[cid].push_back({i,j});
            compVal.push_back(v);
            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                int x = cur.first, y = cur.second;
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dx[dir], ny = y + dy[dir];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
                    if (id[nx][ny] != -1) continue;
                    if (A[nx][ny] != v) continue;
                    id[nx][ny] = cid;
                    q.push({nx, ny});
                    comps[cid].push_back({nx, ny});
                }
            }
            ++cid;
        }
    }
    return comps;
}

int chooseNewValDiff(int oldVal) {
    int newVal = rnd.next(1, 1000);
    if (newVal == oldVal) {
        newVal = (newVal % 1000) + 1;
        if (newVal == oldVal) newVal = (newVal % 1000) + 1;
    }
    return newVal;
}

// YES: no change
void makeYesNoChange(const vector<vector<int>> &A, vector<vector<int>> &B) {
    B = A;
}

// YES: change exactly one whole component to a new uniform value
void makeYesOneComponent(const vector<vector<int>> &A, vector<vector<int>> &B) {
    vector<int> compVal;
    vector<vector<pair<int,int>>> comps = buildComponents(A, compVal);
    int compCnt = (int)comps.size();
    int idx = rnd.next(0, compCnt - 1);
    int oldVal = compVal[idx];
    int newVal = chooseNewValDiff(oldVal);

    B = A;
    for (auto &cell : comps[idx]) {
        B[cell.first][cell.second] = newVal;
    }
}

// NO: start from valid one-component change then also change one outside cell
bool makeNoOutsideChange(const vector<vector<int>> &A, vector<vector<int>> &B) {
    vector<int> compVal;
    vector<vector<pair<int,int>>> comps = buildComponents(A, compVal);
    int compCnt = (int)comps.size();
    int total = N * M;

    // find a component that is not the whole grid
    vector<int> cand;
    for (int i = 0; i < compCnt; ++i)
        if ((int)comps[i].size() < total) cand.push_back(i);
    if (cand.empty()) return false;

    int idx = rnd.any(cand);
    int oldVal = compVal[idx];
    int newVal = chooseNewValDiff(oldVal);

    B = A;
    // change whole component idx
    vector<vector<bool>> inComp(N, vector<bool>(M, false));
    for (auto &cell : comps[idx]) {
        B[cell.first][cell.second] = newVal;
        inComp[cell.first][cell.second] = true;
    }

    // collect outside cells
    vector<pair<int,int>> outside;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (!inComp[i][j]) outside.push_back({i,j});
    if (outside.empty()) return false; // should not happen because of cand check

    auto pos = rnd.any(outside);
    int x = pos.first, y = pos.second;
    int val = A[x][y];
    int newVal2 = chooseNewValDiff(val);
    B[x][y] = newVal2;
    return true;
}

// NO: change only part of one component
bool makeNoPartialComponent(const vector<vector<int>> &A, vector<vector<int>> &B) {
    vector<int> compVal;
    vector<vector<pair<int,int>>> comps = buildComponents(A, compVal);
    int compCnt = (int)comps.size();

    vector<int> cand;
    for (int i = 0; i < compCnt; ++i)
        if ((int)comps[i].size() >= 2) cand.push_back(i);
    if (cand.empty()) return false;

    int idx = rnd.any(cand);
    int oldVal = compVal[idx];
    int newVal = chooseNewValDiff(oldVal);

    B = A;
    int sz = (int)comps[idx].size();
    int skip = rnd.next(0, sz - 1);
    for (int k = 0; k < sz; ++k) {
        if (k == skip) continue;
        auto &cell = comps[idx][k];
        B[cell.first][cell.second] = newVal;
    }
    // skip cell stays oldVal
    return true;
}

// NO: change two distinct whole components to the same new value
bool makeNoTwoComponents(const vector<vector<int>> &A, vector<vector<int>> &B) {
    vector<int> compVal;
    vector<vector<pair<int,int>>> comps = buildComponents(A, compVal);
    int compCnt = (int)comps.size();
    if (compCnt < 2) return false;

    int id1 = rnd.next(0, compCnt - 1);
    int id2 = rnd.next(0, compCnt - 2);
    if (id2 >= id1) ++id2;

    int baseVal = compVal[id1];
    if (compVal[id2] == baseVal) {
        // both have same original value
        int newVal = chooseNewValDiff(baseVal);
        B = A;
        for (auto &cell : comps[id1])
            B[cell.first][cell.second] = newVal;
        for (auto &cell : comps[id2])
            B[cell.first][cell.second] = newVal;
    } else {
        // different original values, choose any value different from both with good chance
        int newVal = rnd.next(1, 1000);
        while (newVal == compVal[id1] || newVal == compVal[id2])
            newVal = rnd.next(1, 1000);
        B = A;
        for (auto &cell : comps[id1])
            B[cell.first][cell.second] = newVal;
        for (auto &cell : comps[id2])
            B[cell.first][cell.second] = newVal;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes with area limit to keep output compact
    int maxN = 7, maxM = 7, areaLimit = 40;
    while (true) {
        N = rnd.next(1, maxN);
        int maxMAllowed = min(maxM, areaLimit / N);
        if (maxMAllowed <= 0) continue;
        M = rnd.next(1, maxMAllowed);
        break;
    }

    vector<vector<int>> A(N, vector<int>(M));

    // Generate initial grid A with several pattern types
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // random small alphabet
        int K = rnd.next(2, 4);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                A[i][j] = rnd.next(1, K);
    } else if (pattern == 1) {
        // mostly constant with a few different cells
        int baseVal = rnd.next(1, 5);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                A[i][j] = baseVal;
        int diffCnt = rnd.next(1, min(4, N * M));
        vector<pair<int,int>> cells;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cells.push_back({i,j});
        shuffle(cells.begin(), cells.end());
        for (int k = 0; k < diffCnt; ++k) {
            int x = cells[k].first, y = cells[k].second;
            int v = rnd.next(1, 5);
            if (v == baseVal) v = (v % 5) + 1;
            A[x][y] = v;
        }
    } else if (pattern == 2) {
        // row or column stripes
        bool horizontal = rnd.next(0, 1);
        int K = rnd.next(2, 4);
        if (horizontal) {
            for (int i = 0; i < N; ++i) {
                int v = rnd.next(1, K);
                for (int j = 0; j < M; ++j)
                    A[i][j] = v;
            }
        } else {
            for (int j = 0; j < M; ++j) {
                int v = rnd.next(1, K);
                for (int i = 0; i < N; ++i)
                    A[i][j] = v;
            }
        }
    } else {
        // chessboard pattern of two values
        int v1 = rnd.next(1, 5);
        int v2 = rnd.next(1, 5);
        if (v2 == v1) v2 = (v2 % 5) + 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                A[i][j] = ((i + j) % 2 == 0) ? v1 : v2;
    }

    vector<vector<int>> B;

    if (N * M == 1) {
        // 1-cell grid: always YES possible; random before/after
        B = A;
        if (rnd.next(0, 1) == 1) {
            int newVal = rnd.next(1, 1000);
            B[0][0] = newVal;
        }
    } else {
        bool wantYes = rnd.next(0, 99) < 60; // 60% YES, 40% NO

        if (wantYes) {
            int sub = rnd.next(0, 1);
            if (sub == 0) makeYesNoChange(A, B);
            else makeYesOneComponent(A, B);
        } else {
            // Try different NO-construction types, fall back to YES if all fail
            bool done = false;
            int order[3] = {0,1,2};
            shuffle(order, order+3);
            for (int k = 0; k < 3 && !done; ++k) {
                if (order[k] == 0) {
                    if (makeNoOutsideChange(A, B)) done = true;
                } else if (order[k] == 1) {
                    if (makeNoPartialComponent(A, B)) done = true;
                } else {
                    if (makeNoTwoComponents(A, B)) done = true;
                }
            }
            if (!done) {
                // Degenerate grid; just produce a valid YES-case
                makeYesOneComponent(A, B);
            }
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i)
        println(A[i]);
    for (int i = 0; i < N; ++i)
        println(B[i]);

    return 0;
}
