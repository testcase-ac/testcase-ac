#include "testlib.h"
#include <vector>
using namespace std;

struct Meeting {
    long long start;
    long long finish;
    int people;
};

static bool overlap(const Meeting& a, const Meeting& b) {
    return max(a.start, b.start) < min(a.finish, b.finish);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 25, "N");
    inf.readEoln();

    vector<Meeting> meetings(n);
    vector<long long> times;
    times.reserve(2 * n);

    const long long maxTime = (1LL << 31) - 1;
    for (int i = 0; i < n; ++i) {
        meetings[i].start = inf.readLong(0LL, maxTime, "start");
        inf.readSpace();
        meetings[i].finish = inf.readLong(0LL, maxTime, "finish");
        inf.readSpace();
        meetings[i].people = inf.readInt(1, 1000, "people");
        inf.readEoln();

        ensuref(meetings[i].start < meetings[i].finish,
                "meeting %d must start before it finishes: %lld >= %lld",
                i + 1, meetings[i].start, meetings[i].finish);

        times.push_back(meetings[i].start);
        times.push_back(meetings[i].finish);
    }

    sort(times.begin(), times.end());
    for (int i = 1; i < (int)times.size(); ++i) {
        ensuref(times[i - 1] != times[i],
                "all start and finish times must be distinct, duplicate time %lld",
                times[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool adjacent = (j == i + 1);
            bool intersects = overlap(meetings[i], meetings[j]);
            if (adjacent) {
                ensuref(intersects,
                        "adjacent meetings %d and %d must overlap",
                        i + 1, j + 1);
            } else {
                ensuref(!intersects,
                        "non-adjacent meetings %d and %d must not overlap",
                        i + 1, j + 1);
            }
        }
    }

    inf.readEof();
    return 0;
}
