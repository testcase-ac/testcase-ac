#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Pos = pair<ll, ll>;

bool inside(ll n, Pos p) {
    return 1 <= p.first && p.first <= n && 1 <= p.second && p.second <= n;
}

bool nearKing(Pos king, Pos q) {
    return llabs(king.first - q.first) <= 1 && llabs(king.second - q.second) <= 1;
}

void addQueen(ll n, Pos king, Pos q, vector<Pos>& queens, set<Pos>& used) {
    if (!inside(n, q) || nearKing(king, q) || used.count(q)) return;
    used.insert(q);
    queens.push_back(q);
}

Pos randomCell(ll n) {
    return {rnd.next(1LL, n), rnd.next(1LL, n)};
}

Pos randomKing(ll n, int mode) {
    if (mode == 0) return {rnd.next(2LL, n - 1), rnd.next(2LL, n - 1)};
    if (mode == 1) return {rnd.any(vector<ll>{1, n}), rnd.next(1LL, n)};
    if (mode == 2) return {rnd.next(1LL, n), rnd.any(vector<ll>{1, n})};
    return {rnd.any(vector<ll>{1, n}), rnd.any(vector<ll>{1, n})};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    ll n = rnd.next(3, 30);
    if (rnd.next(0, 9) == 0) n = rnd.next(100000000LL, 1000000000LL);

    Pos king = randomKing(n, rnd.next(0, 3));
    vector<Pos> queens;
    set<Pos> used;
    used.insert(king);

    if (mode == 0) {
        int want = rnd.next(1, 12);
        while ((int)queens.size() < want) {
            addQueen(n, king, randomCell(n), queens, used);
        }
    } else if (mode == 1) {
        vector<Pos> candidates = {
            {king.first, max(1LL, king.second - rnd.next(2LL, min(10LL, max(2LL, king.second - 1))))},
            {king.first, min(n, king.second + rnd.next(2LL, min(10LL, max(2LL, n - king.second))))},
            {max(1LL, king.first - 2), king.second},
            {min(n, king.first + 2), king.second},
        };
        shuffle(candidates.begin(), candidates.end());
        for (Pos q : candidates) addQueen(n, king, q, queens, used);
    } else {
        vector<Pos> rays;
        for (ll dr = -1; dr <= 1; ++dr) {
            for (ll dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) continue;
                for (ll dist : vector<ll>{2, 3, 5}) {
                    rays.push_back({king.first + dr * dist, king.second + dc * dist});
                }
            }
        }
        shuffle(rays.begin(), rays.end());
        int take = mode == 2 ? rnd.next(2, 5) : rnd.next(5, 12);
        for (Pos q : rays) {
            if ((int)queens.size() >= take) break;
            addQueen(n, king, q, queens, used);
        }
    }

    while (queens.empty()) {
        addQueen(n, king, randomCell(n), queens, used);
    }

    println(n, (int)queens.size());
    println(king.first, king.second);
    for (Pos q : queens) println(q.first, q.second);

    return 0;
}
