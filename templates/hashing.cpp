#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <atcoder/all>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace std::literals::string_literals;
using namespace __gnu_pbds;
using namespace atcoder;
using namespace boost::multiprecision;

using i32 = int;
using i64 = long long;
using i128 = int128_t;
using u32 = unsigned int;
using u64 = unsigned long long;
using usize = size_t;
using f32 = float;
using f64 = double;
using f80 = long double;

template <typename T>
using twin = tuple<T, T>;

template <typename T>
using triplet = tuple<T, T, T>;

template <typename T>
using quadruplet = tuple<T, T, T, T>;

template <typename T>
using quintuplet = tuple<T, T, T, T, T>;

template <typename T, typename Compare = less<T>>
using statistic_set = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

template <typename K, typename V, typename Compare = less<K>>
using statistic_map = tree<K, V, Compare, rb_tree_tag, tree_order_statistics_node_update>;

constexpr auto mod = static_cast<i128>(0x1fffffffffffffffull);
constexpr auto base = static_cast<i128>(10007);

auto modpow(i128 x, i128 k, i128 mod) -> i128
{
    auto y = static_cast<i128>(1);
    while (k > 0)
    {
        if (k & 1)
        {
            y = y * x % mod;
        }
        x = x * x % mod;
        k >>= 1;
    }
    return y;
}

auto op(i128 l, i128 r) -> i128
{
    return (l + r) % mod;
}

auto e() -> i128
{
    return static_cast<i128>(0);
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0, m = 0;
    cin >> n >> m;

    auto d = statistic_set<i128>();

    auto h = [&](i128 x) -> i128
    {
        auto k = d.order_of_key(x);
        return modpow(base, k, mod);
    };

    auto v = vector<i128>(n);
    for (auto &x : v)
    {
        cin >> x;
        d.insert(x);
    }

    auto w = vector<i128>(n);
    for (auto &x : w)
    {
        cin >> x;
        d.insert(x);
    }

    auto s = vector<i128>();
    s.reserve(n);
    for (auto x : v)
    {
        s.push_back(h(x));
    }

    auto t = vector<i128>();
    t.reserve(n);
    for (auto x : w)
    {
        t.push_back(h(x));
    }

    auto f = segtree<i128, op, e>(s);
    auto g = segtree<i128, op, e>(t);

    for (auto i = 0; i < m; ++i)
    {
        auto l = 0, r = 0, p = 0, q = 0;
        cin >> l >> r >> p >> q;
        --l, --p;

        cout << (r - l == q - p && f.prod(l, r) == g.prod(p, q) ? "Yes" : "No") << '\n';
    }

    return 0;
}
