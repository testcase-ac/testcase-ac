#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5000, "n");
    inf.readEoln();

    vector<int> same_as_zero(n, 0);
    same_as_zero[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            string relation = inf.readToken("[+\\-0]", "relation");
            char value = relation[0];

            if (i == j) {
                ensuref(value == '0', "relation[%d][%d] must be 0", i, j);
            } else {
                ensuref(value == '+' || value == '-',
                        "relation[%d][%d] must be + or -", i, j);
            }

            if (i == 0 && j > 0) {
                same_as_zero[j] = (value == '+');
            } else if (j == 0 && i > 0) {
                char expected = same_as_zero[i] ? '+' : '-';
                ensuref(value == expected,
                        "relation[%d][0]=%c is inconsistent with relation[0][%d]",
                        i, value, i);
            } else if (i > 0 && j > 0 && i != j) {
                char expected = (same_as_zero[i] == same_as_zero[j]) ? '+' : '-';
                ensuref(value == expected,
                        "relation[%d][%d]=%c violates balanced network structure",
                        i, j, value);
            }
        }
        inf.readEoln();
    }

    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    for (int query = 0; query < m; ++query) {
        int b = inf.readInt(0, n - 1, "b");
        inf.readSpace();
        int c = inf.readInt(0, n - 1, "c");
        ensuref(b != c, "query %d has equal nodes: %d", query + 1, b);
        inf.readEoln();
    }

    inf.readEof();
}
