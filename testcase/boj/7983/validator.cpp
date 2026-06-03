#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    vector<pair<long long, long long>> tasks;
    tasks.reserve(n);
    for (int i = 0; i < n; ++i) {
        long long d = inf.readLong(1LL, 1000000000LL, "d_i");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t_i");
        inf.readEoln();
        tasks.push_back({t, d});
    }

    sort(tasks.begin(), tasks.end());

    __int128 elapsed = 0;
    for (int i = 0; i < n; ++i) {
        elapsed += tasks[i].second;
        ensuref(elapsed <= tasks[i].first,
                "tasks are not schedulable after doing nothing today at sorted index %d",
                i + 1);
    }

    inf.readEof();
}
