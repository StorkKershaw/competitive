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

auto two_pointers(i64 n, function<void(i64)> add, function<void(i64)> remove, function<bool(i64)> test, function<void(i64, i64)> yield) -> void
{
    auto l = 0ll, r = 0ll;
    do
    {
        if (r < n && test(r))
        {
            add(r++);
            yield(l, r);
        }
        else if (l == r)
        {
            r++, l++;
        }
        else
        {
            remove(l++);
        }
    } while (l < n);
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0ll, k = 0ll;
    cin >> n >> k;

    auto v = vector<i64>(n);
    for (auto &x : v)
    {
        cin >> x;
    }

    if (find(v.begin(), v.end(), 0) != v.end())
    {
        cout << n << '\n';
        return 0;
    }

    auto p = 1ll, x = 0ll;
    auto add = [&](i64 r)
    {
        p *= v[r];
    };
    auto remove = [&](i64 l)
    {
        p /= v[l];
    };
    auto test = [&](i64 r)
    {
        return p * v[r] <= k;
    };
    auto yield = [&](i64 l, i64 r)
    {
        x = max(x, r - l);
    };

    two_pointers(n, add, remove, test, yield);
    cout << x << '\n';

    return 0;
}
