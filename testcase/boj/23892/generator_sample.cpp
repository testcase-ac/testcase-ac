#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomPattern(int len, double openBias) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.next() < openBias ? '(' : ')');
    }
    return s;
}

string balancedPattern(int pairs) {
    string s;
    s.reserve(2 * pairs);
    int balance = 0;
    for (int i = 0; i < 2 * pairs; ++i) {
        int remaining = 2 * pairs - i;
        if (balance == 0) {
            s.push_back('(');
            ++balance;
        } else if (balance == remaining) {
            s.push_back(')');
            --balance;
        } else if (rnd.next(0, 1) == 0) {
            s.push_back('(');
            ++balance;
        } else {
            s.push_back(')');
            --balance;
        }
    }
    return s;
}

string boundaryPattern(int len) {
    string middle = randomPattern(max(0, len - 2), rnd.next(0.25, 0.75));
    return "(" + middle + ")";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n = rnd.next(1LL, 60LL);
    long long k = rnd.next(1LL, 60LL);
    int pInitial = rnd.next(1, 12);
    int pDrink = rnd.next(1, 12);
    string initial;
    string drink;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        n = rnd.next(1LL, 8LL);
        k = 1;
        initial = rnd.any(vector<string>{"(", ")", "()", ")(", "())("});
        drink = rnd.any(vector<string>{"(", ")", "()", ")(", "()()"});
    } else if (mode == 1) {
        initial = balancedPattern(rnd.next(1, 8));
        drink = balancedPattern(rnd.next(1, 8));
    } else if (mode == 2) {
        initial = boundaryPattern(rnd.next(2, 12));
        drink = boundaryPattern(rnd.next(2, 12));
        pInitial = rnd.next(2, 30);
        pDrink = rnd.next(2, 30);
    } else if (mode == 3) {
        initial = randomPattern(rnd.next(1, 20), rnd.next(0.15, 0.4));
        drink = randomPattern(rnd.next(1, 20), rnd.next(0.6, 0.9));
    } else if (mode == 4) {
        initial = randomPattern(rnd.next(1, 20), rnd.next(0.6, 0.9));
        drink = randomPattern(rnd.next(1, 20), rnd.next(0.15, 0.4));
    } else if (mode == 5) {
        n = rnd.next(1000000000000LL, 100000000000000LL);
        k = rnd.next(1000000000000LL, 100000000000000LL);
        pInitial = rnd.next(900000000, 1000000000);
        pDrink = rnd.next(900000000, 1000000000);
        initial = rnd.any(vector<string>{")(", "()", "(()())", "())(()"});
        drink = rnd.any(vector<string>{")(", "()", "((()))", ")(()"});
    } else if (mode == 6) {
        k = rnd.next(2LL, 30LL);
        initial = randomPattern(rnd.next(10, 30), 0.5);
        drink = rnd.any(vector<string>{"(", ")", "))((", "((("});
    } else {
        int lenInitial = rnd.next(1, 30);
        int lenDrink = rnd.next(1, 30);
        initial = randomPattern(lenInitial, rnd.next(0.2, 0.8));
        drink = randomPattern(lenDrink, rnd.next(0.2, 0.8));
        if (rnd.next(0, 3) == 0) reverse(initial.begin(), initial.end());
        if (rnd.next(0, 3) == 0) reverse(drink.begin(), drink.end());
    }

    println(n, k);
    println(initial, pInitial);
    println(drink, pDrink);
    return 0;
}
