#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Process {
    int t;
    int p;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    vector<Process> processes;
    processes.reserve(n);

    if (mode == 0) {
        int t = rnd.next(0, 5);
        int basePriority = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            processes.push_back({t, basePriority + rnd.next(0, 3), rnd.next(0, 10)});
        }
    } else if (mode == 1) {
        int t = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) {
            t += rnd.next(0, 3);
            processes.push_back({t, rnd.next(0, 15), rnd.next(1, 12)});
        }
    } else if (mode == 2) {
        int t = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                t += rnd.next(0, 12);
            }
            int priority = (i % 3 == 0) ? rnd.next(0, 2) : rnd.next(8, 25);
            processes.push_back({t, priority, rnd.next(0, 8)});
        }
    } else if (mode == 3) {
        int t = rnd.next(0, 2);
        int priority = rnd.next(0, 1000);
        int burst = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            t += rnd.next(0, 1);
            processes.push_back({t, priority, burst});
        }
    } else {
        n = rnd.next(1, 8);
        int t = rnd.next(299990, 300000);
        for (int i = 0; i < n; ++i) {
            t += rnd.next(0, 1);
            if (t > 300000) {
                t = 300000;
            }
            processes.push_back({t, rnd.next(995, 1000), rnd.next(0, 1000)});
        }
    }

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.t < b.t;
    });

    println((int)processes.size());
    for (const Process& process : processes) {
        println(process.t, process.p, process.b);
    }

    return 0;
}
