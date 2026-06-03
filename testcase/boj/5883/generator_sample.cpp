#include "testlib.h"
#include <vector>
using namespace std;

int smallId(int offset = 0) {
    return offset + rnd.next(0, 20);
}

void appendRun(vector<int>& a, int value, int len) {
    for (int i = 0; i < len; ++i) a.push_back(value);
}

bool hasTwoDistinct(const vector<int>& a) {
    for (int value : a) {
        if (value != a[0]) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) a.push_back(smallId());
    } else if (mode == 1) {
        int x = smallId();
        int y = x + rnd.next(1, 7);
        int repeats = rnd.next(2, 8);
        for (int i = 0; i < repeats; ++i) {
            a.push_back(x);
            a.push_back(y);
        }
        if (rnd.next(0, 1)) a.push_back(x);
    } else if (mode == 2) {
        int target = smallId();
        int removed = target + rnd.next(1, 10);
        int blocks = rnd.next(2, 6);
        for (int i = 0; i < blocks; ++i) {
            appendRun(a, target, rnd.next(1, 4));
            if (i + 1 < blocks) appendRun(a, removed, rnd.next(1, 2));
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 35);
        int alphabet = rnd.next(2, 6);
        int last = -1;
        while ((int)a.size() < n) {
            int value = smallId(rnd.next(0, alphabet - 1) * 30);
            if (alphabet > 1) {
                while (value == last) value = smallId(rnd.next(0, alphabet - 1) * 30);
            }
            appendRun(a, value, min(rnd.next(1, 5), n - (int)a.size()));
            last = value;
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 80);
        int alphabet = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, alphabet - 1));
    } else {
        int n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 1000000));
    }

    if (!hasTwoDistinct(a)) {
        a.push_back(a[0] == 1000000 ? 0 : a[0] + 1);
    }

    println((int)a.size());
    for (int value : a) println(value);

    return 0;
}
