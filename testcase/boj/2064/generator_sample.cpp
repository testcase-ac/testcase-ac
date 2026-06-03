#include "testlib.h"
#include <cstdint>
#include <string>
#include <vector>
using namespace std;

string formatIp(uint32_t value) {
    return to_string((value >> 24) & 255U) + "." +
           to_string((value >> 16) & 255U) + "." +
           to_string((value >> 8) & 255U) + "." +
           to_string(value & 255U);
}

uint32_t randomIp() {
    uint32_t value = 0;
    for (int i = 0; i < 4; ++i) {
        value = (value << 8) | static_cast<uint32_t>(rnd.next(0, 255));
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<uint32_t> addresses;

    if (mode == 0) {
        uint32_t ip = randomIp();
        n = rnd.next(1, 12);
        addresses.assign(n, ip);
    } else if (mode == 1) {
        int hostBits = rnd.next(0, 5);
        uint32_t mask = hostBits == 32 ? 0U : ~((1U << hostBits) - 1U);
        uint32_t base = randomIp() & mask;
        int span = 1 << hostBits;
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            addresses.push_back(base | static_cast<uint32_t>(rnd.next(0, span - 1)));
        }
    } else if (mode == 2) {
        int commonBits = rnd.next(8, 23);
        int hostBits = 32 - commonBits;
        uint32_t mask = ~((1U << hostBits) - 1U);
        uint32_t base = randomIp() & mask;
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            uint32_t suffix = rnd.next(0, (1 << rnd.next(1, 8)) - 1);
            addresses.push_back(base | (suffix << rnd.next(0, hostBits - 8)));
        }
    } else if (mode == 3) {
        int byteIndex = rnd.next(0, 2);
        uint32_t prefix = randomIp() & (byteIndex == 0 ? 0xFF000000U : byteIndex == 1 ? 0xFFFF0000U : 0xFFFFFF00U);
        n = rnd.next(4, 24);
        for (int i = 0; i < n; ++i) {
            uint32_t value = prefix;
            for (int shift = 8 * (2 - byteIndex); shift >= 0; shift -= 8) {
                value |= static_cast<uint32_t>(rnd.next(0, 255)) << shift;
            }
            addresses.push_back(value);
        }
    } else if (mode == 4) {
        addresses = {0U, 0xFFFFFFFFU};
        n = rnd.next(2, 10);
        while (static_cast<int>(addresses.size()) < n) {
            addresses.push_back(randomIp());
        }
    } else {
        n = rnd.next(2, 16);
        uint32_t a = randomIp();
        uint32_t bit = 1U << rnd.next(0, 31);
        addresses.push_back(a);
        addresses.push_back(a ^ bit);
        while (static_cast<int>(addresses.size()) < n) {
            addresses.push_back(rnd.next(0, 1) ? a : (a ^ bit));
        }
    }

    shuffle(addresses.begin(), addresses.end());

    println(static_cast<int>(addresses.size()));
    for (uint32_t address : addresses) {
        println(formatIp(address));
    }

    return 0;
}
