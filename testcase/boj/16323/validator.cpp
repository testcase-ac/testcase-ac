#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of participants and target sum s
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    // s: 1 ≤ s < 10^1000, no leading zeros
    string s = inf.readToken("[1-9][0-9]{0,999}", "s");
    inf.readEoln();

    set<string> seen_names;
    for (int i = 0; i < n; i++) {
        // name: 1 to 20 English letters
        string name = inf.readToken("[A-Za-z]{1,20}", "t");
        inf.readSpace();
        // bet: 1 ≤ b < 10^1000, no leading zeros
        string bet = inf.readToken("[1-9][0-9]{0,999}", "b");
        inf.readEoln();

        // Check name uniqueness
        ensuref(!seen_names.count(name),
                "Duplicate participant name \"%s\" at line %d",
                name.c_str(), i + 2);
        seen_names.insert(name);
    }

    inf.readEof();
    return 0;
}
