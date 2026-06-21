#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 5000, "n");
    inf.readEoln();

    set<int> chosen;
    for (int i = 0; i < 4; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int student = inf.readInt(1, n, "student");
        ensuref(chosen.insert(student).second,
                "Kobe, LeBron, Curry, and Jordan must be distinct; duplicate %d",
                student);
    }
    inf.readEoln();

    inf.readEof();
}
