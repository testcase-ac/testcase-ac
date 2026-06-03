#include "testlib.h"
#include <map>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    map<string, int> registered;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[a-z]{1,20}", "participant_name");
        inf.readEoln();
        ++registered[name];
    }

    for (int i = 0; i < n - 1; ++i) {
        string name = inf.readToken("[a-z]{1,20}", "finisher_name");
        inf.readEoln();

        auto it = registered.find(name);
        ensuref(it != registered.end() && it->second > 0,
                "finisher %d is not an unconsumed registered participant: %s",
                i + 1, name.c_str());
        --it->second;
    }

    inf.readEof();
    return 0;
}
