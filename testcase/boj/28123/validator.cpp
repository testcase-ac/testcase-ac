#include "testlib.h"

#include <array>

using namespace std;

namespace {

const long long LIMIT = 1000000000000000000LL;
const unsigned long long BASE = 1000000000ULL;
const int CHUNKS = 8;

using Fixed = array<unsigned int, CHUNKS>;

const Fixed LOG10_2 = {
    301029995, 663981195, 213738894, 724493026,
    768189881, 462108541, 310427461, 127108189,
};

const Fixed LOWER[10] = {
    {},
    {434, 294264756, 155640743, 942643677, 707041684, 136166714, 512161201, 9206006},
    {301030212, 811167860, 47510410, 437283021, 375734604, 859963715, 910224728, 220527256},
    {477121399, 484465610, 913115265, 237659024, 916149690, 865559510, 480317441, 739088384},
    {602060099, 901569294, 540137175, 614065501, 350762784, 705066916, 355420299, 977428610},
    {698970091, 194906499, 548146688, 909428640, 548392734, 40076917, 463888887, 609491035},
    {778151322, 766051251, 183604068, 786847273, 716873758, 854504265, 502644979, 852246332},
    {845098102, 56321242, 457982026, 335233326, 39791362, 945130250, 212398396, 654024096},
    {903090041, 278750430, 622338015, 186505621, 100064706, 279025618, 737379645, 225239774},
    {954242557, 694264627, 454766698, 37604214, 520059114, 310750277, 741006895, 467727303},
};

const Fixed UPPER[10] = {
    {},
    {301029778, 516685956, 759491552, 483087690, 452034442, 269321190, 597215842, 177044011},
    {477121109, 954811008, 734506843, 944224666, 176549417, 119334170, 772721174, 882780698},
    {602059882, 754328342, 909699449, 196447000, 197240384, 469197373, 960818828, 456527589},
    {698969917, 477113738, 245099391, 221043675, 235860111, 762563819, 251468285, 136436785},
    {778151178, 1223950, 98321103, 342938316, 743906531, 175078415, 819931592, 705905751},
    {845097977, 972183555, 813758587, 661075234, 909587589, 694959030, 382134490, 757492483},
    {903089932, 705129954, 808815614, 797631027, 496760412, 937654466, 935296557, 817025094},
    {954242461, 184379760, 65074504, 433369599, 266577368, 811228358, 766213950, 994312398},
    {999999956, 570549638, 202262953, 789811405, 836176479, 348380679, 596311464, 154866190},
};

struct Product {
    unsigned long long integerPart;
    Fixed fraction;
};

Product multiplyLog10Two(long long n) {
    Product result{};
    unsigned __int128 carry = 0;
    for (int i = CHUNKS - 1; i >= 0; --i) {
        unsigned __int128 value = static_cast<unsigned __int128>(LOG10_2[i]) *
                                      static_cast<unsigned long long>(n) +
                                  carry;
        result.fraction[i] = static_cast<unsigned int>(value % BASE);
        carry = value / BASE;
    }
    result.integerPart = static_cast<unsigned long long>(carry);
    return result;
}

int compareFixed(const Fixed& a, const Fixed& b) {
    for (int i = 0; i < CHUNKS; ++i) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }
    return 0;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1, LIMIT, "n");
    inf.readSpace();
    long long k = inf.readLong(1, LIMIT, "k");
    inf.readSpace();
    int x = inf.readInt(1, 9, "x");
    inf.readEoln();
    inf.readEof();

    Product exponent = multiplyLog10Two(n);
    ensuref(exponent.integerPart + 1 == static_cast<unsigned long long>(k),
            "2^n digit count does not match k");
    ensuref(compareFixed(LOWER[x], exponent.fraction) < 0 &&
                compareFixed(exponent.fraction, UPPER[x]) < 0,
            "2^n/10^(k-1) does not satisfy the stated x and margin");
}
