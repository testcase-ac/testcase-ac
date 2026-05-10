#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A, B, C (positive integers, <= 50000)
    int A = inf.readInt(1, 50000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 50000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 50000, "C");
    inf.readEoln();

    // Total number of menu items can be large; ensure no overflow later if summing indices only.
    // Names: lowercase alphabetic, length 1..20, all distinct across all types.
    // Prices: positive int <= 1'000'000.

    // To check distinctness of names and to classify menu types
    unordered_map<string, int> type; // 0 = normal, 1 = special, 2 = service
    type.reserve((size_t)A + B + C * 2);
    type.max_load_factor(0.7f);

    auto readName = [&](const char* what)->string {
        string s = inf.readToken("[a-z]{1,20}", what);
        return s;
    };

    // Read normal menus
    for (int i = 0; i < A; ++i) {
        string name = readName("normal_name");
        inf.readSpace();
        int price = inf.readInt(1, 1000000, "normal_price");
        inf.readEoln();

        ensuref(!type.count(name), "Duplicate menu name '%s' in normal menus", name.c_str());
        type[name] = 0;
        (void)price; // price itself need not be checked further for global properties
    }

    // Read special menus
    for (int i = 0; i < B; ++i) {
        string name = readName("special_name");
        inf.readSpace();
        int price = inf.readInt(1, 1000000, "special_price");
        inf.readEoln();

        ensuref(!type.count(name), "Duplicate menu name '%s' in special menus", name.c_str());
        type[name] = 1;
        (void)price;
    }

    // Read service menus
    for (int i = 0; i < C; ++i) {
        string name = readName("service_name");
        inf.readEoln();

        ensuref(!type.count(name), "Duplicate menu name '%s' in service menus", name.c_str());
        type[name] = 2;
    }

    // Next line: N (number of ordered items), positive int <= 150000
    int N = inf.readInt(1, 150000, "N");
    inf.readEoln();

    // Next N lines: ordered item names.
    // They must correspond to existing menu names (problem guarantees in statement,
    // so from validator perspective we must enforce this).
    for (int i = 0; i < N; ++i) {
        string name = inf.readToken("[a-z]{1,20}", "order_name");
        inf.readEoln();

        ensuref(type.count(name),
                "Ordered item name '%s' not found in any menu", name.c_str());
    }

    inf.readEof();
}
