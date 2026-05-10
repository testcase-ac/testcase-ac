#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N
    int N = inf.readInt(3, 100, "N");
    inf.readEoln();

    // We don't know how many countries in advance, but it's at most N
    vector<int> countryCount(N+1, 0);
    vector< set<int> > studentSet(N+1);
    set<int> countrySet;
    set<int> scoreSet;
    int maxCountry = 0;

    // Read each student's record
    for (int i = 0; i < N; i++) {
        // country number: 1..N
        int c = inf.readInt(1, N, "country");
        inf.readSpace();
        // student number: 1..N (we'll later check tightness per country)
        int s = inf.readInt(1, N, "student");
        inf.readSpace();
        // score: 0..1000
        int score = inf.readInt(0, 1000, "score");
        inf.readEoln();

        // Track counts and sets
        countryCount[c]++;
        studentSet[c].insert(s);
        countrySet.insert(c);
        maxCountry = max(maxCountry, c);

        // Ensure no duplicate scores
        auto p = scoreSet.insert(score);
        ensuref(p.second, "Duplicate score %d at input line %d", score, i + 2);
    }

    // At least two distinct countries must participate
    ensuref(countrySet.size() >= 2, "Less than two countries exist");

    // Country numbers must be contiguous from 1 to maxCountry
    ensuref(maxCountry == (int)countrySet.size(),
            "Country numbers are not a contiguous range 1..%d", maxCountry);

    // For each country, student numbers must be exactly 1..(#students from that country)
    for (int c = 1; c <= maxCountry; c++) {
        int cnt = countryCount[c];
        ensuref(cnt > 0, "Country %d has no students", c);
        auto &ss = studentSet[c];
        // no duplicates and count matches
        ensuref((int)ss.size() == cnt,
                "Mismatch or duplicates in student numbers for country %d", c);
        int mn = *ss.begin();
        int mx = *ss.rbegin();
        ensuref(mn == 1,
                "Minimum student number for country %d is %d, expected 1", c, mn);
        ensuref(mx == cnt,
                "Maximum student number for country %d is %d, expected %d", c, mx, cnt);
    }

    // No extra content
    inf.readEof();
    return 0;
}
