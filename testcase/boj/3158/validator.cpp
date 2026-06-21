#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string name = inf.readToken("T[1-4]{1,49}", "A");
    inf.readEoln();

    for (int i = 1; i + 1 < (int)name.size(); ++i) {
        ensuref(name[i] >= '1' && name[i] <= '3',
                "only triangles ending in 1, 2, or 3 are subdivided: A[%d]=%c",
                i + 1, name[i]);
    }

    inf.readEof();
}
