#include "testlib.h"
#include <array>
#include <vector>

using namespace std;

array<long long, 3> splitSum(long long sum, long long maxValue) {
    long long minFirst = max(1LL, sum - 2LL * maxValue);
    long long maxFirst = min(maxValue, sum - 2LL);
    long long first = rnd.next(minFirst, maxFirst);

    long long rest = sum - first;
    long long minSecond = max(1LL, rest - maxValue);
    long long maxSecond = min(maxValue, rest - 1LL);
    long long second = rnd.next(minSecond, maxSecond);
    long long third = rest - second;

    return {first, second, third};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_STAT = 100000000LL;
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 1) {
        m = n + 1;
    } else {
        m = rnd.next(1, n + 1);
    }

    array<long long, 3> jaewon;
    if (mode == 5) {
        jaewon = {MAX_STAT, rnd.next(1LL, MAX_STAT), rnd.next(1LL, MAX_STAT)};
    } else {
        jaewon = {
            rnd.next(1LL, 40LL),
            rnd.next(1LL, 40LL),
            rnd.next(1LL, 40LL),
        };
    }
    long long limit = jaewon[0] + jaewon[1] + jaewon[2];

    vector<array<long long, 3>> students;
    for (int i = 0; i < n; ++i) {
        long long total;
        if (mode == 0) {
            total = rnd.next(limit + 1, limit + 80);
        } else if (mode == 1) {
            total = rnd.next(3LL, limit);
        } else if (mode == 2) {
            total = limit;
        } else if (mode == 3) {
            total = (i % 2 == 0) ? limit : rnd.next(limit + 1, limit + 60);
        } else if (mode == 4) {
            total = rnd.next(3LL, min(limit + 30, 150LL));
        } else {
            total = rnd.next(3LL, min(limit + 100000000LL, 3LL * MAX_STAT));
        }

        total = max(3LL, min(total, 3LL * MAX_STAT));
        students.push_back(splitSum(total, MAX_STAT));
    }

    println(n, m);
    println(jaewon[0], jaewon[1], jaewon[2]);
    for (const auto& student : students) {
        println(student[0], student[1], student[2]);
    }

    return 0;
}
