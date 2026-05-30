#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[()\\-]{1,200000}", "commands");

    int text_size = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        if (c == '(' || c == ')') {
            ++text_size;
        } else {
            ensuref(text_size > 0,
                    "'-' command at position %d when editor text is empty",
                    i + 1);
            --text_size;
        }
    }

    inf.readEof();
    return 0;
}
