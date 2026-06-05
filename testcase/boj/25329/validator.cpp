#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string duration = inf.readToken("[0-9]{2}:[0-9]{2}", "duration");
        int hour = stoi(duration.substr(0, 2));
        int minute = stoi(duration.substr(3, 2));
        ensuref(0 <= hour && hour <= 23,
                "hour out of range at record %d: %s", i + 1, duration.c_str());
        ensuref(0 <= minute && minute <= 59,
                "minute out of range at record %d: %s", i + 1, duration.c_str());
        inf.readSpace();

        inf.readToken("[a-z]{2,10}", "name");
        inf.readEoln();
    }

    inf.readEof();
}
