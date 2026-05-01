#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Event {
    long long key;
    int member;
    int type; // 0 = form, 1 = deposit
};

vector<Event> randomEvents(int N) {
    vector<Event> ev;
    for (int i = 1; i <= N; ++i) {
        int r = rnd.next(100);
        int pattern; // 0 = none, 1 = form, 2 = deposit, 3 = both
        if (r < 15) pattern = 0;           // 15%
        else if (r < 40) pattern = 1;      // 25%
        else if (r < 65) pattern = 2;      // 25%
        else pattern = 3;                  // 35%

        long long base = rnd.next(1, (int)1e9);
        long long key1 = (base << 1);
        long long key2 = key1 + 1;

        if (pattern == 1) {
            ev.push_back({key1, i, 0});
        } else if (pattern == 2) {
            ev.push_back({key1, i, 1});
        } else if (pattern == 3) {
            bool depositFirst = rnd.next(0, 1);
            if (depositFirst) {
                ev.push_back({key1, i, 1});
                ev.push_back({key2, i, 0});
            } else {
                ev.push_back({key1, i, 0});
                ev.push_back({key2, i, 1});
            }
        }
    }

    if (ev.empty()) {
        int i = rnd.next(1, N);
        int t = rnd.next(0, 1);
        long long base = rnd.next(1, (int)1e9);
        ev.push_back({(base << 1), i, t});
    }

    sort(ev.begin(), ev.end(), [](const Event &a, const Event &b) {
        return a.key < b.key;
    });
    return ev;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int bucket = rnd.next(100);
    if (bucket < 20) {              // 1..5
        N = rnd.next(1, 5);
    } else if (bucket < 70) {       // 6..12
        N = rnd.next(6, 12);
    } else {                        // 13..25
        N = rnd.next(13, 25);
    }

    int S;
    vector<Event> events;

    if (N == 1) {
        // Special minimal case
        S = 1;
        int pattern = rnd.next(3); // 0=form only,1=deposit only,2=both
        long long base = rnd.next(1, (int)1e9);
        long long key1 = (base << 1);
        long long key2 = key1 + 1;
        if (pattern == 0) {
            events.push_back({key1, 1, 0});
        } else if (pattern == 1) {
            events.push_back({key1, 1, 1});
        } else {
            bool depositFirst = rnd.next(0, 1);
            if (depositFirst) {
                events.push_back({key1, 1, 1});
                events.push_back({key2, 1, 0});
            } else {
                events.push_back({key1, 1, 0});
                events.push_back({key2, 1, 1});
            }
        }
    } else {
        int scenarioType = rnd.next(5); // 0..4

        if (scenarioType == 0) {
            // Constructed case guaranteeing at least one forgotten member
            S = rnd.next(1, min(3, N - 1));

            vector<bool> hasDeposit(N + 1, false), hasForm(N + 1, false);
            int f = rnd.next(1, N); // member who will surely forget
            vector<int> others;
            for (int i = 1; i <= N; ++i)
                if (i != f) others.push_back(i);
            shuffle(others.begin(), others.end());

            long long key = 0;
            // First: deposit of f
            events.push_back({key++, f, 1});
            hasDeposit[f] = true;

            // Next S distinct others submit forms
            for (int k = 0; k < S; ++k) {
                int j = others[k];
                events.push_back({key++, j, 0});
                hasForm[j] = true;
            }

            // Additional random events after that, without breaking uniqueness
            for (int j = 1; j <= N; ++j) {
                vector<int> possible;
                if (!hasDeposit[j]) possible.push_back(1);
                if (!hasForm[j]) possible.push_back(0);
                if (possible.empty()) continue;

                int choice = rnd.next(3); // 0=none,1=one event,2=two events
                if (choice == 0) continue;

                if ((int)possible.size() == 1) {
                    int t = possible[0];
                    // At most one event can be added actually
                    events.push_back({key++, j, t});
                    if (t == 1) hasDeposit[j] = true;
                    else hasForm[j] = true;
                } else {
                    if (choice == 1) {
                        int idx = rnd.next(0, 1);
                        int t = possible[idx];
                        events.push_back({key++, j, t});
                        if (t == 1) hasDeposit[j] = true;
                        else hasForm[j] = true;
                    } else {
                        bool depositFirst = rnd.next(0, 1);
                        if (depositFirst) {
                            events.push_back({key++, j, 1});
                            events.push_back({key++, j, 0});
                        } else {
                            events.push_back({key++, j, 0});
                            events.push_back({key++, j, 1});
                        }
                        hasDeposit[j] = true;
                        hasForm[j] = true;
                    }
                }
            }
            // keys already increasing; no need to sort
        } else if (scenarioType == 1) {
            // S = N -> no one can ever be forgotten
            S = N;
            events = randomEvents(N);
        } else if (scenarioType == 2) {
            // Small S (1..3) random
            S = rnd.next(1, min(3, N));
            events = randomEvents(N);
        } else if (scenarioType == 3) {
            // Large S close to N
            if (N == 2) S = 2;
            else S = rnd.next(max(2, N - 2), N);
            events = randomEvents(N);
        } else {
            // Fully random S
            S = rnd.next(1, N);
            events = randomEvents(N);
        }
    }

    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        return a.key < b.key;
    });

    int M = (int)events.size();
    if (M < 1) {
        // Safety, though this should never happen
        int i = 1;
        int t = 0;
        long long base = 1;
        events.push_back({(base << 1), i, t});
        M = 1;
    }

    println(N, M);
    println(S);
    for (const auto &e : events) {
        println(e.member, e.type);
    }

    return 0;
}
