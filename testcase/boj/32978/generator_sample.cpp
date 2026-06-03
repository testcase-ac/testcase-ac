#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeName(int index, int style) {
    string name;

    if (style == 0) {
        name.push_back(char('A' + index % 26));
        int x = index / 26;
        while (x > 0) {
            name.push_back(char('a' + x % 26));
            x /= 26;
        }
    } else if (style == 1) {
        name = "ingredient";
        int x = index;
        do {
            name.push_back(char('a' + x % 26));
            x /= 26;
        } while (x > 0);
    } else {
        static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
        int len = rnd.next(1, 20);
        for (int i = 0; i < len; ++i) {
            char c = rnd.any(alphabet);
            if (rnd.next(2) == 0) {
                c = char(c - 'a' + 'A');
            }
            name.push_back(c);
        }
    }

    return name.substr(0, 20);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 80);
    } else {
        n = rnd.next(2, 100);
    }

    vector<string> ingredients;
    int style = rnd.next(3);
    for (int i = 0; (int)ingredients.size() < n; ++i) {
        string candidate = makeName(i, style);
        bool exists = false;
        for (const string& ingredient : ingredients) {
            if (ingredient == candidate) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            ingredients.push_back(candidate);
        }
    }

    if (rnd.next(2) == 0) {
        shuffle(ingredients.begin(), ingredients.end());
    }

    int missing = rnd.next(n);
    vector<string> used;
    for (int i = 0; i < n; ++i) {
        if (i != missing) {
            used.push_back(ingredients[i]);
        }
    }
    shuffle(used.begin(), used.end());

    println(n);
    println(ingredients);
    println(used);

    return 0;
}
