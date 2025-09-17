#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <atcoder/all>

using namespace std;
using namespace std::literals::string_literals;
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

template <typename T>
auto trisect(i64 l, i64 r, function<T(i64)> loss) -> T
{
    while (l + 2 < r)
    {
        auto p = l + (r - l) / 3;
        auto q = r - (r - l) / 3;
        if (loss(p) < loss(q))
        {
            r = q;
        }
        else
        {
            l = p;
        }
    }

    return min({loss(l), loss(l + 1), loss(r)});
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0ll;
    cin >> n;

    auto v = vector<i64>(n);
    for (auto &x : v)
    {
        cin >> x;
    }

    auto loss = [&](i64 d)
    {
        auto e = 0ll;
        for (auto i = 0ll; i < n; ++i)
        {
            auto dx = abs(i - v[(i - d + n) % n]);
            e += min(dx, n - dx);
        }
        return e;
    };

    cout << min({trisect(0, n / 2, forward<function<i64(i64)>>(loss)), trisect(n / 2, n - 1, forward<function<i64(i64)>>(loss))}) << '\n';

    return 0;
}
