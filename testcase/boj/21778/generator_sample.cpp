#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Process {
    long long id;
    long long time;
    long long priority;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMaxValue = 1000000000000LL;

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 9);
    int q = rnd.next(5, 12);

    vector<long long> ids(n);
    iota(ids.begin(), ids.end(), 1);
    if (mode == 4) {
        long long base = kMaxValue - rnd.next(1000, 1000000);
        for (int i = 0; i < n; ++i) ids[i] = base + i;
    } else if (rnd.next(0, 1)) {
        for (int i = 0; i < n; ++i) ids[i] = rnd.next(1LL, 1000000LL);
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());
        while ((int)ids.size() < n) {
            long long candidate = rnd.next(1LL, 1000000LL);
            if (!binary_search(ids.begin(), ids.end(), candidate)) {
                ids.push_back(candidate);
                sort(ids.begin(), ids.end());
            }
        }
    }
    shuffle(ids.begin(), ids.end());

    vector<Process> processes;
    processes.reserve(n);
    long long totalTime = 0;
    for (int i = 0; i < n; ++i) {
        long long time = rnd.next(1LL, 20LL);
        long long priority = rnd.next(1LL, 40LL);

        if (mode == 0) {
            priority = 10;
        } else if (mode == 1) {
            priority = (i == 0 ? rnd.next(100LL, 200LL) : rnd.next(1LL, 20LL));
            time = (i == 0 ? rnd.next(1LL, 3LL) : rnd.next(5LL, 20LL));
        } else if (mode == 2) {
            priority = 1 + i * rnd.next(1LL, 5LL);
        } else if (mode == 3) {
            time = (i % 2 == 0 ? rnd.next(1LL, 4LL) : rnd.next(15LL, 40LL));
            priority = rnd.next(1LL, 60LL);
        } else {
            time = rnd.next(1LL, 1000000LL);
            priority = kMaxValue - rnd.next(0LL, 1000000LL);
        }

        processes.push_back({ids[i], time, priority});
        totalTime += time;
    }

    println(q, n);
    for (const Process& process : processes) {
        println(process.id, process.time, process.priority);
    }

    vector<long long> queries;
    queries.push_back(1);
    queries.push_back(totalTime);
    while ((int)queries.size() < q) {
        queries.push_back(rnd.next(1LL, totalTime));
    }
    shuffle(queries.begin(), queries.end());
    for (long long query : queries) {
        println(query);
    }

    return 0;
}
