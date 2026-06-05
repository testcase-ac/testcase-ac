#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Point = pair<ll, ll>;

const ll LIM = 1000000000LL;

void addPoint(vector<Point>& police, set<Point>& used, Point p) {
    if (used.insert(p).second) police.push_back(p);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<Point> police;
    set<Point> used;

    ll sx = rnd.next(-20, 20);
    ll sy = rnd.next(-20, 20);
    used.insert({sx, sy});

    if (mode == 0) {
        ll d = rnd.next(1, 12);
        addPoint(police, used, {sx - d, sy});
        addPoint(police, used, {sx + d, sy});
    } else if (mode == 1) {
        ll d = rnd.next(1, 8);
        addPoint(police, used, {sx - d, sy});
        addPoint(police, used, {sx + d, sy});
        addPoint(police, used, {sx, sy - d});
        addPoint(police, used, {sx, sy + d});
    } else if (mode == 2) {
        ll d = rnd.next(1, 10);
        int open = rnd.next(0, 3);
        if (open != 0) addPoint(police, used, {sx - d, sy});
        if (open != 1) addPoint(police, used, {sx + d, sy});
        if (open != 2) addPoint(police, used, {sx, sy - d});
        if (open != 3) addPoint(police, used, {sx, sy + d});
    } else if (mode == 3) {
        int n = rnd.next(1, 25);
        while ((int)police.size() < n) {
            addPoint(police, used, {sx + rnd.next(-30, 30), sy + rnd.next(-30, 30)});
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 30);
        ll base = rnd.next(-40, 40);
        for (int i = 0; (int)police.size() < n; ++i) {
            ll t = i + 1;
            if (rnd.next(0, 1)) t = -t;
            addPoint(police, used, {sx + t, base});
        }
    } else if (mode == 5) {
        sx = rnd.next(0, 1) ? LIM : -LIM;
        sy = rnd.next(0, 1) ? LIM : -LIM;
        used.clear();
        used.insert({sx, sy});
        addPoint(police, used, {-sx, sy});
        addPoint(police, used, {sx, -sy});
        addPoint(police, used, {0, 0});
    } else {
        int n = rnd.next(20, 80);
        ll radius = rnd.next(5, 80);
        while ((int)police.size() < n) {
            ll x = sx + rnd.next(-radius, radius);
            ll y = sy + rnd.next(-radius, radius);
            addPoint(police, used, {x, y});
        }
    }

    shuffle(police.begin(), police.end());

    println((int)police.size());
    for (Point p : police) println(p.first, p.second);
    println(sx, sy);

    return 0;
}
