#define _CRT_SECURE_NO_WARNINGS
#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#ifdef _MSC_VER
#include <time.h>
#include <conio.h>
#endif

__inline void real();
int main(void)
{
#ifdef _MSC_VER
	clock_t s = clock();
#endif
	real();
#ifdef _MSC_VER
	clock_t e = clock();
	printf( "\n\nelapsed : %10.5f\n", (double)(e-s) / CLOCKS_PER_SEC );
	printf( "\npress any key...\n" );
	int c =_getch();
#endif
	return 0;
}


class FastIO {
	int fd, bufsz;
	char *buf, *cur, *end;
public:
	FastIO(int _fd = 0, int _bufsz = 1 << 19) : fd(_fd), bufsz(_bufsz) {
		buf = cur = end = new char[bufsz];
	}
	~FastIO() {
		delete[] buf;
	}

	bool eof()
	{
		if( cur == end ) return feof(stdin) != 0;
		return false;
	}

	bool readbuf() {
		cur = buf;
		end = buf + bufsz;
		while (true) {
			size_t res = fread(cur, sizeof(char), end - cur, stdin);
			if (res == 0) break;
			cur += res;
		}
		end = cur;
		cur = buf;
		return buf != end;
	}
	int readint() {
		int n;
		readint(n);
		return n;
	}

	int64_t readint64() {
		int64_t n;
		readint64(n);
		return n;
	}

#define READ_INT( ___funcname___, ___type___) \
	bool ___funcname___(___type___& ret)\
	{	\
		while (true) {\
				if (cur == end) { if( !readbuf() ) return false; } \
				if (isdigit(*cur) || *cur == '-') break;\
				++cur;\
			}\
			int sign = 1;\
			if (*cur == '-') {\
				sign = -1;\
				++cur;\
			}\
			ret = 0;\
			while (true) {\
				if (cur == end && !readbuf()) break;\
				if (!isdigit(*cur)) break;\
				ret = ret * 10 + (*cur - '0');\
				++cur;\
			}\
			ret *= sign;\
			return true;\
	}

	READ_INT(readint, int)
	READ_INT(readint64, int64_t)


	#define READ_STR( ___funcname___, ___comp___) \
	int ___funcname___(char* ret) \
	{\
        while (true) {\
            if (cur == end) readbuf();\
            if (!(___comp___)) break;\
            ++cur;\
        } \
		char* pos = ret; \
        while (true) {\
            if (cur == end && !readbuf()) break;\
            if (___comp___) break;\
			*(pos++) = *(cur++);\
        }\
		*pos = '\0';\
        return (int)(pos - ret);\
    }

	READ_STR( readstr, isspace(*cur) )
	READ_STR( readline, *cur == '\n' )
} f;



struct calc
{
	int h;
	int x;
};

calc cal[100001];
int calend;
int h;
uint64_t maxe;
uint64_t ext;
int lastx;


__inline void real()
{
	uint64_t n;
	uint64_t i;
	int j;

	for( ; ; )
	{
		n = f.readint();
		if( n == 0 ) break;

		maxe = 0;
		calend = -1;

		for(i=0; i<n; i++)
		{
			h = f.readint();
			if(h > 0)
			{
				cal[0].h = h;
				cal[0].x = i++;
				calend = 0;
				break;
			}
		}

		for(; i<n; i++)
		{
			h = f.readint();
			if(cal[calend].h <= h)
			{
				cal[++calend].h = h;
				cal[calend].x = i;
			}
			else
			{
				for(j=calend; j>=0; j--)
				{
					if(cal[j].h <= h) break;

					lastx = cal[j].x;
					ext = cal[j].h * (i - cal[j].x);
					if(maxe < ext) maxe = ext;
				}

				calend = j + 1;
				cal[calend].h = h;
				cal[calend].x = lastx;
			}
		}

		for(j=0; j<=calend; j++)
		{
			ext = cal[j].h * (n - cal[j].x);
			if(maxe < ext) maxe = ext;
		}

		printf( "%"PRIu64"\n", maxe);
	}
}
