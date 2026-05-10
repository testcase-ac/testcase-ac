#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of guitars
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Serial numbers must be unique
    set<string> seen;
    for (int i = 0; i < N; i++) {
        // Each serial: 1 to 50 chars, only 'A'-'Z' or '0'-'9'
        string s = inf.readLine("[A-Z0-9]{1,50}", "serial");
        // Check duplicates
        ensuref(!seen.count(s),
                "Duplicate serial number at index %d: %s", i, s.c_str());
        seen.insert(s);
    }

    // No extra data
    inf.readEof();
    return 0;
}
