#include "testlib.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of names (3 ≤ N ≤ 3000)
    int N = inf.readInt(3, 3000, "N");
    inf.readEoln();

    // Read N distinct names, each uppercase letters only, length < 3000
    set<string> seen;
    for (int i = 0; i < N; i++) {
        // readLine consumes the EOL character
        string name = inf.readLine("[A-Z]+", "name");
        // ensure length constraint: strictly less than 3000
        ensuref((int)name.size() < 3000,
                "Name length must be less than 3000, but got %d for name '%s'",
                (int)name.size(), name.c_str());
        // ensure uniqueness
        ensuref(!seen.count(name),
                "Duplicate name detected: '%s'", name.c_str());
        seen.insert(name);
    }

    // File must end immediately after the last name's newline
    inf.readEof();
    return 0;
}
