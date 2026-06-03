#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Fraction {
    __int128 num;
    __int128 den;

    Fraction(__int128 n = 0, __int128 d = 1) : num(n), den(d) {
        if (num == 0) {
            den = 1;
            return;
        }
        __int128 g = gcd128(abs128(num), den);
        num /= g;
        den /= g;
    }

    static __int128 abs128(__int128 x) {
        return x < 0 ? -x : x;
    }

    static __int128 gcd128(__int128 a, __int128 b) {
        while (b != 0) {
            __int128 r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
};

int cmp(const Fraction& a, const Fraction& b) {
    __int128 lhs = a.num * b.den;
    __int128 rhs = b.num * a.den;
    if (lhs < rhs) return -1;
    if (lhs > rhs) return 1;
    return 0;
}

Fraction add(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den + b.num * a.den, a.den * b.den);
}

Fraction sub(const Fraction& a, const Fraction& b) {
    return Fraction(a.num * b.den - b.num * a.den, a.den * b.den);
}

Fraction mulInt(const Fraction& a, long long x) {
    return Fraction(a.num * x, a.den);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    vector<long long> timeEvents;
    vector<int> distanceEvents;
    for (int i = 0; i < n; ++i) {
        string type = inf.readToken("T|D", "event_type");
        inf.readSpace();
        if (type == "T") {
            // CHECK: The statement omits a numeric upper bound for time-event x.
            // 1e12 is a practical cap far beyond the largest pre-finish time possible for N <= 10000.
            long long x = inf.readLong(1LL, 1000000000000LL, "time");
            timeEvents.push_back(x);
        } else {
            int x = inf.readInt(1, 999, "distance");
            distanceEvents.push_back(x);
        }
        inf.readEoln();
    }
    inf.readEof();

    sort(timeEvents.begin(), timeEvents.end());
    sort(distanceEvents.begin(), distanceEvents.end());

    Fraction currentTime(0);
    Fraction currentDistance(0);
    int inverseSpeed = 1;
    int timeIndex = 0;
    int distanceIndex = 0;

    while (timeIndex < (int)timeEvents.size() || distanceIndex < (int)distanceEvents.size()) {
        Fraction nextTime = timeIndex < (int)timeEvents.size()
                                ? Fraction(timeEvents[timeIndex])
                                : Fraction(1000000000001LL);
        Fraction nextDistance = distanceIndex < (int)distanceEvents.size()
                                    ? Fraction(distanceEvents[distanceIndex])
                                    : Fraction(1000);
        Fraction timeToNextDistance =
            add(currentTime, mulInt(sub(nextDistance, currentDistance), inverseSpeed));

        if (cmp(nextTime, timeToNextDistance) < 0) {
            ensuref(cmp(nextTime, currentTime) >= 0,
                    "time event occurs before the current simulation time");
            currentDistance =
                add(currentDistance, Fraction(sub(nextTime, currentTime).num,
                                              sub(nextTime, currentTime).den * inverseSpeed));
            currentTime = nextTime;

            do {
                ++timeIndex;
                ++inverseSpeed;
            } while (timeIndex < (int)timeEvents.size() &&
                     timeEvents[timeIndex] == timeEvents[timeIndex - 1]);
        } else if (cmp(nextTime, timeToNextDistance) > 0) {
            ensuref(distanceIndex < (int)distanceEvents.size(),
                    "time event occurs after Bessie reaches one kilometer");
            currentTime = timeToNextDistance;
            currentDistance = nextDistance;

            do {
                ++distanceIndex;
                ++inverseSpeed;
            } while (distanceIndex < (int)distanceEvents.size() &&
                     distanceEvents[distanceIndex] == distanceEvents[distanceIndex - 1]);
        } else {
            ensuref(distanceIndex < (int)distanceEvents.size(),
                    "time event occurs exactly when Bessie reaches one kilometer");
            currentTime = nextTime;
            currentDistance = nextDistance;

            do {
                ++timeIndex;
                ++inverseSpeed;
            } while (timeIndex < (int)timeEvents.size() &&
                     timeEvents[timeIndex] == timeEvents[timeIndex - 1]);
            do {
                ++distanceIndex;
                ++inverseSpeed;
            } while (distanceIndex < (int)distanceEvents.size() &&
                     distanceEvents[distanceIndex] == distanceEvents[distanceIndex - 1]);
        }

        ensuref(cmp(currentDistance, Fraction(1000)) < 0,
                "an event occurs at or after one kilometer");
    }
}
