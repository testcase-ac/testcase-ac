//code by dkim110807
#include <bits/stdc++.h>

using ll = long long;

template<ll mod>
struct ModInt {
    using M = ModInt;
    const static M G;
    ll v{};

    ModInt(ll _v = 0) { set_v(_v % mod + mod); }

    ~ModInt() = default;

    M &set_v(ll _v) {
        v = (_v < mod) ? _v : _v - mod;
        return *this;
    }

    explicit operator bool() const { return v != 0; }

    M operator-() const { return M() - *this; }

    M operator+(const M &r) const { return M().set_v(v + r.v); }

    M operator-(const M &r) const { return M().set_v(v + mod - r.v); }

    M operator*(const M &r) const { return M().set_v(v * r.v % mod); }

    M operator/(const M &r) const { return *this * r.inv(); }

    M &operator+=(const M &r) { return *this = *this + r; }

    M &operator-=(const M &r) { return *this = *this - r; }

    M &operator*=(const M &r) { return *this = *this * r; }

    M &operator/=(const M &r) { return *this = *this / r; }

    bool operator==(const M &r) const { return v == r.v; }

    bool operator!=(const M &r) const { return v != r.v; }

    explicit operator ll() const { return v; }

    [[nodiscard]] M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    constexpr static ll get_mod() { return mod; }

    [[nodiscard]] M inv() const { return pow(mod - 2); }

    friend std::ostream &operator<<(std::ostream &out, const M &r) { return out << r.v; }
};

constexpr ll mod = 1'000'000'007;

using MInt = ModInt<1'000'000'007>;

ll P;

ll pow(ll a, ll b, ll m) {
    ll c = 1;
    for (; b; b >>= 1) {
        if (b & 1) c = c * a % m;
        a = a * a % m;
    }
    return c;
}

class Polynomial {
public:
    std::vector<ll> a;

    explicit Polynomial(int n = 0) {
        a.resize(n + 1);
    }

    int deg() {
        for (; !a.empty() && a.back() == 0;) a.pop_back();
        return (int) a.size() - 1;
    }

    ll &operator[](int k) {
        return a[k];
    }

    const ll &operator[](int k) const {
        return a[k];
    }

    void resize(int deg) {
        a.resize(deg + 1);
    }

    Polynomial operator+(Polynomial &b) {
        int d = std::max(deg(), b.deg());
        Polynomial p(d);
        for (int i = 0; i <= d; i++) p[i] = ((i < a.size() ? a[i] : 0) + (i < b.a.size() ? b[i] : 0)) % P;
        return p;
    }

    Polynomial operator-(Polynomial &b) {
        int d = std::max(deg(), b.deg());
        Polynomial p(d);
        for (int i = 0; i <= d; i++) p[i] = ((i < a.size() ? a[i] : 0) - (i < b.a.size() ? b[i] : 0) + P) % P;
        return p;
    }

    Polynomial operator*(ll s) {
        int d = deg();
        Polynomial p(d);
        s = (s % P + P) % P;
        for (int i = 0; i <= d; i++) p[i] = a[i] * s % P;
        return p;
    }

    Polynomial operator<<(int s) {
        int d = deg();
        Polynomial p(d + s);
        for (int i = 0; i <= d; i++) p[i + s] = a[i];
        return p;
    }

    Polynomial operator*(Polynomial &b) {
        if (deg() == -1 || b.deg() == -1) return Polynomial(-1);
        int d = deg() + b.deg();
        Polynomial p(d);
        for (int i = 0; i <= deg(); i++) {
            for (int j = 0; j <= b.deg(); j++) {
                p[i + j] = (p[i + j] + a[i] * b[j] % P) % P;
            }
        }
        return p;
    }

    Polynomial operator%(Polynomial &b) {
        int d = deg(), bd = b.deg();
        Polynomial p(d);
        for (int i = 0; i <= d; i++) p[i] = a[i];
        ll inv = pow(b[bd], P - 2, P);
        for (int i = d; i >= bd; i--) {
            if (p[i] == 0) continue;
            ll t = p[i] * inv % P;
            for (int j = 0; j <= bd; j++) {
                p[i - j] -= t * b[bd - j] % P, p[i - j] += P, p[i - j] %= P;
            }
        }
        return p;
    }

    Polynomial operator/(Polynomial &b) {
        int d = deg(), bd = b.deg();
        Polynomial p(d), q(d - bd);
        for (int i = 0; i <= d; i++) p[i] = a[i];
        ll inv = pow(b[bd], P - 2, P);
        for (int i = d; i >= bd; i--) {
            if (p[i] == 0) continue;
            ll t = p[i] * inv % P;
            q[i - bd] = t;
            for (int j = 0; j <= bd; j++) {
                p[i - j] -= t * b[bd - j] % P, p[i - j] += P, p[i - j] %= P;
            }
        }
        return q;
    }

    static Polynomial gcd(Polynomial a, Polynomial b) {
        return b.deg() == -1 ? a : gcd(b, a % b);
    }

    Polynomial diff() {
        if (deg() <= 0) return Polynomial();
        Polynomial p(deg() - 1);
        for (int i = 0; i < deg(); i++) p[i] = a[i + 1] * (i + 1) % P;
        return p;
    }

    // Square-free factorization
    static std::vector<Polynomial> sff(Polynomial f) {
        std::vector<Polynomial> R(f.deg() + 1, Polynomial(0));
        for (auto &x: R) x[0] = 1;

        Polynomial fp = f.diff(), c;
        if (fp.deg() != -1) c = gcd(f, fp);
        else c = f;
        Polynomial w = f / c;

        int i = 1;
        while (w.deg() != 0) {
            Polynomial y = gcd(w, c);
            R[i++] = w / y;
            w = y, c = c / y;
        }

        if (c.deg() != 0) {
            assert(c.deg() % P == 0);
            Polynomial q(c.deg() / P);
            for (int j = 0; j <= c.deg(); j += P) {
                q[j / P] = c[j];
            }
            std::vector<Polynomial> v = sff(q);
            for (int j = 0; j < (int) v.size(); j++) {
                R[P * j] = R[P * j] * v[j];
            }
        }
        return R;
    }

    // Distinct-Degree Factorization
    static std::vector<std::pair<Polynomial, int>> ddf(Polynomial f) {
        std::vector<std::pair<Polynomial, int>> S;
        int i = 1;
        Polynomial p = f;

        Polynomial h(1), l(1);
        h[1] = 1, l[1] = P - 1;

        {
            auto tmp = h;
            for (ll exp = P - 1; exp; exp >>= 1) {
                if (exp & 1) h = h * tmp % p;
                tmp = tmp * tmp % p;
            }
        }

        while (p.deg() >= 2 * i) {
            Polynomial t = h + l, g;

            if (t.deg() == -1) g = p;
            else g = gcd(p, t);

            if (g.deg() != 0) {
                S.emplace_back(g, i);
                p = p / g;
            }

            i = i + 1;
            auto tmp = h;
            for (ll exp = P - 1; exp; exp >>= 1) {
                if (exp & 1) h = h * tmp % p;
                tmp = tmp * tmp % p;
            }
        }

        if (p.deg() != 0) S.emplace_back(p, p.deg());
        if (S.empty()) return {{f, 1}};

        return S;
    }

    friend std::ostream &operator<<(std::ostream &out, Polynomial &p) {
        for (int i = 0; i <= p.deg(); i++) {
            if (i != 0) out << " ";
            out << p[i];
        }
        return out;
    }
};

class miller_rabin {
public:
    using u64 = uint64_t;

    bool is_prime(u64 n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 6 != 1 && n % 6 != 5) return false;

        const auto &base = n < 4759123141ull ? base_small : base_large;
        const int s = __builtin_ctzll(n - 1);
        const u64 d = n >> s;

        for (const auto &b: base) {
            if (b >= n) break;
            if (check_composite(n, b, d, s)) return false;
        }
        return true;
    }

    static u64 pow(u64 a, u64 p, u64 m) {
        u64 ret = 1;
        for (; p; p >>= 1) {
            if (p & 1) ret = mul(ret, a, m);
            a = mul(a, a, m);
        }
        return ret;
    }

protected:
    static u64 mul(u64 a, u64 b, u64 m) {
        int64_t ret = a * b - m * u64(1.L / m * a * b);
        return ret + m * (ret < 0) - m * (ret >= int64_t(m));
    }

private:
    const std::vector<u64> base_small = {2, 7, 61}, base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    static bool check_composite(u64 n, u64 x, u64 d, int s) {
        x = pow(x, d, n);
        if (x == 1 || x == n - 1) return false;
        while (--s) {
            x = mul(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };
};

class pollard_rho : miller_rabin {
private:
    static u64 pollard(u64 n) {
        auto f = [&](u64 x) { return mul(x, x, n) + 1; };
        u64 x = 0, y = 0, prd = 2, i = 1, q;
        for (int t = 30; t++ % 40 || std::gcd(prd, n) == 1; x = f(x), y = f(f(y))) {
            if (x == y) x = ++i, y = f(x);
            if ((q = mul(prd, x > y ? x - y : y - x, n))) prd = q;
        }
        return std::gcd(prd, n);
    }

public:
    std::vector<u64> factorize(u64 n) {
        if (n == 1) return {};
        if (n == 2 || n == 3 || n == 5) return {n};
        if (is_prime(n)) return {n};

        const u64 x = pollard(n);
        auto l = factorize(x), r = factorize(n / x);

        decltype(l) ret(l.size() + r.size());
        merge(l.begin(), l.end(), r.begin(), r.end(), ret.begin());
        return ret;
    }
} pollard;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int64_t n;
    std::cin >> P >> n;

    Polynomial f(-1);
    std::vector<ll> powers;
    for (ll m = n, a = 1; m; m /= P, a *= P) f.a.push_back(m % P), powers.push_back(a);

    auto fun = [&](ll p, ll k) -> MInt {
        return MInt(p) * (MInt(p).pow(2 * k) - 1) / MInt(p + 1) + 1;
    };

    auto notfun = [&](ll n, ll k) {
        auto g = [&](ll a) {
            assert(n * (k - 1) < powers.size());
            if (powers[a] >= k) return powers[n * (k - 1)];
            return powers[n * (k - 1 - (k - 1) / powers[a])];
        };
        std::vector<MInt> v;
        for (int i = 0; i < k; i++) {
            MInt s = 0;
            if (i >= 0) s += g(i - 0);
            if (i >= 1) s -= g(i - 1);
            v.push_back(s);
        }
        return v;
    };

    std::map<ll, std::vector<MInt>> map;

    auto update = [&](ll prime, const std::vector<MInt> &v) {
        if (!map.count(prime)) map[prime] = {1};
        auto &q = map[prime];
        std::vector<MInt> res(std::max(q.size(), v.size()));
        for (int i = 0; i < q.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                res[std::max(i, j)] += q[i] * v[j];
            }
        }
        map[prime] = res;
    };

    MInt ans = MInt(P).pow(f.deg()).inv();
    auto sff = Polynomial::sff(f);
    for (int exp = 1; exp < sff.size(); exp++) {
        auto &tmp = sff[exp];
        if (tmp.deg() < 0) continue;
        auto ddf = Polynomial::ddf(tmp);
        for (auto &[q, deg]: ddf) {
            assert(deg > 0 && q.deg() % deg == 0);
            int cnt = q.deg() / deg;
            if (cnt == 0) continue;
            auto fact = pollard.factorize(powers[deg] - 1);
            for (int i = 0, j = 0; i < fact.size(); i = j) {
                for (; j < fact.size() && fact[i] == fact[j]; j++);
                std::vector<MInt> v;
                MInt a = 1, b = 0;
                for (int k = 0; k <= j - i; k++) {
                    v.push_back(a - b);
                    a *= (ll) fact[i];
                    if (b == 0) b = 1;
                    else b *= (ll) fact[i];
                }
                for (int rep = cnt; rep--;) update((ll) fact[i], v);
            }
            auto v = notfun(deg, exp);
            for (int rep = cnt; rep--;) {
                update(P, v);
            }
        }
    }
    for (auto &[p, v]: map) {
        MInt sum = 0, m = 1;
        for (const auto &x: v) sum += m * x, m *= p;
        ans *= sum;
    }
    std::cout << ans << "\n";
}
