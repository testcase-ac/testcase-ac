#include "testlib.h"
#include <string>
using namespace std;

string randomNumber(int len, int mode) {
    if (len == 1 && mode == 0) return "0";

    string s;
    s.reserve(len);
    s.push_back(char('1' + rnd.next(9)));

    for (int i = 1; i < len; ++i) {
        if (mode == 1) {
            s.push_back(char('0' + rnd.next(2)));
        } else if (mode == 2) {
            s.push_back(char('8' + rnd.next(2)));
        } else if (mode == 3) {
            s.push_back(char('0' + (i % 10)));
        } else {
            s.push_back(char('0' + rnd.next(10)));
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int lenA = rnd.next(1, 30);
    int lenB = rnd.next(1, 30);

    if (mode == 0) {
        if (rnd.next(2) == 0) lenA = 1;
        else lenB = 1;
    } else if (mode == 2) {
        lenA = rnd.next(20, 60);
        lenB = rnd.next(20, 60);
    } else if (mode == 4) {
        lenA = rnd.next(1, 5);
        lenB = rnd.next(20, 80);
        if (rnd.next(2)) swap(lenA, lenB);
    }

    string A = randomNumber(lenA, mode);
    string B = randomNumber(lenB, (mode + rnd.next(5)) % 5);

    println(A, B);
    return 0;
}
