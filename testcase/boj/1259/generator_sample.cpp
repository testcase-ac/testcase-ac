#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

string makePalindrome(int len) {
    string s(len, '0');
    s[0] = char('1' + rnd.next(9));
    for (int i = 1; i < (len + 1) / 2; ++i) {
        s[i] = char('0' + rnd.next(10));
    }
    for (int i = 0; i < len / 2; ++i) {
        s[len - 1 - i] = s[i];
    }
    return s;
}

string makeNonPalindrome(int len) {
    string s = makePalindrome(len);
    int pos = rnd.next((len + 1) / 2);
    int mirror = len - 1 - pos;
    if (pos == mirror) {
        pos = 0;
        mirror = len - 1;
    }

    char replacement = char('0' + rnd.next(10));
    while (replacement == s[pos] || (pos == 0 && replacement == '0')) {
        replacement = char('0' + rnd.next(10));
    }
    s[pos] = replacement;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int count = rnd.next(6, 24);
    vector<string> cases;
    cases.push_back("1");
    cases.push_back("9");
    cases.push_back("10");
    cases.push_back("11");
    cases.push_back("99999");

    while ((int)cases.size() < count) {
        int len = rnd.next(1, 5);
        if (rnd.next(100) < 45) {
            cases.push_back(makePalindrome(len));
        } else {
            len = rnd.next(2, 5);
            cases.push_back(makeNonPalindrome(len));
        }
    }

    shuffle(cases.begin(), cases.end());
    for (const string& s : cases) {
        println(s);
    }
    println(0);

    return 0;
}
