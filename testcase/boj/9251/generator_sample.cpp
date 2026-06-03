#include "testlib.h"
#include <algorithm>
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

string mutateWithNoise(const string& base, const string& alphabet, int maxGap) {
    string result;
    for (char ch : base) {
        int before = rnd.next(0, maxGap);
        for (int i = 0; i < before; ++i) {
            result += rnd.any(alphabet);
        }
        result += ch;
    }
    int tail = rnd.next(0, maxGap);
    for (int i = 0; i < tail; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string first;
    string second;

    if (mode == 0) {
        int length = rnd.next(1, 30);
        string alphabet = "ABC";
        first = randomString(length, alphabet);
        second = first;
    } else if (mode == 1) {
        first = randomString(rnd.next(1, 30), "ABC");
        second = randomString(rnd.next(1, 30), "XYZ");
    } else if (mode == 2) {
        int commonLength = rnd.next(1, 12);
        string common = randomString(commonLength, "ABCDE");
        first = mutateWithNoise(common, "ABCXYZ", rnd.next(0, 2));
        second = mutateWithNoise(common, "ABCXYZ", rnd.next(0, 2));
    } else if (mode == 3) {
        int blocks = rnd.next(1, 10);
        string alphabet = "ABCD";
        for (int i = 0; i < blocks; ++i) {
            int run = rnd.next(1, 4);
            char a = rnd.any(alphabet);
            char b = rnd.any(alphabet);
            first += string(run, a);
            second += string(rnd.next(1, 4), b);
        }
    } else if (mode == 4) {
        int length = rnd.next(1, 26);
        string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        shuffle(letters.begin(), letters.end());
        first = letters.substr(0, length);
        second = first;
        shuffle(second.begin(), second.end());
    } else {
        int firstLength = rnd.next(1, 30);
        int secondLength = rnd.next(1, 30);
        string alphabet = "ABCDE";
        first = randomString(firstLength, alphabet);
        second = randomString(secondLength, alphabet);
    }

    println(first);
    println(second);

    return 0;
}
