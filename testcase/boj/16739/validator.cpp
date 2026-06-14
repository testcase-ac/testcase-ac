#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

void validateFileName(const string& s, const char* name) {
    ensuref(1 <= (int)s.size() && (int)s.size() <= 9,
            "%s length must be between 1 and 9: %d", name, (int)s.size());

    for (int i = 0; i < (int)s.size(); ++i) {
        unsigned char ch = s[i];
        ensuref(isdigit(ch) || ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'),
                "%s has invalid character at position %d: %c", name, i + 1, s[i]);

        if (isdigit(ch) && s[i] == '0' && (i == 0 || !isdigit((unsigned char)s[i - 1]))) {
            ensuref(false, "%s has a digit sequence starting with zero at position %d",
                    name, i + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i <= n; ++i) {
        string name = inf.readToken("[A-Za-z0-9]{1,9}", "s_i");
        validateFileName(name, "s_i");
        inf.readEoln();
    }

    inf.readEof();
}
