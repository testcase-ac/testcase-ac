#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string teamFromMask(int mask, int c) {
    string team;
    team.reserve(c);
    for (int bit = c - 1; bit >= 0; --bit) {
        team.push_back((mask & (1 << bit)) ? 'G' : 'H');
    }
    return team;
}

int flipRandomBits(int mask, int c, int flips) {
    vector<int> bits(c);
    for (int i = 0; i < c; ++i) {
        bits[i] = i;
    }
    shuffle(bits.begin(), bits.end());
    for (int i = 0; i < flips; ++i) {
        mask ^= 1 << bits[i];
    }
    return mask;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c;
    if (mode == 0) {
        c = rnd.next(1, 4);
    } else if (mode == 1) {
        c = rnd.next(15, 18);
    } else {
        c = rnd.next(2, 12);
    }

    int n = rnd.next(2, mode == 1 ? 24 : 40);
    int fullMask = (1 << c) - 1;
    vector<int> teams;
    teams.reserve(n);

    if (mode == 0) {
        int limit = 1 << c;
        for (int mask = 0; mask < limit && (int)teams.size() < n; ++mask) {
            teams.push_back(mask);
        }
        while ((int)teams.size() < n) {
            teams.push_back(rnd.next(0, fullMask));
        }
    } else if (mode == 1) {
        int base = rnd.next(0, fullMask);
        teams.push_back(base);
        teams.push_back(base ^ fullMask);
        while ((int)teams.size() < n) {
            int flips = rnd.next(0, c);
            teams.push_back(flipRandomBits(base, c, flips));
        }
    } else if (mode == 2) {
        int base = rnd.next(0, fullMask);
        int maxFlips = rnd.next(1, c);
        while ((int)teams.size() < n) {
            teams.push_back(flipRandomBits(base, c, rnd.next(0, maxFlips)));
        }
    } else if (mode == 3) {
        while ((int)teams.size() < n) {
            int mask = rnd.next(0, fullMask);
            teams.push_back(mask);
            if ((int)teams.size() < n && rnd.next(0, 1)) {
                teams.push_back(mask);
            }
            if ((int)teams.size() < n && rnd.next(0, 2) == 0) {
                teams.push_back(mask ^ fullMask);
            }
        }
    } else {
        while ((int)teams.size() < n) {
            int gCount = rnd.next(0, c);
            int mask = 0;
            vector<int> bits(c);
            for (int i = 0; i < c; ++i) {
                bits[i] = i;
            }
            shuffle(bits.begin(), bits.end());
            for (int i = 0; i < gCount; ++i) {
                mask |= 1 << bits[i];
            }
            teams.push_back(mask);
        }
    }

    shuffle(teams.begin(), teams.end());

    println(c, n);
    for (int i = 0; i < n; ++i) {
        println(teamFromMask(teams[i], c));
    }

    return 0;
}
