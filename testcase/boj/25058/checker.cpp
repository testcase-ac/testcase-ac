#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<pair<int, int>> requests;
};

struct Answer {
    bool impossible;
    vector<string> arrangements;
};

vector<TestCase> cases;

bool satisfiesRequest(const string& arrangement, int red, int white) {
    const int len = red + white;
    int red_count = 0;
    int white_count = 0;

    for (int i = 0; i < (int)arrangement.size(); ++i) {
        if (arrangement[i] == 'R') {
            ++red_count;
        } else {
            ++white_count;
        }

        if (i >= len) {
            if (arrangement[i - len] == 'R') {
                --red_count;
            } else {
                --white_count;
            }
        }

        if (i + 1 >= len && red_count == red && white_count == white) {
            return true;
        }
    }

    return false;
}

void validateArrangement(InStream& stream, TResult invalid_result, const string& value, int case_index) {
    const TestCase& tc = cases[case_index];

    if ((int)value.size() != tc.n) {
        stream.quitf(invalid_result,
                     "case %d: arrangement length is %d instead of %d",
                     case_index + 1,
                     (int)value.size(),
                     tc.n);
    }

    for (int i = 0; i < tc.n; ++i) {
        if (value[i] != 'R' && value[i] != 'W') {
            stream.quitf(invalid_result,
                         "case %d: character %d is '%c' instead of R or W",
                         case_index + 1,
                         i + 1,
                         value[i]);
        }
    }

    for (int i = 0; i < (int)tc.requests.size(); ++i) {
        int red = tc.requests[i].first;
        int white = tc.requests[i].second;
        if (!satisfiesRequest(value, red, white)) {
            stream.quitf(invalid_result,
                         "case %d: arrangement does not satisfy request %d (%d red, %d white)",
                         case_index + 1,
                         i + 1,
                         red,
                         white);
        }
    }
}

Answer readAnswer(InStream& stream, TResult invalid_result) {
    Answer result;
    result.impossible = false;
    result.arrangements.reserve(cases.size());

    for (int case_index = 0; case_index < (int)cases.size(); ++case_index) {
        string token = stream.readToken();

        if (token == "IMPOSSIBLE") {
            result.arrangements.push_back("");
            continue;
        }

        validateArrangement(stream, invalid_result, token, case_index);
        result.arrangements.push_back(token);
    }

    if (!stream.seekEof()) {
        stream.quitf(invalid_result, "extra output after %d test cases", (int)cases.size());
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.reserve(t);
    for (int case_index = 0; case_index < t; ++case_index) {
        TestCase tc;
        int m;
        tc.n = inf.readInt();
        m = inf.readInt();
        tc.requests.reserve(m);
        for (int i = 0; i < m; ++i) {
            int red = inf.readInt();
            int white = inf.readInt();
            tc.requests.push_back({red, white});
        }
        cases.push_back(tc);
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    for (int case_index = 0; case_index < t; ++case_index) {
        bool jury_impossible = jury.arrangements[case_index].empty();
        bool participant_impossible = participant.arrangements[case_index].empty();

        if (!jury_impossible && participant_impossible) {
            quitf(_wa, "case %d: participant printed IMPOSSIBLE but jury has a valid arrangement", case_index + 1);
        }

        if (jury_impossible && !participant_impossible) {
            quitf(_fail, "case %d: participant found a valid arrangement but jury printed IMPOSSIBLE", case_index + 1);
        }
    }

    quitf(_ok, "%d test case(s) accepted", t);
}
