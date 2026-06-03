#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> tasks;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        long long d = rnd.next(1, 30);
        long long idle = rnd.next(0, 30);
        tasks.push_back({d, d + idle});
    } else if (mode == 1) {
        int n = rnd.next(2, 18);
        long long idle = rnd.next(0, 12);
        long long elapsed = 0;
        for (int i = 0; i < n; ++i) {
            long long d = rnd.next(1, 8);
            elapsed += d;
            tasks.push_back({d, elapsed + idle});
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 20);
        long long idle = rnd.next(0, 40);
        long long elapsed = 0;
        long long deadline = 0;
        for (int i = 0; i < n; ++i) {
            long long d = rnd.next(1, 10);
            elapsed += d;
            deadline = max(deadline, elapsed + idle + rnd.next(0, 50));
            tasks.push_back({d, deadline});
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 16);
        long long total = 0;
        for (int i = 0; i < n; ++i) {
            long long d = rnd.next(1, 9);
            total += d;
            tasks.push_back({d, 0});
        }
        long long commonDeadline = total + rnd.next(0, 80);
        for (auto& task : tasks) task.second = commonDeadline;
    } else if (mode == 4) {
        int n = rnd.next(5, 25);
        long long idle = rnd.next(0, 1000);
        long long elapsed = 0;
        long long deadline = 0;
        for (int i = 0; i < n; ++i) {
            long long d = rnd.next(1, 20);
            elapsed += d;
            deadline = max(deadline, elapsed + idle + rnd.next(0, 200));
            tasks.push_back({d, deadline});
        }
    } else {
        int n = rnd.next(2, 12);
        long long elapsed = 0;
        long long deadline = 999000000LL;
        for (int i = 0; i < n; ++i) {
            long long d = rnd.next(1, 1000);
            elapsed += d;
            deadline += rnd.next(0, 1000);
            tasks.push_back({d, deadline});
        }
    }

    shuffle(tasks.begin(), tasks.end());

    println(static_cast<int>(tasks.size()));
    for (auto [d, t] : tasks) println(d, t);

    return 0;
}
