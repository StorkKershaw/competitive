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

constexpr auto inf = 1ll << 50;

// when dealing with a negative edge, test if the value is inf before taking min
auto floyd_warshall(i32 n, vector<triplet<i64>> &edges, vector<vector<i64>> &distances) -> void
{
    for (auto i = 0; i < n; ++i)
    {
        distances[i][i] = 0;
    }
    for (auto [u, v, w] : edges)
    {
        distances[u][v] = w;
    }

    for (auto k = 0; k < n; ++k)
    {
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                if (distances[i][k] == inf || distances[k][j] == inf)
                {
                    continue;
                }
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }
}

// when dealing with a negative edge, test if the value is inf before taking min
auto traveling_salesperson(i32 n, vector<vector<i64>> &distances) -> i64
{
    auto l = 1 << n;
    auto dp = vector<vector<i64>>(l, vector<i64>(n, inf));
    for (auto i = 0; i < n; ++i)
    {
        dp[1 << i][i] = 0;
    }
    for (auto s = 1; s < l; ++s)
    {
        for (auto i = 0, m = 1; i < n; ++i, m <<= 1)
        {
            if (s & m)
            {
                for (auto j = 0; j < n; ++j)
                {
                    if (dp[s ^ m][j] == inf || distances[j][i] == inf)
                    {
                        continue;
                    }
                    dp[s][i] = min(dp[s][i], dp[s ^ m][j] + distances[j][i]);
                }
            }
        }
    }

    return *min_element(dp[l - 1].begin(), dp[l - 1].end());
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0, m = 0;
    cin >> n >> m;

    auto edges = vector<triplet<i64>>();
    for (auto i = 0; i < m; ++i)
    {
        auto u = 0ll, v = 0ll, w = 0ll;
        cin >> u >> v >> w;
        --u, --v;
        edges.emplace_back(u, v, w);
    }

    auto distances = vector<vector<i64>>(n, vector<i64>(n, inf));
    floyd_warshall(n, edges, distances);
    auto r = traveling_salesperson(n, distances);
    if (r < inf)
    {
        cout << r << '\n';
    }
    else
    {
        cout << "No" << '\n';
    }
    return 0;
}
