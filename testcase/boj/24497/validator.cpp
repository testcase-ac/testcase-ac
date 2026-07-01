#include "testlib.h"

#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int to;
    long long sum;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    vector<vector<Edge>> graph(n);
    for (int e = 1; e <= m; ++e) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readSpace();
        long long k = inf.readLong(-1000000000LL, 1000000000LL, "k");
        inf.readEoln();

        // CHECK: the statement does not require two distinct indices, so i == j
        // is accepted when the resulting equation system has an integer solution.
        graph[i - 1].push_back({j - 1, k});
        graph[j - 1].push_back({i - 1, k});
    }

    vector<int> sign(n, 0);
    vector<long long> constant(n, 0);
    vector<int> stack;

    for (int start = 0; start < n; ++start) {
        if (sign[start] != 0) {
            continue;
        }

        sign[start] = 1;
        constant[start] = 0;
        stack.clear();
        stack.push_back(start);

        bool hasFixedValue = false;
        long long fixedNumerator = 0;
        int fixedDenominator = 1;

        for (int pos = 0; pos < (int)stack.size(); ++pos) {
            int u = stack[pos];
            for (const Edge& edge : graph[u]) {
                int v = edge.to;
                long long expectedConstant = edge.sum - constant[u];
                int expectedSign = -sign[u];

                if (sign[v] == 0) {
                    sign[v] = expectedSign;
                    constant[v] = expectedConstant;
                    stack.push_back(v);
                    continue;
                }

                int coefficient = sign[u] + sign[v];
                long long rhs = edge.sum - constant[u] - constant[v];
                if (coefficient == 0) {
                    ensuref(rhs == 0,
                            "inconsistent sum equation between %d and %d",
                            u + 1, v + 1);
                } else {
                    ensuref(rhs % coefficient == 0,
                            "non-integer forced value from equation between %d and %d",
                            u + 1, v + 1);
                    if (!hasFixedValue) {
                        hasFixedValue = true;
                        fixedNumerator = rhs;
                        fixedDenominator = coefficient;
                    } else {
                        ensuref(fixedNumerator * coefficient == rhs * fixedDenominator,
                                "conflicting forced values in component containing %d",
                                start + 1);
                    }
                }
            }
        }
    }

    inf.readEof();
}
