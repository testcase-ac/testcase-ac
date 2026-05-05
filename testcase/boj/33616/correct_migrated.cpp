#include <iostream>
#include <cmath>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    size_t T;
    
    std::cin >> T;
    
    for (size_t tc = 0; tc < T; tc++)
    {
        int a, b;
        char ch;
        
        std::cin >> a >> b;
        
        if ((a ^ b) & 1)
        {
            std::cout << -1 << '\n';
            continue;
        }
        else
        {
            ch = (a > b) ? 'A' : 'B';
        }
        
        int diff = std::abs(a - b) / 2;
        if (a < b) std::swap(a, b);
        
        if ((a ^ diff) == (b + diff))
        {
            std::cout << 1 << '\n';
            std::cout << ch << ' ' << diff << '\n';
        }
        else
        {
            std::cout << 2 << '\n';
            std::cout << ch << ' ' << diff << '\n';
            std::cout << ch << ' ' << diff << '\n';
        }
    }
}
