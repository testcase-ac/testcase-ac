#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

struct Customer {
    int id;
    int duration;
    int arrival;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 7);
    int t = rnd.next(1, 8);
    int w = rnd.next(1, 35);
    int m = rnd.next(1, 8);

    if (mode == 0) {
        n = 1;
        t = rnd.next(1, 6);
        w = rnd.next(t + 1, t + 20);
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        t = rnd.next(1, 3);
        w = rnd.next(12, 35);
    } else if (mode == 2) {
        t = rnd.next(4, 10);
    } else if (mode == 3) {
        m = rnd.next(4, 10);
    }

    vector<int> ids(n + m);
    iota(ids.begin(), ids.end(), 1);
    shuffle(ids.begin(), ids.end());

    vector<Customer> initial;
    int totalInitialWork = 0;
    for (int i = 0; i < n; ++i) {
        int duration;
        if (mode == 0 && i == 0) {
            duration = w + rnd.next(0, 15);
        } else if (mode == 1) {
            duration = rnd.next(t + 1, t * 4 + 8);
        } else if (mode == 2) {
            duration = rnd.next(1, t);
        } else {
            duration = rnd.next(1, 20);
        }
        initial.push_back({ids[i], duration, 0});
        totalInitialWork += duration;
    }

    while (totalInitialWork < w) {
        int add = min(20, w - totalInitialWork);
        initial[rnd.next(n)].duration += add;
        totalInitialWork += add;
    }

    set<int> usedArrivalTimes;
    vector<Customer> arrivals;
    for (int i = 0; i < m; ++i) {
        int duration = rnd.next(1, 20);
        int arrival;
        if (mode == 4) {
            arrival = rnd.next(w + 1, w + 60);
        } else if (mode == 3) {
            arrival = rnd.next(1, max(1, w));
        } else {
            arrival = rnd.next(1, w + 20);
        }
        while (!usedArrivalTimes.insert(arrival).second) {
            ++arrival;
        }
        arrivals.push_back({ids[n + i], duration, arrival});
    }
    shuffle(arrivals.begin(), arrivals.end());

    println(n, t, w);
    for (const Customer& customer : initial) {
        println(customer.id, customer.duration);
    }
    println(m);
    for (const Customer& customer : arrivals) {
        println(customer.id, customer.duration, customer.arrival);
    }

    return 0;
}
