#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

struct Meeting {
    int start;
    int end;
    int people;
};

static bool overlap(const Meeting& a, const Meeting& b) {
    return max(a.start, b.start) < min(a.end, b.end);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<Meeting> meetings(n);
    set<int> times;
    for (int i = 0; i < n; ++i) {
        meetings[i].start = inf.readInt(0, 2147483647, "start");
        inf.readSpace();
        meetings[i].end = inf.readInt(0, 2147483647, "end");
        inf.readSpace();
        meetings[i].people = inf.readInt(1, 1000, "people");
        inf.readEoln();

        ensuref(meetings[i].start < meetings[i].end,
                "meeting %d start must be less than end: %d >= %d",
                i + 1,
                meetings[i].start,
                meetings[i].end);
        ensuref(times.insert(meetings[i].start).second,
                "duplicate time at meeting %d start: %d",
                i + 1,
                meetings[i].start);
        ensuref(times.insert(meetings[i].end).second,
                "duplicate time at meeting %d end: %d",
                i + 1,
                meetings[i].end);
    }

    for (int i = 0; i + 1 < n; ++i) {
        ensuref(overlap(meetings[i], meetings[i + 1]),
                "adjacent meetings %d and %d do not overlap",
                i + 1,
                i + 2);
    }

    vector<tuple<int, int, int>> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        events.emplace_back(meetings[i].start, 1, i);
        events.emplace_back(meetings[i].end, 0, i);
    }
    sort(events.begin(), events.end());

    set<int> active;
    for (auto [time, type, index] : events) {
        if (type == 0) {
            active.erase(index);
            continue;
        }

        for (int other : active) {
            ensuref(abs(index - other) == 1,
                    "non-adjacent meetings %d and %d overlap at time %d",
                    other + 1,
                    index + 1,
                    time);
        }
        active.insert(index);
    }

    inf.readEof();
}
