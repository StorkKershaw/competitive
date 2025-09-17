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
auto digit_dp(i32 n, const vector<i32> &v, i32 modulo) -> T
{
    auto que = map<tuple<i32, bool, i32, i32>, T>();
    que.emplace(make_tuple(0, true, 0, 0), 1);
    while (!que.empty() && get<0>(que.begin()->first) < n)
    {
        auto [i, same, mod_sum, digit_sum] = que.begin()->first;
        auto value = que.begin()->second;
        que.erase(que.begin());

        if (same)
        {
            for (auto d = 0; d <= v[i] && digit_sum + d <= modulo; ++d)
            {
                auto key = make_tuple(i + 1, d == v[i], (mod_sum * 10 + d) % modulo, digit_sum + d);
                que[key] += value;
            }
        }
        else
        {
            for (auto d = 0; d <= 9 && digit_sum + d <= modulo; ++d)
            {
                auto key = make_tuple(i + 1, false, (mod_sum * 10 + d) % modulo, digit_sum + d);
                que[key] += value;
            }
        }
    }

    auto r = T(0);
    for (auto &[key, value] : que)
    {
        if (get<2>(key) == 0 && get<3>(key) == modulo)
        {
            r += value;
        }
    }
    return r;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto s = ""s;
    cin >> s;

    auto v = vector(0, 0);
    for (auto &c : s)
    {
        v.push_back(c - '0');
    }

    auto r = 0ll;
    for (auto m = 1; m <= 126; ++m)
    {
        r += digit_dp<i64>(v.size(), v, m);
    }
    cout << r << '\n';

    return 0;
}
