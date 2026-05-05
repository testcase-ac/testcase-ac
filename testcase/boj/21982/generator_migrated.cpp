#include "testlib.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

struct TestCase
{
    int n;
    std::int64_t X;
    std::int64_t hs, ha, hb, hc;
    std::int64_t ws, wa, wb, wc;
};

constexpr std::int64_t LIM = 1'000'000'000LL;

std::int64_t encodeStart(std::int64_t target, std::int64_t mod)
{
    // H[0] = hs % hc + 1, W[0] = ws % wc + 1
    // target in [1, mod] 를 정확히 만들기 위한 hs/ws 구성
    assert(1 <= target && target <= mod);
    if (target == 1) return mod;   // mod % mod + 1 = 1
    return target - 1;
}

std::int64_t randomCongruent(std::int64_t mod, std::int64_t residue)
{
    // 1 <= x <= 1e9 이고 x % mod == residue 인 x를 랜덤하게 생성
    assert(1 <= mod && mod <= LIM);
    residue %= mod;
    const std::int64_t first = (residue == 0 ? mod : residue);
    assert(1 <= first && first <= LIM);
    const std::int64_t maxK = (LIM - first) / mod;
    return first + mod * rnd.next(static_cast<std::int64_t>(0), maxK);
}

void buildHConst(TestCase& tc, std::int64_t start, std::int64_t step)
{
    // H를 등차수열처럼 만듦:
    // H[i] = H[i-1] + step
    // 이를 위해 ha % hc == 0, hb % hc == step - 1 로 둔다.
    assert(step >= 1);

    const std::int64_t base = std::max({static_cast<std::int64_t>(1), start, step});
    const std::int64_t extra = rnd.next(
        static_cast<std::int64_t>(0),
        std::min<std::int64_t>(1'000'000, LIM - base)
    );
    tc.hc = base + extra;

    tc.ha = randomCongruent(tc.hc, 0);           // ha % hc == 0
    tc.hb = randomCongruent(tc.hc, step - 1);    // hb % hc == step - 1
    tc.hs = encodeStart(start, tc.hc);
}

void buildHRandomBounded(TestCase& tc, std::int64_t maxStep)
{
    // step이 항상 [1, hc] 범위이므로 hc <= maxStep 이면
    // 전체 H 증가량을 안전하게 통제할 수 있다.
    assert(maxStep >= 1);
    tc.hc = rnd.next(static_cast<std::int64_t>(1), maxStep);
    const std::int64_t start = rnd.next(static_cast<std::int64_t>(1), tc.hc);
    tc.hs = encodeStart(start, tc.hc);
    tc.ha = rnd.next(static_cast<std::int64_t>(1), LIM);
    tc.hb = rnd.next(static_cast<std::int64_t>(1), LIM);
}

void buildWConst(TestCase& tc, std::int64_t value)
{
    // W를 상수수열처럼 만듦:
    // W[i] = W[i-1]
    assert(1 <= value && value <= LIM);

    const std::int64_t minWc = std::max<std::int64_t>(2, value);
    const std::int64_t extra = rnd.next(
        static_cast<std::int64_t>(0),
        std::min<std::int64_t>(1'000'000, LIM - minWc)
    );
    tc.wc = minWc + extra;

    tc.ws = encodeStart(value, tc.wc);
    tc.wa = randomCongruent(tc.wc, 1 % tc.wc);             // wa % wc == 1
    tc.wb = randomCongruent(tc.wc, (tc.wc - 1) % tc.wc);  // wb % wc == wc - 1
}

void buildWLinear(TestCase& tc, std::int64_t n, std::int64_t start, std::int64_t diff)
{
    // W를 등차수열처럼 만듦:
    // W[i] = W[i-1] + diff
    assert(n >= 2);
    assert(diff >= 1);

    const std::int64_t finalValue = start + (n - 1) * diff;
    assert(1 <= start && finalValue <= LIM);

    const std::int64_t minWc = std::max<std::int64_t>(2, finalValue);
    const std::int64_t extra = rnd.next(
        static_cast<std::int64_t>(0),
        std::min<std::int64_t>(1'000'000, LIM - minWc)
    );
    tc.wc = minWc + extra;

    tc.ws = encodeStart(start, tc.wc);
    tc.wa = randomCongruent(tc.wc, 1 % tc.wc);            // wa % wc == 1
    tc.wb = randomCongruent(tc.wc, (diff - 1) % tc.wc);  // wb % wc == diff - 1
}

void buildWAlternating(TestCase& tc, std::int64_t low, std::int64_t high)
{
    // low, high, low, high, ... 패턴
    // wa ≡ -1 (mod wc), wb ≡ -1 (mod wc) 이면
    // W[i] = wc - W[i-1] 꼴이 된다.
    assert(low >= 1 && high >= 1);

    tc.wc = low + high;
    assert(2 <= tc.wc && tc.wc <= LIM);

    tc.ws = encodeStart(low, tc.wc);
    tc.wa = randomCongruent(tc.wc, (tc.wc - 1) % tc.wc); // -1 mod wc
    tc.wb = randomCongruent(tc.wc, (tc.wc - 1) % tc.wc); // -1 mod wc
}

void buildWRandom(TestCase& tc, std::int64_t maxWc)
{
    maxWc = std::max<std::int64_t>(2, std::min<std::int64_t>(maxWc, LIM));
    tc.wc = rnd.next(static_cast<std::int64_t>(2), maxWc);
    const std::int64_t start = rnd.next(static_cast<std::int64_t>(1), tc.wc);
    tc.ws = encodeStart(start, tc.wc);
    tc.wa = rnd.next(static_cast<std::int64_t>(1), LIM);
    tc.wb = rnd.next(static_cast<std::int64_t>(1), LIM);
}

void validateCase(const TestCase& tc)
{
    // 실제로 H/W를 한 번 돌려보며 constraints를 만족하는지 확인
    assert(2 <= tc.n && tc.n <= 5'000'000);
    assert(1 <= tc.X && tc.X <= LIM);

    assert(1 <= tc.hs && tc.hs <= LIM);
    assert(1 <= tc.ha && tc.ha <= LIM);
    assert(1 <= tc.hb && tc.hb <= LIM);
    assert(1 <= tc.hc && tc.hc <= LIM);

    assert(1 <= tc.ws && tc.ws <= LIM);
    assert(1 <= tc.wa && tc.wa <= LIM);
    assert(1 <= tc.wb && tc.wb <= LIM);
    assert(1 <= tc.wc && tc.wc <= LIM);

    std::int64_t H = tc.hs % tc.hc + 1;
    std::int64_t W = tc.ws % tc.wc + 1;
    assert(1 <= H && H <= LIM);
    assert(1 <= W && W <= LIM);

    for (int i = 1; i < tc.n; ++i)
    {
        H = H + 1 + ((H * tc.ha + tc.hb) % tc.hc);
        W = ((W * tc.wa + tc.wb) % tc.wc) + 1;
        assert(1 <= H && H <= LIM);
        assert(1 <= W && W <= LIM);
    }
}

TestCase makeSmallRandom()
{
    TestCase tc{};
    tc.n = rnd.next(2, 40);

    const std::int64_t maxStep = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(50, (LIM - 1) / (tc.n - 1))
    );
    buildHRandomBounded(tc, maxStep);
    buildWRandom(tc, rnd.next(static_cast<std::int64_t>(20), static_cast<std::int64_t>(200)));

    const std::int64_t k = rnd.next(static_cast<std::int64_t>(1), static_cast<std::int64_t>(tc.n - 1));
    tc.X = std::min<std::int64_t>(LIM, k * maxStep);
    return tc;
}

TestCase makeNoPairLarge()
{
    // 모든 인접한 높이 차이도 X보다 크게 만들어서 답이 -1이 되게 함
    TestCase tc{};
    tc.n = rnd.next(700'000, 1'500'000);

    const std::int64_t maxD = std::min<std::int64_t>(1000, (LIM - 1) / (tc.n - 1));
    const std::int64_t d = rnd.next(static_cast<std::int64_t>(2), maxD);

    const std::int64_t startMax = LIM - (tc.n - 1) * d;
    const std::int64_t start = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(1'000'000, startMax)
    );
    buildHConst(tc, start, d);

    if (rnd.next(0, 1) == 0) buildWRandom(tc, LIM);
    else buildWConst(tc, rnd.next(static_cast<std::int64_t>(1), LIM));

    tc.X = rnd.next(static_cast<std::int64_t>(1), d - 1);
    return tc;
}

TestCase makeAdjacentOnlyLarge()
{
    // X = d 로 두면 등차수열 H에서 인접한 상자만 선택 가능
    TestCase tc{};
    tc.n = rnd.next(700'000, 1'500'000);

    const std::int64_t d = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(200, (LIM - 1) / (tc.n - 1))
    );
    const std::int64_t startMax = LIM - (tc.n - 1) * d;
    const std::int64_t start = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(1'000'000, startMax)
    );
    buildHConst(tc, start, d);

    const std::int64_t wDiff = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(1000, (LIM - 1) / (tc.n - 1))
    );
    const std::int64_t wStartMax = LIM - (tc.n - 1) * wDiff;
    const std::int64_t wStart = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(1'000'000, wStartMax)
    );
    buildWLinear(tc, tc.n, wStart, wDiff);

    tc.X = d;
    return tc;
}

TestCase makeFullWindowHuge()
{
    // 모든 쌍 가능: 답은 사실상 전체에서 volume 상위 2개
    TestCase tc{};
    tc.n = rnd.next(3'000'000, 5'000'000);

    const std::int64_t d = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(10, (LIM - 1) / (tc.n - 1))
    );
    const std::int64_t startMax = LIM - (tc.n - 1) * d;
    const std::int64_t slack = std::min<std::int64_t>(1'000'000, startMax - 1);
    std::int64_t start = startMax - rnd.next(static_cast<std::int64_t>(0), std::max<std::int64_t>(0, slack));
    start = std::max<std::int64_t>(1, start);
    buildHConst(tc, start, d);

    if (rnd.next(0, 1) == 0)
    {
        const std::int64_t low = rnd.next(static_cast<std::int64_t>(1), static_cast<std::int64_t>(10'000));
        const std::int64_t high = rnd.next(static_cast<std::int64_t>(100'000'000), LIM - low);
        buildWAlternating(tc, low, high);
    }
    else
    {
        buildWRandom(tc, LIM);
    }

    tc.X = static_cast<std::int64_t>(tc.n - 1) * d;
    return tc;
}

TestCase makeRandomBoundedLarge()
{
    TestCase tc{};
    tc.n = rnd.next(200'000, 800'000);

    const std::int64_t maxStep = std::min<std::int64_t>(500, (LIM - 1) / (tc.n - 1));
    buildHRandomBounded(tc, maxStep);

    const int pick = rnd.next(0, 2);
    if (pick == 0)
    {
        buildWConst(tc, rnd.next(static_cast<std::int64_t>(1), LIM));
    }
    else if (pick == 1)
    {
        buildWRandom(tc, rnd.next(static_cast<std::int64_t>(1000), LIM));
    }
    else
    {
        const std::int64_t wDiff = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(100, (LIM - 1) / (tc.n - 1))
        );
        const std::int64_t wStartMax = LIM - (tc.n - 1) * wDiff;
        const std::int64_t wStart = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(1'000'000, wStartMax)
        );
        buildWLinear(tc, tc.n, wStart, wDiff);
    }

    const std::int64_t k = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(static_cast<std::int64_t>(tc.n - 1), 1'000'000)
    );
    tc.X = std::min<std::int64_t>(LIM, k * maxStep);
    return tc;
}

TestCase makeOscillatingMedium()
{
    TestCase tc{};
    tc.n = rnd.next(100'000, 500'000);

    const std::int64_t d = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(20, (LIM - 1) / (tc.n - 1))
    );
    const std::int64_t startMax = LIM - (tc.n - 1) * d;
    const std::int64_t start = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(1'000'000, startMax)
    );
    buildHConst(tc, start, d);

    const std::int64_t low = rnd.next(static_cast<std::int64_t>(1), static_cast<std::int64_t>(10'000));
    const std::int64_t high = rnd.next(static_cast<std::int64_t>(100'000'000), LIM - low);
    buildWAlternating(tc, low, high);

    const std::int64_t k = rnd.next(
        static_cast<std::int64_t>(1),
        std::min<std::int64_t>(static_cast<std::int64_t>(tc.n - 1), 5000)
    );
    tc.X = k * d;
    return tc;
}

TestCase makeNearOverflowSmall()
{
    // H, W를 크게 잡아서 64-bit 처리 확인
    TestCase tc{};
    tc.n = rnd.next(2, 6);

    const std::int64_t maxD = (LIM - 1) / (tc.n - 1);
    const std::int64_t d = rnd.next(std::max<std::int64_t>(1, maxD / 4), maxD);

    const std::int64_t startMax = LIM - (tc.n - 1) * d;
    const std::int64_t slack = std::min<std::int64_t>(1000, startMax - 1);
    std::int64_t start = startMax - rnd.next(static_cast<std::int64_t>(0), std::max<std::int64_t>(0, slack));
    start = std::max<std::int64_t>(1, start);
    buildHConst(tc, start, d);

    buildWConst(tc, rnd.next(static_cast<std::int64_t>(500'000'000), LIM));
    tc.X = static_cast<std::int64_t>(tc.n - 1) * d;
    return tc;
}

TestCase makeMixedMedium()
{
    TestCase tc{};
    tc.n = rnd.next(10'000, 200'000);
    const int type = rnd.next(0, 2);

    if (type == 0)
    {
        const std::int64_t d = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(500, (LIM - 1) / (tc.n - 1))
        );
        const std::int64_t startMax = LIM - (tc.n - 1) * d;
        const std::int64_t start = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(1'000'000, startMax)
        );
        buildHConst(tc, start, d);
        buildWConst(tc, rnd.next(static_cast<std::int64_t>(1), LIM));
        const std::int64_t k = rnd.next(static_cast<std::int64_t>(1), static_cast<std::int64_t>(tc.n - 1));
        tc.X = std::min<std::int64_t>(LIM, k * d);
    }
    else if (type == 1)
    {
        const std::int64_t maxStep = std::min<std::int64_t>(2000, (LIM - 1) / (tc.n - 1));
        buildHRandomBounded(tc, maxStep);

        const std::int64_t wDiff = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(1000, (LIM - 1) / (tc.n - 1))
        );
        const std::int64_t wStartMax = LIM - (tc.n - 1) * wDiff;
        const std::int64_t wStart = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(1'000'000, wStartMax)
        );
        buildWLinear(tc, tc.n, wStart, wDiff);

        const std::int64_t k = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(static_cast<std::int64_t>(tc.n - 1), 1'000'000)
        );
        tc.X = std::min<std::int64_t>(LIM, k * maxStep);
    }
    else
    {
        const std::int64_t d = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(1000, (LIM - 1) / (tc.n - 1))
        );
        const std::int64_t startMax = LIM - (tc.n - 1) * d;
        const std::int64_t start = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(1'000'000, startMax)
        );
        buildHConst(tc, start, d);
        buildWRandom(tc, LIM);
        tc.X = rnd.next(
            static_cast<std::int64_t>(1),
            std::min<std::int64_t>(LIM, d * std::min<std::int64_t>(static_cast<std::int64_t>(tc.n - 1), 1'000'000))
        );
    }

    return tc;
}

TestCase makePriorityQueueKillerFull()
{
    TestCase tc{};
    tc.n = 5'000'000;

    // H = 1, 2, 3, ..., n
    buildHConst(tc, 1, 1);

    // W는 시간복잡도와 거의 무관하니 아무거나 크게 흔들리게
    buildWAlternating(tc, 1, LIM - 1);

    // 모든 쌍 가능에 가깝게
    tc.X = LIM;
    return tc;
}

TestCase makePriorityQueueKillerWide()
{
    TestCase tc{};
    tc.n = 5'000'000;

    // H = 1, 2, 3, ..., n
    buildHConst(tc, 1, 1);

    // 부피 우선순위가 자주 뒤집히도록
    buildWRandom(tc, LIM);

    // 윈도우 크기가 매우 크게 유지되도록
    tc.X = 2'500'000;
    return tc;
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    std::vector<TestCase> tests;
    tests.push_back(makeSmallRandom());
    tests.push_back(makeNoPairLarge());
    tests.push_back(makeAdjacentOnlyLarge());
    tests.push_back(makeFullWindowHuge());
    tests.push_back(makeRandomBoundedLarge());
    tests.push_back(makeOscillatingMedium());
    tests.push_back(makeNearOverflowSmall());
    tests.push_back(makeMixedMedium());
    tests.push_back(makePriorityQueueKillerFull());
    tests.push_back(makePriorityQueueKillerWide());

    for (const auto& tc : tests)
    {
        validateCase(tc);
    }

    std::cout << tests.size() << '\n';
    for (const auto& tc : tests)
    {
        std::cout << tc.n << ' ' << tc.X << '\n';
        std::cout << tc.hs << ' ' << tc.ha << ' ' << tc.hb << ' ' << tc.hc << '\n';
        std::cout << tc.ws << ' ' << tc.wa << ' ' << tc.wb << ' ' << tc.wc << '\n';
    }

    return 0;
}
