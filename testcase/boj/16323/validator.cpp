#include "testlib.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

static bool decimalLess(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a < b;
}

static string twiceDecimal(const string& value) {
    string result;
    int carry = 0;
    for (int i = int(value.size()) - 1; i >= 0; --i) {
        int digit = (value[i] - '0') * 2 + carry;
        result.push_back(char('0' + digit % 10));
        carry = digit / 10;
    }
    if (carry > 0) {
        result.push_back(char('0' + carry));
    }
    reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    string s = inf.readToken("[1-9][0-9]{0,999}", "s");
    inf.readEoln();

    set<string> seen_names;
    vector<string> bids;
    for (int i = 0; i < n; i++) {
        string name = inf.readToken("[A-Za-z]{1,20}", "t");
        inf.readSpace();
        string bet = inf.readToken("[1-9][0-9]{0,999}", "b");
        inf.readEoln();

        ensuref(!seen_names.count(name),
                "Duplicate participant name \"%s\" at line %d",
                name.c_str(), i + 2);
        seen_names.insert(name);
        bids.push_back(bet);
    }

    sort(bids.begin(), bids.end(), decimalLess);
    for (int i = 1; i < n; ++i) {
        string required = twiceDecimal(bids[i - 1]);
        ensuref(!decimalLess(bids[i], required),
                "bid %d in sorted order is %s, but must be at least twice %s",
                i + 1, bids[i].c_str(), bids[i - 1].c_str());
    }

    inf.readEof();
    return 0;
}
