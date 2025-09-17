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

struct lowest_common_ancestor
{
    lowest_common_ancestor(i32 n) : built(false), n(n), h(1), graph(n), distances(n)
    {
        while ((1 << h) < n)
        {
            ++h;
        }
        parents.resize(h, vector<i32>(n, -1));
    }

    auto edge(i32 u, i32 v) -> void
    {
        graph[u].push_back(v);
    }

    auto build() -> void
    {
        dfs(0, -1, 0);
        for (auto k = 0; k + 1 < h; ++k)
        {
            for (auto u = 0; u < n; ++u)
            {
                auto p = parents[k][u];
                parents[k + 1][u] = p != -1 ? parents[k][p] : -1;
            }
        }
        built = true;
    }

    auto query(i32 u, i32 v) -> i32
    {
        assert(built);

        if (distances[u] < distances[v])
        {
            swap(u, v);
        }

        for (auto k = 0; k < h; ++k)
        {
            if ((distances[u] - distances[v]) >> k & 1)
            {
                u = parents[k][u];
            }
        }

        if (u == v)
        {
            return u;
        }

        for (auto k = h - 1; k >= 0; --k)
        {
            if (parents[k][u] != parents[k][v])
            {
                u = parents[k][u], v = parents[k][v];
            }
        }

        return parents[0][u];
    }

    auto distance(i32 u, i32 v) -> i32
    {
        return distances[u] + distances[v] - 2 * distances[query(u, v)];
    }

private:
    bool built;
    i32 n, h;
    vector<vector<i32>> graph;
    vector<vector<i32>> parents;
    vector<i32> distances;

    auto dfs(i32 u, i32 p, i32 d) -> void
    {
        parents[0][u] = p;
        distances[u] = d;
        for (auto v : graph[u])
        {
            if (v == p)
            {
                continue;
            }
            dfs(v, u, d + 1);
        }
    }
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto lca = lowest_common_ancestor(n);
    for (auto i = 0; i < n - 1; ++i)
    {
        auto u = 0, v = 0;
        cin >> u >> v;
        --u, --v;
        lca.edge(u, v), lca.edge(v, u);
    }
    lca.build();

    auto q = 0;
    cin >> q;

    for (auto i = 0; i < q; ++i)
    {
        auto u = 0, v = 0;
        cin >> u >> v;
        --u, --v;
        cout << lca.distance(u, v) + 1 << '\n';
    }

    return 0;
}
