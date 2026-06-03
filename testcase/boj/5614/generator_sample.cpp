#include "testlib.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

string makeName(int len, int index) {
    string s(len, 'A');
    for (int pos = len - 1; pos >= 0; --pos) {
        s[pos] = char('A' + index % 26);
        index /= 26;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int productCount = rnd.next(1, 12);
    vector<string> products;

    if (mode == 0) {
        int len = rnd.next(1, 5);
        int offset = rnd.next(0, 200);
        for (int i = 0; i < productCount; ++i) {
            products.push_back(makeName(len, offset + i));
        }
    } else if (mode == 1) {
        for (int len = 1; len <= 5 && (int)products.size() < productCount; ++len) {
            int countForLength = rnd.next(1, 3);
            int offset = rnd.next(0, 200);
            for (int i = 0; i < countForLength && (int)products.size() < productCount; ++i) {
                products.push_back(makeName(len, offset + i));
            }
        }
    } else {
        map<string, bool> used;
        while ((int)products.size() < productCount) {
            int len = rnd.next(1, 5);
            string name;
            for (int i = 0; i < len; ++i) {
                name += char('A' + rnd.next(0, 25));
            }
            if (!used[name]) {
                used[name] = true;
                products.push_back(name);
            }
        }
    }

    shuffle(products.begin(), products.end());

    vector<pair<string, int>> orders;
    map<string, int> totals;
    int n = rnd.next(productCount, 30);
    for (int i = 0; i < n; ++i) {
        vector<string> available;
        for (const string& product : products) {
            if (totals[product] < 100000000) {
                available.push_back(product);
            }
        }
        if (available.empty()) {
            break;
        }

        string product = rnd.any(available);
        int remaining = 100000000 - totals[product];
        int quantity;
        if (mode == 3 && rnd.next(0, 3) == 0) {
            quantity = remaining;
        } else if (mode == 4) {
            int upper = min(remaining, 100000000);
            quantity = rnd.next(max(1, upper - 1000), upper);
        } else {
            quantity = rnd.next(1, min(remaining, 1000));
        }
        totals[product] += quantity;
        orders.push_back({product, quantity});
    }

    shuffle(orders.begin(), orders.end());

    println((int)orders.size());
    for (const auto& order : orders) {
        println(order.first, order.second);
    }

    return 0;
}
