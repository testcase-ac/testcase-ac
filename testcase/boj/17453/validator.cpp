#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20, "m");
    inf.readEoln();

    // Build regex for binary string of exact length n: "[01]{n,n}"
    string len_spec = "{" + to_string(n) + "," + to_string(n) + "}";
    string bin_regex = "[01]" + len_spec;

    // Read initial door states
    inf.readLine(bin_regex, "initial_state");

    // Read each switch's toggle pattern
    for (int i = 1; i <= m; i++) {
        inf.readLine(bin_regex, ("switch_" + to_string(i)).c_str());
    }

    // No extra data
    inf.readEof();
    return 0;
}
