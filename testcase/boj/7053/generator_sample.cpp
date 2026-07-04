#include "testlib.h"

#include <vector>

using namespace std;

vector<int> buildRegisterSequence(int n, const vector<int>& state, const vector<int>& switches) {
    vector<int> reg = state;
    vector<int> output;
    output.reserve(2 * n);

    for (int tick = 0; tick < 2 * n; ++tick) {
        output.push_back(reg[n - 1]);

        int next = 0;
        for (int i = 0; i < n; ++i) {
            if (switches[i]) {
                next ^= reg[i];
            }
        }

        for (int i = n - 1; i > 0; --i) {
            reg[i] = reg[i - 1];
        }
        reg[0] = next;
    }

    return output;
}

vector<int> randomBits(int count, double oneProbability) {
    vector<int> bits(count);
    for (int i = 0; i < count; ++i) {
        bits[i] = rnd.next() < oneProbability ? 1 : 0;
    }
    return bits;
}

int chooseN(int mode) {
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return rnd.next(2, 4);
    }
    if (mode == 2) {
        return rnd.next(5, 12);
    }
    if (mode == 3) {
        return rnd.next(13, 40);
    }
    if (mode == 4) {
        return rnd.any(vector<int>{100, 250, 500, 750});
    }
    return rnd.next(2, 30);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = chooseN(mode);
    vector<int> bits;

    if (mode <= 2 || mode == 4) {
        double switchDensity = rnd.any(vector<double>{0.0, 0.2, 0.5, 0.8, 1.0});
        double stateDensity = rnd.any(vector<double>{0.0, 0.25, 0.5, 0.75, 1.0});
        vector<int> state = randomBits(n, stateDensity);
        vector<int> switches = randomBits(n, switchDensity);
        bits = buildRegisterSequence(n, state, switches);
    } else if (mode == 3) {
        bits.resize(2 * n);
        int pattern = rnd.next(0, 3);
        for (int i = 0; i < 2 * n; ++i) {
            if (pattern == 0) {
                bits[i] = i % 2;
            } else if (pattern == 1) {
                bits[i] = (i / rnd.next(1, 4)) % 2;
            } else {
                bits[i] = (i == 0 || i == n || i == 2 * n - 1) ? 1 : 0;
            }
        }
    } else {
        double oneProbability = rnd.any(vector<double>{0.1, 0.3, 0.5, 0.7, 0.9});
        bits = randomBits(2 * n, oneProbability);
    }

    println(n);
    println(bits);

    return 0;
}
