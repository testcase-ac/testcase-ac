#include <iostream>
#include <random>
#include <string>
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


int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> t_dis(1, 5);
    uniform_int_distribution<> r_dis(1, 8);
    uniform_int_distribution<> len_dis(1, 10);
    string qr_alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$%*+-./:";
    uniform_int_distribution<> char_dis(0, qr_alphanumeric.size() - 1);
    int T = t_dis(gen);
    cout << T << endl;
    for (int t = 0; t < T; ++t) {
        int R = r_dis(gen);
        int len = len_dis(gen);
        string S = "";
        for (int i = 0; i < len; ++i) {
            S += qr_alphanumeric[char_dis(gen)];
        } cout << R << " " << S << endl;
    } return 0;
}
