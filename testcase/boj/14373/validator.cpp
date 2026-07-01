#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 16, "N");
        inf.readEoln();

        set<pair<string, string>> topics;
        for (int i = 1; i <= N; ++i) {
            string first = inf.readToken("[A-Z]{1,20}", "first_word");
            inf.readSpace();
            string second = inf.readToken("[A-Z]{1,20}", "second_word");
            inf.readEoln();

            ensuref(topics.insert({first, second}).second,
                    "duplicate topic in case %d at row %d: %s %s",
                    tc,
                    i,
                    first.c_str(),
                    second.c_str());
        }
    }

    inf.readEof();
}
