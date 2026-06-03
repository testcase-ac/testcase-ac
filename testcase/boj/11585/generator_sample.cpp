#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

vector<char> randomWheel(int n, const string& alphabet) {
    vector<char> wheel(n);
    for (int i = 0; i < n; ++i) {
        wheel[i] = rnd.any(alphabet);
    }
    return wheel;
}

vector<char> rotateWheel(const vector<char>& wheel, int shift) {
    int n = int(wheel.size());
    vector<char> rotated(n);
    for (int i = 0; i < n; ++i) {
        rotated[i] = wheel[(i + shift) % n];
    }
    return rotated;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<char> target;
    vector<char> roulette;

    if (mode == 0) {
        n = 1;
        char c = rnd.any(string("ABC"));
        target.assign(1, c);
        roulette.assign(1, c);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        target = randomWheel(n, alphabet.substr(0, rnd.next(2, 7)));
        roulette = rotateWheel(target, rnd.next(0, n - 1));
    } else if (mode == 2) {
        n = rnd.next(2, 24);
        char c = rnd.any(string("ABCD"));
        target.assign(n, c);
        roulette.assign(n, c);
    } else if (mode == 3) {
        int period = rnd.next(1, 6);
        int repeat = rnd.next(2, 5);
        n = period * repeat;
        vector<char> base = randomWheel(period, "ABC");
        target.resize(n);
        for (int i = 0; i < n; ++i) {
            target[i] = base[i % period];
        }
        roulette = rotateWheel(target, rnd.next(0, n - 1));
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        target = randomWheel(n, "ABCD");
        roulette = rotateWheel(target, rnd.next(0, n - 1));
        int changes = rnd.next(1, n / 2);
        for (int i = 0; i < changes; ++i) {
            int at = rnd.next(0, n - 1);
            char before = roulette[at];
            while (roulette[at] == before) {
                roulette[at] = rnd.any(string("ABCD"));
            }
        }
        target = rotateWheel(roulette, rnd.next(0, n - 1));
    } else {
        n = rnd.next(18, 30);
        target = randomWheel(n, "ABC");
        roulette = target;
        shuffle(roulette.begin(), roulette.end());
        target = rotateWheel(roulette, rnd.next(0, n - 1));
    }

    println(n);
    println(target);
    println(roulette);

    return 0;
}
