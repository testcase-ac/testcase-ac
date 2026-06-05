#include "testlib.h"

#include <string>

using namespace std;

bool isAllowedChar(char c) {
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9') ||
           c == ' ' || c == '<' || c == '>' || c == '&' || c == '|' ||
           c == '(' || c == ')' || c == '$' || c == '?' || c == '+' || c == '_';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[^]{1,1000000}", "S");
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        ensuref(isAllowedChar(c),
                "S[%d] has disallowed character with ASCII code %d",
                i + 1,
                (int)(unsigned char)c);

        if (c == '&' || c == '|') {
            int j = i;
            while (j < (int)s.size() && s[j] == c) {
                ++j;
            }
            ensuref((j - i) % 2 == 0,
                    "run of '%c' from position %d has odd length %d",
                    c,
                    i + 1,
                    j - i);
            i = j - 1;
        }
    }

    inf.readEof();
}
