#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int q = rnd.next(1, 30);
    int alphabet = rnd.next(1, 6);
    string queries;
    int length = 0;

    auto add_char = [&](char c) {
        queries.push_back(c);
        ++length;
    };

    auto remove_char = [&]() {
        queries.push_back('-');
        --length;
    };

    if (mode == 0) {
        char c = static_cast<char>('a' + rnd.next(alphabet));
        for (int i = 0; i < q; ++i) {
            if (length > 1 && rnd.next(0, 4) == 0) {
                remove_char();
            } else {
                add_char(c);
            }
        }
    } else if (mode == 1) {
        int period = rnd.next(2, min(6, alphabet + 1));
        for (int i = 0; i < q; ++i) {
            if (length > 1 && rnd.next(0, 5) == 0) {
                remove_char();
            } else {
                add_char(static_cast<char>('a' + (length % period)));
            }
        }
    } else if (mode == 2) {
        string base;
        int base_len = rnd.next(1, min(q, 15));
        for (int i = 0; i < base_len; ++i) {
            char c = static_cast<char>('a' + rnd.next(alphabet));
            base.push_back(c);
            add_char(c);
        }
        reverse(base.begin(), base.end());
        for (char c : base) {
            if (static_cast<int>(queries.size()) == q) break;
            add_char(c);
        }
        while (static_cast<int>(queries.size()) < q) {
            if (length > 1 && rnd.next(0, 1) == 0) {
                remove_char();
            } else {
                add_char(static_cast<char>('a' + rnd.next(alphabet)));
            }
        }
    } else if (mode == 3) {
        while (static_cast<int>(queries.size()) < q) {
            if (length > 1 && rnd.next(0, 2) == 0) {
                remove_char();
            } else {
                add_char(static_cast<char>('a' + rnd.next(alphabet)));
            }
        }
    } else {
        int grow = rnd.next(1, q);
        for (int i = 0; i < grow; ++i) {
            char c = static_cast<char>('a' + rnd.next(0, 2));
            add_char(c);
        }
        while (static_cast<int>(queries.size()) < q) {
            if (length > 1) {
                remove_char();
            } else {
                add_char(static_cast<char>('a' + rnd.next(0, 2)));
            }
        }
    }

    println(q);
    println(queries);
    return 0;
}
