#include "testlib.h"

#include <utility>
#include <vector>
using namespace std;

struct TestCase {
    int guests;
    int washrooms;
    vector<int> times;
    vector<pair<int, int>> updates;
};

vector<int> makeTimes(int guests, int mode) {
    vector<int> times(guests);
    if (mode == 0) {
        int base = rnd.next(1, 8);
        for (int& time : times) time = base + rnd.next(0, 3);
    } else if (mode == 1) {
        for (int i = 0; i < guests; ++i) {
            times[i] = (i % 2 == 0) ? rnd.next(1, 5) : rnd.next(99990, 100000);
        }
        shuffle(times.begin(), times.end());
    } else if (mode == 2) {
        for (int i = 0; i < guests; ++i) times[i] = rnd.next(1, 20);
    } else {
        for (int i = 0; i < guests; ++i) times[i] = rnd.next(1, 100000);
    }
    return times;
}

TestCase makeCase(int mode) {
    TestCase tc{};

    if (mode == 0) {
        tc.guests = 1;
        tc.washrooms = rnd.next(1, 50000);
    } else if (mode == 1) {
        tc.guests = rnd.next(2, 9);
        tc.washrooms = 1;
    } else if (mode == 2) {
        tc.guests = rnd.next(3, 12);
        tc.washrooms = tc.guests;
    } else if (mode == 3) {
        tc.guests = rnd.next(4, 14);
        tc.washrooms = rnd.next(2, tc.guests - 1);
    } else if (mode == 4) {
        tc.guests = rnd.next(8, 25);
        tc.washrooms = rnd.next(tc.guests + 1, 50000);
    } else {
        tc.guests = rnd.next(5, 30);
        tc.washrooms = rnd.next(1, 50000);
    }

    tc.times = makeTimes(tc.guests, rnd.next(0, 3));

    int updateCount = rnd.next(1, 8);
    int repeatedGuest = rnd.next(1, tc.guests);
    for (int i = 0; i < updateCount; ++i) {
        int guest;
        if (i > 0 && rnd.next(0, 2) == 0) {
            guest = repeatedGuest;
        } else {
            guest = rnd.next(1, tc.guests);
        }

        int value;
        if (rnd.next(0, 4) == 0) {
            value = rnd.next(99990, 100000);
        } else if (rnd.next(0, 3) == 0) {
            value = rnd.next(1, 5);
        } else {
            value = rnd.next(1, 100);
        }
        tc.updates.push_back({guest, value});
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 4);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        TestCase test = makeCase(rnd.next(0, 5));
        println(test.guests, test.washrooms);
        println(test.times);
        println((int)test.updates.size());
        for (const auto& update : test.updates) {
            println(update.first, update.second);
        }
    }

    return 0;
}
