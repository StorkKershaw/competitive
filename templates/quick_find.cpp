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

struct quick_find
{
public:
    explicit quick_find(i32 n) : _n(n), members(n)
    {
        for (auto i = 0; i < n; ++i)
        {
            members[i] = make_shared<list<i32>>();
            members[i]->push_back(i);
        }
    }

    auto merge(i32 u, i32 v) -> void
    {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);

        if (same(u, v))
        {
            return;
        }

        if (members[u]->size() < members[v]->size())
        {
            swap(u, v);
        }

        auto member = members[v];
        for (auto x : *member)
        {
            members[x] = members[u];
        }
        members[u]->splice(members[u]->end(), move(*member));
    }

    auto same(i32 u, i32 v) -> bool
    {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        return members[u] == members[v];
    }

    auto member(i32 u) const -> shared_ptr<list<i32>>
    {
        assert(0 <= u && u < _n);
        return members[u];
    }

    auto size(i32 u) const -> i32
    {
        assert(0 <= u && u < _n);
        return members[u]->size();
    }

private:
    i32 _n;
    vector<shared_ptr<list<i32>>> members;
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0, q = 0;
    cin >> n >> q;

    auto d = quick_find(n);
    auto w = vector<i64>(n);
    auto r = vector<i64>();
    for (auto i = 1; i <= q; ++i)
    {
        auto u = 0, v = 0, c = 0;
        cin >> u >> v >> c;
        --u, --v;

        if (d.same(u, v))
        {
            if (w[u] - w[v] == c)
            {
                r.push_back(i);
            }
            continue;
        }

        if (d.size(u) < d.size(v))
        {
            swap(u, v);
            c = -c;
        }

        auto dx = w[u] - c - w[v];
        for (auto j : *d.member(v))
        {
            w[j] += dx;
        }
        d.merge(u, v);
        r.push_back(i);
    }

    if (r.size() > 0)
    {
        for (auto x : r | views::take(r.size() - 1))
        {
            cout << x << ' ';
        }
        cout << r.back();
    }
    cout << '\n';

    return 0;
}
