#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to use very large values
    bool bigValues = (rnd.next(0, 9) == 0); // 10% chance

    int q;
    int maxT, maxD;

    if (bigValues) {
        q = rnd.next(5, 20);
        maxT = 1000000;
        maxD = 1000000;
    } else {
        q = rnd.next(10, 30);
        maxT = max(q + 2, rnd.next(10, 30)); // ensure enough distinct times
        maxD = rnd.next(3, 15);
    }

    println(q);

    // State for joins and cancels
    bool hadCancel = false;

    set<int> activeTimes;                 // entrance times of active knights
    vector<int> timeOfEvent(q + 1, 0);    // time for each event index if it's a join
    vector<int> activeJoinEvents;         // event indices of currently active joins

    auto generateQueryTime = [&](void) -> int {
        if (activeTimes.empty()) {
            return rnd.next(1, maxT);
        }
        int t;
        int r = rnd.next(0, 99);
        vector<int> times(activeTimes.begin(), activeTimes.end());
        if (r < 40) {
            // Exactly at some knight's time
            t = rnd.any(times);
        } else if (r < 70) {
            // Near some knight's time
            int base = rnd.any(times);
            int offset = (rnd.next(0, 1) == 0 ? -1 : 1);
            t = base + offset;
            if (t < 1 || t > maxT) t = rnd.next(1, maxT);
        } else {
            // Completely random
            t = rnd.next(1, maxT);
        }
        return t;
    };

    for (int e = 1; e <= q; ++e) {
        int remaining = q - e + 1;
        bool canCancel = !activeJoinEvents.empty();

        if (e == 1) {
            // First event: always a query, with empty queue
            int t = rnd.next(1, maxT);
            println("?", t);
            continue;
        }

        if (e == 2 && activeJoinEvents.empty()) {
            // Ensure at least one join exists by event 2
            int t;
            do {
                t = rnd.next(1, maxT);
            } while (activeTimes.count(t));
            int d;
            if (maxD <= 5) d = rnd.next(1, maxD);
            else {
                if (rnd.next(0, 1) == 0) d = rnd.next(1, min(5, maxD));
                else d = rnd.next(1, maxD);
            }

            timeOfEvent[e] = t;
            activeTimes.insert(t);
            activeJoinEvents.push_back(e);

            println("+", t, d);
            continue;
        }

        // If this is the last event and we haven't cancelled yet but can, force a cancel
        if (remaining == 1 && !hadCancel && canCancel) {
            int pos = rnd.next(0, (int)activeJoinEvents.size() - 1);
            int evId = activeJoinEvents[pos];
            activeJoinEvents[pos] = activeJoinEvents.back();
            activeJoinEvents.pop_back();
            int t = timeOfEvent[evId];
            activeTimes.erase(t);
            hadCancel = true;
            println("-", evId);
            continue;
        }

        int p = rnd.next(0, 99);

        auto doJoin = [&](int eventIndex) {
            int t;
            do {
                t = rnd.next(1, maxT);
            } while (activeTimes.count(t));
            int d;
            if (maxD <= 5) d = rnd.next(1, maxD);
            else {
                if (rnd.next(0, 1) == 0) d = rnd.next(1, min(5, maxD));
                else d = rnd.next(1, maxD);
            }

            timeOfEvent[eventIndex] = t;
            activeTimes.insert(t);
            activeJoinEvents.push_back(eventIndex);

            println("+", t, d);
        };

        auto doCancel = [&]() {
            int pos = rnd.next(0, (int)activeJoinEvents.size() - 1);
            int evId = activeJoinEvents[pos];
            activeJoinEvents[pos] = activeJoinEvents.back();
            activeJoinEvents.pop_back();
            int t = timeOfEvent[evId];
            activeTimes.erase(t);
            hadCancel = true;
            println("-", evId);
        };

        if (!canCancel) {
            // Only joins and queries possible
            if (p < 40) {
                int t = generateQueryTime();
                println("?", t);
            } else {
                doJoin(e);
            }
        } else {
            // All three types possible
            if (p < 35) {
                int t = generateQueryTime();
                println("?", t);
            } else if (p < 70) {
                doJoin(e);
            } else {
                doCancel();
            }
        }
    }

    return 0;
}
