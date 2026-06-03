#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string makePassword() {
    int mode = rnd.next(0, 4);
    int len = rnd.next(1, 14);
    string alphabet = "MNOPQR";
    string password;

    if (mode == 0) {
        char ch = rnd.any(alphabet);
        password.assign(len, ch);
    } else if (mode == 1) {
        char a = rnd.any(alphabet);
        char b = rnd.any(alphabet);
        while (b == a) {
            b = rnd.any(alphabet);
        }
        for (int i = 0; i < len; ++i) {
            password += (i % 2 == 0 ? a : b);
        }
    } else if (mode == 2) {
        string half;
        int halfLen = (len + 1) / 2;
        for (int i = 0; i < halfLen; ++i) {
            half += rnd.any(alphabet);
        }
        password = half;
        for (int i = len / 2 - 1; i >= 0; --i) {
            password += half[i];
        }
    } else {
        for (int i = 0; i < len; ++i) {
            password += rnd.any(alphabet);
        }
    }

    return password;
}

static string addFillers(const string& password, const string& fillers, int budget) {
    string result;
    for (char ch : password) {
        int count = rnd.next(0, budget);
        for (int i = 0; i < count; ++i) {
            result += rnd.any(fillers);
        }
        result += ch;
    }
    int count = rnd.next(0, budget);
    for (int i = 0; i < count; ++i) {
        result += rnd.any(fillers);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string password = makePassword();
    int firstBudget = rnd.next(0, 3);
    int secondBudget = rnd.next(0, 3);

    string first = addFillers(password, "ABCDEFGHJKL", firstBudget);
    string second = addFillers(password, "STUVWXYZ", secondBudget);

    println(first);
    println(second);

    return 0;
}
