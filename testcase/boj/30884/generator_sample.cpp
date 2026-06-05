#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string nested(int pairs) {
    return string(pairs, '(') + string(pairs, ')');
}

string flat(int pairs) {
    string s;
    for (int i = 0; i < pairs; ++i) {
        s += "()";
    }
    return s;
}

string randomDyck(int pairs) {
    string s;
    int opens = 0;
    int closes = 0;
    while (closes < pairs) {
        bool canOpen = opens < pairs;
        bool canClose = closes < opens;
        if (!canClose || (canOpen && rnd.next(0, 1) == 0)) {
            s += '(';
            ++opens;
        } else {
            s += ')';
            ++closes;
        }
    }
    return s;
}

string grouped(int pairs) {
    string s;
    int remaining = pairs;
    while (remaining > 0) {
        int take = rnd.next(1, min(remaining, 8));
        if (rnd.next(0, 2) == 0) {
            s += flat(take);
        } else {
            s += nested(take);
        }
        remaining -= take;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int pairs;
    if (mode == 0) {
        pairs = rnd.next(1, 30);
        println(nested(pairs));
    } else if (mode == 1) {
        pairs = rnd.next(1, 30);
        println(flat(pairs));
    } else if (mode == 2) {
        pairs = rnd.next(2, 40);
        println(randomDyck(pairs));
    } else if (mode == 3) {
        pairs = rnd.next(2, 40);
        println(grouped(pairs));
    } else {
        pairs = rnd.next(20, 80);
        string s = randomDyck(pairs);
        if (rnd.next(0, 1) == 0) {
            reverse(s.begin(), s.end());
            for (char& c : s) {
                c = (c == '(' ? ')' : '(');
            }
        }
        println(s);
    }

    return 0;
}
