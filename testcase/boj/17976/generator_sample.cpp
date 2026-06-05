#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Thread = pair<long long, long long>;

static void addThread(vector<Thread>& threads, long long x, long long right) {
    threads.push_back({x, right - x});
}

static vector<Thread> makeSeparated() {
    int n = rnd.next(2, 18);
    vector<Thread> threads;
    long long x = rnd.next(0, 20);
    for (int i = 0; i < n; ++i) {
        long long len = rnd.next(1, 40);
        addThread(threads, x, x + len);
        x += len + rnd.next(1, 35);
    }
    return threads;
}

static vector<Thread> makeOverlappingChain() {
    int n = rnd.next(3, 24);
    vector<Thread> threads;
    long long x = rnd.next(0, 15);
    long long right = x + rnd.next(20, 80);
    addThread(threads, x, right);

    for (int i = 1; i < n; ++i) {
        x += rnd.next(1, 15);
        right += rnd.next(1, 30);
        if (right <= x) right = x + 1;
        addThread(threads, x, right);
    }
    return threads;
}

static vector<Thread> makeTightEndpoints() {
    int n = rnd.next(2, 20);
    vector<Thread> threads;
    long long x = rnd.next(0, 10);
    long long right = x + rnd.next(1, 8);
    for (int i = 0; i < n; ++i) {
        addThread(threads, x, right);
        x += rnd.next(0, 2);
        right += rnd.next(1, 3);
        if (right <= x) right = x + 1;
    }
    return threads;
}

static vector<Thread> makeSameStartPressure() {
    int n = rnd.next(3, 16);
    vector<Thread> threads;
    long long x = rnd.next(0, 30);
    long long right = x + rnd.next(1, 15);
    for (int i = 0; i < n; ++i) {
        addThread(threads, x, right);
        x += rnd.next(0, 1);
        right += rnd.next(1, 20);
        if (right <= x) right = x + 1;
    }
    return threads;
}

static vector<Thread> makeLargeCoordinates() {
    int n = rnd.next(2, 12);
    vector<Thread> threads;
    long long x = rnd.next(999999000LL, 999999500LL);
    long long right = x + rnd.next(1, 1000);
    for (int i = 0; i < n; ++i) {
        addThread(threads, x, right);
        x += rnd.next(0, 60);
        right += rnd.next(1, 1000000);
        if (right <= x) right = x + 1;
        if (right - x > 1000000000LL) right = x + 1000000000LL;
    }
    return threads;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Thread> threads;
    if (mode == 0) {
        threads = makeSeparated();
    } else if (mode == 1) {
        threads = makeOverlappingChain();
    } else if (mode == 2) {
        threads = makeTightEndpoints();
    } else if (mode == 3) {
        threads = makeSameStartPressure();
    } else {
        threads = makeLargeCoordinates();
    }

    shuffle(threads.begin(), threads.end());

    println(static_cast<int>(threads.size()));
    for (auto [x, len] : threads) {
        println(x, len);
    }

    return 0;
}
