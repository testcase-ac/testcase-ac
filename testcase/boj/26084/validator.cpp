#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Z]{3}", "S");
    inf.readEoln();

    int n = inf.readInt(3, 50000, "N");
    inf.readEoln();

    set<string> handles;
    for (int i = 0; i < n; ++i) {
        string handle = inf.readToken("[A-Z]{1,10}", "handle");
        inf.readEoln();
        ensuref(handles.insert(handle).second,
                "duplicate handle at index %d: %s", i + 1, handle.c_str());
    }

    inf.readEof();
}
