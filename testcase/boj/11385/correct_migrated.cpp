// #define BENCH(...) __VA_ARGS__
#define BENCH(...) (void*)(0);

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,bmi2")

#pragma clang attribute push(__attribute__((target("avx,avx2,bmi2"))), apply_to=function)

#include <unistd.h>
#include <cstring>
#include <array>
#include <algorithm>
#include <cassert>

#include <iostream>
#include <chrono>

using namespace std;

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

template <int IN_SZ, int OUT_SZ>
struct PosixIO {
    array<u8, IN_SZ> inbuf;
    int insz = 0, inpos = 0;
    bool is_eof = false;
   
    array<u8, OUT_SZ> outbuf;
    int outsz = 0;

    void flush() {
        if (outsz > 0) { int _ = write(STDOUT_FILENO, outbuf.data(), outsz); }
        outsz = 0;
    }

    constexpr bool is_digit(u8 ch) { return '0' <= ch && ch <= '9'; }

    void refill_append() {
        //if (is_eof) { return; }

        // shrink buffer
        for (int i = 0; i < insz-inpos; i++) { inbuf[i] = inbuf[i + inpos]; }
        fill(inbuf.data()+insz-inpos, inbuf.data()+insz, 0);
        insz -= inpos; inpos = 0;

        // append
        int len = ::read(STDIN_FILENO, inbuf.data()+insz, inbuf.size()-insz);
        is_eof = len < inbuf.size()-insz;
        insz += len;
    }

    void skip(int cnt=1) {
        //if (!is_eof && inpos + cnt > insz) { refill_append(); }
        inpos += cnt;
    }

    // Peek raw bytes as type T
    template <class T = u8>
    T peek() {
        //if (!is_eof && inpos + sizeof(T) > insz) { refill_append(); }
        T res;
        memcpy(&res, inbuf.data() + inpos, sizeof(T));
        return res;
    }

    // Read raw bytes as type T
    template <class T = u8>
    T read() {
        T val = peek<T>();
        skip(sizeof(T));
        return val;
    }

    void skip_until_numeric() {
        while (!is_digit(peek()) && peek() != '-') {
            inpos++;
        }
    }

    template <class T, bool skip_next = true>
    T read_num() {
        T x = 0;
        bool neg = peek() == '-';
        if (neg) { skip(); }
        while (true) {
            char ch = peek();
            if (!is_digit(ch)) { break; }
            skip();
            x = 10*x + ch-'0';
        }

        if constexpr (skip_next) { skip(); }
        return neg ? -x : x;
    }

    // NOTE: This assumes 0 <= x <= 99999999
    u32 read_u32() {
        u64 bytes = peek<u64>(); // load little endian
        int len = __builtin_ctzll(~bytes & 0x1010101010101010) / 8; // all digit chars have the bit 0x10; ' ' and '\n' don't
        bytes <<= 8 * (8-len); // truncate after the delimiter
        bytes &= 0x0F0F0F0F0F0F0F0F; // the lower nibble of a digit char == the digit they represent
        
        // instead of repeating x = 10x + bytes[i], parallelize the process with bit ops

        // bytes[2i..2i+2] = bytes[2i] + 10*bytes[2i+1] for i in 0..4
        bytes += (bytes << 8) * 10;
        bytes = (bytes >> 8) & 0x00FF00FF00FF00FF; // zero out used slots

        // bytes[4i..4i+4] = bytes[4i..4i+2] + 100*bytes[4i+2..4i+4] for i in 0..2
        bytes += (bytes << 16) * 100;
        bytes = (bytes >> 16) & 0x0000FFFF0000FFFF; // zero out used slots

        // bytes[8i..8i+8] = bytes[8i..8i+4] + 10000*bytes[8i+4..8i+8] for i in 0..1
        bytes += (bytes << 32) * 10000;
        bytes = (bytes >> 32) & 0x00000000FFFFFFFF; // zero out used slots

        skip(len+1);
        return u32(bytes);
    }

    void write_char(char ch) {
        outbuf[outsz++] = ch;
    }

    template <class T>
    void write_num(T x) {
        if (x < 0) {
            outbuf[outsz++] = '-';
            x = -x;
        }

        int begin = outsz;
        if (x == 0) {
            outbuf[outsz++] = '0';
            return;
        }
        while (x > 0) {
            outbuf[outsz++] = '0' + x % 10;
            x /= 10;
        }
        reverse(outbuf.begin()+begin, outbuf.begin()+outsz);
    }
};
PosixIO<16001000, 32> io;



// Source: https://en.algorithmica.org/hpc/number-theory/montgomery/x
// Despite taking MOD, it does arithmetic modulo 2MOD (for performance reasons).
template <u64 MOD>
struct ModArith64 {
    struct Mont64 { u64 x; };

    static constexpr u64 MOD_INV = []() {
        u64 res = 1;
        for (int i = 0; i < 6; i++) {
            res *= 2 - MOD*res;
        }
        return res;
    }();

    static constexpr Mont64 R = Mont64 { (u128(1) << 64) % MOD }; // = transform(1)
    static constexpr Mont64 R2 = Mont64 { (u128(R.x) << 64) % MOD }; // = transform(transform(1).x)
    
    // divide by R = 2^64
    static constexpr u64 reduce_raw(u128 x) {
        // (x - MOD*(x*MOD_INV % R))/R
        //   = x/R - MOD*(x*MOD_INV % R)/R
        u64 mod_r = u64(x)*MOD_INV;
        u64 term1 = x >> 64;
        u64 term2 = (u128(MOD)*mod_r) >> 64;
        return term1 - term2 + MOD; // -mod < term1 - term2 < mod; shift to [0, 2MOD)
    }
    static constexpr u64 reduce(Mont64 x) { return reduce_raw(x.x); }

    // multiply by R = 2^64
    static constexpr u64 transform_raw(u64 x) { return modmul(x, R2); }
    static constexpr Mont64 transform(u64 x) { return Mont64 { transform_raw(x) }; }

    static constexpr u64 modmul(u64 a, Mont64 b) { return reduce_raw(u128(a)*b.x); }
    static constexpr Mont64 modmul(Mont64 a, Mont64 b) { return Mont64 { reduce_raw(u128(a.x)*b.x) }; }

    static constexpr u64 MOD2 = 2*MOD;
    static constexpr u64 modadd(u64 a, u64 b) {
        u64 x = a + b;
        return x - (MOD2 & -u64(x >= MOD2));
    }
    static constexpr Mont64 modadd(Mont64 a, Mont64 b) { return Mont64 { modadd(a.x, b.x) }; }
    static constexpr u64 modsub(u64 a, u64 b) {
        u64 x = a - b;
        return x + (MOD2 & -u64(a < b));
    }
    static constexpr Mont64 modsub(Mont64 a, Mont64 b) { return Mont64 { modsub(a.x, b.x) }; }
    static constexpr Mont64 modpow_transform(u64 b, u64 e) {
        Mont64 b_mont = transform(b);
        Mont64 res = transform(1);
        while (e > 0) {
            if (e & 1) { res = modmul(res, b_mont); }
            b_mont = modmul(b_mont, b_mont);
            e >>= 1;
        }
        return res;
    }
    static constexpr u64 modpow(u64 b, u64 e) { return reduce(modpow_transform(b, e)); }
    
    static constexpr u64 mod(u64 x) { return x - ((2*MOD) & -u64(x >= 2*MOD)); }
    static constexpr Mont64 mod(Mont64 x) { return Mont64 { mod(x.x) }; }
    static constexpr u64 mod_proper(u64 x) { return x - (MOD & -u64(x >= MOD)); }
    static constexpr Mont64 mod_proper(Mont64 x) { return Mont64 { mod_proper(x.x) }; }
};

// Idea by @byeongkeunahn, https://www.acmicpc.net/source/87853143

/**
 * We use a different layout of twiddle factors, which I will refer to as the "deferred form".
 * 
 * Example when n = 18 (base_sz = 1).
 * 
 * Let's look at only the exponent of each element.
 *       S0: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 * 
 * The first stage of the DIF has the following twiddle factors (assume all are divided by 18):
 *       S1: 0 0 0 0 0 0|0 1 2 3 4 5|0 2 4 6 8 10
 * 
 * We split them in two parts like this, aligned to the subsz:
 *     S1-A: 0 0 0 0 0 0|0 0 2 2 4 4|0 0 4 4 8 8
 *     S1-B: 0 0 0 0 0 0|0 1 0 1 0 1|0 2 0 2 0 2
 * 
 * S1-A must be applied right away before going to S2 (otherwise different exponents mix).
 * But does S1-B have to too? Nope. It exactly matches the stride of the stage, so they are carried over S2 intact.
 *  Applied:               1   1   1   2   2   2
 *       S2: 0 0|0 3|0 6|0 1|0 4|0 7|0 2|0 5|0 8
 * 
 *     S2-A: 0 0|0 3|0 6|0 1|0 4|0 7|0 2|0 5|0 8
 *     S2-B: 0 0|0 0|0 0|0 0|0 0|0 0|0 0|0 0|0 0    (Nothing to split here, S2-B is empty)
 * 
 *       S3: 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0    (Complete)
 * 
 * This, as you can see, defers all intra-block twiddle factors to the later stages.
 * In effect, twiddle factors can stay constant inside each block.
 * This allows us to load less twiddle factors in the nested loop in CooleyTukey::ntt.
 * 
 * O(n log n) twiddle factor loads:
 *     for i in [0, n), stride=sz:
 *         for j in [0, subsz), stride=1:
 *             w = load(j)
 *             butterfly(arr[j], w)
 * 
 * O(n) twiddle factor loads:
 *     for i in [0, n), stride=sz:
 *         w = load(i)
 *         for j in [0, subsz), stride=1:
 *             butterfly(arr[j], w)
 * 
 * In addition to this, notice how the first twiddle factor in a stage is always 1.
 * Twiddle factors can be entirely skipped for the first block, shaving a few percents off of runtime in large stages.
 * 
 * First block optimization:
 *     for j in [0, subsz), stride=1:
 *         butterfly(arr[j], 1)
 *     for i in [sz, n), stride=sz:
 *         w = load(i)
 *         for j in [0, subsz), stride=1:
 *             butterfly(arr[j], w)
 * 
 * 진짜 댕어렵네요;;
 */

struct NTTStage { int subsz, radix; };

template <u64 MOD, u64 W, bool DIF>
struct CooleyTukey {
    using MA = ModArith64<MOD>;
    using Mont = typename MA::Mont64;
    
    // A little helper for nicer code
    template <bool ACTIVE>
    constexpr u64 option_modmul(u64 a, Mont b) const {
        if constexpr (ACTIVE) { return MA::modmul(a, b); }
        else { return a; }
    }

    NTTStage* plan;
    int len_p, n;

    CooleyTukey(NTTStage* plan, int len_p, int n) : plan(plan), len_p(len_p), n(n) {}

    template <bool FBO>
    void butterfly_2(
        u64& __restrict a0, u64& __restrict a1, 
        Mont w1
    ) const {
        u64 in0 = a0, in1 = a1;

        if constexpr (!DIF) {
            a0 = MA::modadd(in0, in1);
            a1 = option_modmul<!FBO>(in0 + 2*MOD-in1, w1);
        } else {
            in0 = MA::mod(in0);
            in1 = option_modmul<!FBO>(in1, w1);
            a0 = MA::modadd(in0, in1);
            a1 = MA::modsub(in0, in1);

            // optimization for radix-2 only transformation
            // a0 = in0 + in1;
            // a1 = in0 + 2*MOD-in1;
        }
    }

    static constexpr Mont ROOT3 = MA::modpow_transform(W, (MOD-1)/3);
    
    template <bool FBO>
    void butterfly_3(
        u64& __restrict a0, u64& __restrict a1, u64& __restrict a2, 
        Mont w1, Mont w2
    ) const {
        u64 in0 = a0, in1 = a1, in2 = a2;

        if constexpr (!FBO && DIF) {
            in1 = MA::modmul(in1, w1);
            in2 = MA::modmul(in2, w2);
        }

        u64 w_d12 = MA::modmul(MA::modsub(in1, in2), ROOT3);

        a0 = MA::modadd(in0, MA::modadd(in1, in2));
        a1 = option_modmul<!FBO && !DIF>(MA::modadd(MA::modsub(in0, in2), w_d12), w1);
        a2 = option_modmul<!FBO && !DIF>(MA::modsub(MA::modsub(in0, in1), w_d12), w2);
    }
    
    static constexpr Mont ROOT4 = MA::modpow_transform(W, (MOD-1) >> 2);

    template <bool FBO>
    void butterfly_4(
        u64& __restrict a0, u64& __restrict a1, u64& __restrict a2, u64& __restrict a3, 
        Mont w1, Mont w2, Mont w3
    ) const {
        u64 in0 = a0, in1 = a1, in2 = a2, in3 = a3;

        if constexpr (!FBO && DIF) {
            in1 = MA::modmul(in1, w1);
            in2 = MA::modmul(in2, w2);
            in3 = MA::modmul(in3, w3);
        }

        u64 s02 = MA::modadd(in0, in2);
        u64 d02 = MA::modsub(in0, in2);
        u64 i_d13 = MA::modmul(in1 + 2*MOD-in3, ROOT4);
        u64 s13 = MA::modadd(in1, in3);

        a0 = MA::modadd(s02, s13);
        a1 = option_modmul<!FBO && !DIF>(MA::modadd(d02, i_d13), w1);
        a2 = option_modmul<!FBO && !DIF>(MA::modsub(s02, s13), w2);
        a3 = option_modmul<!FBO && !DIF>(MA::modsub(d02, i_d13), w3);

        // return { out0, out1, out2, out3 };
    }
    
    static constexpr Mont ROOT6 = MA::modpow_transform(W, (MOD-1)/6);

    template <bool FBO>
    void butterfly_6(
        u64& __restrict a0, u64& __restrict a1, u64& __restrict a2, u64& __restrict a3, u64& __restrict a4, u64& __restrict a5, 
        Mont w1, Mont w2, Mont w3, Mont w4, Mont w5
    ) const {
        u64 in0 = a0, in1 = a1, in2 = a2, in3 = a3, in4 = a4, in5 = a5;

        if constexpr (!FBO && DIF) {
            in1 = MA::modmul(in1, w1);
            in2 = MA::modmul(in2, w2);
            in3 = MA::modmul(in3, w3);
            in4 = MA::modmul(in4, w4);
            in5 = MA::modmul(in5, w5);
        }

        u64 s03 = MA::modadd(in0, in3);
        u64 d03 = MA::modsub(in0, in3);
        u64 s14 = MA::modadd(in1, in4);
        u64 d14 = MA::modsub(in1, in4);
        u64 s25 = MA::modadd(in2, in5);
        u64 d25 = MA::modsub(in2, in5);

        u64 w_ds14s25 = MA::modmul(MA::modsub(s14, s25), ROOT6);
        u64 w_sd14d25 = MA::modmul(MA::modadd(d14, d25), ROOT6);

        a0 = MA::modadd(s03, MA::modadd(s14, s25));
        a1 = option_modmul<!FBO && !DIF>(MA::modadd(MA::modsub(d03, d25), w_sd14d25), w1);
        a2 = option_modmul<!FBO && !DIF>(MA::modadd(MA::modsub(s03, s14), w_ds14s25), w2);
        a3 = option_modmul<!FBO && !DIF>(MA::modsub(d03, MA::modsub(d14, d25)), w3);
        a4 = option_modmul<!FBO && !DIF>(MA::modsub(MA::modsub(s03, s25), w_ds14s25), w4);
        a5 = option_modmul<!FBO && !DIF>(MA::modsub(MA::modadd(d03, d14), w_sd14d25), w5);
    }

    template <bool FBO>
    void block_2(u64* __restrict arr, Mont* __restrict tf, int subsz) {
        u64* __restrict a0 = arr;
        u64* __restrict a1 = arr + subsz;

        Mont w1;
        if constexpr (!FBO) { w1 = *tf; }

        for (int j = 0; j < subsz; j++) {
            asm volatile("# Radix2 Start");
            butterfly_2<FBO>(
                a0[j], a1[j], 
                w1
            );
            asm volatile("# Radix2 End");
        }
    }

    template <bool FBO>
    void block_3(u64* __restrict arr, Mont* __restrict tf, int subsz) {
        u64* __restrict a0 = arr;
        u64* __restrict a1 = arr + subsz;
        u64* __restrict a2 = arr + 2*subsz;

        Mont w1, w2;
        if constexpr (!FBO) {
            w1 = *tf;
            w2 = MA::modmul(w1, w1);
        }

        for (int j = 0; j < subsz; j++) {
            asm volatile("# Radix3 Start");
            butterfly_3<FBO>(
                a0[j], a1[j], a2[j], 
                w1, w2
            );
            asm volatile("# Radix3 End");
        }
    }

    template <bool FBO>
    void block_4(u64* __restrict arr, Mont* __restrict tf, int subsz) {
        u64* __restrict a0 = arr;
        u64* __restrict a1 = arr + subsz;
        u64* __restrict a2 = arr + 2*subsz;
        u64* __restrict a3 = arr + 3*subsz;

        Mont w1, w2, w3;
        if constexpr (!FBO) {
            w1 = *tf;
            w2 = MA::modmul(w1, w1);
            w3 = MA::modmul(w1, w2);
        }

        for (int j = 0; j < subsz; j++) {
            asm volatile("# Radix4 Start");
            butterfly_4<FBO>(
                a0[j], a1[j], a2[j], a3[j], 
                w1, w2, w3
            );
            asm volatile("# Radix4 End");
        }
    }

    // Not inlining faster for radix-6?
    template <bool FBO>
    __attribute__((noinline)) void block_6(u64* __restrict arr, Mont* __restrict tf, int subsz) {
        u64* __restrict a0 = arr;
        u64* __restrict a1 = arr + subsz;
        u64* __restrict a2 = arr + 2*subsz;
        u64* __restrict a3 = arr + 3*subsz;
        u64* __restrict a4 = arr + 4*subsz;
        u64* __restrict a5 = arr + 5*subsz;

        Mont w1, w2, w3, w4, w5;
        if constexpr (!FBO) {
            w1 = *tf;
            w2 = MA::modmul(w1, w1);
            w3 = MA::modmul(w1, w2);
            w4 = MA::modmul(w2, w2);
            w5 = MA::modmul(w2, w3);
        }

        for (int j = 0; j < subsz; j++) {
            asm volatile("# Radix6 Start");
            butterfly_6<FBO>(
                a0[j], a1[j], a2[j], a3[j], a4[j], a5[j], 
                w1, w2, w3, w4, w5
            );
            asm volatile("# Radix6 End");
        }
    }

    void ntt(u64* __restrict arr, Mont* __restrict tf) {
        for (int _i = 0; _i < len_p; _i++) {
            int i_p = DIF ? len_p-1-_i : _i;

            auto [subsz, radix] = plan[i_p];
            int sz = subsz*radix;

            // 진짜 byeongkeunahn님 대체 뭐 하시는 분인가요... ㄷㄷㄷㄷㄷ
            switch (radix) {
                case 2: {
                    block_2<true>(arr, tf, subsz); tf++;
                    for (int i = sz; i < n; i += sz) {
                        block_2<false>(arr + i, tf, subsz); tf++;
                    }
                    break;
                }
                case 3: {
                    block_3<true>(arr, tf, subsz); tf++;
                    for (int i = sz; i < n; i += sz) {
                        block_3<false>(arr + i, tf, subsz); tf++;
                    }
                    break;
                }
                case 4: {
                    block_4<true>(arr, tf, subsz); tf++;
                    for (int i = sz; i < n; i += sz) {
                        block_4<false>(arr + i, tf, subsz); tf++;
                    }
                    break;
                }
                case 6: {
                    block_6<true>(arr, tf, subsz); tf++;
                    for (int i = sz; i < n; i += sz) {
                        block_6<false>(arr + i, tf, subsz); tf++;
                    }
                    break;
                }
                default:
                    assert(0);
            }
        }

        for (int i = 0; i < n; i++) { arr[i] = MA::mod_proper(MA::mod(arr[i])); }
    }
};

template <u64 MOD, u64 W, int MAX_N, int BASE_SZ = -1>
struct NTTConvolutor {
    using MA = ModArith64<MOD>;
    using Mont = typename MA::Mont64;

    static constexpr u64 W_INV = MA::modpow(W, MOD-2);

    alignas(128) array<Mont, MAX_N> tf;
    int n, base_sz, base_radix;

    array<NTTStage, 64> plan;
    int len_p;

    void init(int base_sz, initializer_list<int> radices) {
        if constexpr (BASE_SZ != -1) { assert(base_sz == BASE_SZ); }

        this->base_sz = base_sz;
        this->base_radix = *radices.begin();
        this->n = base_sz;
        for (int x : radices) { n *= x; }

        len_p = 0; int len_w = 0;
        int subsz = base_sz;
        for (int radix : radices) {
            plan[len_p] = { subsz, radix };
            len_p++; len_w += subsz;

            subsz *= radix;
        }

        assert(len_p <= plan.size());
        assert(len_w <= tf.size());
    }

    int fill_tf_stage(Mont* __restrict out, int i_p, u64 w0) {
        u64 cur_exp = (MOD-1)/plan[i_p].radix;

        out[0] = MA::R; int tf_sz = 1;
        for (int k = i_p+1; k < len_p; k++) {
            // Required block twiddle
            //  = (current stage twiddle) * (subsize)
            //  = (n/parent_size) * (size/radix)
            //  = (n/(size*parent_radix)) * (size/radix)
            //  = n/parent_radix/radix
            // and keep dividing that by ancestor radices.

            int radix = plan[k].radix;
            cur_exp /= radix;
            Mont w = MA::modpow_transform(w0, cur_exp);
            for (int i = tf_sz; i < radix*tf_sz; i++) {
                out[i] = MA::modmul(out[i-tf_sz], w);
            }
            tf_sz *= radix;
        }

        return tf_sz;
    }

    void conv_naive(int sz, u64* __restrict dst, u64* __restrict src, u64* __restrict tmp, Mont wrap, Mont mult_mont2) {
        if constexpr (BASE_SZ != -1) {
            // GCC you should probably unroll less!
            if (sz != BASE_SZ) { __builtin_unreachable(); }
        }

        for (int i = 0; i < sz; i++) { tmp[i] = MA::modmul(dst[i], mult_mont2); }
        for (int i = 0; i < sz; i++) {
            // Cyclic convolution
            // For explanation, see ::conv()
            u128 acc = 0;
            for (int j = i+1; j < sz; j++) { acc += u128(src[i-j+sz]) * tmp[j]; }
            acc = u128(wrap.x) * MA::reduce_raw(acc);
            for (int j = 0; j <= i; j++) { acc += u128(src[i-j]) * tmp[j]; }
            dst[i] = MA::reduce_raw(acc);
        }
    }

    void conv(u64* arr_a, u64* arr_b) {
BENCH(
        auto t1 = std::chrono::high_resolution_clock::now();
)
        auto fw_ntt = CooleyTukey<MOD, W, true>(plan.data(), u64(len_p), n);
        auto bw_ntt = CooleyTukey<MOD, W_INV, false>(plan.data(), u64(len_p), n);
        
        int tf_sz = 0;
        for (int i_p = len_p-1; i_p >= 1; i_p--) {
            tf_sz += fill_tf_stage(tf.data()+tf_sz, i_p, W);
        }
        int base_tf_offset = tf_sz;
        fill_tf_stage(tf.data()+tf_sz, 0, W);
        
        fw_ntt.ntt(arr_a, tf.data());
        fw_ntt.ntt(arr_b, tf.data());
BENCH(
        auto t2 = std::chrono::high_resolution_clock::now();
)
        Mont n_inv = MA::modpow_transform(n/base_sz, MOD-2);
        Mont n_inv_mont2 = MA::transform(n_inv.x);

        /**
         * Instead of doing pointwise multiplication, we stop early at base_sz
         * so that it can be handled with a naive (but with less constant factor) cyclic convolution.
         * 
         * For example, n=8, base_sz=4 and radix-2:
         * 
         * A In: 1 2 3 4 0  0    0    0
         * A S1: 1 2 3 4 1 2w 3w^2 4w^3
         *               ^^^^^^^^^^^^^^ Convolve this
         * B in: 5 6 7 8 0  0    0    0
         * B S1: 5 6 7 8 5 6w 7w^2 8w^3
         *               ^^^^^^^^^^^^^^ With this
         * 
         * The task is to circular convolve [1 2w 3w^2 4w^3] and [5 6w 7w^2 8w^3].
         *
         * The second term in this convolution, for example, is:
         *     1   2w 3w^2 4w^3
         *    6w    5 8w^3 7w^2 
         *            ^^^^ ^^^^    Multiplied by w^4 = -1
         * 
         * This would have worked if the terms were stored as it is.
         * But here, the terms are stored in the deferred form
         * as [1 2 3 4] and [5 6 7 8], where w is deferred.
         *     1    2    3    4
         *     6    5    8    7
         *               ^    ^    Missing -1
         * 
         * To compensate for this exponent wraparound, we need to multiply the wrapped terms
         * by the corresponding deferred roots of unity (-1 for the case above).
         */

        array<u64, 64> tmp;
        Mont unity = MA::modpow_transform(W, (MOD-1)/base_radix);

        Mont* __restrict tf_base = tf.data() + base_tf_offset;
        for (int i = 0; i < n/base_sz/base_radix; i++) {
            Mont wrap = tf_base[i];
            u64* group_a = arr_a + i*base_sz*base_radix;
            u64* group_b = arr_b + i*base_sz*base_radix;
            for (int j = 0; j < base_radix; j++) {
                u64* block_a = group_a + j*base_sz;
                u64* block_b = group_b + j*base_sz;
                // also don't forget to divide by n
                conv_naive(base_sz, block_a, block_b, tmp.data(), wrap, n_inv_mont2);
                wrap = MA::modmul(wrap, unity);
            }
        }

        tf_sz = 0;
        for (int i_p = 0; i_p < len_p; i_p++) {
            tf_sz += fill_tf_stage(tf.data()+tf_sz, i_p, W_INV);
        }
BENCH(
        auto t3 = std::chrono::high_resolution_clock::now();
)
        bw_ntt.ntt(arr_a, tf.data());
BENCH(
        auto t4 = std::chrono::high_resolution_clock::now();

        cout << "New: Two NTTs took " << (t2 - t1).count()/1e6
            << " ms; Multiplication took " << (t3 - t2).count()/1e6
            << " ms; Final NTT took " << (t4 - t3).count()/1e6
            << " ms" << endl;
        cout << "Total: " << (t4 - t1).count()/1e6 << " ms" << endl;
)
    }
};

constexpr u64 MOD = 1000008843169628161;
constexpr u64 W = 67; // uh it's a coincidence
constexpr u64 BASE_SZ = 8;

NTTConvolutor<MOD, W, 1 << 21, BASE_SZ> ntt;
alignas(128) array<u64, 1 << 21> buf1, buf2;
int main() {
    io.refill_append();
    int n = io.read_u32();
    int m = io.read_u32();
    for (int i = 0; i <= n; i++) { buf1[i] = io.read_u32(); }
    for (int i = 0; i <= m; i++) { buf2[i] = io.read_u32(); }
    
    // benchmark different factorizations
    ntt.init(BASE_SZ, { 4,4,4,4,4,4,4,4,4 });
    // ntt.init(8, { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 });
    // ntt.init(1, { 2,2,2,2,3,6,6,6,6,6,6 });
    // ntt.init(15, { 3,6,6,6,6,6,6 });
    // ntt.init(BASE_SZ, { 3,6,6,6,6,6,6 });
    // ntt.init(15, { 3,3,3,3,3,3,3,4,4,4 });
    ntt.conv(buf1.data(), buf2.data());
    u64 acc = 0;
    for (int i = 0; i <= n+m; i++) {
        acc ^= buf1[i];
    }

    io.write_num(acc);
    io.flush();

    return 0;
}

#pragma clang attribute pop
