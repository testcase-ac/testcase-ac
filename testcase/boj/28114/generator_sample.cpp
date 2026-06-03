#include "testlib.h"

#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

string makeSurname(int index, int length) {
    string s(length, char('A' + index));
    if (length >= 2) {
        s[1] = char('A' + rnd.next(26));
    }
    if (length >= 3) {
        s[length - 1] = char('A' + rnd.next(26));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<int> p;
    vector<int> y;
    vector<int> surnameLengths;

    if (mode == 0) {
        p = {1, 2, 3};
        y = {2010, 2011, 2012};
        surnameLengths = {1, 1, 1};
    } else if (mode == 1) {
        p = {19998, 19999, 20000};
        y = {2097, 2098, 2099};
        surnameLengths = {5, 5, 5};
    } else if (mode == 2) {
        int pBase = rnd.next(1, 19998);
        int yBase = rnd.next(2010, 2097);
        p = {pBase, pBase + 1, pBase + 2};
        y = {yBase, yBase + 1, yBase + 2};
        surnameLengths = {1, rnd.next(2, 4), 5};
    } else {
        set<int> usedP;
        set<int> usedY;
        while ((int)p.size() < 3) {
            usedP.insert(rnd.next(1, 20000));
            p.assign(usedP.begin(), usedP.end());
        }
        while ((int)y.size() < 3) {
            usedY.insert(rnd.next(2010, 2099));
            y.assign(usedY.begin(), usedY.end());
        }
        surnameLengths = {rnd.next(1, 5), rnd.next(1, 5), rnd.next(1, 5)};
    }

    shuffle(p.begin(), p.end());
    shuffle(y.begin(), y.end());
    shuffle(surnameLengths.begin(), surnameLengths.end());

    vector<tuple<int, int, string>> members;
    set<string> usedSurnames;
    for (int i = 0; i < 3; ++i) {
        string surname;
        do {
            surname = makeSurname(i + rnd.next(20), surnameLengths[i]);
        } while (!usedSurnames.insert(surname).second);
        members.emplace_back(p[i], y[i], surname);
    }

    shuffle(members.begin(), members.end());
    for (const auto& [solved, year, surname] : members) {
        println(solved, year, surname);
    }

    return 0;
}
