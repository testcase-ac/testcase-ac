#include "testlib.h"
#include <set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int PART_MIN = 1;
    const int PART_MAX = 1000000;
    const int N_MIN = 1;
    const int N_MAX = 1000000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    // To ensure at least one Q exists
    bool has_query = false;

    for (int i = 0; i < N; ++i) {
        std::string cmd = inf.readToken("[IQ]", "command");
        inf.readSpace();

        if (cmd == "I") {
            int a = inf.readInt(PART_MIN, PART_MAX, "a");
            inf.readSpace();
            int b = inf.readInt(PART_MIN, PART_MAX, "b");
            inf.readEoln();

            ensuref(a != b, "In 'I a b' command at line %d: a (%d) and b (%d) must be different", i+2, a, b);
        } else if (cmd == "Q") {
            int c = inf.readInt(PART_MIN, PART_MAX, "c");
            inf.readEoln();
            has_query = true;
        } else {
            ensuref(false, "Unknown command '%s' at line %d", cmd.c_str(), i+2);
        }
    }

    ensuref(has_query, "There must be at least one 'Q c' command in the input");

    inf.readEof();
}
