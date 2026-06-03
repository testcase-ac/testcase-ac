#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomNoiseChar() {
    string letters = "abcdefghijklmnopqrstuvwxyz";
    if (rnd.next(100) < 65) letters = "abdefghijklm nqrtvwxyz";
    letters.erase(remove(letters.begin(), letters.end(), ' '), letters.end());
    return rnd.any(letters);
}

void addRepeated(string& s, char c, int count) {
    for (int i = 0; i < count; ++i) s += c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) s += randomNoiseChar();
    } else if (mode == 1) {
        int copies = rnd.next(1, 12);
        for (int i = 0; i < copies; ++i) s += "uospc";
        int extra = rnd.next(0, 25);
        for (int i = 0; i < extra; ++i) s += randomNoiseChar();
    } else if (mode == 2) {
        int base = rnd.next(1, 15);
        vector<char> need = {'u', 'o', 's', 'p', 'c'};
        char scarce = rnd.any(need);
        for (char c : need) addRepeated(s, c, c == scarce ? base - 1 : base + rnd.next(0, 6));
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) s += randomNoiseChar();
    } else if (mode == 3) {
        int target = rnd.next(0, 8);
        vector<char> need = {'u', 'o', 's', 'p', 'c'};
        for (char c : need) addRepeated(s, c, target + rnd.next(0, 8));
        int other = rnd.next(0, 35);
        for (int i = 0; i < other; ++i) s += randomNoiseChar();
    } else if (mode == 4) {
        int n = rnd.next(80, 180);
        string alphabet = rnd.next(2) ? "uospc" : "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else {
        int n = rnd.next(700, 1000);
        string alphabet = "uospc";
        int bias = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 50) {
                s += alphabet[bias];
            } else if (rnd.next(100) < 80) {
                s += rnd.any(alphabet);
            } else {
                s += randomNoiseChar();
            }
        }
    }

    shuffle(s.begin(), s.end());

    println((int)s.size());
    println(s);

    return 0;
}
