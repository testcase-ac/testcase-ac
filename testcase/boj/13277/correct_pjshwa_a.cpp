// This program multiplies two 300,000-size decimal integers
// Utilizing the Fast Number Theoretic Transform

#ifdef __GNUC__
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif

#if __cpp_if_constexpr >= 201606
#define CONSTIF if constexpr
#else
#define CONSTIF if
#endif

#include <immintrin.h>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <unistd.h>

constexpr int LOG_MAX_SZ = 17;
constexpr int MAX_SZ = 1 << LOG_MAX_SZ;

// Helpers
constexpr int32_t modpow(int32_t x, int y, int32_t P) {
    int32_t r = x;
    for (--y; y; y >>= 1) {
        if (y & 1) r = int64_t(r) * x % P;
        x = int64_t(x) * x % P;
    }
    return r;
}

constexpr int32_t modinv(int32_t x, int32_t P) {
    return modpow(x, P - 2, P);
}

// Modular Arithmetic
// P: modulus, R: primitive root of P
// MR: Montgomery number, MRR : Inverse of MR
template <int32_t P_, int32_t R_>
struct Ring {

    // Convert to Montgomery form and back
    static constexpr int32_t montify(int32_t x) {
        return (int64_t(x) << 32) % P;
    }

    static constexpr int32_t unmontify(int32_t x) {
        return int64_t(x) * MRR % P;
    }

    static constexpr int32_t add(int32_t a, int32_t b) {
        int32_t c = a + b;
        return c < P? c : c - P;
    }

    static constexpr int32_t sub(int32_t a, int32_t b) {
        int32_t c = P + a - b;
        return c < P? c : c - P;
    }

    static constexpr int32_t mul(int32_t a, int32_t b) {
        int64_t x = int64_t(a) * b;
        int64_t s = ((x & (MR - 1)) * K) & (MR - 1);
        int64_t u = (x + s * P) >> 32;
        int32_t up = u - P;
        return up < 0? u : up;
    }

    static constexpr int32_t pow(int32_t a, int n) {
        int32_t r = ONE;
        for (; n; n >>= 1) {
            if (n & 1) r = mul(r, a);
            a = mul(a, a);
        }
        return r;
    }

    static constexpr int32_t inv(int32_t a) {
        return pow(a, P - 2);
    }

    __attribute__((target("avx2")))
    static __m256i add(__m256i a, __m256i b) {
        auto add = _mm256_add_epi32(a, b);
        auto mmP = _mm256_set1_epi32(P);
        auto cmp = _mm256_cmpgt_epi32(mmP, add);
        return _mm256_sub_epi32(add, _mm256_andnot_si256(cmp, mmP));
    }

    __attribute__((target("avx2")))
    static __m256i sub(__m256i a, __m256i b) {
        auto sub = _mm256_sub_epi32(a, b);
        auto cmp = _mm256_cmpgt_epi32(_mm256_setzero_si256(), sub);
        auto mmP = _mm256_set1_epi32(P);
        return _mm256_add_epi32(sub, _mm256_and_si256(cmp, mmP));
    }

    __attribute__((target("avx2")))
    static __m256i mul(__m256i a, __m256i b) {
        auto mmK64 = _mm256_set1_epi64x(K);
        auto mmP64 = _mm256_set1_epi64x(P);
        auto shft_a = _mm256_bsrli_epi128(a, 4);
        auto shft_b = _mm256_bsrli_epi128(b, 4);
        auto ab_hi = _mm256_mul_epu32(shft_a, shft_b);
        auto s_hi = _mm256_mul_epu32(ab_hi, mmK64);
        auto u_hi = _mm256_add_epi64(_mm256_mul_epu32(s_hi, mmP64), ab_hi);

        auto ab_lo = _mm256_mul_epu32(a, b);
        auto s_lo = _mm256_mul_epu32(ab_lo, mmK64);
        auto u_lo = _mm256_add_epi64(_mm256_mul_epu32(s_lo, mmP64), ab_lo);

        auto mask = _mm256_setr_epi32(0, -1, 0, -1, 0, -1, 0, -1);
        auto u = _mm256_blendv_epi8(_mm256_bsrli_epi128(u_lo, 4), u_hi, mask);
        auto mmP32 = _mm256_set1_epi32(P);
        auto cmp = _mm256_cmpgt_epi32(mmP32, u);
        return _mm256_sub_epi32(u, _mm256_andnot_si256(cmp, mmP32));
    }

    // N-th Primitive root of unity
    template <int f>
    static constexpr int32_t proot(int32_t N) {
        CONSTIF (f > 0) return pow(RRI, P / N);
        else return pow(RR, P / N);
    }

    /*
    * input : vector of 4 32-bit ints in Montgomery form.
    * output : Montgomery-form NTT in `a`.
    */
    template <int f>
    __attribute__((target("avx2")))
    static void mont_NTT(__m256i *x, int N) { // verified
        auto w = _mm256_set1_epi32(proot<f>(N));
        for (int k = N; k > 1; k >>= 1) {
            auto t = _mm256_set1_epi32(ONE);
            for (int l = 0; l < k / 2; ++l) {
                for (int a = l; a < N; a += k) {
                    int b = a + k / 2;
                    auto u = sub(x[a], x[b]);
                    x[a] = add(x[a], x[b]);
                    x[b] = mul(t, u);
                }
                t = mul(t, w);
            }
            w = mul(w, w);
        }
        for (int i = 1, j = 0; i < N; i++) {
            int b = N >> 1;
            for (; j >= b; b >>= 1) j -= b;
            j += b;
            if (i < j) std::swap(x[i], x[j]);
        }
        CONSTIF (f < 0) {
            auto z = _mm256_set1_epi32(inv(montify(N)));
            for (int i = 0; i < N; i++)
                x[i] = mul(x[i], z);
        }
    }

    template <int f>
    __attribute__((target("avx2")))
    static __m256i roots(int N) {
        __m256i wN;
        alignas(32) int32_t t[8] = {ONE};
        int32_t root = proot<f>(N);
        for (int i = 1; i < 8; ++i) t[i] = mul(t[i - 1], root);
        std::memcpy(&wN, t, 32);
        return wN;
    }

    template <int f>
    __attribute__((target("avx2")))
    static void ntt8(__m256i *a, int N) {
        constexpr auto w4 = proot<f>(4), w8 = proot<f>(8), w4w8 = mul(w4, w8);
        const auto f1 = _mm256_setr_epi32(ONE, ONE, ONE, w4, ONE, ONE, ONE, w4);
        const auto f2 = _mm256_setr_epi32(ONE, ONE, ONE, ONE, ONE, w8, w4, w4w8);
        const auto mmP = _mm256_set1_epi32(P);
        const auto mP = _mm_set1_epi32(P);
        for (int i = 0; i < N; ++i) {
            a[i] = _mm256_permutevar8x32_epi32(a[i], _mm256_setr_epi32(0, 4, 2, 6, 1, 5, 3, 7));
            auto mm1 = _mm256_hadd_epi32(a[i], _mm256_setzero_si256());
            auto cmp = _mm256_cmpgt_epi32(mmP, mm1);
            mm1 = _mm256_sub_epi32(mm1, _mm256_andnot_si256(cmp, mmP));
            auto mm2 = _mm256_hsub_epi32(a[i], _mm256_setzero_si256());
            cmp = _mm256_cmpgt_epi32(_mm256_setzero_si256(), mm2);
            mm2 = _mm256_add_epi32(mm2, _mm256_and_si256(cmp, mmP));
            a[i] = _mm256_unpacklo_epi32(mm1, mm2);
            a[i] = mul(a[i], f1);
            auto s1 = _mm256_bsrli_epi128(a[i], 8);
            auto s2 = add(a[i], s1);
            auto s3 = sub(a[i], s1);
            auto s4 = _mm256_bslli_epi128(s3, 8);
            a[i] = _mm256_blend_epi32(s2, s4, 204);
            a[i] = mul(a[i], f2);
            auto m1 = _mm256_extracti128_si256(a[i], 0);
            auto m2 = _mm256_extracti128_si256(a[i], 1);
            auto m3 = _mm_add_epi32(m1, m2);
            auto c = _mm_cmpgt_epi32(mP, m3);
            m3 = _mm_sub_epi32(m3, _mm_andnot_si128(c, mP));
            auto m4 = _mm_sub_epi32(m1, m2);
            c = _mm_cmpgt_epi32(_mm_setzero_si128(), m4);
            m4 = _mm_add_epi32(m4, _mm_and_si128(c, mP));
            a[i] = _mm256_inserti128_si256(_mm256_castsi128_si256(m3), (m4), 1);
        }
    }

    // Performs the 8-step Number Theoretic Transform
    // transposed as a 8 x N/8 matrix in parallel.
    __attribute__((target("avx2")))
    static void NTT(int32_t *a, int N) {
        auto *va = reinterpret_cast<__m256i*>(a);
        mont_NTT<1>(va, N / 8);
        // Apply twiddle factors and perform 8-point fft
        const __m256i wN = roots<1>(N);
        auto w = _mm256_set1_epi32(ONE);
        for (int i = 0; i < N / 8; ++i) {
            va[i] = mul(va[i], w);
            w = mul(w, wN);
        }
        ntt8<1>(va, N / 8);
    }

    __attribute__((target("avx2")))
    static void iNTT(int32_t *a, int N) {
        // Perform a 8-point FFT and apply twiddle factors
        auto *va = reinterpret_cast<__m256i*>(a);
        ntt8<-1>(va, N / 8);
        const __m256i wN = roots<-1>(N);
        auto w = _mm256_set1_epi32(ONE);
        for (int i = 0; i < N / 8; ++i) {
            va[i] = mul(va[i], w);
            w = mul(w, wN);
        }
        mont_NTT<-1>(va, N / 8);
        // Normalize
        auto z = _mm256_set1_epi32(montify(modinv(8, P)));
        for (int i = 0; i < N / 8; i++)
            va[i] = mul(va[i], z);
    }

    __attribute__((target("avx2")))
    static void polymul_ring(int32_t *f, int fn, int32_t *g, int gn) {
        int N = 8;
        while (N < fn + gn + 1) N *= 2;
        for (int i = 0; i < fn; ++i) f[i] = montify(f[i]);
        for (int i = 0; i < gn; ++i) g[i] = montify(g[i]);
        NTT(f, N);
        NTT(g, N);
        auto *va = reinterpret_cast<__m256i*>(f);
        auto *vb = reinterpret_cast<__m256i*>(g);
        for (int i = 0; i < N / 8; ++i) va[i] = mul(va[i], vb[i]);
        iNTT(f, N);
    }

    static constexpr int64_t MR = 1LL << 32;
    static constexpr int32_t P = P_, R = R_;
    static constexpr int32_t MRR = modinv(MR % P, P);
    static constexpr int32_t K = (int64_t(MR) * MRR - 1) / P;
    static constexpr int32_t ONE = MR % P;
    static constexpr int32_t RR = int64_t(R) * MR % P;
    static constexpr int32_t RRI = inv(RR);
};
using R1 = Ring<469762049,  3>;
using R2 = Ring<754974721, 11>;

int six_block(char* s) {
    return (s[5] & 15) * 100000 + (s[4] & 15) * 10000 +
        (s[3] & 15) * 1000 + (s[2] & 15) * 100 +
        (s[1] & 15) * 10 + (s[0] & 15);
}

int string_mul(char* s1, int l1, char* s2, int l2) {
    int32_t *F = reinterpret_cast<int32_t*>(s1);
    alignas(32) int32_t G[MAX_SZ]{0};
    alignas(32) int32_t a[MAX_SZ]{0}, b[MAX_SZ]{0};
    int64_t R[100010]{0};
    int i, t;
    std::reverse(s1, s1 + l1);
    std::reverse(s2, s2 + l2);
    for (i = 0; i < l1; i += 6) a[i / 6] = six_block(s1 + i);
    l1 = l1 / 6 + 1;
    for (i = 0; i < l2; i += 6) b[i / 6] = six_block(s2 + i);
    l2 = l2 / 6 + 1;
    std::memset(F, 0, MAX_SZ * 4);
    std::copy(a, a + l1, F);
    std::copy(b, b + l2, G);
    R1::polymul_ring(a, l1, b, l2);
    R2::polymul_ring(F, l1, G, l2);
    // Apply the Chinese Remainder Theorem
    constexpr int32_t X1 = R1::inv(R1::montify(R2::P));
    constexpr int32_t X2 = R2::inv(R2::montify(R1::P));
    constexpr int64_t M = int64_t(R1::P) * R2::P;
    for (int i = 0; i < l1 + l2 + 1; ++i) {
        int64_t t1 = R1::unmontify(R1::mul(a[i], X1)) * int64_t(R2::P);
        int64_t t2 = R2::unmontify(R2::mul(F[i], X2)) * int64_t(R1::P);
        R[i] = t1 + t2;
        R[i] = R[i] < M? R[i]: R[i] - M;
    }
    for (i = 0; i < l1 + l2 + 1; ++i) {
        R[i + 1] += R[i] / 1000000;
        R[i] %= 1000000;
    }
    while (!R[--i] && i > 0);
    sprintf(s1, "%ld%n", R[i--], &t);
    for (int j = 5; j >= 0; --j) {
        for (int k = i, l = t; k >= 0; --k, l += 6)
                s1[l + j] = (R[k] % 10) | 48, R[k] /= 10;
    }
    s1[t + i * 6 + 6] = 0;
    return t + i * 6 + 6;
}

constexpr int SIZE = 300016;
int main() {
    alignas(32) char s1[SIZE * 2] = {0};
    char *s2 = s1 + SIZE;
    read(0, s1, SIZE * 2);
    int l1, l2 = 0;
    for (l1 = 0; s1[l1] != ' '; ++l1);
    for (l2 = 0; s1[l1 + 1 + l2] != '\n'; ++l2);
    s1[l1] = s1[l1 + 1 + l2] = 0;
    for (int i = l2 - 1; i >= 0; --i) {
        s2[i] = s1[l1 + 1 + i];
        s1[l1 + 1 + i] = 0;
    }
    int l = string_mul(s1, l1, s2, l2);
    write(1, s1, l);
    return 0;
}

// https://www.acmicpc.net/source/12416307
