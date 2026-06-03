#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDigits(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('0' + rnd.next(0, 9));
    }
    return s;
}

string makePalindrome(int len) {
    string s = randomDigits(len);
    for (int i = 0; i < len / 2; ++i) {
        s[len - 1 - i] = s[i];
    }
    return s;
}

string withLeadingZeros(int len) {
    string s = randomDigits(len);
    int zeroCount = rnd.next(1, len - 1);
    for (int i = 0; i < zeroCount; ++i) {
        s[i] = '0';
    }
    return s;
}

string carryHeavy(int len) {
    string s = randomDigits(len);
    int firstHalf = (len + 1) / 2;
    for (int i = firstHalf; i < len; ++i) {
        s[i] = char('7' + rnd.next(0, 2));
    }
    if (rnd.next(0, 1) == 0) {
        s[len - 1] = char('0' + rnd.next(0, 3));
    }
    return s;
}

string nearPalindrome(int len) {
    string s = makePalindrome(len);
    int pos = rnd.next((len + 1) / 2, len - 1);
    int digit = s[pos] - '0';
    int delta = rnd.next(1, 9);
    s[pos] = char('0' + (digit + delta) % 10);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCaseCount = rnd.next(8, 24);
    vector<string> readings;
    readings.reserve(testCaseCount);

    for (int tc = 0; tc < testCaseCount; ++tc) {
        int len = rnd.next(2, 9);
        int mode = rnd.next(0, 6);

        if (mode == 0) {
            readings.push_back(randomDigits(len));
        } else if (mode == 1) {
            readings.push_back(makePalindrome(len));
        } else if (mode == 2) {
            readings.push_back(withLeadingZeros(len));
        } else if (mode == 3) {
            readings.push_back(carryHeavy(len));
        } else if (mode == 4) {
            readings.push_back(nearPalindrome(len));
        } else if (mode == 5) {
            readings.push_back(string(len, '9'));
        } else {
            string s(len, '0');
            s[len - 1] = char('1' + rnd.next(0, 8));
            readings.push_back(s);
        }
    }

    shuffle(readings.begin(), readings.end());
    for (const string& reading : readings) {
        println(reading);
    }
    println("0");

    return 0;
}
