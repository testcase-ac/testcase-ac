#include "testlib.h"

#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct TestCase {
    int jackets;
    int pants;
    int shirts;
    int limit;
};

struct Answer {
    vector<int> days;
};

vector<TestCase> cases;

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.days.reserve(cases.size());

    for (int caseIndex = 1; caseIndex <= (int)cases.size(); ++caseIndex) {
        string caseToken = stream.readToken();
        if (caseToken != "Case") {
            stream.quitf(_wa, "case %d: expected 'Case', found '%s'", caseIndex, caseToken.c_str());
        }

        string numberToken = stream.readToken();
        string expectedNumberToken = "#" + to_string(caseIndex) + ":";
        if (numberToken != expectedNumberToken) {
            stream.quitf(_wa,
                         "case %d: expected '%s', found '%s'",
                         caseIndex,
                         expectedNumberToken.c_str(),
                         numberToken.c_str());
        }

        const TestCase& tc = cases[caseIndex - 1];
        int days = stream.readInt(0,
                                  tc.jackets * tc.pants * tc.shirts,
                                  format("case %d number of days", caseIndex).c_str());
        answer.days.push_back(days);

        set<tuple<int, int, int>> outfits;
        vector<vector<int>> jacketPants(tc.jackets + 1, vector<int>(tc.pants + 1));
        vector<vector<int>> jacketShirts(tc.jackets + 1, vector<int>(tc.shirts + 1));
        vector<vector<int>> pantsShirts(tc.pants + 1, vector<int>(tc.shirts + 1));

        for (int i = 0; i < days; ++i) {
            int jacket = stream.readInt(1,
                                        tc.jackets,
                                        format("case %d outfit %d jacket", caseIndex, i + 1).c_str());
            int pants = stream.readInt(1,
                                       tc.pants,
                                       format("case %d outfit %d pants", caseIndex, i + 1).c_str());
            int shirts = stream.readInt(1,
                                        tc.shirts,
                                        format("case %d outfit %d shirt", caseIndex, i + 1).c_str());

            auto outfit = make_tuple(jacket, pants, shirts);
            if (!outfits.insert(outfit).second) {
                stream.quitf(_wa,
                             "case %d: outfit %d (%d, %d, %d) is repeated",
                             caseIndex,
                             i + 1,
                             jacket,
                             pants,
                             shirts);
            }

            if (++jacketPants[jacket][pants] > tc.limit) {
                stream.quitf(_wa,
                             "case %d: jacket-pants pair (%d, %d) appears more than %d times",
                             caseIndex,
                             jacket,
                             pants,
                             tc.limit);
            }
            if (++jacketShirts[jacket][shirts] > tc.limit) {
                stream.quitf(_wa,
                             "case %d: jacket-shirt pair (%d, %d) appears more than %d times",
                             caseIndex,
                             jacket,
                             shirts,
                             tc.limit);
            }
            if (++pantsShirts[pants][shirts] > tc.limit) {
                stream.quitf(_wa,
                             "case %d: pants-shirt pair (%d, %d) appears more than %d times",
                             caseIndex,
                             pants,
                             shirts,
                             tc.limit);
            }
        }
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    cases.reserve(testCount);
    for (int i = 0; i < testCount; ++i) {
        int jackets = inf.readInt();
        int pants = inf.readInt();
        int shirts = inf.readInt();
        int limit = inf.readInt();
        cases.push_back({jackets, pants, shirts, limit});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        int juryDays = jury.days[caseIndex - 1];
        int participantDays = participant.days[caseIndex - 1];
        if (participantDays < juryDays) {
            quitf(_wa,
                  "case %d: participant has %d days, jury has %d",
                  caseIndex,
                  participantDays,
                  juryDays);
        }
        if (participantDays > juryDays) {
            quitf(_fail,
                  "case %d: participant has %d valid days, more than jury's %d",
                  caseIndex,
                  participantDays,
                  juryDays);
        }
    }

    quitf(_ok, "all %d case(s) match the jury baseline", testCount);
}
