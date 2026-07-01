#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    long long totalLetters = 0;

    while (true) {
        string preorder = inf.readToken("[A-Z]{1,26}|#", "preorder_or_terminator");
        if (preorder == "#") {
            inf.readEoln();
            break;
        }

        inf.readSpace();
        string inorder = inf.readToken("[A-Z]{1,26}", "inorder");
        inf.readEoln();

        ++cases;
        totalLetters += static_cast<long long>(preorder.size()) + inorder.size();

        ensuref(preorder.size() == inorder.size(),
                "case %d has lengths %d and %d",
                cases, static_cast<int>(preorder.size()), static_cast<int>(inorder.size()));

        array<int, 26> preorderCount{};
        array<int, 26> inorderCount{};

        for (char c : preorder) {
            int index = c - 'A';
            ++preorderCount[index];
            ensuref(preorderCount[index] == 1,
                    "case %d repeats label %c in preorder",
                    cases, c);
        }

        for (char c : inorder) {
            int index = c - 'A';
            ++inorderCount[index];
            ensuref(inorderCount[index] == 1,
                    "case %d repeats label %c in inorder",
                    cases, c);
        }

        ensuref(preorderCount == inorderCount,
                "case %d preorder and inorder strings are not permutations",
                cases);

        // CHECK: The statement gives no number of tree lines, so use local caps.
        ensuref(cases <= 100000, "too many tree cases: %d", cases);
        ensuref(totalLetters <= 10000000LL,
                "too many total traversal characters: %lld",
                totalLetters);
    }

    ensuref(cases > 0, "input must contain at least one tree case before #");
    inf.readEof();
}
