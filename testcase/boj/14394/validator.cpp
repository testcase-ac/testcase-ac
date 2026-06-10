#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 2; ++i) {
        string state = inf.readLine("[RGBY*]{10}", i == 0 ? "current" : "target");
        ensuref(count(state.begin(), state.end(), '*') == 1,
                "%s state must contain exactly one blank",
                i == 0 ? "current" : "target");
    }

    inf.readEof();
}
