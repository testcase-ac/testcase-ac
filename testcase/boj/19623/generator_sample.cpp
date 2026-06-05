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

int takeTime(vector<int>& times, int& pos) {
    return times[pos++];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    int mode = rnd.next(0, 4);
    vector<Meeting> meetings;

    if (mode == 4) {
        println(1);
        println(0, 2147483647, rnd.next(1, 1000));
        return 0;
    }

    vector<int> times;
    for (int i = 0; i < 2 * n; ++i) {
        int base = 3 * i + 1;
        if (mode == 3 && i + 1 == 2 * n) base = 2147483647;
        times.push_back(base);
    }

    int pos = 0;
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int start = takeTime(times, pos);
            int end = takeTime(times, pos);
            meetings.push_back({start, end, rnd.next(1, 1000)});
        }
    } else if (mode == 1) {
        vector<pair<int, int>> intervals;
        for (int i = 0; i < n; ++i) {
            intervals.push_back({times[i], times[2 * n - 1 - i]});
        }
        for (auto [start, end] : intervals) {
            if (start < end) meetings.push_back({start, end, rnd.next(1, 1000)});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int start = times[i];
            int end = times[i + n];
            meetings.push_back({start, end, rnd.next(1, 1000)});
        }
    }

    shuffle(meetings.begin(), meetings.end());
    println((int)meetings.size());
    for (const Meeting& meeting : meetings) {
        println(meeting.start, meeting.end, meeting.people);
    }

    return 0;
}
