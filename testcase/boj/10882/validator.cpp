#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int parseTimezone(const string &s) {
    // s format: UTC(+|-)D(.5)? , D integer, -12 <= D <= 12
    ensuref(s.size() >= 5, "timezone string too short: '%s'", s.c_str());
    ensuref(s.substr(0, 3) == "UTC", "timezone must start with 'UTC', got '%s'", s.c_str());
    ensuref(s[3] == '+' || s[3] == '-', "timezone must have '+' or '-' after 'UTC', got '%s'", s.c_str());
    char sign = s[3];
    string rest = s.substr(4);
    ensuref(!rest.empty(), "missing offset value in timezone '%s'", s.c_str());

    // rest is D or D.5, where D is integer, no leading zeros (canonical)
    // handle optional ".5"
    bool half = false;
    if (rest.size() >= 2 && rest.substr(rest.size() - 2) == ".5") {
        half = true;
        rest = rest.substr(0, rest.size() - 2);
        ensuref(!rest.empty(), "missing integer part before .5 in timezone '%s'", s.c_str());
    }

    // canonical integer token for D (no sign here, sign handled separately)
    // Only digits.
    for (char c : rest)
        ensuref(c >= '0' && c <= '9', "non-digit in UTC offset integer part: '%s'", s.c_str());

    // no leading zeros unless single '0'
    if (rest.size() > 1)
        ensuref(rest[0] != '0', "leading zeros not allowed in UTC offset '%s'", s.c_str());

    int D = 0;
    for (char c : rest) {
        D = D * 10 + (c - '0');
        ensuref(D <= 12, "absolute integer part of UTC offset exceeds 12 in '%s'", s.c_str());
    }
    if (sign == '-') D = -D;

    // Check range including .5
    // Effective offset in half-hours is 2*D (+/-) plus optional +/-1
    int halfUnits = 2 * D + (sign == '+' ? (half ? 1 : 0) : (half ? -1 : 0));
    ensuref(halfUnits >= -24 && halfUnits <= 24,
            "UTC offset out of allowed range [-12,12] or invalid .5 usage in '%s'", s.c_str());

    return halfUnits; // offset in half-hours relative to UTC
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read line: "HH:MM UTC+X[.5]"
    string timeToken = inf.readToken("[^]+", "time_token");
    inf.readSpace();
    string tzToken = inf.readToken("[^]+", "timezone");
    inf.readEoln();

    // Validate timeToken "HH:MM"
    ensuref(timeToken.size() == 5 && timeToken[2] == ':',
            "meeting time must be in format HH:MM, got '%s'", timeToken.c_str());
    ensuref(timeToken[0] >= '0' && timeToken[0] <= '9' &&
            timeToken[1] >= '0' && timeToken[1] <= '9' &&
            timeToken[3] >= '0' && timeToken[3] <= '9' &&
            timeToken[4] >= '0' && timeToken[4] <= '9',
            "meeting time contains non-digit characters: '%s'", timeToken.c_str());
    int HH = (timeToken[0] - '0') * 10 + (timeToken[1] - '0');
    int MM = (timeToken[3] - '0') * 10 + (timeToken[4] - '0');
    ensuref(0 <= HH && HH <= 23, "meeting hour out of range [0,23]: %d", HH);
    ensuref(0 <= MM && MM <= 59, "meeting minute out of range [0,59]: %d", MM);

    // Validate tzToken and obtain offset of YJ's timezone relative to UTC in half-hours
    int yjOffset = parseTimezone(tzToken);

    // Read N coworker timezones, lines like "UTC+X[.5]"
    vector<int> coworkerOffsets(N);
    for (int i = 0; i < N; ++i) {
        string line = inf.readToken("[^]+", "coworker_timezone");
        inf.readEoln();
        coworkerOffsets[i] = parseTimezone(line);
    }

    // No extra content
    inf.readEof();
}
