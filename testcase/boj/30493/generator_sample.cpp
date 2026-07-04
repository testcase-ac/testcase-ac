#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Exam {
    long long s;
    long long p;
    long long e;
    long long a;
};

long long choosePrep(long long availableBefore, int mode) {
    if (mode == 0) {
        return rnd.next(1LL, max(1LL, min(availableBefore + 3, 20LL)));
    }
    if (mode == 1) {
        return rnd.next(max(1LL, availableBefore), min(1000000000LL, availableBefore + 30));
    }
    if (mode == 2) {
        return rnd.next(1LL, 1000000000LL);
    }
    return rnd.next(1LL, 50LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 4) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(2, 12);
    }

    vector<Exam> exams;
    exams.reserve(n);

    long long current = 0;
    if (mode == 3) {
        current = rnd.next(999999000LL, 999999900LL);
    } else if (rnd.next(3) == 0) {
        current = rnd.next(0LL, 20LL);
    }

    long long studyGained = current;
    for (int i = 0; i < n; ++i) {
        long long gap;
        if (mode == 1) {
            gap = rnd.next(0LL, 2LL);
        } else if (mode == 2) {
            gap = rnd.next(0LL, 100LL);
        } else if (mode == 3) {
            gap = rnd.next(0LL, 8LL);
        } else {
            gap = rnd.next(0LL, 20LL);
        }

        long long s = current + gap;
        if (s > 999999998LL) {
            s = 999999998LL;
        }

        long long maxDuration = min(1000000000LL - s, mode == 3 ? 20LL : 200LL);
        long long preparedDuration = rnd.next(1LL, max(1LL, min(maxDuration, mode == 1 ? 3LL : 50LL)));
        long long p = s + preparedDuration;

        long long extraUnprepared = rnd.next(0LL, max(0LL, min(1000000000LL - p, mode == 1 ? 2LL : 80LL)));
        long long e = p + extraUnprepared;

        long long availableBefore = studyGained + gap;
        long long a = choosePrep(availableBefore, mode);
        if (rnd.next(6) == 0) {
            a = 1000000000LL;
        }

        exams.push_back({s, p, e, a});
        studyGained = availableBefore + (e - p);
        current = e;

        if (current >= 999999998LL) {
            n = i + 1;
            break;
        }
    }

    println(static_cast<int>(exams.size()));
    for (const Exam& exam : exams) {
        println(exam.s, exam.p, exam.e, exam.a);
    }

    return 0;
}
