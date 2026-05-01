#include "testlib.h"
using namespace std;

long long genFixedDecimals(int d) {
    // Generates a value in [-100000, 100000] with exactly d decimal digits,
    // represented as scaled integer (value * 10000).
    long long limit = 100000;
    for (int i = 0; i < d; ++i) limit *= 10; // 100000 * 10^d
    long long k = rnd.next(-limit, limit);    // k / 10^d in [-100000,100000]
    long long mult = 1;
    for (int i = 0; i < 4 - d; ++i) mult *= 10; // 10^(4-d)
    return k * mult; // (k / 10^d) * 10^4
}

long long genSmallWithRandomDecimals() {
    // Generates value in about [-5,5] with random decimals (0..4),
    // represented as scaled integer (value * 10000).
    int d = rnd.next(0, 4); // number of decimal digits
    long long limit = 5;
    for (int i = 0; i < d; ++i) limit *= 10; // 5 * 10^d
    long long k = rnd.next(-limit, limit);   // k / 10^d in [-5,5]
    long long mult = 1;
    for (int i = 0; i < 4 - d; ++i) mult *= 10; // 10^(4-d)
    return k * mult;
}

string scaledToString(long long scaled) {
    bool neg = false;
    if (scaled < 0) {
        neg = true;
        scaled = -scaled;
    }
    long long integerPart = scaled / 10000;
    int fracPart = (int)(scaled % 10000);

    string s;
    if (neg && (integerPart > 0 || fracPart > 0)) s.push_back('-');
    s += to_string(integerPart);

    if (fracPart > 0) {
        s.push_back('.');
        string fs = to_string(fracPart);
        while ((int)fs.size() < 4) fs = "0" + fs; // pad to 4
        while (!fs.empty() && fs.back() == '0') fs.pop_back(); // trim trailing zeros
        s += fs;
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long scaled; // value * 10000

    int scenario = rnd.next(0, 6);
    switch (scenario) {
        case 0:
            // Fully random in entire range with up to 4 decimals
            scaled = rnd.next(-1000000000LL, 1000000000LL);
            break;
        case 1:
            // Integers only
            scaled = genFixedDecimals(0);
            break;
        case 2:
            // Exactly 1 decimal digit
            scaled = genFixedDecimals(1);
            break;
        case 3:
            // Exactly 2 decimal digits
            scaled = genFixedDecimals(2);
            break;
        case 4:
            // Exactly 3 decimal digits
            scaled = genFixedDecimals(3);
            break;
        case 5: {
            // Special/boundary and near-0.3 style values
            vector<long long> cand = {
                -1000000000LL,  // -100000.0000
                -999999999LL,   // -99999.9999
                -999999700LL,   // -99999.9700
                -3000LL,        // -0.3000
                -2999LL,        // -0.2999
                -1LL,           // -0.0001
                0LL,            // 0
                1LL,            // 0.0001
                2999LL,         // 0.2999
                3000LL,         // 0.3000
                999999700LL,    // 99999.9700
                999999999LL,    // 99999.9999
                1000000000LL    // 100000.0000
            };
            scaled = rnd.any(cand);
            break;
        }
        default:
            // Small magnitudes near zero, random decimals
            scaled = genSmallWithRandomDecimals();
            break;
    }

    // Safety clamp (shouldn't be needed, but just in case)
    if (scaled < -1000000000LL) scaled = -1000000000LL;
    if (scaled > 1000000000LL) scaled = 1000000000LL;

    string out = scaledToString(scaled);
    println(out);

    return 0;
}
