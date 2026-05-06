#include <iostream>
#include <random>
#include <ctime>
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
    uniform_int_distribution<> dis(1, 10000);
    uniform_int_distribution<> dis_type(1, 3);
    
    int count = 0;
    while (true) {
        int a = dis(gen);
        int b = dis(gen);
        int type = dis_type(gen);
        
        if (type == 1) {
            b = a * (dis(gen) % 10 + 1);
            if(b<10001&&a!=b) cout << a << " " << b << endl;
        } else if (type == 2) {
            a = b * (dis(gen) % 10 + 1);
            if(a<10001&&a!=b) cout << a << " " << b << endl;
        } else {
            while (a % b == 0 || b % a == 0) {
                a = dis(gen);
                b = dis(gen);
            } if(a!=b) cout << a << " " << b << endl;
        }

        count++;
        if (count > 10 && dis_type(gen) == 3) {
            cout << "0 0" << endl;
            break;
        }
    } return 0;
}
