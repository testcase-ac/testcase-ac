#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

const int kMaxProblems = 20;
const int kMaxTeams = 50;
const int kMaxValue = 1000000000;
const int kMaxTeamLineLength = 10000;
const int kMaxTotalTeams = 100000;

bool isCanonicalNonNegativeInteger(const string& s) {
    if (s.empty()) {
        return false;
    }
    if (s.size() > 1 && s[0] == '0') {
        return false;
    }
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

int parseNonNegativeInteger(const string& s, const char* fieldName, int lineIndex) {
    ensuref(isCanonicalNonNegativeInteger(s), "%s on team line %d is not a canonical non-negative integer", fieldName, lineIndex);

    long long value = 0;
    for (char c : s) {
        value = value * 10 + (c - '0');
        ensuref(value <= kMaxValue, "%s on team line %d exceeds practical cap %d", fieldName, lineIndex, kMaxValue);
    }
    return static_cast<int>(value);
}

vector<string> splitCommaSeparated(const string& line) {
    vector<string> parts;
    size_t start = 0;
    while (true) {
        size_t comma = line.find(',', start);
        if (comma == string::npos) {
            parts.push_back(line.substr(start));
            return parts;
        }
        parts.push_back(line.substr(start, comma - start));
        start = comma + 1;
    }
}

void validateTeamLine(const string& line, int p, int teamIndex) {
    ensuref(!line.empty(), "team line %d is empty", teamIndex);
    ensuref(static_cast<int>(line.size()) <= kMaxTeamLineLength,
            "team line %d exceeds practical length cap %d", teamIndex, kMaxTeamLineLength);

    for (char c : line) {
        ensuref(c != '\r', "team line %d contains carriage return", teamIndex);
    }

    vector<string> parts = splitCommaSeparated(line);
    ensuref(static_cast<int>(parts.size()) == p + 1,
            "team line %d has %d comma-separated fields, expected %d",
            teamIndex, static_cast<int>(parts.size()), p + 1);

    const string& name = parts[0];
    // CHECK: The statement says the data starts with the team name and forbids commas in it,
    // but gives no length or character set. Require a non-empty line field and otherwise
    // allow the spaces and punctuation demonstrated by the sample.
    ensuref(!name.empty(), "team line %d has an empty team name", teamIndex);
    ensuref(name.front() != ' ' && name.back() != ' ',
            "team line %d has leading or trailing spaces in the team name", teamIndex);

    for (int problem = 1; problem <= p; ++problem) {
        const string& record = parts[problem];
        size_t slash = record.find('/');
        ensuref(slash != string::npos, "team line %d problem %d record has no slash", teamIndex, problem);
        ensuref(record.find('/', slash + 1) == string::npos,
                "team line %d problem %d record has multiple slashes", teamIndex, problem);

        string submissions = record.substr(0, slash);
        string result = record.substr(slash + 1);
        parseNonNegativeInteger(submissions, "submission count", teamIndex);

        if (result == "-") {
            continue;
        }
        parseNonNegativeInteger(result, "solved time", teamIndex);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int totalTeams = 0;
    int contest = 0;
    while (true) {
        int p = inf.readInt(0, kMaxProblems, "P");
        inf.readEoln();
        if (p == 0) {
            break;
        }

        ++contest;
        setTestCase(contest);

        for (int i = 1; i <= p; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            // CHECK: The statement says point values are positive but gives no upper bound.
            inf.readInt(1, kMaxValue, "points_i");
        }
        inf.readEoln();

        int t = inf.readInt(1, kMaxTeams, "T");
        inf.readEoln();

        totalTeams += t;
        // CHECK: The statement gives no upper bound on the number of contests.
        ensuref(totalTeams <= kMaxTotalTeams, "total number of team rows exceeds practical cap %d", kMaxTotalTeams);

        for (int i = 1; i <= t; ++i) {
            // CHECK: The statement does not bound team name length or omitted integer fields;
            // this line cap keeps malformed inputs from becoming impractically large.
            string line = inf.readLine("[^]{1,10000}", "team_line");
            validateTeamLine(line, p, i);
        }
    }

    inf.readEof();
}
