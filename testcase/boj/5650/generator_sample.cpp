#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string fixedDecimal(long double value, int digits) {
    ostringstream out;
    out << fixed << setprecision(digits) << (double)value;
    string s = out.str();
    if (digits > 0) {
        while (!s.empty() && s.back() == '0') s.pop_back();
        if (!s.empty() && s.back() == '.') s.pop_back();
    }
    return s;
}

pair<string, string> makeLicense(long double price, long double growth, int priceDigits, int growthDigits) {
    return {fixedDecimal(price, priceDigits), fixedDecimal(growth, growthDigits)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<string, string>> licenses;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        licenses.push_back(makeLicense(rnd.next(1, 1000), 1.0L + rnd.next(1, 900) / 100.0L, 0, 2));
    } else if (mode == 1) {
        int n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            long double price = rnd.next(10, 900) + rnd.next(0, 99) / 100.0L;
            long double growth = 1.0L + rnd.next(1, 80) / 100.0L;
            licenses.push_back(makeLicense(price, growth, rnd.next(0, 2), rnd.next(2, 3)));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            long double price = rnd.next(1, 1000000);
            long double growth = 1.0L + rnd.next(1, 999999) / 1000000000000.0L;
            licenses.push_back(makeLicense(price, growth, rnd.next(0, 6), 12));
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            long double price = rnd.next(1, 5000) + rnd.next(0, 999) / 1000.0L;
            long double growth = rnd.next(500000000000LL, 1000000000000LL) / 100000000000.0L;
            if (growth <= 1.0L) growth = 1.000000000001L;
            if (growth > 10.0L) growth = 10.0L;
            licenses.push_back(makeLicense(price, growth, 3, 12));
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 10);
        vector<long double> deltas = {0.01L, 0.02L, 0.05L, 0.1L, 0.25L, 0.5L, 1.0L};
        long double target = rnd.next(10, 500);
        for (int i = 0; i < n; ++i) {
            long double delta = rnd.any(deltas);
            long double price = target / delta;
            if (rnd.next(0, 2) == 0) price += rnd.next(-5, 5) / 100.0L;
            if (price <= 0.0L) price = 0.01L;
            licenses.push_back(makeLicense(price, 1.0L + delta, 2, 2));
        }
    } else if (mode == 5) {
        int n = rnd.next(4, 12);
        for (int i = 0; i < n; ++i) {
            long double price = 1000000000.0L - rnd.next(0, 1000000) - rnd.next(0, 999999) / 1000000.0L;
            long double growth = 1.0L + rnd.next(1LL, 900000000000LL) / 100000000000.0L;
            if (growth > 10.0L) growth = 10.0L;
            licenses.push_back(makeLicense(price, growth, 6, 12));
        }
    } else {
        int n = rnd.next(15, 30);
        long double base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            long double price = base + rnd.next(0, 2000) / 10.0L;
            long double growth = 1.0L + rnd.next(1, 300) / 100.0L;
            licenses.push_back(makeLicense(price, growth, 1, 2));
        }
    }

    shuffle(licenses.begin(), licenses.end());

    println((int)licenses.size());
    for (const auto& license : licenses) {
        println(license.first, license.second);
    }

    return 0;
}
