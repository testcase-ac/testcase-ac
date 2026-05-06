//NnaxhO님 제너레이터 코드에서 범위를 수정했습니다.
//대부분의 경우에 testcase.ac에서 짤릴 정도로 긴 테스트케이스를 출력하여 반례 찾기에 도움이 되기 어렵다고 판단했습니다.
#include <iostream>
#include <random>
#include <cstdlib>
#include <chrono>

using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device

using ui = unsigned int;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ui> distN(1, 50);
uniform_int_distribution<ui> distQ(1, 100);

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    ios_base::sync_with_stdio(false);

    ui N = distN(gen), Q = distQ(gen);
    cout << N << '\n' << Q << '\n';

    uniform_int_distribution<ui> distL(1, N);
    uniform_int_distribution<ui> distR(1, N);

    while(Q--) {
        ui l = distL(gen);
        distR.param(uniform_int_distribution<ui>::param_type(l, N));
        ui r = distR(gen);
        cout << l << ' ' << r << '\n';
    }

    return 0;
}
