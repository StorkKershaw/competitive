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

template <typename T, typename F, i32 iteration = 100>
    requires is_invocable_r_v<bool, F, T>
auto bisect(T l, T r, F pred) -> T
{
    for (auto i = 0; i < iteration; ++i)
    {
        if constexpr (is_integral_v<T>)
        {
            if (r - l <= 1)
            {
                break;
            }
        }

        auto m = l + (r - l) / T(2);
        if (pred(m))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    return r;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0ll, q = 0ll;
    cin >> n >> q;

    auto v = vector(n, 0ll);
    for (auto &x : v)
    {
        cin >> x;
    }
    sort(v.begin(), v.end());

    while (q--)
    {
        auto x = 0ll;
        cin >> x;

        auto i = bisect(-1ll, n, [&](i64 i)
                        { return v[i] >= x; });
        cout << i << '\n';
    }

    return 0;
}
