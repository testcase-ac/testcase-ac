#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string n(5, '0');
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n[0] = char('1' + rnd.next(9));
        for (int i = 1; i < 5; ++i) n[i] = char('0' + rnd.next(10));
    } else if (mode == 1) {
        n[0] = char('1' + rnd.next(9));
        int nonZeroPos = rnd.next(1, 4);
        n[nonZeroPos] = char('1' + rnd.next(9));
        for (int i = 1; i < 5; ++i)
            if (i != nonZeroPos && rnd.next(3) == 0) n[i] = char('1' + rnd.next(9));
    } else if (mode == 2) {
        char d = char('1' + rnd.next(9));
        for (int i = 0; i < 5; ++i) n[i] = d;
        int changes = rnd.next(0, 2);
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, 4);
            n[pos] = char('0' + rnd.next(10));
        }
        if (n[0] == '0') n[0] = char('1' + rnd.next(9));
    } else if (mode == 3) {
        n[0] = char('7' + rnd.next(3));
        for (int i = 1; i < 5; ++i) n[i] = char('7' + rnd.next(3));
    } else if (mode == 4) {
        string digits = "0123456789";
        shuffle(digits.begin(), digits.end());
        for (int i = 0; i < 5; ++i) n[i] = digits[i];
        if (n[0] == '0') swap(n[0], n[rnd.next(1, 4)]);
    } else {
        string bases[] = {"54748", "92727", "93084"};
        n = bases[rnd.next(0, 2)];
        int pos = rnd.next(0, 4);
        n[pos] = char('0' + rnd.next(10));
        if (n[0] == '0') n[0] = char('1' + rnd.next(9));
    }

    println(n);
    return 0;
}
