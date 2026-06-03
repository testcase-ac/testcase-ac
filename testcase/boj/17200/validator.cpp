#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 25, "n");
    inf.readEoln();

    set<set<string>> populations;
    for (int i = 0; i < n; ++i) {
        int k = inf.readInt(0, 25, "k");

        set<string> features;
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            string feature = inf.readToken("[a-z]{1,20}", "feature");
            ensuref(features.insert(feature).second,
                    "duplicate feature in sub-population %d: %s",
                    i + 1,
                    feature.c_str());
        }
        inf.readEoln();

        ensuref(populations.insert(features).second,
                "duplicate feature set at sub-population %d",
                i + 1);
    }

    inf.readEof();
}
