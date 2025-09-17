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
using twin = pair<T, T>;

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

template <auto action, auto yield>
auto combinations(i32 n, i32 k) -> void
{
    static_assert(is_invocable_v<decltype(action), i32, i32>, "action must be invocable with (i32, i32)");
    static_assert(is_invocable_v<decltype(yield), vector<i32> &>, "yield must be invocable with (vector<i32> &)");

    auto v = vector(k, 0);
    iota(v.begin(), v.end(), 0);
    yield(v);

    auto exhausted = false;
    do
    {
        exhausted = true;

        for (auto i = k - 1; i >= 0; --i)
        {
            if (v[i] != i + n - k)
            {
                action(v[i], v[i] + 1);

                ++v[i];
                for (auto j = i + 1; j < k; ++j)
                {
                    action(v[j], v[j - 1] + 1);
                    v[j] = v[j - 1] + 1;
                }

                yield(v);
                exhausted = false;
                break;
            }
        }
    } while (!exhausted);
}

template <bool small>
auto dfs(const string &s, string &t) -> string
{
    if constexpr (small)
    {
        sort(t.begin(), t.end());
    }
    else
    {
        sort(t.rbegin(), t.rend());
    }

    auto stack = vector(1, make_tuple(""s, true));
    while (!stack.empty())
    {
        auto [u, same] = stack.back();
        stack.pop_back();

        if (u.size() == s.size())
        {
            return u;
        }

        if (!same)
        {
            for (auto c : t)
            {
                auto v = u + c;
                stack.emplace_back(v, false);
            }
        }
        else
        {
            for (auto c : t)
            {
                if constexpr (small)
                {
                    if (c > s[u.size()])
                    {
                        break;
                    }
                }
                else
                {
                    if (c < s[u.size()])
                    {
                        break;
                    }
                }
                stack.emplace_back(u + c, c == s[u.size()]);
            }
        }
    }
    return ""s;
}

auto s = ""s;
auto k = 0;
auto m = numeric_limits<i64>::max();

auto nop(i32, i32) -> void
{
}

auto yield(vector<i32> &v) -> void
{
    auto t = ""s;
    for (auto x : v)
    {
        t += to_string(x);
    }

    auto p = dfs<true>(s, t);
    if (!p.empty() && p.front() != '0')
    {
        m = min(m, abs(stoll(p) - stoll(s)));
    }

    auto q = dfs<false>(s, t);
    if (!q.empty() && q.front() != '0')
    {
        m = min(m, abs(stoll(q) - stoll(s)));
    }
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> s >> k;
    if (s.size() == 1)
    {
        cout << 0 << '\n';
        return 0;
    }

    auto t = string(s.size() - 1, '9');
    m = min(m, abs(stoll(t) - stoll(s)));
    combinations<nop, yield>(10, k);
    cout << m << '\n';

    return 0;
}
