#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

bool hasValidTree(const string& preorder, const string& postorder, int m,
                  int preL, int preR, int postL, int postR) {
    if (preorder[preL] != postorder[postR]) {
        return false;
    }
    if (preL == preR) {
        return true;
    }

    vector<int> balance(26, 0);
    int childCount = 0;
    int childPreL = preL + 1;
    int childPostL = postL;

    for (int offset = 0; offset < preR - preL; ++offset) {
        ++balance[preorder[preL + 1 + offset] - 'a'];
        --balance[postorder[postL + offset] - 'a'];

        bool balanced = true;
        for (int value : balance) {
            if (value != 0) {
                balanced = false;
                break;
            }
        }
        if (!balanced) {
            continue;
        }

        int childPreR = preL + 1 + offset;
        int childPostR = postL + offset;
        if (!hasValidTree(preorder, postorder, m, childPreL, childPreR,
                          childPostL, childPostR)) {
            return false;
        }

        ++childCount;
        childPreL = childPreR + 1;
        childPostL = childPostR + 1;
    }

    return childCount <= m && childPreL == preR + 1 && childPostL == postR;
}

void validateTraversalString(const string& s, int expectedLength,
                             const char* name) {
    vector<bool> seen(expectedLength, false);
    for (int i = 0; i < expectedLength; ++i) {
        int value = s[i] - 'a';
        ensuref(0 <= value && value < expectedLength,
                "%s[%d] must be one of the first %d lowercase letters",
                name, i + 1, expectedLength);
        ensuref(!seen[value], "%s repeats character '%c'", name, s[i]);
        seen[value] = true;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (true) {
        // CHECK: The statement gives no testcase-count cap; each case is tiny,
        // so 100000 keeps the validator bounded while allowing large batches.
        ensuref(testCaseCount <= 100000, "too many test cases");

        int m = inf.readInt(0, 20, "m");
        if (m == 0) {
            inf.readEoln();
            break;
        }

        ++testCaseCount;
        setTestCase(testCaseCount);

        inf.readSpace();
        string preorder = inf.readToken("[a-z]{1,26}", "s1");
        inf.readSpace();
        string postorder = inf.readToken("[a-z]{1,26}", "s2");
        inf.readEoln();

        int n = static_cast<int>(preorder.size());
        ensuref(static_cast<int>(postorder.size()) == n,
                "s1 and s2 lengths differ: %d vs %d",
                n, static_cast<int>(postorder.size()));
        validateTraversalString(preorder, n, "s1");
        validateTraversalString(postorder, n, "s2");
        ensuref(hasValidTree(preorder, postorder, m, 0, n - 1, 0, n - 1),
                "no valid %d-ary tree has the given traversals", m);
    }

    inf.readEof();
}
