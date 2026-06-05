#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    set<string> places;
    for (int i = 0; i < n; ++i) {
        inf.readToken("[a-z]{1,10}", "name");
        inf.readSpace();
        string place = inf.readToken("[a-z]{1,20}", "place");
        inf.readSpace();
        int start = inf.readInt(1, 50000, "start");
        inf.readSpace();
        int end = inf.readInt(1, 50000, "end");
        inf.readEoln();

        ensuref(start < end, "submission %d has start %d >= end %d", i + 1, start, end);
        places.insert(place);
        ensuref(places.size() <= 10, "more than 10 distinct places");
    }

    inf.readEof();
}
