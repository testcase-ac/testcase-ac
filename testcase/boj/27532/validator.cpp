#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M
    int M = inf.readInt(1, 1500, "M");
    inf.readEoln();

    // Read M time entries
    for (int i = 0; i < M; i++) {
        // Each line must be exactly HH:MM
        string s = inf.readLine("[0-9][0-9]:[0-9][0-9]", "time");
        // Parse hour and minute
        int hh = (s[0] - '0') * 10 + (s[1] - '0');
        int mm = (s[3] - '0') * 10 + (s[4] - '0');
        ensuref(1 <= hh && hh <= 12,
                "Hour out of range at line %d: %d", i + 2, hh);
        ensuref(0 <= mm && mm <= 59,
                "Minute out of range at line %d: %d", i + 2, mm);
    }

    inf.readEof();
    return 0;
}
