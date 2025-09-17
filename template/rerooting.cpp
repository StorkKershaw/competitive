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

template <class S, auto op, auto add, auto e>
struct rerooting
{
    static_assert(is_convertible_v<decltype(op), function<S(S, S)>>, "op must work as S(S, S)");
    static_assert(is_convertible_v<decltype(add), function<S(S, i32)>>, "add must work as S(S, i32)");
    static_assert(is_convertible_v<decltype(e), function<S()>>, "e must work as S()");

    rerooting(i32 n) : graph(n), dp(n), results(n, e()) {}

    auto edge(i32 u, i32 v) -> void
    {
        graph[u].push_back(v);
    }

    auto solve(vector<i32> w = {0}) -> vector<S>
    {
        for (auto u : w)
        {
            dfs1(u, -1);
            dfs2(u, -1, e());
        }
        return results;
    }

private:
    vector<vector<i32>> graph;
    vector<vector<S>> dp;
    vector<S> results;

    auto dfs1(i32 u, i32 parent) -> S
    {
        auto t = e();
        auto d = static_cast<i32>(graph[u].size());
        dp[u].resize(d, e());
        for (auto i = 0; i < d; ++i)
        {
            auto v = graph[u][i];
            if (v == parent)
            {
                continue;
            }
            dp[u][i] = dfs1(v, u);
            t = op(t, dp[u][i]);
        }

        return add(t, u);
    }

    auto dfs2(i32 u, i32 parent, const S from_parent) -> void
    {
        auto d = static_cast<i32>(graph[u].size());
        for (auto i = 0; i < d; ++i)
        {
            if (graph[u][i] == parent)
            {
                dp[u][i] = from_parent;
                break;
            }
        }

        auto p = vector<S>(d + 1, e());
        auto q = vector<S>(d + 1, e());
        for (auto i = 0; i < d; ++i)
        {
            p[i + 1] = op(p[i], dp[u][i]);
        }
        for (auto i = d - 1; i >= 0; --i)
        {
            q[i] = op(q[i + 1], dp[u][i]);
        }

        results[u] = add(p[d], u);
        for (auto i = 0; i < d; ++i)
        {
            auto v = graph[u][i];
            if (v == parent)
            {
                continue;
            }
            dfs2(v, u, add(op(p[i], q[i + 1]), u));
        }
    }
};

struct S
{
    i64 weight, sum;

    S() : weight(0), sum(0) {}
    S(i64 weight, i64 sum) : weight(weight), sum(sum) {}

    auto operator<(const S &other) const -> bool
    {
        return sum < other.sum;
    }
};

auto v = vector<i64>();

auto op(S l, S r) -> S
{
    return S(l.weight + r.weight, l.sum + r.sum);
}

auto add(S s, i32 u) -> S
{
    return S(s.weight + v[u], s.sum + s.weight);
}

auto e() -> S
{
    return S();
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto r = rerooting<S, op, add, e>(n);
    for (auto i = 0; i < n - 1; ++i)
    {
        auto u = 0, v = 0;
        cin >> u >> v;
        --u, --v;
        r.edge(u, v), r.edge(v, u);
    }

    v.resize(n);
    for (auto &x : v)
    {
        cin >> x;
    }

    auto w = r.solve();
    cout << min_element(w.begin(), w.end())->sum << '\n';

    return 0;
}
