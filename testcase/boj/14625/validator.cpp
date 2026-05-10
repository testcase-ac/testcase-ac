#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read start time
    int H1 = inf.readInt(0, 23, "H_start");
    inf.readSpace();
    int M1 = inf.readInt(0, 59, "M_start");
    inf.readEoln();

    // Read end time
    int H2 = inf.readInt(0, 23, "H_end");
    inf.readSpace();
    int M2 = inf.readInt(0, 59, "M_end");
    inf.readEoln();

    // Read digit N
    int N = inf.readInt(0, 9, "N");
    inf.readEoln();

    // Ensure no day wrap: end time is at or after start time within same day
    int startMinutes = H1 * 60 + M1;
    int endMinutes = H2 * 60 + M2;
    ensuref(endMinutes >= startMinutes,
            "End time must not be earlier than start time (no day wrap). Got %02d:%02d to %02d:%02d",
            H1, M1, H2, M2);

    inf.readEof();
}
