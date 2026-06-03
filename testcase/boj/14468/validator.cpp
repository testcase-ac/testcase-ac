#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Z]{52}", "s");
    inf.readEoln();

    vector<int> count(26, 0);
    for (char c : s) {
        ++count[c - 'A'];
    }

    for (int i = 0; i < 26; ++i) {
        ensuref(count[i] == 2, "letter %c appears %d times", char('A' + i), count[i]);
    }

    inf.readEof();
}
