#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter t biases the distribution:
    // t < 0 -> bias toward small numbers, t > 0 -> bias toward large numbers, t = 0 -> uniform
    vector<int> tChoices = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(tChoices);

    // rnd.wnext(718, t) yields [0, 717] with bias; +1 shifts to [1, 718]
    int pokemonId = rnd.wnext(718, t) + 1;

    // Output a single valid Pokémon ID
    println(pokemonId);
    return 0;
}
