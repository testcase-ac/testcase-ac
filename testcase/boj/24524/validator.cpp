#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,1000000}", "S");
    inf.readEoln();
    string t = inf.readToken("[a-z]{1,26}", "T");
    inf.readEoln();

    ensuref(t.size() <= s.size(), "|T| must be at most |S|: |T|=%d, |S|=%d",
            int(t.size()), int(s.size()));

    array<bool, 26> seen{};
    for (char ch : t) {
        int index = ch - 'a';
        ensuref(!seen[index], "T contains duplicate character '%c'", ch);
        seen[index] = true;
    }

    inf.readEof();
}
