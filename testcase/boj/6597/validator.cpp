#include "testlib.h"

#include <array>
#include <string>

using namespace std;

static void validateTraversalPair(const string& preorder, const string& inorder,
                                  int caseIndex) {
    ensuref(preorder.size() == inorder.size(),
            "case %d: traversal lengths differ: %d vs %d", caseIndex,
            int(preorder.size()), int(inorder.size()));

    array<int, 26> preorderSeen{};
    array<int, 26> inorderSeen{};
    for (char ch : preorder) {
        ++preorderSeen[ch - 'A'];
    }
    for (char ch : inorder) {
        ++inorderSeen[ch - 'A'];
    }

    for (int i = 0; i < 26; ++i) {
        ensuref(preorderSeen[i] <= 1,
                "case %d: preorder repeats label %c", caseIndex, char('A' + i));
        ensuref(inorderSeen[i] <= 1,
                "case %d: inorder repeats label %c", caseIndex, char('A' + i));
        ensuref(preorderSeen[i] == inorderSeen[i],
                "case %d: label %c appears in only one traversal", caseIndex,
                char('A' + i));
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (!inf.eof()) {
        // CHECK: The statement gives EOF-terminated cases with no case-count
        // bound; local policy caps such inputs at 100000 cases.
        ensuref(caseCount < 100000, "too many test cases");

        const string preorder = inf.readToken("[A-Z]{1,26}", "preord");
        inf.readSpace();
        const string inorder = inf.readToken("[A-Z]{1,26}", "inord");
        inf.readEoln();

        ++caseCount;
        setTestCase(caseCount);
        validateTraversalPair(preorder, inorder, caseCount);
    }

    ensuref(caseCount > 0, "input must contain at least one test case");
    inf.readEof();
}
