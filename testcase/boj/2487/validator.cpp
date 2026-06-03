#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20000, "n");
    inf.readEoln();

    vector<int> p(n);
    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        p[i] = inf.readInt(1, n, "p_i");
        ensuref(!seen[p[i]], "p_i is not a permutation: value %d appears more than once", p[i]);
        seen[p[i]] = 1;
    }
    inf.readEoln();

    vector<int> visited(n, 0);
    long long trajectory = 1;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }

        int length = 0;
        int current = i;
        while (!visited[current]) {
            visited[current] = 1;
            current = p[current] - 1;
            ++length;
        }

        long long g = gcd(trajectory, static_cast<long long>(length));
        trajectory = trajectory / g * length;
        ensuref(trajectory <= 2000000000LL, "trajectory exceeds 2000000000");
    }

    inf.readEof();
}
