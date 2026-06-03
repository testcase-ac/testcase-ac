#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_M = 2000000000LL;
    const long long MAX_REQUEST = 1999999999LL;

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> requests;

    if (mode == 0) {
        n = rnd.next(1, 6);
        requests.resize(n);
        for (long long& request : requests) request = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        long long base = rnd.next(1LL, 200LL);
        requests.assign(n, base);
        for (long long& request : requests) request += rnd.next(0LL, 4LL);
    } else if (mode == 2) {
        n = rnd.next(2, 35);
        requests.resize(n);
        for (int i = 0; i < n; ++i) {
            requests[i] = (i % 5 == 0 ? rnd.next(500LL, 5000LL) : rnd.next(1LL, 40LL));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        requests.resize(n);
        long long current = rnd.next(1LL, 20LL);
        for (long long& request : requests) {
            current += rnd.next(0LL, 30LL);
            request = current;
        }
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        requests.resize(n);
        for (long long& request : requests) request = rnd.next(MAX_REQUEST - 100000LL, MAX_REQUEST);
    } else {
        n = rnd.next(50, 120);
        requests.resize(n);
        for (long long& request : requests) request = rnd.next(1LL, 1000000LL);
    }

    long long total = accumulate(requests.begin(), requests.end(), 0LL);
    if (total == 1) {
        requests[0] = 2;
        total = 2;
    }
    long long m;
    if (total <= MAX_M) {
        m = rnd.next(1LL, total - 1);
    } else if (rnd.next(0, 1) == 0) {
        m = rnd.next(1LL, MAX_M);
    } else {
        long long lower = max(1LL, min(MAX_M, total) - rnd.next(1LL, 1000000LL));
        long long upper = min(MAX_M, total - 1);
        m = rnd.next(lower, upper);
    }

    if (rnd.next(0, 1) == 0) shuffle(requests.begin(), requests.end());

    println(m, n);
    for (long long request : requests) println(request);

    return 0;
}
