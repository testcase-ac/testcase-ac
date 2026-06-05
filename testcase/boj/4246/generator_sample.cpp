#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

string patternedString(int length, int mode) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        if (mode == 0) {
            result += static_cast<char>('a' + (i % 26));
        } else if (mode == 1) {
            result += static_cast<char>('a' + ((i / 2) % 26));
        } else if (mode == 2) {
            result += (i % 2 == 0 ? 'a' : 'z');
        } else {
            result += static_cast<char>('a' + rnd.next(0, 25));
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(4, 10);
    vector<int> columns;
    columns.push_back(2);
    columns.push_back(3);
    columns.push_back(20);
    while (static_cast<int>(columns.size()) < caseCount) {
        columns.push_back(rnd.next(2, 20));
    }
    shuffle(columns.begin(), columns.end());

    for (int tc = 0; tc < caseCount; ++tc) {
        int c = columns[tc];
        int maxRows = 200 / c;
        int rows;
        if (tc == 0) {
            rows = 1;
        } else if (tc == 1) {
            rows = maxRows;
        } else {
            rows = rnd.next(1, maxRows);
        }

        int length = c * rows;
        string encrypted;
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            encrypted = string(length, rnd.next(0, 1) == 0 ? 'a' : 'z');
        } else if (mode <= 3) {
            encrypted = patternedString(length, mode - 1);
        } else {
            string alphabet = rnd.next(0, 1) == 0 ? "abc" : "abcdefghijklmnopqrstuvwxyz";
            encrypted = randomString(length, alphabet);
        }

        println(c);
        println(encrypted);
    }
    println(0);

    return 0;
}
