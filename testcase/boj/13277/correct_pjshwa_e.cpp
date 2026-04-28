#include <bits/stdc++.h>
#include <smmintrin.h>
#include <immintrin.h>
using namespace std;
#pragma GCC target("avx2")
#pragma GCC target("fma")

//Who might read this code
//This code uses AVX2 operation for fast FFT calculation.
//This depends on judging environment, and should be used carefully


//simple debug code of "print" operation
void print(__m256d a)
{
    cout << a[0] << " ";
    cout << a[1] << " ";
    cout << a[2] << " ";
    cout << a[3] << endl;
}

/*

Flow of function "mult" a, b consist of two complex number.
Return value is multiple of each complex number.
Required operations: 6

    +-------+----movedup----+-------+    +-------+-------+-------+-------+    +-------+----shuffle----+-------+
    |  a1R  |  a1R  |  a2R  |  a2R  | <- |  a1R  |  a1I  |  a2R  |  a2I  | -> |  a1I  |  a1I  |  a2I  |  a2I  |
    +-------+-------+-------+-------+    +-------+-------+-------+-------+    +-------+-------+-------+-------+
                    |                                                                         |
                    v                                                                         v
    +-------+------mul------+-------+    +-------+-------+-------+-------+    +-------+------mul------+-------+
    |a1R*b1R|a1R*b1I|a2R*b2R|a2R*b2I| <- |  b1R  |  b1I  |  b2R  |  b2I  | -> |a1I*b1R|a1I*b1I|a2I*b2R|a2I*b2I|
    +-------+-------+-------+-------+    +-------+-------+-------+-------+    +-------+-------+-------+-------+
                                                                                              |
        -       +       -       +                                                             |
                                                                                              |
    +-------+----shuffle----+-------+                                                         |
    |a1I*b1I|a1I*b1R|a2I*b2I|a2I*b2R| <-------------------------------------------------------+
    +-------+-------+-------+-------+                    
                    | addsub
                    v
    +---------------+---------------+---------------+---------------+
    |a1R*b1R-a1I*b1I|a1R*b1I+a1I*b1R|a2R*b2R-a2I*b2I|a2R*b2I+a2I*b2R|
    +---------------+---------------+---------------+---------------+
*/

__m256d mult(__m256d a, __m256d b)
{
    __m256d c = _mm256_movedup_pd(a);
    __m256d d = _mm256_shuffle_pd(a, a, 15);
    __m256d cb = _mm256_mul_pd(c, b);
    __m256d db = _mm256_mul_pd(d, b);
    __m256d e = _mm256_shuffle_pd(db, db, 5);
    __m256d r = _mm256_addsub_pd(cb, e);
    return r;    
}

/*
Just plain FFT operation.
kth power of root of unity is calculated by w * wlen, not precalculated one.
To reduce memory access and gain speed for two complex multiplication.
And also reduce for calling sincos system call.
*/
void fft(int n, __m128d a[], bool invert)
{
    //xor bit-reversal
    unsigned int sl = 32 - __builtin_ctz(n);
	for(unsigned i=0,j=0; i<n-1;++i)
	{
	    if(i<j) swap(a[i], a[j]);
	    unsigned t = i^(i+1);
	    t <<= __builtin_clz(t);
	    t >>= sl;
	    j ^= t;
	}
	
    for(int len=2; len<=n; len<<=1)
    {
        double ang = 2*3.14159265358979/len*(invert?-1:1);
        __m256d wlen; wlen[0] = cos(ang), wlen[1] = sin(ang);
        for(int i=0; i<n; i += len)
        {
            __m256d w; w[0] = 1; w[1] = 0;
            for(int j=0; j<len/2; ++j)
            {
                w = _mm256_permute2f128_pd(w, w, 0);
                wlen = _mm256_insertf128_pd(wlen, a[i+j+len/2], 1);
                w = mult(w, wlen);
                __m128d vw = _mm256_extractf128_pd(w, 1);
                __m128d u = a[i+j];
                a[i+j] = _mm_add_pd(u, vw);
                a[i+j+len/2] = _mm_sub_pd(u, vw);
            }
        }
    }
    if(invert)
    {
        __m128d inv; inv[0] = inv[1] = 1.0/n;
        for(int i=0; i<n; ++i)
            a[i] = _mm_mul_pd(a[i], inv);
    }
}
vector<int64_t> multiply(vector<int64_t>& v, vector<int64_t>& w)
{
    //v+w-1 is enough for size. odd n will cause error.
    int n = 2; while(n < v.size()+w.size()-1) n<<=1; 
    __m128d* fv = new __m128d[n];
    
    for(int i=0; i<n; ++i)
        fv[i][0] = fv[i][1] = 0;
    for(int i=0; i<v.size(); ++i)
        fv[i][0] = v[i];
    for(int i=0; i<w.size(); ++i)
        fv[i][1] = w[i];

    fft(n, fv, 0); //(a+bi) is stored in FFT
    
    //(a+bi)(c+di) will give ac-bd + (ad+bc)i
    //imaginary part is taken to convolution
    //it is counted twice
    for(int i=0; i<n; i += 2)
    {
        __m256d a, b;
        a = _mm256_insertf128_pd(a, fv[i], 0);
        a = _mm256_insertf128_pd(a, fv[i+1], 1);
        a = mult(a, a);
        fv[i] = _mm256_extractf128_pd(a, 0);
        fv[i+1] = _mm256_extractf128_pd(a, 1);
    }
    
    fft(n, fv, 1); 
    
    vector<int64_t> ret(n);
    for(int i=0; i<n; ++i) ret[i] = (int64_t)round(fv[i][1]/2);
    
    delete[] fv;
    return ret;
}


char buf1[524288];  
char buf2[524288];  
char buf3[1048576];  
int tp=0;  
const int pow10v[8]={1,10,100,1000,10000,100000,1000000,10000000};

// digit is grouped by 3; floor(log2(600000/3)) = 17
// which is also given if grouped by 4. 5 might cause real error and overflow.
int main()  
{  
    scanf("%s%s",buf1,buf2);  
    int N=strlen(buf1), M=strlen(buf2);  
    reverse(buf1,buf1+N);  
    reverse(buf2,buf2+M);
    vector<int64_t> A(N/3+1),B(M/3+1);  
    for(int i=0;i<N;i++)  
        A[i/3]+=(buf1[i]-'0')*pow10v[i%3];  
    for(int i=0;i<M;i++)  
        B[i/3]+=(buf2[i]-'0')*pow10v[i%3];
    vector<int64_t> res = multiply(A,B); 
    
    for(int i=0;i<res.size()-1;i++)  
    {
        res[i+1]+=res[i]/1000;
        res[i]%=1000;
    }
    
    //some minor bug was here.
    //If last term is larger than 1000, They should be added more.
    while(res.back()>=1000)
    {
        int v = res.back()/1000;
        res.back() %= 1000;
        res.push_back(v);
    }
    
    bool nonzero=true;  
    for(int i=res.size()-1;i>=0;i--)  
    {  
        if(nonzero && res[i]==0) continue;  
        nonzero=false;
        buf3[tp++]=res[i]/100+'0';
        buf3[tp++]=res[i]/10%10+'0';
        buf3[tp++]=res[i]%10+'0';
    }
    if(tp==0) puts("0");  
    else if(buf3[0]=='0' && buf3[1]=='0') puts(buf3+2);
    else if(buf3[0]=='0') puts(buf3+1);  
    else puts(buf3);  
    return 0;  
}  

// https://www.acmicpc.net/source/7347729
