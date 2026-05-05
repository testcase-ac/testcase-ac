#include <iostream>
#include <vector>
#include <cstdint>

int main()
{
    size_t N;
    std::vector<uint32_t> powers;
    std::vector<uint64_t> need_pass_powers;
    std::vector<size_t> max_gain_powers;
    std::vector<size_t> need_return_counts;
    
    std::cin >> N;
    
    powers.resize(N);
    for (uint32_t& power : powers)
    {
        std::cin >> power;
    }
    
    need_pass_powers.resize(N, 0);
    need_pass_powers[0] = powers[0];
    for (size_t i = 1; i < N; i++)
    {
        need_pass_powers[i] = need_pass_powers[i - 1] + powers[i];
    }
    
    max_gain_powers.resize(N, 0);
    max_gain_powers[0] = powers[0];
    for (size_t i = 1; i < N; i++)
    {
        if (powers[i] > need_pass_powers[i - 1])
            max_gain_powers[i] = powers[i] - need_pass_powers[i - 1];
        
        max_gain_powers[i] = std::max(max_gain_powers[i], max_gain_powers[i - 1]);
    }
    
    uint64_t sum = 0;
    need_return_counts.resize(N, 0);
    need_return_counts[0] = 1;
    for (size_t i = 1; i < N; i++)
    {
        need_return_counts[i] = need_return_counts[i - 1];
        
        if (sum >= powers[i])
        {
            sum -= powers[i];
        }
        else
        {
            uint64_t count = (powers[i] - sum + (max_gain_powers[i] - 1)) / max_gain_powers[i];
            
            need_return_counts[i] += count;
            sum = (sum + max_gain_powers[i] * count) - powers[i];
        }
    }
    
    std::cout << need_return_counts[N - 1] << std::endl;
}
