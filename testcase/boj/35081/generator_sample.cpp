#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Trip {
    int p;
    long long l;
    long long r;
};

static bool overlapsOrTouches(const Trip& a, const Trip& b) {
    return !(a.r < b.l || b.r < a.l);
}

static bool canAddTrip(const vector<Trip>& trips, const set<long long>& usedTimes, const Trip& next) {
    if (next.l >= next.r || usedTimes.count(next.l) || usedTimes.count(next.r)) {
        return false;
    }

    for (const Trip& trip : trips) {
        if (trip.p == next.p && overlapsOrTouches(trip, next)) {
            return false;
        }
    }

    return true;
}

static void addTrip(vector<Trip>& trips, set<long long>& usedTimes, const Trip& trip) {
    trips.push_back(trip);
    usedTimes.insert(trip.l);
    usedTimes.insert(trip.r);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 12);
    int k = rnd.next(1, n);
    int targetQ = rnd.next(1, mode == 0 ? 12 : 24);

    vector<Trip> trips;
    set<long long> usedTimes;

    if (mode == 0) {
        // Mostly one person's separated trips, with occasional other people.
        int mainPerson = rnd.next(1, n);
        long long now = rnd.next(0, 5);
        while (static_cast<int>(trips.size()) < targetQ) {
            int p = rnd.next(0, 4) == 0 ? rnd.next(1, n) : mainPerson;
            long long len = rnd.next(1, 8);
            Trip trip{p, now, now + len};
            now += len + rnd.next(1, 5);
            if (canAddTrip(trips, usedTimes, trip)) {
                addTrip(trips, usedTimes, trip);
            }
        }
    } else if (mode == 1) {
        // A nested-looking schedule where different people can overlap heavily.
        long long base = rnd.next(0, 10);
        for (int i = 0; i < targetQ; ++i) {
            int p = i % n + 1;
            long long l = base + i;
            long long r = base + 2LL * targetQ + rnd.next(1, 20) - i;
            Trip trip{p, l, r};
            if (canAddTrip(trips, usedTimes, trip)) {
                addTrip(trips, usedTimes, trip);
            }
        }
    } else if (mode == 2) {
        // Staggered intervals with varied gaps and lengths.
        long long now = rnd.next(0, 20);
        for (int i = 0; i < targetQ; ++i) {
            int p = rnd.next(1, n);
            long long l = now + rnd.next(0, 3);
            long long r = l + rnd.next(1, 12);
            now += rnd.next(1, 5);
            Trip trip{p, l, r};
            if (canAddTrip(trips, usedTimes, trip)) {
                addTrip(trips, usedTimes, trip);
            }
        }
    } else {
        // General small random schedule, retrying until validator-shaped constraints hold.
        for (int attempt = 0; attempt < 4000 && static_cast<int>(trips.size()) < targetQ; ++attempt) {
            long long l = rnd.next(0, 180);
            long long r = rnd.next(l + 1, 220LL);
            Trip trip{rnd.next(1, n), l, r};
            if (canAddTrip(trips, usedTimes, trip)) {
                addTrip(trips, usedTimes, trip);
            }
        }
    }

    if (trips.empty()) {
        addTrip(trips, usedTimes, Trip{1, 0, 1});
    }

    shuffle(trips.begin(), trips.end());

    println(n, k, static_cast<int>(trips.size()));
    for (const Trip& trip : trips) {
        println(trip.p, trip.l, trip.r);
    }

    return 0;
}
