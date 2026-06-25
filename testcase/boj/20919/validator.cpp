#include "testlib.h"

#include <map>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxValue = (1 << 25) - 1;

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50000, "n");
        inf.readSpace();
        int q = inf.readInt(1, 50000, "q");
        inf.readEoln();

        map<int, int> count;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int s = inf.readInt(0, maxValue, "s_i");
            ++count[s];
            ++total;
        }
        inf.readEoln();

        for (int i = 0; i < q; ++i) {
            ensuref(total > 0, "S is empty before operation %d", i + 1);

            int op = inf.readInt(1, 5, "op");
            if (op <= 3) {
                inf.readSpace();
                int v = inf.readInt(0, maxValue, "v");
                inf.readEoln();

                if (op == 3) {
                    ++count[v];
                    ++total;
                }
            } else {
                inf.readEoln();

                if (op == 4) {
                    total -= count.begin()->second;
                    count.erase(count.begin());
                } else {
                    auto it = prev(count.end());
                    total -= it->second;
                    count.erase(it);
                }
            }

            ensuref(total > 0, "S is empty after operation %d", i + 1);
        }
    }

    inf.readEof();
}
