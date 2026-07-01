#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    vector<int> child_count(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int parent = inf.readInt(0, i - 1, "p_i");
        ++child_count[parent];
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    vector<char> is_leaf(n + 1, false);
    int leaf_count = 0;
    for (int i = 1; i <= n; ++i) {
        if (child_count[i] == 0) {
            is_leaf[i] = true;
            ++leaf_count;
        }
    }

    vector<char> seen(n + 1, false);
    for (int i = 1; i <= leaf_count; ++i) {
        int word = inf.readInt(1, n, "w_i");
        inf.readEoln();

        ensuref(is_leaf[word], "w_%d=%d is not a word-bank leaf", i, word);
        ensuref(!seen[word], "duplicate word-bank entry w_%d=%d", i, word);
        seen[word] = true;
    }

    inf.readEof();
}
