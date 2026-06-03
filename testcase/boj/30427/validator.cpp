#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string message = inf.readLine("[^]{1,100}", "message");
    ensuref(message == "swi's cake is missing!",
            "first line must be exactly \"swi's cake is missing!\"");

    int n = inf.readInt(0, 1000, "N");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[a-z]{1,8}", "name");
        inf.readEoln();

        ensuref(name != "swi", "person %d is swi, who is excluded from N", i + 1);
        ensuref(names.insert(name).second, "duplicate housemate name: %s", name.c_str());
    }

    int m = inf.readInt(0, 10000, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        string witness = inf.readToken("[a-z]{1,8}", "witness");
        inf.readEoln();

        ensuref(witness != "swi", "witness %d is swi, but swi was not witnessed elsewhere", i + 1);
    }

    inf.readEof();
}
