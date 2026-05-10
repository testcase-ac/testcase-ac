#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int parseTime(const string &t, const char *name) {
    ensuref(t.size() == 5, "%s must have length 5, got '%s'", name, t.c_str());
    ensuref(t[2] == ':', "%s must have ':' at position 2, got '%s'", name, t.c_str());
    ensuref(isdigit(t[0]) && isdigit(t[1]) && isdigit(t[3]) && isdigit(t[4]),
            "%s must be in HH:MM with digits, got '%s'", name, t.c_str());
    int hh = (t[0] - '0') * 10 + (t[1] - '0');
    int mm = (t[3] - '0') * 10 + (t[4] - '0');
    ensuref(0 <= hh && hh <= 23, "%s hour out of range: %d in '%s'", name, hh, t.c_str());
    ensuref(0 <= mm && mm <= 59, "%s minute out of range: %d in '%s'", name, mm, t.c_str());
    return hh * 60 + mm;
}

bool validNickChar(char c) {
    if ('a' <= c && c <= 'z') return true;
    if ('A' <= c && c <= 'Z') return true;
    if ('0' <= c && c <= '9') return true;
    if (c == '.' || c == '_' || c == '-') return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: S E Q as HH:MM
    string Sstr = inf.readToken("[0-9:]{5}", "S");
    inf.readSpace();
    string Estr = inf.readToken("[0-9:]{5}", "E");
    inf.readSpace();
    string Qstr = inf.readToken("[0-9:]{5}", "Q");
    inf.readEoln();

    int S = parseTime(Sstr, "S");
    int E = parseTime(Estr, "E");
    int Q = parseTime(Qstr, "Q");

    ensuref(S >= 0 && S <= 23 * 60 + 59, "S out of range in minutes: %d", S);
    ensuref(E >= 0 && E <= 23 * 60 + 59, "E out of range in minutes: %d", E);
    ensuref(Q >= 0 && Q <= 23 * 60 + 59, "Q out of range in minutes: %d", Q);
    ensuref(S < E, "Must have S < E, but S=%d, E=%d", S, E);
    ensuref(E < Q, "Must have E < Q, but E=%d, Q=%d", E, Q);
    ensuref(S >= 0 && Q <= 23 * 60 + 59, "Times must be between 00:00 and 23:59");

    const int MAX_LOGS = 100000;
    int lineCnt = 0;
    int lastTime = -1;
    set<string> seenLines; // to detect accidental duplicates in time+nick is not required, so omit

    // To verify problem's implied constraints about times range and format,
    // also check chronological order: "시간순으로 주어지는데"
    // Process until EOF
    string timestr, nick;
    while (!inf.eof()) {
        // Peek: if next is EOF directly after newline, we stop
        // testlib does not have direct peek; we'll try to read token, if fail it's EOF.
        // But we must obey whitespace-strict: lines are "time nickname\n".
        // Use readToken; if EOF, loop ends.
        timestr = inf.readToken("[0-9:]{5}", "log_time");
        inf.readSpace();
        nick = inf.readToken("[^]+", "nickname");
        inf.readEoln();

        ++lineCnt;
        ensuref(lineCnt <= MAX_LOGS, "Number of chat logs exceeds limit (%d)", MAX_LOGS);

        int t = parseTime(timestr, "log_time");
        ensuref(t >= 0 && t <= 23 * 60 + 59,
                "Chat time must be between 00:00 and 23:59, got %s", timestr.c_str());

        // times are given in chronological order (non-decreasing)
        ensuref(lastTime <= t,
                "Chat times must be in non-decreasing order, but time %s (%d) after %d",
                timestr.c_str(), t, lastTime);
        lastTime = t;

        // nickname constraints: allowed chars and length <= 20
        ensuref(1 <= (int)nick.size() && (int)nick.size() <= 20,
                "Nickname length must be between 1 and 20, got %d for '%s'",
                (int)nick.size(), nick.c_str());
        for (char c : nick) {
            ensuref(validNickChar(c),
                    "Invalid character '%c' in nickname '%s'. Allowed: [A-Za-z0-9._-]",
                    c, nick.c_str());
        }

        // Also ensure that every log is within the same day: already done by parseTime.
        // Problem statement says logs after Q may belong to other streaming videos,
        // but they are still allowed in input as long as time is within 00:00-23:59,
        // which is already enforced.
    }

    // Additionally, ensure at least one line of logs? Statement doesn't guarantee, so allow zero.
    // But we already allowed lineCnt == 0 as valid.

    inf.readEof();
}
