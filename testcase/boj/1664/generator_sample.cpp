#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int controlDigit(const string& first18) {
    int sum = 0;
    for (int i = 0; i < 18; ++i) {
        int weight = 10 - (i % 9);
        sum = (sum + weight * (first18[i] - '0')) % 19;
    }
    return sum <= 9 ? sum : 19 - sum;
}

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int year, int month) {
    static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month] + (month == 2 && isLeap(year));
}

string twoDigits(int value) {
    string result = "00";
    result[0] = char('0' + value / 10);
    result[1] = char('0' + value % 10);
    return result;
}

string fourDigits(int value) {
    string result = "0000";
    for (int i = 3; i >= 0; --i) {
        result[i] = char('0' + value % 10);
        value /= 10;
    }
    return result;
}

string randomDigits(int count) {
    string result;
    for (int i = 0; i < count; ++i) {
        result += char('0' + rnd.next(0, 9));
    }
    return result;
}

string randomValidId() {
    int year = rnd.next(1, 9999);
    int month = rnd.next(1, 12);
    int day = rnd.next(1, daysInMonth(year, month));

    string id = twoDigits(day) + twoDigits(month) + fourDigits(year) + randomDigits(10);
    id += char('0' + controlDigit(id));
    return id;
}

void eraseWithProbability(string& pattern, double probability) {
    bool erased = false;
    for (char& ch : pattern) {
        if (rnd.next() < probability) {
            ch = 'X';
            erased = true;
        }
    }
    if (!erased) {
        pattern[rnd.next(0, int(pattern.size()) - 1)] = 'X';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string pattern = randomValidId();
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        eraseWithProbability(pattern, rnd.next(0.10, 0.30));
    } else if (mode == 1) {
        eraseWithProbability(pattern, rnd.next(0.55, 0.90));
    } else if (mode == 2) {
        for (int i = 0; i < 8; ++i) {
            if (rnd.next(0, 99) < 65) {
                pattern[i] = 'X';
            }
        }
        for (int i = 8; i < 19; ++i) {
            if (rnd.next(0, 99) < 25) {
                pattern[i] = 'X';
            }
        }
    } else if (mode == 3) {
        for (int i = 8; i < 18; ++i) {
            if (rnd.next(0, 99) < 75) {
                pattern[i] = 'X';
            }
        }
        if (rnd.next(0, 1)) {
            pattern[18] = 'X';
        }
    } else if (mode == 4) {
        pattern = randomDigits(19);
        eraseWithProbability(pattern, rnd.next(0.20, 0.50));
    } else {
        vector<int> interesting = {0, 1, 2, 3, 4, 5, 6, 7, 18};
        shuffle(interesting.begin(), interesting.end());
        int erased = rnd.next(3, int(interesting.size()));
        for (int i = 0; i < erased; ++i) {
            pattern[interesting[i]] = 'X';
        }
    }

    println(pattern);
    return 0;
}
