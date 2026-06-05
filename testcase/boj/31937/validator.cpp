#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<int> infected(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int x = inf.readInt(1, n, "infected_i");
        ensuref(!infected[x], "duplicate infected computer: %d", x);
        infected[x] = 1;
    }
    inf.readEoln();

    vector<tuple<int, int, int>> logs;
    set<int> times;
    for (int i = 0; i < m; ++i) {
        int t = inf.readInt(1, 1000000000, "t_i");
        inf.readSpace();
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "source and destination are equal at log %d: %d", i + 1, a);
        ensuref(times.insert(t).second, "duplicate transfer time at log %d: %d", i + 1, t);
        logs.emplace_back(t, a, b);
    }
    inf.readEof();

    sort(logs.begin(), logs.end());

    int answer_count = 0;
    for (int start = 1; start <= n; ++start) {
        vector<int> current(n + 1, 0);
        current[start] = 1;
        for (const auto& [t, a, b] : logs) {
            (void)t;
            if (current[a]) {
                current[b] = 1;
            }
        }

        if (current == infected) {
            ++answer_count;
        }
    }

    ensuref(answer_count == 1, "expected exactly one possible initial computer, found %d", answer_count);
}
