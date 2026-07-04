#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string chars = "()[]";
    string s;
    int mode = rnd.next(0, 8);

    if (mode == 0) {
        s = "";
    } else if (mode == 1) {
        s += rnd.any(chars);
    } else if (mode == 2) {
        int n = rnd.next(2, 20);
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += rnd.any(chars);
    } else if (mode == 3) {
        int pairs = rnd.next(1, 15);
        vector<char> opens;
        for (int i = 0; i < pairs; ++i) {
            char open = rnd.next(0, 1) == 0 ? '(' : '[';
            s += open;
            opens.push_back(open);
        }
        while (!opens.empty()) {
            char open = opens.back();
            opens.pop_back();
            s += open == '(' ? ')' : ']';
        }
    } else if (mode == 4) {
        int parts = rnd.next(1, 12);
        for (int i = 0; i < parts; ++i) {
            if (rnd.next(0, 1) == 0) {
                s += "()";
            } else {
                s += "[]";
            }
        }
    } else if (mode == 5) {
        int n = rnd.next(2, 30);
        s.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                s += rnd.next(0, 1) == 0 ? '(' : '[';
            } else {
                s += rnd.next(0, 1) == 0 ? ')' : ']';
            }
        }
    } else if (mode == 6) {
        int n = rnd.next(2, 40);
        s.reserve(n);
        char c = rnd.any(chars);
        for (int i = 0; i < n; ++i) s += c;
    } else if (mode == 7) {
        int n = rnd.next(40, 100);
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += rnd.any(chars);
    } else {
        int blocks = rnd.next(2, 12);
        for (int i = 0; i < blocks; ++i) {
            int blockLen = rnd.next(1, 6);
            char c = rnd.any(chars);
            for (int j = 0; j < blockLen && (int)s.size() < 100; ++j) s += c;
        }
    }

    println(s);
    return 0;
}
