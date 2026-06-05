#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string shuffledCake(int n) {
    string cake(n / 2, 's');
    cake += string(n / 2, 'k');
    shuffle(cake.begin(), cake.end());
    return cake;
}

string alternatingCake(int n) {
    string cake;
    cake.reserve(n);
    char first = rnd.next(0, 1) == 0 ? 's' : 'k';
    for (int i = 0; i < n; ++i) {
        cake += (i % 2 == 0) ? first : (first == 's' ? 'k' : 's');
    }
    return cake;
}

string runCake(int n) {
    vector<int> cuts;
    int parts = rnd.next(2, min(8, n));
    for (int i = 1; i < parts; ++i) {
        cuts.push_back(rnd.next(1, n - 1));
    }
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());

    string cake;
    char fruit = rnd.next(0, 1) == 0 ? 's' : 'k';
    for (int i = 1; i < static_cast<int>(cuts.size()); ++i) {
        cake += string(cuts[i] - cuts[i - 1], fruit);
        fruit = fruit == 's' ? 'k' : 's';
    }

    int strawberries = count(cake.begin(), cake.end(), 's');
    vector<int> over, under;
    for (int i = 0; i < n; ++i) {
        if (cake[i] == 's') {
            over.push_back(i);
        } else {
            under.push_back(i);
        }
    }
    shuffle(over.begin(), over.end());
    shuffle(under.begin(), under.end());
    while (strawberries > n / 2) {
        cake[over.back()] = 'k';
        over.pop_back();
        --strawberries;
    }
    while (strawberries < n / 2) {
        cake[under.back()] = 's';
        under.pop_back();
        ++strawberries;
    }
    return cake;
}

string balancedHalfCake(int n) {
    string left(n / 4, 's');
    left += string(n / 4, 'k');
    string right = left;
    shuffle(left.begin(), left.end());
    shuffle(right.begin(), right.end());
    return left + right;
}

string skewedHalfCake(int n) {
    int leftStrawberries = rnd.next(0, n / 2);
    if (leftStrawberries == n / 4) {
        leftStrawberries += leftStrawberries == 0 ? 1 : -1;
    }
    string left(leftStrawberries, 's');
    left += string(n / 2 - leftStrawberries, 'k');
    string right(n / 2 - leftStrawberries, 's');
    right += string(leftStrawberries, 'k');
    shuffle(left.begin(), left.end());
    shuffle(right.begin(), right.end());
    return left + right;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizes;
    for (int n = 4; n <= 28; n += 4) {
        sizes.push_back(n);
    }
    if (rnd.next(0, 9) == 0) {
        sizes.push_back(rnd.next(8, 50) * 4);
    }
    int n = rnd.any(sizes);

    string cake;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        cake = shuffledCake(n);
    } else if (mode == 1) {
        cake = alternatingCake(n);
    } else if (mode == 2) {
        cake = runCake(n);
    } else if (mode == 3) {
        cake = balancedHalfCake(n);
    } else {
        cake = skewedHalfCake(n);
    }

    println(n);
    println(cake);
    return 0;
}
