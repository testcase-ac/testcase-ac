#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read P and V
    int P = inf.readInt(1, 50, "P");
    inf.readSpace();
    long long V = inf.readLong(1LL, 1000000000LL, "V");
    inf.readEoln();

    set<string> party_names;
    long long sum_r = 0;
    long long sum_votes = 0;

    for (int i = 0; i < P; ++i) {
        // Read party name
        string name = inf.readToken("[a-z_]{1,50}", "party_name");
        // Check for duplicate party names
        ensuref(party_names.count(name) == 0, "Duplicate party name: %s", name.c_str());
        party_names.insert(name);

        inf.readSpace();

        // Read regional seat count
        int r_i = inf.readInt(0, 253, "regional_seat_count");
        inf.readSpace();

        // Read proportional votes
        long long v_i = inf.readLong(0LL, V, "proportional_votes");
        inf.readEoln();

        sum_r += r_i;
        sum_votes += v_i;
    }

    // Check sum of regional seats
    ensuref(sum_r <= 253, "Sum of regional seats is %lld, exceeds 253", sum_r);

    // Check sum of proportional votes
    ensuref(sum_votes <= V, "Sum of proportional votes is %lld, exceeds V=%lld", sum_votes, V);

    inf.readEof();
}
