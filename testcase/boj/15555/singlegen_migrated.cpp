#include <iostream>
#include <vector>
#include <string>

int main() {
    int n = 3000, m = 3000;
    std::cout << n << " " << m << std::endl;
    std::vector<char> l = {'R', 'G', 'W'};
    for (int i = 0; i < 3000; ++i) {
        std::string k;
        k.reserve(3000);
        for (int j = 0; j < 3000; ++j) {
            k += l[(i + j) % 3];
        }
        std::cout << k << std::endl;
    }
    return 0;
}
