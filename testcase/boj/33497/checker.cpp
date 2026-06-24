#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, m;
vector<int> needMorning, needEvening;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");

    verdict = upperCase(verdict);

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "expected YES or NO, found '%s'", verdict.c_str());
    }

    vector<int> skipped(n, 0);
    vector<int> morning(m, 0), evening(m, 0);

    for (int student = 0; student < n; ++student) {
        string row = stream.readToken("[+\\-X]+", format("S_%d", student + 1).c_str());
        if ((int)row.size() != m) {
            stream.quitf(_wa,
                         "S_%d has length %d instead of %d",
                         student + 1,
                         (int)row.size(),
                         m);
        }

        for (int day = 0; day < m; ++day) {
            if (row[day] == '+') {
                ++morning[day];
            } else if (row[day] == '-') {
                ++evening[day];
            } else if (row[day] == 'X') {
                ++skipped[student];
            } else {
                stream.quitf(_wa,
                             "S_%d[%d] has invalid character '%c'",
                             student + 1,
                             day + 1,
                             row[day]);
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after schedule");
    }

    for (int student = 0; student < n; ++student) {
        if (skipped[student] != 1) {
            stream.quitf(_wa,
                         "student %d skips %d days instead of exactly 1",
                         student + 1,
                         skipped[student]);
        }
    }

    for (int day = 0; day < m; ++day) {
        if (morning[day] < needMorning[day]) {
            stream.quitf(_wa,
                         "day %d has %d morning students, need at least %d",
                         day + 1,
                         morning[day],
                         needMorning[day]);
        }
        if (evening[day] < needEvening[day]) {
            stream.quitf(_wa,
                         "day %d has %d evening students, need at least %d",
                         day + 1,
                         evening[day],
                         needEvening[day]);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    needMorning.resize(m);
    needEvening.resize(m);
    for (int day = 0; day < m; ++day) {
        needMorning[day] = inf.readInt();
        needEvening[day] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid schedule, participant answered NO");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid schedule but jury answered NO");
    }

    quitf(_ok, "%s", participant.possible ? "valid schedule" : "impossible");
}
