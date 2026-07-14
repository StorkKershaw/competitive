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

template <typename T, auto op, auto e>
    requires is_invocable_r_v<T, decltype(op), T, T> &&
             is_invocable_r_v<T, decltype(e)>
struct functional_graph
{
    struct cycle
    {
        cycle(vector<i32> &v, T w) : vertices(v.begin(), v.end()), weight(w) {}

        set<i32> vertices;
        T weight;
    };

    functional_graph(vector<i32> &v, vector<T> &w) : successor(v), weight(w), cycles(), distances(v.size(), -1), nearest_cycles(v.size(), nullptr)
    {
        auto n = static_cast<i32>(successor.size());
        auto g = scc_graph(n);
        for (auto i = 0; i < n; ++i)
        {
            g.add_edge(i, successor[i]);
        }

        for (auto &s : g.scc())
        {
            if (s.size() > 1 || successor[s.front()] == s.front())
            {
                auto w = e();
                for (auto u : s)
                {
                    w = op(w, weight[u]);
                }
                cycles.emplace_back(s, w);
            }
        }

        for (auto &cycle : cycles)
        {
            for (auto u : cycle.vertices)
            {
                distances[u] = 0;
                nearest_cycles[u] = &cycle;
            }
        }
    }

    auto nearest_cycle(i32 u) -> pair<i32, cycle *>
    {
        auto &d = distances[u];
        if (d == -1)
        {
            auto p = nearest_cycle(successor[u]);
            d = p.first + 1;
            nearest_cycles[u] = p.second;
        }
        return make_pair(d, nearest_cycles[u]);
    }

    vector<i32> successor;
    vector<T> weight;
    vector<cycle> cycles;
    vector<i32> distances;
    vector<cycle *> nearest_cycles;
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto v = vector(n, 0);
    for (auto &e : v)
    {
        cin >> e;
        --e;
    }

    auto w = vector(n, 0ll);
    for (auto &x : w)
    {
        cin >> x;
    }

    auto op = [](i64 l, i64 r) -> i64
    {
        return min(l, r);
    };

    auto g = functional_graph<i64, op, numeric_limits<i64>::max>(v, w);
    auto r = 0ll;
    for (auto &cycle : g.cycles)
    {
        r += cycle.weight;
    }
    cout << r << '\n';

    return 0;
}
