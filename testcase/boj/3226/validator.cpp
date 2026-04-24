#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of calls
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // Read time in HH:MM format (exactly 2 digits, colon, 2 digits)
        string ts = inf.readToken("[0-9][0-9]:[0-9][0-9]", "time");
        // Exactly one space
        inf.readSpace();
        // Duration DD: 1 or 2 decimal digits, allowing leading zero
        string dd_str = inf.readToken("[0-9]{1,2}", "DD");
        inf.readEoln(); // end of this line

        // Parse hours and minutes
        int hh = (ts[0] - '0') * 10 + (ts[1] - '0');
        int mm = (ts[3] - '0') * 10 + (ts[4] - '0');
        ensuref(hh >= 0 && hh <= 23,
                "Hour out of range at call %d: %d", i + 1, hh);
        ensuref(mm >= 0 && mm <= 59,
                "Minute out of range at call %d: %d", i + 1, mm);

        // Parse and validate duration
        int dd = 0;
        for (char c : dd_str) {
            dd = dd * 10 + (c - '0');
        }
        ensuref(dd >= 0 && dd <= 60,
                "Duration out of range at call %d: %d", i + 1, dd);
    }

    inf.readEof();
    return 0;
}
