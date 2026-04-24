#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

// Generate a truly possible outcome: each team plays 5 matches.
static vector<int> genValid() {
    const int n = 6;
    vector<int> w(n, 0), d(n, 0), l(n, 0);
    vector<pair<int,int>> matches;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            matches.emplace_back(i, j);
    // randomize match order and draw probability
    shuffle(matches.begin(), matches.end());
    double pDraw = rnd.next();
    for (auto &m : matches) {
        int i = m.first, j = m.second;
        double r = rnd.next();
        if (r < pDraw) {
            d[i]++; d[j]++;
        } else if (r < pDraw + (1 - pDraw) / 2) {
            w[i]++; l[j]++;
        } else {
            w[j]++; l[i]++;
        }
    }
    vector<int> res;
    for (int i = 0; i < n; i++) {
        res.push_back(w[i]);
        res.push_back(d[i]);
        res.push_back(l[i]);
    }
    return res;
}

// Generate an impossible outcome by having total wins != total losses
// but keep each team's sum = 5 and total draws even.
static vector<int> genWinLossMismatch() {
    vector<int> v(18);
    while (1) {
        int sumW = 0, sumD = 0, sumL = 0;
        for (int i = 0; i < 6; i++) {
            int di = rnd.next(0, 5);
            int wi = rnd.next(0, 5 - di);
            int li = 5 - di - wi;
            v[3*i]   = wi;
            v[3*i+1] = di;
            v[3*i+2] = li;
            sumW += wi;
            sumD += di;
            sumL += li;
        }
        if (sumD % 2 == 0 && sumW != sumL)
            break;
    }
    return v;
}

// Generate an impossible outcome by making total draws odd,
// while each team still plays exactly 5 matches.
static vector<int> genOddDraws() {
    vector<int> v(18);
    int sumD = 0;
    for (int i = 0; i < 5; i++) {
        int di = rnd.next(0, 5);
        int wi = rnd.next(0, 5 - di);
        int li = 5 - di - wi;
        v[3*i]   = wi;
        v[3*i+1] = di;
        v[3*i+2] = li;
        sumD += di;
    }
    // choose d6 so that total draws is odd
    vector<int> cand;
    for (int x = 0; x <= 5; x++)
        if ((sumD + x) % 2 == 1)
            cand.push_back(x);
    int d6 = rnd.any(cand);
    int w6 = rnd.next(0, 5 - d6);
    int l6 = 5 - d6 - w6;
    v[15] = w6; v[16] = d6; v[17] = l6;
    return v;
}

// Generate an impossible outcome by structure:
// two teams win all 5 games, four teams lose all 5 games.
// That respects sum=5 and draws=0 but can't happen because
// those two winners face each other.
static vector<int> genImpossibleStructure() {
    vector<int> base = {
        5,0,0,  // team A: 5 wins
        5,0,0,  // team B: 5 wins
        0,0,5,  // team C: 5 losses
        0,0,5,  // team D: 5 losses
        0,0,5,  // team E: 5 losses
        0,0,5   // team F: 5 losses
    };
    vector<int> perm = {0,1,2,3,4,5};
    shuffle(perm.begin(), perm.end());
    vector<int> v(18);
    for (int i = 0; i < 6; i++) {
        int oi = perm[i];
        v[3*i]   = base[3*oi];
        v[3*i+1] = base[3*oi+1];
        v[3*i+2] = base[3*oi+2];
    }
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<vector<int>> cases;
    // two valid scenarios
    cases.push_back(genValid());
    cases.push_back(genValid());
    // two impossible scenarios
    cases.push_back(genWinLossMismatch());
    cases.push_back(genOddDraws());
    // you could also include the structural impossibility for more diversity:
    // cases.push_back(genImpossibleStructure());
    shuffle(cases.begin(), cases.end());
    for (auto &c : cases)
        println(c);
    return 0;
}
