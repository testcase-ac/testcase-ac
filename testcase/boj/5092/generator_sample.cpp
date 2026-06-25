#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Product {
    string name;
    int points;
    int days;
};

string productName(int scenario, int index, int mode) {
    static const vector<string> prefixes = {
        "A", "Reward", "Gift", "Item", "Zed", "Fast", "Slow", "Edge"
    };
    string name = prefixes[(index + mode) % prefixes.size()] + to_string(scenario)
        + "_" + to_string(index);
    if (name.size() > 20) {
        name.resize(20);
    }
    return name;
}

vector<Product> makeProducts(int scenario, int n, int mode) {
    vector<Product> products;
    products.reserve(n);

    for (int i = 0; i < n; ++i) {
        int points;
        if (mode == 0) {
            points = (i % 2 == 0 ? 0 : rnd.next(1, 30));
        } else if (mode == 1) {
            points = rnd.next(900, 1000);
        } else {
            points = rnd.next(0, 1000);
        }

        int days;
        if (mode == 0) {
            days = rnd.any(vector<int>{0, 1, 99, 100});
        } else if (mode == 1) {
            days = min(100, max(0, 50 + rnd.next(-3, 3)));
        } else {
            days = rnd.next(0, 100);
        }

        products.push_back({productName(scenario, i, mode), points, days});
    }
    return products;
}

vector<string> chooseRequests(const vector<Product>& products, int p) {
    vector<int> order(products.size());
    for (int i = 0; i < int(products.size()); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    vector<string> requests;
    requests.reserve(p);
    for (int i = 0; i < p; ++i) {
        if (i > 0 && rnd.next(5) == 0) {
            requests.push_back(requests[rnd.next(int(requests.size()))]);
        } else {
            requests.push_back(products[order[i % int(order.size())]].name);
        }
    }
    return requests;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenarioCount = rnd.next(1, 4);
    int customerBase = rnd.next(0, 10000);

    for (int scenario = 1; scenario <= scenarioCount; ++scenario) {
        int mode = rnd.next(0, 2);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 5);
        } else if (mode == 1) {
            n = rnd.next(8, 15);
        } else {
            n = rnd.next(1, 50);
        }

        vector<Product> products = makeProducts(scenario, n, mode);
        println(n);
        for (const Product& product : products) {
            println(product.name, product.points, product.days);
        }

        int c = (mode == 2 ? rnd.next(4, 12) : rnd.next(1, 6));
        println(c);
        for (int customer = 0; customer < c; ++customer) {
            int p;
            if (customer == 0) {
                p = 1;
            } else if (customer == c - 1) {
                p = n;
            } else {
                p = rnd.next(1, n);
            }

            int maxDays;
            if (mode == 0) {
                maxDays = rnd.any(vector<int>{1, 2, 98, 99});
            } else if (mode == 1) {
                maxDays = rnd.next(47, 53);
            } else {
                maxDays = rnd.next(1, 99);
            }

            println(customerBase + scenario * 1000 + customer, p, maxDays);
            vector<string> requests = chooseRequests(products, p);
            for (const string& request : requests) {
                println(request);
            }
        }
    }

    println(0);
    return 0;
}
