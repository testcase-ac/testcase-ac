#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int cat = rnd.next(0, 99);
    string s;
    if (cat < 15) {
        // mostly '1' and '2'
        int n = rnd.next(1, 10);
        string d = "12";
        for (int i = 0; i < n; i++) s += rnd.any(d);
    } else if (cat < 30) {
        // digits 3-9
        int n = rnd.next(1, 15);
        string d = "3456789";
        for (int i = 0; i < n; i++) s += rnd.any(d);
    } else if (cat < 50) {
        // mix with some zeros
        int n = rnd.next(5, 25);
        for (int i = 0; i < n; i++) {
            if (rnd.next(0, 4) == 0) s += '0';
            else s += char('0' + rnd.next(1, 9));
        }
    } else if (cat < 60) {
        // small edge patterns
        vector<string> edge = {"0", "00", "000", "10", "20", "30"};
        s = rnd.any(edge);
    } else if (cat < 70) {
        // alternating pattern of '1' with '0' or '2'
        int n = rnd.next(2, 20);
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) s += '1';
            else s += (rnd.next(0, 1) ? '0' : '2');
        }
    } else if (cat < 85) {
        // long run of '1's
        int n = rnd.next(10, 20);
        s = string(n, '1');
    } else {
        // fully random digits 0-9
        int n = rnd.next(1, 30);
        for (int i = 0; i < n; i++) s += char('0' + rnd.next(0, 9));
    }
    println(s);
    return 0;
}
