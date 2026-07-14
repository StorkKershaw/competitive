#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <atcoder/all>

using namespace std;
using namespace std::string_literals;
using namespace std::complex_literals;
using namespace __gnu_pbds;
using namespace atcoder;

using i32 = int;
using i64 = long long;
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

auto factorize(i64 n) -> vector<twin<i64>>
{
    auto magnitude = abs(n);

    auto p = vector(0, make_tuple(0ll, 0ll));
    auto q = vector(0, make_tuple(0ll, 0ll));
    for (auto i = 1ll; i * i <= magnitude; ++i)
    {
        if (magnitude % i != 0)
        {
            continue;
        }

        p.emplace_back(i, n / i);
        if (i * i != magnitude)
        {
            auto d = magnitude / i;
            q.emplace_back(d, n / d);
        }
    }
    p.insert(p.end(), q.rbegin(), q.rend());

    auto r = vector(0, make_tuple(0ll, 0ll));
    for (auto it = p.rbegin(); it != p.rend(); ++it)
    {
        auto [a, b] = *it;
        r.emplace_back(-a, -b);
    }
    r.insert(r.end(), p.begin(), p.end());
    return r;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto x = 0ll;
    cin >> x;

    auto v = factorize(4 * x - 1);
    auto w = vector(0, 0ll);
    for (auto [p, q] : v)
    {
        auto r = div(p - q - 2, 4ll);
        if (r.rem)
        {
            continue;
        }
        w.emplace_back(r.quot);
    }

    sort(w.begin(), w.end());
    w.erase(unique(w.begin(), w.end()), w.end());

    auto out = to_string(w.size());
    out += '\n';
    for (auto x : w)
    {
        out += to_string(x);
        out += ' ';
    }
    cout << out << '\n';

    return 0;
}
