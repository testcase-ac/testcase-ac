#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 20, "N");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < N; ++i) {
        string name = inf.readToken("[A-Z]{2,12}", "name");
        inf.readEoln();

        // Check for duplicate names
        ensuref(names.count(name) == 0, "Duplicate name found: %s at line %d", name.c_str(), i+2);
        names.insert(name);
    }

    inf.readEof();
}
