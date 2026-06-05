#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Event {
    int type;
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 12));
    int q = rnd.next(1, 45);
    vector<Event> events;
    events.reserve(q);
    vector<int> votes(n + 2, 0);

    auto add_vote = [&](int candidate, int amount) {
        events.push_back({1, amount, candidate});
        votes[candidate] += amount;
    };

    auto add_query = [&](int extra_jeonghu, int extra_others) {
        events.push_back({2, extra_jeonghu, extra_others});
    };

    while ((int)events.size() + 1 < q) {
        int remaining = q - (int)events.size();
        bool force_query = remaining <= 2;
        bool make_query = force_query || rnd.next(0, 99) < 38;

        if (make_query) {
            int x;
            int y;
            int pattern = rnd.next(0, 5);
            int jeonghu = votes[n + 1];
            int max_other = 0;
            int sum_other = 0;
            for (int i = 1; i <= n; ++i) {
                max_other = max(max_other, votes[i]);
                sum_other += votes[i];
            }

            if (pattern == 0) {
                x = rnd.next(0, 8);
                y = rnd.next(0, 8);
            } else if (pattern == 1) {
                x = max(0, max_other - jeonghu + rnd.next(-1, 2));
                y = rnd.next(0, 15);
            } else if (pattern == 2) {
                x = rnd.next(0, 20);
                y = max(0, n * max(0, jeonghu + x - 1) - sum_other + rnd.next(-2, 3));
            } else if (pattern == 3) {
                x = rnd.next(999990, 1000000);
                y = rnd.next(0, 1000000);
            } else {
                x = rnd.next(0, 1000000);
                y = rnd.next(999990, 1000000);
            }
            add_query(min(x, 1000000), min(y, 1000000));
        } else {
            int candidate;
            if (mode == 1) {
                candidate = n + 1;
            } else if (mode == 2) {
                candidate = rnd.next(1, n);
            } else if (rnd.next(0, 99) < 28) {
                candidate = n + 1;
            } else {
                candidate = rnd.next(1, n);
            }

            int amount;
            int pattern = rnd.next(0, 4);
            if (pattern == 0) {
                amount = 0;
            } else if (pattern == 1) {
                amount = rnd.next(1, 9);
            } else if (pattern == 2) {
                amount = rnd.next(10, 60);
            } else {
                amount = rnd.next(999990, 1000000);
            }
            add_vote(candidate, amount);
        }
    }

    int finalPattern = rnd.next(0, 4);
    if (finalPattern == 0) {
        add_query(0, 0);
    } else if (finalPattern == 1) {
        add_query(rnd.next(0, 10), rnd.next(0, 10));
    } else if (finalPattern == 2) {
        add_query(1000000, rnd.next(0, 1000000));
    } else {
        add_query(rnd.next(0, 1000000), 1000000);
    }

    println(n, (int)events.size());
    for (const Event& event : events) {
        println(event.type, event.x, event.y);
    }

    return 0;
}
