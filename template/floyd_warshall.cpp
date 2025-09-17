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

auto floyd_warshall(i32 n, vector<vector<i64>> &dist) -> void
{
    for (auto k = 0; k < n; ++k)
    {
        for (auto i = 0; i < n; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

auto differential_update(vector<vector<i64>> &dist, i32 n, triplet<i32> edge) -> void
{
    auto [u, v, c] = edge;
    for (auto i = 0; i < n; ++i)
    {
        for (auto j = 0; j < n; ++j)
        {
            dist[i][j] = min({dist[i][j], dist[i][u] + c + dist[v][j], dist[i][v] + c + dist[u][j]});
        }
    }
}

constexpr auto inf = 1ll << 50;

auto main() -> i32
{
    using query_t = variant<triplet<i32>, twin<i32>>;

    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0, m = 0, q = 0;
    cin >> n >> m >> q;

    auto roads = vector<triplet<i64>>();
    roads.reserve(m);
    for (auto i = 0; i < m; ++i)
    {
        auto u = 0, v = 0, c = 0;
        cin >> u >> v >> c;
        --u, --v;
        roads.emplace_back(u, v, c);
    }

    auto blocked = unordered_set<i32>();
    auto queries = vector<query_t>();
    for (auto i = 0; i < q; ++i)
    {
        auto t = 0;
        cin >> t;

        if (t == 1)
        {
            auto i = 0;
            cin >> i;
            --i;

            blocked.insert(i);
            queries.emplace_back(roads[i]);
        }
        else
        {
            auto x = 0, y = 0;
            cin >> x >> y;
            --x, --y;

            queries.emplace_back(make_tuple(x, y));
        }
    }
    reverse(queries.begin(), queries.end());

    auto dist = vector<vector<i64>>(n, vector<i64>(n, inf));
    for (auto i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
    }

    for (auto i = 0; i < m; ++i)
    {
        if (blocked.contains(i))
        {
            continue;
        }

        auto [u, v, c] = roads[i];
        dist[u][v] = c;
        dist[v][u] = c;
    }

    floyd_warshall(n, dist);
    auto distances = vector<i64>();
    for (auto query : queries)
    {
        if (query.index() == 0)
        {
            differential_update(dist, n, get<0>(query));
        }
        else
        {
            auto [x, y] = get<1>(query);
            distances.push_back(dist[x][y] < inf ? dist[x][y] : -1);
        }
    }

    reverse(distances.begin(), distances.end());
    for (auto distance : distances)
    {
        cout << distance << '\n';
    }

    return 0;
}
