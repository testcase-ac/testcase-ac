#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <random>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::fprintf(stderr, "usage: generator_random <seed>\n");
		return 1;
	}
	std::uint64_t seed = std::strtoull(argv[1], nullptr, 10);
	std::mt19937_64 rng(seed);
	std::uniform_int_distribution<int> dist(1, 9);
	std::printf("%d %d\n", dist(rng), dist(rng));
	return 0;
}
