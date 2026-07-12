#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string document = inf.readLine("[a-z\\ ]{1,2500}", "document");
    ensuref(any_of(document.begin(), document.end(), [](char c) { return c >= 'a' && c <= 'z'; }),
            "document must contain at least one lowercase letter");
    ensuref(document.front() != ' ' && document.back() != ' ',
            "document must not have leading or trailing spaces");

    string pattern = inf.readLine("[a-z\\ ]{1,50}", "pattern");
    ensuref(any_of(pattern.begin(), pattern.end(), [](char c) { return c >= 'a' && c <= 'z'; }),
            "pattern must contain at least one lowercase letter");
    ensuref(pattern.front() != ' ' && pattern.back() != ' ',
            "pattern must not have leading or trailing spaces");

    inf.readEof();
    return 0;
}
