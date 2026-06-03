#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int phone = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) a.push_back(phone);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        int first = rnd.next(1, 9);
        int second = rnd.next(1, 8);
        if (second >= first) ++second;
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? first : second);
    } else if (mode == 2) {
        n = rnd.next(15, 80);
        while ((int)a.size() < n) {
            int phone = rnd.next(1, 9);
            int len = rnd.next(1, 8);
            while (len-- > 0 && (int)a.size() < n) a.push_back(phone);
        }
    } else if (mode == 3) {
        n = rnd.next(40, 160);
        int last = rnd.next(1, 9);
        a.push_back(last);
        while ((int)a.size() < n) {
            if (rnd.next(0, 99) < 35) {
                a.push_back(last);
            } else {
                int next = rnd.next(1, 8);
                if (next >= last) ++next;
                last = next;
                a.push_back(last);
            }
        }
    } else if (mode == 4) {
        int cycles = rnd.next(3, 12);
        for (int c = 0; c < cycles; ++c) {
            int phone = rnd.next(1, 9);
            int len = rnd.next(5, 7);
            for (int i = 0; i < len; ++i) a.push_back(phone);
            int other = rnd.next(1, 8);
            if (other >= phone) ++other;
            a.push_back(other);
        }
        n = (int)a.size();
    } else {
        n = 1000;
        int alphabet = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 99) < 45) {
                a.push_back(a.back());
            } else {
                a.push_back(rnd.next(1, alphabet));
            }
        }
    }

    println((int)a.size());
    println(a);
    return 0;
}
