#include "testlib.h"

#include <vector>

using namespace std;

static void validatePermutation(const vector<int>& values, int n, const char* name) {
    vector<char> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int value = values[i];
        ensuref(!seen[value], "%s is not a permutation: duplicate value %d at index %d",
                name, value, i + 1);
        seen[value] = 1;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<int> preorder = inf.readInts(n, 1, n, "preorder_i");
    inf.readEoln();
    validatePermutation(preorder, n, "preorder");

    vector<int> postorder = inf.readInts(n, 1, n, "postorder_i");
    inf.readEoln();
    validatePermutation(postorder, n, "postorder");

    inf.readEof();
}
