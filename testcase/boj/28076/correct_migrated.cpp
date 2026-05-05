#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

int main()
{
    size_t N;
    std::vector<uint32_t> multi_taps;
    uint32_t ans = 0;
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cin >> N;
    
    multi_taps.resize(N);
    for (uint32_t& multi_tap : multi_taps)
    {
        std::cin >> multi_tap;
    }
    
    std::sort(multi_taps.begin(), multi_taps.end(), std::greater<uint32_t>());
    
    ans += *multi_taps.begin();
    if (N >= 2) ans += *(multi_taps.begin() + (N + 2) / 3);
    if (N >= 3) ans += *(multi_taps.begin() + (N + 2) / 3 + (N + 1) / 3);
    
    if (N >= 3) ans -= 3;
    else if (N >= 2) ans -= 1;
    
    std::cout << ans << std::endl;
}
