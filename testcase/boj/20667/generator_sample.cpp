#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Tab {
    int cpu;
    int memory;
    int priority;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, k;
    vector<Tab> tabs;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 8);
        k = rnd.next(1, 20);
        tabs.push_back({rnd.next(1, m), rnd.next(1, k), rnd.next(1, 5)});
    } else if (mode == 1) {
        n = rnd.next(2, 9);
        m = rnd.next(20, 45);
        k = rnd.next(40, 120);
        int maxCpu = max(1, m / (n + 1));
        int maxMemory = max(1, k / (n + 1));
        for (int i = 0; i < n; ++i) {
            tabs.push_back({rnd.next(1, maxCpu), rnd.next(1, maxMemory), rnd.next(1, 5)});
        }
    } else if (mode == 2) {
        n = rnd.next(5, 14);
        m = rnd.next(12, 35);
        k = rnd.next(12, 60);
        for (int i = 0; i < n; ++i) {
            int cpu = (i % 3 == 0) ? rnd.next(max(1, m / 2), m) : rnd.next(1, max(1, m / 3));
            int memory = (i % 3 == 1) ? rnd.next(max(1, k / 2), k) : rnd.next(1, max(1, k / 3));
            int priority = (i % 4 == 0) ? 1 : rnd.next(2, 5);
            tabs.push_back({cpu, memory, priority});
        }
    } else if (mode == 3) {
        n = rnd.next(8, 22);
        m = rnd.next(40, 130);
        k = rnd.next(500, 5000);
        for (int i = 0; i < n; ++i) {
            int cpu = rnd.next(1, m);
            int memory;
            if (i < 2) {
                memory = rnd.next(max(1, k / 2), k);
            } else {
                memory = rnd.next(1, max(1, k / 8));
            }
            tabs.push_back({cpu, memory, rnd.next(1, 5)});
        }
    } else if (mode == 4) {
        n = rnd.next(20, 45);
        m = rnd.next(100, 400);
        k = rnd.next(1000, 20000);
        for (int i = 0; i < n; ++i) {
            int cpu = rnd.next(1, m);
            int memory = rnd.next(1, k);
            int priority = rnd.next(1, 5);
            tabs.push_back({cpu, memory, priority});
        }
    } else {
        n = rnd.next(10, 30);
        m = rnd.next(8, 60);
        k = rnd.next(8, 100);
        int priorityA = rnd.next(1, 5);
        int priorityB = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            int cpu = rnd.next(1, m);
            int memory = rnd.next(1, k);
            int priority = (i % 2 == 0) ? priorityA : priorityB;
            tabs.push_back({cpu, memory, priority});
        }
    }

    shuffle(tabs.begin(), tabs.end());

    println(n, m, k);
    for (const Tab& tab : tabs) {
        println(tab.cpu, tab.memory, tab.priority);
    }

    return 0;
}
