#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

struct Bus {
    int a;
    int b;
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int kMaxTime = 86400000 - 1;
    const int mode = rnd.next(0, 5);

    int n = rnd.next(2, 10);
    vector<Bus> buses;
    vector<int> queries;

    if (mode == 0) {
        int t = rnd.next(0, 20);
        buses.push_back({1, n, t, t + rnd.next(1, 20)});
        if (rnd.next(0, 1) == 1) {
            int later = t + rnd.next(1, 10);
            buses.push_back({1, n, later, later + rnd.next(1, 20)});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        int current = rnd.next(0, 10);
        for (int stop = 1; stop < n; ++stop) {
            int wait = rnd.next(0, 5);
            int travel = rnd.next(1, 8);
            buses.push_back({stop, stop + 1, current + wait, current + wait + travel});
            current += wait + travel;
        }
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        int branches = rnd.next(2, min(n - 2, 5));
        for (int i = 0; i < branches; ++i) {
            int mid = 2 + i;
            int start = rnd.next(0, 30);
            int arriveMid = start + rnd.next(1, 10);
            int departMid = arriveMid + rnd.next(0, 10);
            int arriveEnd = departMid + rnd.next(1, 10);
            buses.push_back({1, mid, start, arriveMid});
            buses.push_back({mid, n, departMid, arriveEnd});
        }
    } else if (mode == 3) {
        n = rnd.next(3, 8);
        int base = rnd.next(0, 20);
        buses.push_back({1, 2, base + 10, base + 20});
        buses.push_back({2, n, base + 5, base + 30});
        buses.push_back({2, n, base + 20, base + 35});
        buses.push_back({1, n, base + rnd.next(0, 15), base + 40});
    } else if (mode == 4) {
        n = rnd.next(4, 10);
        int m = rnd.next(n - 1, min(25, n * (n - 1)));
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            int x = rnd.next(0, 200);
            int y = x + rnd.next(1, 30);
            buses.push_back({a, b, x, y});
        }
    } else {
        n = rnd.next(2, 6);
        int t = kMaxTime - rnd.next(20, 200);
        int mid = n == 2 ? 2 : rnd.next(2, n - 1);
        buses.push_back({1, mid, t, t + rnd.next(1, 10)});
        if (mid != n) {
            int depart = t + rnd.next(10, 30);
            buses.push_back({mid, n, depart, min(kMaxTime, depart + rnd.next(1, 10))});
        }
    }

    shuffle(buses.begin(), buses.end());

    int q = rnd.next(1, 8);
    for (int i = 0; i < q; ++i) {
        if (!buses.empty() && rnd.next(0, 2) != 0) {
            const Bus& bus = rnd.any(buses);
            int delta = rnd.next(-3, 3);
            queries.push_back(max(0, min(kMaxTime, bus.y + delta)));
        } else {
            queries.push_back(rnd.next(0, min(kMaxTime, 250)));
        }
    }

    println(n, static_cast<int>(buses.size()));
    for (const Bus& bus : buses) {
        println(bus.a, bus.b, bus.x, bus.y);
    }
    println(q);
    for (int query : queries) {
        println(query);
    }

    return 0;
}
