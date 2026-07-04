#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomDigit(bool first) {
    return char('0' + rnd.next(first ? 1 : 0, 9));
}

string randomPattern(int len, int mode) {
    string s;
    s.reserve(len);

    int questionPercent = 0;
    if (mode == 0) {
        questionPercent = rnd.next(75, 100);
    } else if (mode == 1) {
        questionPercent = rnd.next(35, 70);
    } else {
        questionPercent = rnd.next(5, 30);
    }

    for (int i = 0; i < len; ++i) {
        bool makeQuestion = rnd.next(1, 100) <= questionPercent;
        s.push_back(makeQuestion ? '?' : randomDigit(i == 0));
    }

    if (s[0] == '0') {
        s[0] = randomDigit(true);
    }
    return s;
}

vector<string> additionPattern(int len) {
    string a(len, '0'), b(len, '0'), c(len, '0');
    int carry = 0;
    for (int i = len - 1; i >= 0; --i) {
        int da = rnd.next(i == 0 ? 1 : 0, 9);
        int maxB = (i == 0 && da + carry >= 10) ? 8 : 9;
        int db = rnd.next(i == 0 ? 1 : 0, maxB);
        int sum = da + db + carry;
        c[i] = char('0' + sum % 10);
        carry = sum / 10;
        a[i] = char('0' + da);
        b[i] = char('0' + db);
    }

    if (c[0] == '0') {
        c[0] = char('1' + rnd.next(0, 8));
    }

    vector<string> rows = {a, b, c};
    int holes = rnd.next(1, max(1, len * 3 / 2));
    for (int i = 0; i < holes; ++i) {
        int row = rnd.next(0, 2);
        int pos = rnd.next(0, len - 1);
        rows[row][pos] = '?';
    }
    return rows;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 12);
    for (int tc = 0; tc < datasets; ++tc) {
        int lenMode = rnd.next(0, 4);
        int len;
        if (lenMode == 0) {
            len = 1;
        } else if (lenMode == 1) {
            len = rnd.next(2, 5);
        } else if (lenMode == 2) {
            len = rnd.next(6, 15);
        } else if (lenMode == 3) {
            len = rnd.next(16, 30);
        } else {
            len = rnd.next(31, 50);
        }

        vector<string> rows;
        if (rnd.next(0, 3) == 0) {
            rows = additionPattern(len);
        } else {
            int mode = rnd.next(0, 2);
            rows = {randomPattern(len, mode), randomPattern(len, mode),
                    randomPattern(len, mode)};

            bool hasQuestion = false;
            for (const string& row : rows) {
                hasQuestion = hasQuestion || row.find('?') != string::npos;
            }
            if (!hasQuestion) {
                rows[rnd.next(0, 2)][rnd.next(0, len - 1)] = '?';
            }
        }

        for (const string& row : rows) {
            println(row);
        }
    }
    println("0");

    return 0;
}
