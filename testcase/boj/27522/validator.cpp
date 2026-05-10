#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Racer {
    int time; // in milliseconds (or any consistent unit)
    char team; // 'R' or 'B'
};

int parseTime(const string &s, int idx) {
    // Format M:SS:sss
    // s.size() must be exactly 8, validate before calling if needed.
    ensuref(s.size() == 8, "Time string length must be 8 at line %d, got '%s'", idx + 1, s.c_str());
    // Check fixed positions for ':'
    ensuref(s[1] == ':' && s[4] == ':',
            "Time format must be M:SS:sss at line %d, got '%s'", idx + 1, s.c_str());
    // Extract parts
    string mStr  = s.substr(0, 1);
    string sStr  = s.substr(2, 2);
    string msStr = s.substr(5, 3);

    // All must be digits
    auto allDigits = [](const string &t) {
        for (char c : t) if (!(c >= '0' && c <= '9')) return false;
        return true;
    };
    ensuref(allDigits(mStr) && allDigits(sStr) && allDigits(msStr),
            "Time components must be digits at line %d, got '%s'", idx + 1, s.c_str());

    int M  = stoi(mStr);
    int SS = stoi(sStr);
    int sss= stoi(msStr);

    ensuref(0 <= M && M <= 9,
            "Minutes out of range [0,9] at line %d, got %d", idx + 1, M);
    ensuref(0 <= SS && SS <= 59,
            "Seconds out of range [0,59] at line %d, got %d", idx + 1, SS);
    ensuref(0 <= sss && sss <= 999,
            "Milliseconds out of range [0,999] at line %d, got %d", idx + 1, sss);

    // Global constraint: 0:00:001 <= time <= 9:59:999
    long long total_ms = (long long)M * 60LL * 1000LL + (long long)SS * 1000LL + (long long)sss;
    long long min_ms = 0LL * 60LL * 1000LL + 0LL * 1000LL + 1LL;    // 0:00:001
    long long max_ms = 9LL * 60LL * 1000LL + 59LL * 1000LL + 999LL; // 9:59:999

    ensuref(total_ms >= min_ms && total_ms <= max_ms,
            "Time out of allowed global range [0:00:001, 9:59:999] at line %d, got '%s'",
            idx + 1, s.c_str());

    return (int)total_ms;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 8;
    vector<Racer> racers;
    racers.reserve(N);

    for (int i = 0; i < N; ++i) {
        // Read the full line, because time contains ':' and we also have team separated by space.
        string line = inf.readLine("[^]+", "line");
        // Split by single space; statement says "공백을 사이에 두고" (one space separator)
        // But to be robust, allow any single space, no extra tokens.
        string timeStr, teamStr;
        {
            stringstream ss(line);
            ss >> timeStr >> teamStr;
            string extra;
            ss >> extra;
            ensuref(!timeStr.empty() && !teamStr.empty() && extra.empty(),
                    "Each line must contain exactly two tokens: time and team, at line %d, got '%s'",
                    i + 1, line.c_str());
        }

        int t = parseTime(timeStr, i);

        ensuref(teamStr.size() == 1 && (teamStr[0] == 'R' || teamStr[0] == 'B'),
                "Team must be 'R' or 'B' at line %d, got '%s'", i + 1, teamStr.c_str());
        char team = teamStr[0];

        racers.push_back({t, team});
    }

    // Global constraint: all finish times are distinct
    {
        vector<int> times;
        times.reserve(N);
        for (auto &r : racers) times.push_back(r.time);
        sort(times.begin(), times.end());
        for (int i = 1; i < N; ++i) {
            ensuref(times[i] != times[i - 1],
                    "All finish times must be distinct, but duplicate found at index pair (%d, %d)",
                    i, i - 1);
        }
    }

    // No additional global guarantees about scores in the statement must be enforced
    // beyond correctness of input; we do NOT compute or check the match winner here.

    inf.readEof();
}
