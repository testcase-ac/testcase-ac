#include <iostream>
#include <vector>
#include <cstdint>
#include <deque>

struct Box
{
    uint32_t h;
    uint32_t w;
    uint64_t v;
};

struct Entry
{
    Box box;
    size_t index;
};

int main() 
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    size_t t;
    std::cin >> t;
    
    while (t--) 
    {
        size_t n;
        uint64_t X;
        uint64_t result = 0;
        std::deque<std::vector<Box>::const_iterator> deq;
        
        std::cin >> n >> X;
        
        uint32_t hs, ha, hb, hc;
        uint32_t ws, wa, wb, wc;
        
        std::cin >> hs >> ha >> hb >> hc;
        std::cin >> ws >> wa >> wb >> wc;

        std::vector<Box> boxes(n);
        
        uint32_t h0 = hs % hc + 1;
        uint32_t w0 = ws % wc + 1;
        boxes[0] = Box{ h0, w0, h0 * w0 };
        
        for (size_t i = 1; i < n; i++) 
        {
            boxes[i].h = boxes[i-1].h + 1 + (static_cast<uint64_t>(boxes[i - 1].h) * ha + hb) % hc;
            boxes[i].w = (static_cast<uint64_t>(boxes[i-1].w) * wa + wb) % wc + 1;
            boxes[i].v = static_cast<uint64_t>(boxes[i].h) * boxes[i].w;
        }
        
        auto vitf = boxes.cbegin();
        auto vitb = vitf;
        
        while (vitb != boxes.cend())
        {
            if (vitb->h - vitf->h <= X)
            {
                if (vitb - vitf >= 1)
                {
                    result = std::max(result, deq.front()->v + vitb->v);
                }
                
                while (!deq.empty() && deq.back()->v <= vitb->v)
                {
                    deq.pop_back();
                }
                
                deq.push_back(vitb);
                vitb++;
            }
            else
            {
                vitf++;
                
                while (!deq.empty() && deq.front() < vitf)
                {
                    deq.pop_front();
                }
            }
        }
        
        if (result != 0)
        {
            std::cout << result << std::endl;
        }
        else
        {
            std::cout << -1 << std::endl;
        }
    }
}
