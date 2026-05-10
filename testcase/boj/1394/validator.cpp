#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: allowed characters (char set)
    string charset = inf.readToken("[^ \n\r\t]+", "charset");
    inf.readEoln();

    int charset_len = charset.length();
    ensuref(1 <= charset_len && charset_len <= 100, "charset length must be between 1 and 100, got %d", charset_len);

    // Check for duplicate characters in charset
    set<char> charset_set;
    for (int i = 0; i < charset_len; ++i) {
        char c = charset[i];
        ensuref(c != ' ', "charset must not contain spaces (found at position %d)", i+1);
        ensuref(charset_set.count(c) == 0, "charset contains duplicate character '%c' at position %d", c, i+1);
        charset_set.insert(c);
    }

    // Read second line: password
    string password = inf.readToken("[^ \n\r\t]+", "password");
    inf.readEoln();

    int password_len = password.length();
    ensuref(1 <= password_len && password_len <= 1000000, "password length must be between 1 and 1,000,000, got %d", password_len);

    // Check that all password characters are in charset
    for (int i = 0; i < password_len; ++i) {
        char c = password[i];
        ensuref(charset_set.count(c), "password contains character '%c' at position %d not in charset", c, i+1);
    }

    inf.readEof();
}
