#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 2879, "A");
    inf.readEoln();

    set<int> scoringSeconds;
    int previous = 0;
    for (int i = 1; i <= a; ++i) {
        int second = inf.readInt(1, 2880, "As");
        inf.readEoln();

        ensuref(previous < second,
                "Team A scoring seconds must be strictly increasing at index %d: %d after %d",
                i, second, previous);
        ensuref(scoringSeconds.insert(second).second,
                "multiple points scored in second %d", second);
        previous = second;
    }

    int b = inf.readInt(1, 2879, "B");
    inf.readEoln();

    previous = 0;
    for (int i = 1; i <= b; ++i) {
        int second = inf.readInt(1, 2880, "Bs");
        inf.readEoln();

        ensuref(previous < second,
                "Team B scoring seconds must be strictly increasing at index %d: %d after %d",
                i, second, previous);
        ensuref(scoringSeconds.insert(second).second,
                "multiple points scored in second %d", second);
        previous = second;
    }

    inf.readEof();
}
