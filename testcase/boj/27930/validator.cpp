#include "testlib.h"
#include <string>

using namespace std;

int firstCompletionIndex(const string& s, const string& target) {
    int matched = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (matched < (int)target.size() && s[i] == target[matched]) {
            ++matched;
            if (matched == (int)target.size()) {
                return i;
            }
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[A-Z]{5,500000}", "S");
    inf.readEoln();

    int yonsei = firstCompletionIndex(s, "YONSEI");
    int korea = firstCompletionIndex(s, "KOREA");

    ensuref(yonsei != -1 || korea != -1,
            "at least one of YONSEI or KOREA must be obtainable as a subsequence");
    ensuref(yonsei == -1 || korea == -1 || yonsei != korea,
            "YONSEI and KOREA must not first become obtainable at the same prefix");

    inf.readEof();
}
