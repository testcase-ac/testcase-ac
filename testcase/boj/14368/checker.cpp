#include "testlib.h"

#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct TestCase {
    int jackets;
    int pants;
    int shirts;
    int limit;
};

struct Claim {
    vector<int> days;
};

vector<TestCase> cases;

Claim readClaim(InStream& stream, TResult verdict, const char* who) {
    Claim claim;
    claim.days.reserve(cases.size());

    for (int caseIndex = 1; caseIndex <= int(cases.size()); ++caseIndex) {
        const TestCase& tc = cases[caseIndex - 1];

        string caseWord = stream.readToken();
        if (caseWord != "Case") {
            stream.quitf(verdict, "%s case %d: expected 'Case', found '%s'",
                         who, caseIndex, caseWord.c_str());
        }

        string label = stream.readToken();
        string expectedLabel = format("#%d:", caseIndex);
        if (label != expectedLabel) {
            stream.quitf(verdict, "%s case %d: expected label '%s', found '%s'",
                         who, caseIndex, expectedLabel.c_str(), label.c_str());
        }

        int maxOutfits = tc.jackets * tc.pants * tc.shirts;
        int dayCount = stream.readInt(0, maxOutfits, format("%s case %d day count", who, caseIndex).c_str());
        claim.days.push_back(dayCount);

        set<tuple<int, int, int> > outfits;
        vector<vector<int> > jacketPants(tc.jackets + 1, vector<int>(tc.pants + 1, 0));
        vector<vector<int> > jacketShirts(tc.jackets + 1, vector<int>(tc.shirts + 1, 0));
        vector<vector<int> > pantsShirts(tc.pants + 1, vector<int>(tc.shirts + 1, 0));

        for (int day = 1; day <= dayCount; ++day) {
            int jacket = stream.readInt(1, tc.jackets,
                                        format("%s case %d day %d jacket", who, caseIndex, day).c_str());
            int pants = stream.readInt(1, tc.pants,
                                      format("%s case %d day %d pants", who, caseIndex, day).c_str());
            int shirt = stream.readInt(1, tc.shirts,
                                      format("%s case %d day %d shirt", who, caseIndex, day).c_str());

            tuple<int, int, int> outfit(jacket, pants, shirt);
            if (!outfits.insert(outfit).second) {
                stream.quitf(verdict,
                             "%s case %d repeats outfit (%d, %d, %d)",
                             who, caseIndex, jacket, pants, shirt);
            }

            if (++jacketPants[jacket][pants] > tc.limit) {
                stream.quitf(verdict,
                             "%s case %d uses jacket-pants (%d, %d) %d times, limit is %d",
                             who, caseIndex, jacket, pants, jacketPants[jacket][pants], tc.limit);
            }
            if (++jacketShirts[jacket][shirt] > tc.limit) {
                stream.quitf(verdict,
                             "%s case %d uses jacket-shirt (%d, %d) %d times, limit is %d",
                             who, caseIndex, jacket, shirt, jacketShirts[jacket][shirt], tc.limit);
            }
            if (++pantsShirts[pants][shirt] > tc.limit) {
                stream.quitf(verdict,
                             "%s case %d uses pants-shirt (%d, %d) %d times, limit is %d",
                             who, caseIndex, pants, shirt, pantsShirts[pants][shirt], tc.limit);
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(verdict, "%s has extra output", who);
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(1, 100, "T");
    cases.resize(t);
    for (int i = 0; i < t; ++i) {
        cases[i].jackets = inf.readInt(1, 10, format("J[%d]", i + 1).c_str());
        cases[i].pants = inf.readInt(cases[i].jackets, 10, format("P[%d]", i + 1).c_str());
        cases[i].shirts = inf.readInt(cases[i].pants, 10, format("S[%d]", i + 1).c_str());
        cases[i].limit = inf.readInt(1, 10, format("K[%d]", i + 1).c_str());
    }

    Claim jury = readClaim(ans, _fail, "jury");
    Claim participant = readClaim(ouf, _wa, "participant");

    for (int i = 0; i < t; ++i) {
        if (participant.days[i] < jury.days[i]) {
            quitf(_wa,
                  "case %d: participant has %d valid outfits, jury has %d",
                  i + 1, participant.days[i], jury.days[i]);
        }
        if (participant.days[i] > jury.days[i]) {
            quitf(_fail,
                  "case %d: participant found %d valid outfits, better than jury's %d",
                  i + 1, participant.days[i], jury.days[i]);
        }
    }

    quitf(_ok, "all %d cases match the jury optimum counts", t);
}
