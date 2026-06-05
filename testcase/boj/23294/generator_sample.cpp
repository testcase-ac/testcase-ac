#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int q = rnd.next(1, 40);
    int c = rnd.next(1, 80);

    vector<int> cap(n + 1);
    if (mode == 0) {
        int base = rnd.next(1, c);
        for (int i = 1; i <= n; ++i) cap[i] = base;
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) cap[i] = rnd.next(max(1, c / 2), c);
    } else {
        for (int i = 1; i <= n; ++i) cap[i] = rnd.next(1, c);
    }

    vector<string> ops;
    ops.reserve(q);

    auto addAccess = [&]() {
        int page;
        if (n == 1 || (mode == 2 && !ops.empty() && rnd.next(0, 3) != 0)) {
            page = rnd.next(1, min(n, 3));
        } else {
            page = rnd.next(1, n);
        }
        ops.push_back("A " + to_string(page));
    };

    if (mode == 3) {
        int ignored = min(q - 1, rnd.next(0, 5));
        for (int i = 0; i < ignored; ++i) ops.push_back(rnd.next(0, 1) == 0 ? "B" : "F");
    }

    addAccess();

    while ((int)ops.size() < q) {
        int pick = rnd.next(0, 99);
        if (mode == 0) {
            if (pick < 55) addAccess();
            else if (pick < 75) ops.push_back("B");
            else if (pick < 92) ops.push_back("F");
            else ops.push_back("C");
        } else if (mode == 1) {
            if (pick < 70) addAccess();
            else if (pick < 85) ops.push_back("B");
            else if (pick < 95) ops.push_back("F");
            else ops.push_back("C");
        } else if (mode == 2) {
            if (pick < 60) addAccess();
            else if (pick < 70) ops.push_back("B");
            else if (pick < 80) ops.push_back("F");
            else ops.push_back("C");
        } else {
            if (pick < 45) addAccess();
            else if (pick < 70) ops.push_back("B");
            else if (pick < 90) ops.push_back("F");
            else ops.push_back("C");
        }
    }

    println(n, q, c);
    println(vector<int>(cap.begin() + 1, cap.end()));
    for (const string& op : ops) println(op);

    return 0;
}
