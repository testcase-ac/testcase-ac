#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two space-separated integers HH and MM, then newline, then EOF.

    int HH = inf.readInt(9, 11, "HH");
    inf.readSpace();
    int MM = inf.readInt(0, 59, "MM");
    inf.readEoln();

    // Problem guarantees: Charlie's team solved the problem, i.e., submission time
    // must not be earlier than 9:00 AM (contest start).
    // With bounds 9 <= HH <= 11, 0 <= MM <= 59 this is automatically true,
    // but we explicitly enforce it to reflect the statement.
    int startMinutes = 9 * 60;
    int submitMinutes = HH * 60 + MM;
    ensuref(submitMinutes >= startMinutes,
            "Submission time (%d:%02d) is earlier than contest start 09:00.", HH, MM);

    // Additionally, ensure that the resulting time consumed is non-negative and fits in int.
    int consumed = submitMinutes - startMinutes;
    ensuref(consumed >= 0, "Computed consumed time is negative (%d).", consumed);

    inf.readEof();
}
