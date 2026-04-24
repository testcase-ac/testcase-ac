#include <iomanip>
#include <iostream>
#include <map>
#include <string>

int main() {
    // Initialize a map to store the count of each species
    std::map<std::string, int> speciesCount;

    // Read the list of species
    std::string species;
    while(std::getline(std::cin, species)) {
        // Increment the count of the current species
        speciesCount[species]++;
    }

    // Calculate the total number of trees
    int totalTrees = 0;
    for(const auto& [species, count]: speciesCount) {
        totalTrees += count;
    }

    // Print the result for each species
    for(const auto& [species, count]: speciesCount) {
        // Calculate the percentage of the population represented by this species
        double percentage = 100.0 * count / totalTrees;

        // Print the result
        std::cout << species << " " << std::fixed << std::setprecision(4) << percentage << std::endl;
    }

    return 0;
}
