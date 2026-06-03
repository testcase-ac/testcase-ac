#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct State {
    long double time = 0.0L;
    long double distance = 0.0L;
    int inverseSpeed = 1;
};

long long ceilTime(long double value) {
    long long t = (long long)ceill(value - 1e-12L);
    return max(1LL, t);
}

void addDistanceEvent(vector<pair<char, long long>>& events, State& state, int distance) {
    events.push_back({'D', distance});
    state.time += (distance - state.distance) * state.inverseSpeed;
    state.distance = distance;
    ++state.inverseSpeed;
}

void addTimeEvent(vector<pair<char, long long>>& events, State& state, long long time) {
    events.push_back({'T', time});
    state.distance += (time - state.time) / state.inverseSpeed;
    state.time = time;
    ++state.inverseSpeed;
}

void addDuplicateDistanceEvents(vector<pair<char, long long>>& events, State& state, int distance,
                                int count) {
    addDistanceEvent(events, state, distance);
    for (int i = 1; i < count; ++i) {
        events.push_back({'D', distance});
        ++state.inverseSpeed;
    }
}

void addDuplicateTimeEvents(vector<pair<char, long long>>& events, State& state, long long time,
                            int count) {
    addTimeEvent(events, state, time);
    for (int i = 1; i < count; ++i) {
        events.push_back({'T', time});
        ++state.inverseSpeed;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<char, long long>> events;
    State state;
    int mode = rnd.next(0, 5);
    int targetN = rnd.next(1, 24);

    if (mode == 0) {
        int count = targetN;
        vector<int> distances;
        int maxDistance = rnd.next(1, 999);
        for (int i = 0; i < count; ++i) distances.push_back(rnd.next(1, maxDistance));
        sort(distances.begin(), distances.end());
        for (int distance : distances) events.push_back({'D', distance});
    } else if (mode == 1) {
        int count = targetN;
        int maxTime = rnd.next(1, 999);
        vector<int> times;
        for (int i = 0; i < count; ++i) times.push_back(rnd.next(1, maxTime));
        sort(times.begin(), times.end());
        for (int time : times) events.push_back({'T', time});
    } else if (mode == 2) {
        int distance = rnd.next(1, 40);
        addDuplicateDistanceEvents(events, state, distance, rnd.next(1, 5));
        long long time = max<long long>(ceilTime(state.time), rnd.next(1, 80));
        addDuplicateTimeEvents(events, state, time, rnd.next(1, 5));
        while ((int)events.size() < targetN && state.distance < 950.0L) {
            if (rnd.next(0, 1) == 0) {
                int lo = (int)floor(state.distance) + 1;
                if (lo > 999) break;
                int hi = min(999, lo + rnd.next(0, 80));
                addDuplicateDistanceEvents(events, state, rnd.next(lo, hi), rnd.next(1, 3));
            } else {
                long double latest = state.time + (990.0L - state.distance) * state.inverseSpeed;
                long long lo = ceilTime(state.time);
                long long hi = max(lo, min(1000000000000LL, (long long)floorl(latest)));
                addDuplicateTimeEvents(events, state, rnd.next(lo, hi), rnd.next(1, 3));
            }
        }
    } else {
        while ((int)events.size() < targetN && state.distance < 940.0L) {
            bool useDistance = mode == 3 ? rnd.next(0, 99) < 70 : rnd.next(0, 99) < 45;
            if (useDistance) {
                int lo = (int)floor(state.distance) + 1;
                if (lo > 999) break;
                int span = mode == 4 ? rnd.next(1, 25) : rnd.next(1, 120);
                int hi = min(999, lo + span);
                addDistanceEvent(events, state, rnd.next(lo, hi));
            } else {
                long double latest = state.time + (990.0L - state.distance) * state.inverseSpeed;
                long long lo = ceilTime(state.time);
                long long hi = min(1000000000000LL, (long long)floorl(latest));
                if (lo > hi) continue;
                long long width = mode == 5 ? rnd.next(0, 1000) : rnd.next(0, 80);
                addTimeEvent(events, state, rnd.next(lo, min(hi, lo + width)));
            }
        }
    }

    shuffle(events.begin(), events.end());

    println((int)events.size());
    for (auto [type, value] : events) println(string(1, type), value);

    return 0;
}
