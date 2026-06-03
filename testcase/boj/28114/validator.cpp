#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<int> solved_counts;
    set<int> admission_years;
    set<string> surnames;

    for (int i = 1; i <= 3; ++i) {
        int p = inf.readInt(1, 20000, format("P_%d", i));
        inf.readSpace();
        int y = inf.readInt(2010, 2099, format("Y_%d", i));
        inf.readSpace();
        string s = inf.readToken("[A-Z]{1,5}", format("S_%d", i));
        inf.readEoln();

        ensuref(solved_counts.insert(p).second, "P_i values must be distinct: %d", p);
        ensuref(admission_years.insert(y).second, "Y_i values must be distinct: %d", y);
        ensuref(surnames.insert(s).second, "S_i values must be distinct: %s", s.c_str());
    }

    inf.readEof();
}
