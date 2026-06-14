#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(2, 300000, "L");
    inf.readEoln();

    vector<long long> values(l);
    for (int i = 0; i < l; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        values[i] = inf.readLong(-1000000000LL, 1000000000LL, "integral_i");
    }
    inf.readEoln();

    long long a = inf.readLong(-1000000000LL, 1000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(a, 1000000000LL, "b");
    inf.readEoln();
    inf.readEof();

    vector<int> pi(l);
    for (int i = 1; i < l; ++i) {
        int j = pi[i - 1];
        while (j > 0 && values[i] != values[j]) {
            j = pi[j - 1];
        }
        if (values[i] == values[j]) {
            ++j;
        }
        pi[i] = j;
    }

    int shortest_period = l - pi[l - 1];
    ensuref(shortest_period <= l / 2,
            "no integer period with length at most L/2 exists: L=%d, shortest_period=%d",
            l, shortest_period);
}
