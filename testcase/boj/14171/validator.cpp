#include "testlib.h"

#include <map>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    map<string, set<string>> statesByCity;
    for (int i = 0; i < n; ++i) {
        string city = inf.readToken("[A-Z]{2,10}", "city");
        inf.readSpace();
        string state = inf.readToken("[A-Z]{2}", "state");
        inf.readEoln();

        bool inserted = statesByCity[city].insert(state).second;
        ensuref(inserted,
                "duplicate city/state pair at row %d: %s %s",
                i + 1,
                city.c_str(),
                state.c_str());
    }

    inf.readEof();
}
