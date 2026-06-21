#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement omits a lower bound, but the sentence is formed from
    // two-letter words, so length 1 is not a well-defined instance.
    string s = inf.readToken("[A-Za-z]{2,2500}", "s");
    inf.readEoln();

    for (int i = 1; i < static_cast<int>(s.size()); ++i) {
        bool prevUpper = isupper(static_cast<unsigned char>(s[i - 1]));
        bool curUpper = isupper(static_cast<unsigned char>(s[i]));
        ensuref(prevUpper != curUpper,
                "adjacent characters must alternate case at positions %d and %d",
                i, i + 1);
    }

    inf.readEof();
}
