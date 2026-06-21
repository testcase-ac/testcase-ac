#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string makeName(int index, int style) {
    static const string lower = "abcdefghijklmnopqrstuvwxyz";
    static const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const string digits = "0123456789";
    static const string all = lower + upper + digits;

    if (style == 0) {
        return string(1, lower[index]);
    }
    if (style == 1) {
        return "S" + to_string(index);
    }
    if (style == 2) {
        string s = "Station";
        string num = to_string(index);
        while (s.size() + num.size() < 10) {
            s += "0";
        }
        return s + num;
    }

    int len = rnd.next(1, 10);
    string s;
    for (int i = 0; i < len; ++i) {
        s += all[rnd.next((int)all.size())];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else if (mode == 2) {
        n = rnd.next(15, 20);
    } else {
        n = rnd.next(1, 20);
    }

    int m;
    if (mode == 0) {
        m = 1;
    } else if (mode == 3) {
        m = n;
    } else if (mode == 4) {
        m = 1;
    } else {
        m = rnd.next(1, n);
    }

    int style = rnd.next(4);
    vector<string> names;
    set<string> used;
    for (int i = 0; i < n; ++i) {
        string name;
        do {
            name = makeName(i, style);
            if (style != 3) {
                break;
            }
        } while (used.count(name));
        used.insert(name);
        names.push_back(name);
    }

    if (rnd.next(2) == 1) {
        shuffle(names.begin(), names.end());
    }

    println(n, m);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
