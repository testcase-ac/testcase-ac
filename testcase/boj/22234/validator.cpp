#include "testlib.h"

#include <algorithm>
#include <deque>
#include <set>
#include <vector>

using namespace std;

struct Customer {
    long long id;
    long long remaining;
};

struct Arrival {
    long long time;
    long long id;
    long long duration;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_COUNT = 200000;
    const long long MAX_VALUE = 1000000000LL;

    int n = inf.readInt(1, MAX_COUNT, "N");
    inf.readSpace();
    int t = inf.readInt(1, MAX_COUNT, "T");
    inf.readSpace();
    int w = inf.readInt(1, MAX_COUNT, "W");
    inf.readEoln();

    set<long long> ids;
    deque<Customer> queue;
    for (int i = 0; i < n; ++i) {
        long long p = inf.readLong(1LL, MAX_VALUE, "P_i");
        inf.readSpace();
        long long duration = inf.readLong(1LL, MAX_VALUE, "t_i");
        inf.readEoln();

        ensuref(ids.insert(p).second, "duplicate customer id at initial customer %d: %lld", i + 1, p);
        queue.push_back({p, duration});
    }

    int m = inf.readInt(1, MAX_COUNT, "M");
    inf.readEoln();

    set<long long> arrivalTimes;
    vector<Arrival> arrivals;
    arrivals.reserve(m);
    for (int i = 0; i < m; ++i) {
        long long p = inf.readLong(1LL, MAX_VALUE, "P_arrival_i");
        inf.readSpace();
        long long duration = inf.readLong(1LL, MAX_VALUE, "t_arrival_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, MAX_VALUE, "c_i");
        inf.readEoln();

        ensuref(ids.insert(p).second, "duplicate customer id at arriving customer %d: %lld", i + 1, p);
        ensuref(arrivalTimes.insert(c).second, "duplicate arrival time at arriving customer %d: %lld", i + 1, c);
        arrivals.push_back({c, p, duration});
    }
    inf.readEof();

    sort(arrivals.begin(), arrivals.end(), [](const Arrival& a, const Arrival& b) {
        return a.time < b.time;
    });

    long long currentTime = 0;
    int nextArrival = 0;
    while (currentTime < w) {
        while (nextArrival < m && arrivals[nextArrival].time <= currentTime) {
            queue.push_back({arrivals[nextArrival].id, arrivals[nextArrival].duration});
            ++nextArrival;
        }

        ensuref(!queue.empty(),
                "queue is empty at time %lld before W=%d, contradicting the statement guarantee",
                currentTime,
                w);

        Customer current = queue.front();
        queue.pop_front();
        long long served = min<long long>(current.remaining, t);
        long long finishTime = currentTime + served;

        while (nextArrival < m && arrivals[nextArrival].time <= finishTime) {
            queue.push_back({arrivals[nextArrival].id, arrivals[nextArrival].duration});
            ++nextArrival;
        }

        current.remaining -= served;
        if (current.remaining > 0) {
            queue.push_back(current);
        }
        currentTime = finishTime;
    }
}
