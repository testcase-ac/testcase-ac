#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

long long digitsToNumber(const string& digits) {
    long long value = 0;
    for (char digit : digits) value = value * 10 + (digit - '0');
    return value;
}

long long randomByDigits(int length, const string& firstDigits, const string& otherDigits) {
    string digits;
    digits += rnd.any(firstDigits);
    for (int i = 1; i < length; ++i) digits += rnd.any(otherDigits);
    return digitsToNumber(digits);
}

long long randomRepeatedDigit() {
    int digit = rnd.next(1, 9);
    int length = rnd.next(1, 9);
    string digits(length, char('0' + digit));
    return digitsToNumber(digits);
}

long long randomWithZero() {
    int length = rnd.next(2, 9);
    string digits;
    digits += char('1' + rnd.next(9));
    for (int i = 1; i < length; ++i) {
        if (rnd.next(100) < 45) {
            digits += '0';
        } else {
            digits += char('1' + rnd.next(9));
        }
    }
    return digitsToNumber(digits);
}

long long randomCase() {
    int mode = rnd.next(8);
    if (mode == 0) return rnd.any(vector<long long>{1, 9, 10, 11, 99, 100, 101, 2022, 2023, 1000000000LL});
    if (mode == 1) return randomByDigits(rnd.next(1, 9), "1", "01");
    if (mode == 2) return randomByDigits(rnd.next(2, 9), "123456789", "01");
    if (mode == 3) return randomWithZero();
    if (mode == 4) return randomRepeatedDigit();
    if (mode == 5) return rnd.next(1, 9999);
    if (mode == 6) return rnd.next(100000000, 1000000000);
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    vector<long long> cases;
    cases.reserve(t);

    vector<long long> anchors = {1, 9, 10, 11, 100, 101, 2022, 2023, 1000000000LL};
    shuffle(anchors.begin(), anchors.end());
    while ((int)cases.size() < t && !anchors.empty()) {
        cases.push_back(anchors.back());
        anchors.pop_back();
    }
    while ((int)cases.size() < t) cases.push_back(randomCase());

    shuffle(cases.begin(), cases.end());

    println(t);
    for (long long n : cases) println(n);
    return 0;
}
