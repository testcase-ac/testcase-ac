#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

long long dist2(const Point& p) {
    return 1LL * p.first * p.first + 1LL * p.second * p.second;
}

long long dist2(const Point& a, const Point& b) {
    long long dx = 1LL * a.first - b.first;
    long long dy = 1LL * a.second - b.second;
    return dx * dx + dy * dy;
}

bool validPoint(const vector<Point>& stones, const set<long long>& usedDistances,
                int rs, const Point& p) {
    if (p.first < -20000 || p.first > 20000 || p.second < -20000 || p.second > 20000)
        return false;
    if (usedDistances.count(dist2(p)))
        return false;

    long long minStoneDistance = 2LL * rs * 2LL * rs;
    for (const Point& q : stones) {
        if (dist2(p, q) < minStoneDistance)
            return false;
    }
    return true;
}

Point randomPoint(int rs, int rh, int mode, const vector<Point>& stones,
                  const set<long long>& usedDistances) {
    int reach = min(20000, rh + rs);
    for (int attempt = 0; attempt < 20000; ++attempt) {
        Point p;
        if (mode == 0 && attempt < 4000) {
            int r = rnd.next(0, max(0, reach + 5));
            p = {rnd.next(0, 1) ? r : -r, rnd.next(-3, 3)};
        } else if (mode == 1 && attempt < 4000) {
            int r = max(0, reach + rnd.next(-2 * rs, 2 * rs + 8));
            p = {rnd.next(-r, r), rnd.next(-r, r)};
        } else if (mode == 2 && attempt < 4000) {
            vector<Point> candidates = {
                {-20000, -20000}, {-20000, 0}, {-19999, 20000}, {0, -19998},
                {1, 19999}, {19997, -20000}, {19998, 1}, {20000, 20000}
            };
            p = rnd.any(candidates);
            p.first += rnd.next(-2, 2);
            p.second += rnd.next(-2, 2);
        } else {
            int bound = min(20000, max(reach + 3 * rs + 30, 50));
            p = {rnd.next(-bound, bound), rnd.next(-bound, bound)};
        }

        if (validPoint(stones, usedDistances, rs, p))
            return p;
    }

    quitf(_fail, "failed to place a valid stone");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(2, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int rs;
        if (mode == 2)
            rs = rnd.next(1, 1000);
        else
            rs = rnd.next(1, 30);
        int rh = rnd.next(rs + 1, min(10000, rs + rnd.next(2, 200)));

        int n = 0, m = 0;
        if (mode == 0) {
            n = rnd.next(0, 8);
            m = 0;
        } else if (mode == 1) {
            n = rnd.next(1, 8);
            m = rnd.next(1, 8);
        } else if (mode == 2) {
            n = rnd.next(1, 4);
            m = rnd.next(1, 4);
        } else {
            n = rnd.next(0, 8);
            m = rnd.next(0, 8);
            if (n + m == 0)
                n = 1;
        }

        vector<Point> red, yellow, stones;
        set<long long> usedDistances;

        vector<int> teams;
        for (int i = 0; i < n; ++i) teams.push_back(0);
        for (int i = 0; i < m; ++i) teams.push_back(1);
        shuffle(teams.begin(), teams.end());

        for (int team : teams) {
            Point p = randomPoint(rs, rh, mode, stones, usedDistances);
            stones.push_back(p);
            usedDistances.insert(dist2(p));
            if (team == 0)
                red.push_back(p);
            else
                yellow.push_back(p);
        }

        shuffle(red.begin(), red.end());
        shuffle(yellow.begin(), yellow.end());

        println(rs, rh);
        println((int)red.size());
        for (const Point& p : red)
            println(p.first, p.second);
        println((int)yellow.size());
        for (const Point& p : yellow)
            println(p.first, p.second);
    }

    return 0;
}
