#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Job {
    int a;
    int b;
    vector<int> duration;
};

Job makeJob(int a, int b, int mode) {
    Job job{a, b, {}};
    for (int day = a; day <= b; ++day) {
        int remaining = b - day + 1;
        int value;
        if (mode == 0) {
            value = 1;
        } else if (mode == 1) {
            value = remaining;
        } else if (mode == 2) {
            value = remaining + rnd.next(0, 4);
        } else if (mode == 3) {
            value = rnd.next(1, min(100, max(1, b - a + 3)));
        } else {
            value = rnd.next(1, 100);
        }
        job.duration.push_back(min(100, max(1, value)));
    }
    return job;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Job> jobs;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int day = rnd.next(1, 20);
            jobs.push_back(makeJob(day, day, rnd.next(0, 4)));
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 12);
        int start = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 4);
            jobs.push_back(makeJob(start, min(100, start + len - 1), rnd.next(0, 2)));
            start += len + rnd.next(0, 2);
            if (start > 100) break;
        }
    } else if (mode == 2) {
        int n = rnd.next(6, 15);
        int center = rnd.next(8, 25);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(max(1, center - 6), center);
            int b = rnd.next(center, min(100, center + 6));
            jobs.push_back(makeJob(a, b, rnd.next(0, 4)));
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 15);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 85);
            int b = rnd.next(a, min(100, a + rnd.next(0, 7)));
            jobs.push_back(makeJob(a, b, rnd.next(2, 4)));
        }
    } else if (mode == 4) {
        int n = rnd.next(8, 15);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 100);
            int b = rnd.next(a, min(100, a + rnd.next(0, 10)));
            jobs.push_back(makeJob(a, b, rnd.next(0, 4)));
        }
    } else {
        int n = rnd.next(6, 12);
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(90, 100);
            int a = rnd.next(max(1, b - 8), b);
            jobs.push_back(makeJob(a, b, rnd.next(0, 4)));
        }
    }

    shuffle(jobs.begin(), jobs.end());

    println((int)jobs.size());
    for (const Job& job : jobs) {
        cout << job.a << ' ' << job.b;
        for (int value : job.duration) {
            cout << ' ' << value;
        }
        cout << '\n';
    }

    return 0;
}
