#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string genRandomMBTI() {
    static const vector<string> pos = {"IE", "SN", "TF", "JP"};
    string s;
    for (int i = 0; i < 4; i++) {
        s += rnd.any(pos[i]);
    }
    return s;
}

string oppositeMBTI(const string &t) {
    string s = t;
    for (char &c : s) {
        switch (c) {
            case 'I': c = 'E'; break;
            case 'E': c = 'I'; break;
            case 'S': c = 'N'; break;
            case 'N': c = 'S'; break;
            case 'T': c = 'F'; break;
            case 'F': c = 'T'; break;
            case 'J': c = 'P'; break;
            case 'P': c = 'J'; break;
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(1, 10);
    int mode = rnd.next(0, 2);

    vector<string> men(N), women(N);

    if (mode == 0) {
        // All men same, all women opposite to maximize score
        string base = genRandomMBTI();
        string opp = oppositeMBTI(base);
        for (int i = 0; i < N; i++) {
            men[i] = base;
            women[i] = opp;
        }
    } else if (mode == 1) {
        // Fully random
        for (int i = 0; i < N; i++) men[i] = genRandomMBTI();
        for (int i = 0; i < N; i++) women[i] = genRandomMBTI();
    } else {
        // Mixed clusters around a base pattern
        string base = genRandomMBTI();
        string opp = oppositeMBTI(base);
        double p1 = rnd.next(0.0, 1.0);
        double p2 = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++) {
            double r = rnd.next();
            if (r < p1) men[i] = base;
            else if (r < p1 + 0.2) men[i] = opp;
            else men[i] = genRandomMBTI();
        }
        for (int i = 0; i < N; i++) {
            double r = rnd.next();
            if (r < p2) women[i] = opp;
            else if (r < p2 + 0.2) women[i] = base;
            else women[i] = genRandomMBTI();
        }
    }

    // Shuffle order to avoid any order bias
    shuffle(men.begin(), men.end());
    shuffle(women.begin(), women.end());

    // Output
    println(N);
    for (auto &s : men) println(s);
    for (auto &s : women) println(s);

    return 0;
}
