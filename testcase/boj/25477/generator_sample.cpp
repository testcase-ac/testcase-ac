#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 80);
    int mode = rnd.next(0, 4);
    vector<string> commands;
    vector<int> specialValues{1, 2, 3, 99998, 99999, 100000};
    int currentSize = 0;
    int popCount = 0;

    auto addPush = [&]() {
        int x;
        int valueMode = rnd.next(0, 4);
        if (valueMode == 0) {
            x = rnd.next(1, 5);
        } else if (valueMode == 1) {
            x = rnd.next(99990, 100000);
        } else if (valueMode == 2) {
            x = rnd.next(1, 100000);
        } else {
            x = rnd.any(specialValues);
        }
        commands.push_back("UBACI " + to_string(x));
        ++currentSize;
    };

    auto addPop = [&]() {
        commands.push_back("IZBACI");
        --currentSize;
        ++popCount;
    };

    while ((int)commands.size() < n) {
        int remaining = n - (int)commands.size();
        bool mustPush = currentSize == 0;
        bool reservePop = popCount == 0 && remaining == 1;
        if (mustPush) {
            addPush();
            continue;
        }
        if (reservePop) {
            addPop();
            continue;
        }

        bool doPop = false;
        if (mode == 0) {
            doPop = currentSize > 0 && rnd.next(0, 1) == 0;
        } else if (mode == 1) {
            doPop = currentSize > 0 && commands.size() > (size_t)n / 2 && rnd.next(0, 2) != 0;
        } else if (mode == 2) {
            doPop = currentSize > 0 && rnd.next(0, 3) == 0;
        } else if (mode == 3) {
            doPop = currentSize > 0 && rnd.next(0, 4) <= currentSize;
        } else {
            doPop = currentSize > 0 && remaining <= currentSize + rnd.next(1, 4);
        }

        if (doPop) {
            addPop();
        } else {
            addPush();
        }
    }

    println((int)commands.size());
    for (const string& command : commands) {
        println(command);
    }

    return 0;
}
