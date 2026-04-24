#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

static void check_time(const string &s, const char *name) {
    // Format must be exactly HH:MM:SS, length 8
    ensuref((int)s.size() == 8,
            "%s has invalid length %d, expected 8", name, (int)s.size());
    // Colons at positions 2 and 5
    ensuref(s[2] == ':' && s[5] == ':',
            "%s has invalid format, expected ':' at positions 3 and 6", name);
    // Digits elsewhere
    for (int i = 0; i < 8; i++) {
        if (i == 2 || i == 5) continue;
        ensuref(isdigit(s[i]),
                "%s has invalid character '%c' at position %d, expected digit",
                name, s[i], i+1);
    }
    // Parse and check ranges
    int hh = (s[0]-'0')*10 + (s[1]-'0');
    int mm = (s[3]-'0')*10 + (s[4]-'0');
    int ss = (s[6]-'0')*10 + (s[7]-'0');
    ensuref(0 <= hh && hh <= 23,
            "%s hour out of range: %02d", name, hh);
    ensuref(0 <= mm && mm <= 59,
            "%s minute out of range: %02d", name, mm);
    ensuref(0 <= ss && ss <= 59,
            "%s second out of range: %02d", name, ss);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read current time
    string cur = inf.readLine("[^]+", "current_time");
    check_time(cur, "current_time");

    // Read target time
    string tgt = inf.readLine("[^]+", "target_time");
    check_time(tgt, "target_time");

    // No extra data
    inf.readEof();
    return 0;
}
