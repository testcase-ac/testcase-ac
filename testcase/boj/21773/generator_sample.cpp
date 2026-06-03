#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Process {
    int id;
    int time;
    int priority;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    vector<Process> processes;

    if (mode == 0) {
        n = 1;
        processes.push_back({rnd.next(1, 20), rnd.next(1, 12), rnd.next(1, 20)});
    } else {
        n = rnd.next(2, 10);

        vector<int> ids(30);
        iota(ids.begin(), ids.end(), 1);
        shuffle(ids.begin(), ids.end());

        int basePriority = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int time = rnd.next(1, 12);
            int priority = basePriority;

            if (mode == 1) {
                priority = basePriority;
            } else if (mode == 2) {
                priority = (i == 0 ? rnd.next(40, 80) : rnd.next(1, 10));
                if (i == 0) time = rnd.next(6, 15);
            } else if (mode == 3) {
                priority = basePriority + (i % 3);
            } else {
                priority = rnd.next(1, 50);
                if (rnd.next(0, 3) == 0) priority = basePriority;
            }

            processes.push_back({ids[i], time, priority});
        }

        if (mode == 1) {
            sort(processes.begin(), processes.end(), [](const Process& lhs, const Process& rhs) {
                return lhs.id > rhs.id;
            });
        } else {
            shuffle(processes.begin(), processes.end());
        }
    }

    int totalTime = 0;
    for (const Process& process : processes) totalTime += process.time;

    int t = rnd.next(1, totalTime);
    if (mode == 2) t = rnd.next(1, min(totalTime, rnd.next(6, 15)));

    println(t, n);
    for (const Process& process : processes) {
        println(process.id, process.time, process.priority);
    }

    return 0;
}
