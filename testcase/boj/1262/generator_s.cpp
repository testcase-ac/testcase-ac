#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <algorithm>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: generator_random <seed>\n");
        return 1;
    }

    std::uint64_t seed = std::strtoull(argv[1], nullptr, 10);
    std::mt19937_64 rng(seed);

    std::uniform_int_distribution<int> n_dist(1, 20000);
    std::uniform_int_distribution<int> coord_dist(0, 20000);

    int N = n_dist(rng);

    int R1 = coord_dist(rng);
    int C1 = coord_dist(rng);

    int max_height = std::min(40000, 20000 - R1 + 1);
    std::uniform_int_distribution<int> height_dist(1, max_height);
    int height = height_dist(rng);

    int max_width_by_area = 40000 / height;
    int max_width_by_coord = 20000 - C1 + 1;
    int max_width = std::min(max_width_by_area, max_width_by_coord);

    std::uniform_int_distribution<int> width_dist(1, max_width);
    int width = width_dist(rng);

    int R2 = R1 + height - 1;
    int C2 = C1 + width - 1;

    std::printf("%d %d %d %d %d\n", N, R1, C1, R2, C2);

    return 0;
}