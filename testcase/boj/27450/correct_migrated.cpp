#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>

struct Human
{
    uint64_t p;
    uint64_t t;
};

int main()
{
    size_t N;
    uint64_t K;
    
    std::cin >> N >> K;
    
    std::vector<Human> humans(N);
    
    for (Human& human : humans)
    {
        std::cin >> human.p;
    }
    
    for (Human& human : humans)
    {
        std::cin >> human.t;
    }
    
    uint64_t loud = 0;
    uint64_t dc = 0;
    std::queue<size_t> pq;
    std::queue<uint64_t> tq;
    uint64_t count = 0;
    
    for (size_t i = 0; i < N; i++)
    {
        loud -= dc;
        
        if (!pq.empty() && i > pq.front())
        {
            dc -= tq.front();
            
            pq.pop(), tq.pop();
        }
        
        humans[i].p += loud;
        
        if (humans[i].t > humans[i].p)
        {
            uint64_t req = (humans[i].t - humans[i].p + (K - 1)) / K;
            loud += req * K;
            
            pq.push(i + static_cast<size_t>(K - 1));
            tq.push(req);
            dc += req;
            count += req;
        }
    }
    
    std::cout << count << std::endl;
}
