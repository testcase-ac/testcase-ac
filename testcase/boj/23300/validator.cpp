#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 2000, "Q");
    inf.readEoln();

    bool hasAccess = false;

    vector<int> backStack;
    vector<int> forwardStack;
    int current = -1; // -1 means no current page yet

    for (int qi = 0; qi < Q; ++qi) {
        string cmd = inf.readToken("[A-Z]", "command");
        if (cmd == "A") {
            inf.readSpace();
            int x = inf.readInt(1, N, "page");
            inf.readEoln();

            hasAccess = true;

            // simulate: Access
            if (current != -1) {
                backStack.push_back(current);
            }
            current = x;
            forwardStack.clear();
        } else if (cmd == "B") {
            inf.readEoln();

            // simulate: Backward
            if (!backStack.empty()) {
                forwardStack.push_back(current);
                current = backStack.back();
                backStack.pop_back();
            }
        } else if (cmd == "F") {
            inf.readEoln();

            // simulate: Forward
            if (!forwardStack.empty()) {
                backStack.push_back(current);
                current = forwardStack.back();
                forwardStack.pop_back();
            }
        } else if (cmd == "C") {
            inf.readEoln();

            // simulate: Compress on backStack
            if (!backStack.empty()) {
                vector<int> compressed;
                compressed.reserve(backStack.size());
                // keep only last occurrence in contiguous equal segments
                // traverse from oldest to newest while removing previous duplicates in each run
                for (int i = 0; i < (int)backStack.size(); ) {
                    int j = i + 1;
                    while (j < (int)backStack.size() && backStack[j] == backStack[i]) ++j;
                    // keep only the last one in this run: backStack[j-1]
                    compressed.push_back(backStack[j-1]);
                    i = j;
                }
                backStack.swap(compressed);
            }
        } else {
            // Should not happen because of regex "[A-Z]"
            ensuref(false, "Unknown command at line %d", qi + 2);
        }
    }

    ensuref(hasAccess, "At least one access command 'A i' must appear");

    // Also ensure that current page is set when at least one access occurred
    ensuref(current != -1, "Internal error: current page not set despite access");

    inf.readEof();
}
