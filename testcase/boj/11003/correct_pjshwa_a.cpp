#include <stdio.h>
#include <algorithm>
using namespace std;

namespace FIO {
    const size_t BUFFER_SIZE = 1048576;
    char buffer[BUFFER_SIZE];
    char* ptr = buffer + BUFFER_SIZE;

    inline char readByte() {
        if (ptr == buffer + BUFFER_SIZE) {
            fread(buffer, 1, BUFFER_SIZE, stdin);
            ptr = buffer;
        }
        return *(ptr++);
    }

    int readInt() {
        unsigned ret = 0;
        unsigned char c = readByte();
        while (c <= ' ') {
            c = readByte();
        }
        bool neg = false;
        if (c == '-') {
            neg = true;
            c = readByte();
        }
        while (c > ' ') {
            ret = ret * 10 + (c - '0');
            c = readByte();
        }
        return neg ? -(int)ret : (int)ret;
    }

    char outbuf[BUFFER_SIZE + 20];
    char* outp = outbuf;

    void printInt(int n)
    {
        unsigned nn;
        if (n < 0) nn = -n, *outp++ = '-';
        else nn = n;
        char *end = outp;
        do
        {
            *end++ = nn % 10 + '0';
            nn /= 10;
        } while (nn);
        reverse(outp, end);
        *end++ = ' ';
        if (end < outbuf + BUFFER_SIZE) outp = end;
        else
        {
            fwrite(outbuf, 1, end - outbuf, stdout);
            outp = outbuf;
        }
    }

    void flush()
    {
        fwrite(outbuf, 1, outp - outbuf, stdout);
        fflush(stdout);
    }
};

pair<int, int> deq[5000005];
int head, tail;

inline bool empty()
{
    return head == tail;
}

inline void emplace_back(int a, int b)
{
    deq[tail++] = { a, b };
}

inline pair<int, int> &front()
{
    return deq[head];
}

inline pair<int, int> &back()
{
    return deq[tail - 1];
}

inline void pop_front()
{
    head++;
}

inline void pop_back()
{
    tail--;
}

int main()
{
    int n = FIO::readInt(), l = FIO::readInt();

    for (int i = 0; i < n; i++)
    {
        int tmp = FIO::readInt();
        while (empty() == false && front().second + l <= i) pop_front();
        while (empty() == false && back().first >= tmp) pop_back();
        emplace_back(tmp, i);
        FIO::printInt(front().first);
    }

    FIO::flush();
    _Exit(0);
}
