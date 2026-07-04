#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 100, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        setTestCase(caseIndex++);

        set<string> words;
        for (int i = 0; i < n; ++i) {
            string word = inf.readToken("[0-9A-F]{1,50}", "code_word");
            inf.readEoln();

            ensuref(words.insert(word).second,
                    "duplicate code word in test case %d: %s",
                    caseIndex - 1,
                    word.c_str());
        }
    }

    inf.readEof();
}
