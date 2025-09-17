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

template <class T>
struct dynamic_fenwick_tree
{
public:
    explicit dynamic_fenwick_tree(i32 n) : _n(n) {}

    auto add(i32 p, T x) -> void
    {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n)
        {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    auto sum(i32 l, i32 r) -> T
    {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

private:
    i32 _n;
    gp_hash_table<i32, T> data;

    auto sum(i32 r) -> T
    {
        T s = 0;
        while (r > 0)
        {
            s += data.find(r - 1) != data.end() ? data[r - 1] : 0;
            r -= r & -r;
        }
        return s;
    }
};

template <class T, class inner_tree = fenwick_tree<T>>
struct fenwick_tree_2d
{
public:
    explicit fenwick_tree_2d(i32 w, i32 h) : _w(w), data(vector<inner_tree>(w, inner_tree(h))) {}

    auto add(i32 x, i32 y, T v) -> void
    {
        assert(0 <= x && x < _w);
        x++;
        while (x <= _w)
        {
            data[x - 1].add(y, v);
            x += x & -x;
        }
    }

    auto sum(i32 l, i32 b, i32 r, i32 t) -> T
    {
        assert(0 <= l && l <= r && r <= _w);
        return sum(r, b, t) - sum(l, b, t);
    }

private:
    i32 _w;
    vector<inner_tree> data;

    auto sum(i32 r, i32 b, i32 t) -> T
    {
        T s = 0;
        while (r > 0)
        {
            s += data[r - 1].sum(b, t);
            r -= r & -r;
        }
        return s;
    }
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto s = statistic_set<i32>();
    auto v = vector<i32>(n);
    for (auto &p : v)
    {
        cin >> p;
        s.insert(p);
    }

    auto tree_2d = fenwick_tree_2d<i64, dynamic_fenwick_tree<i64>>(n, s.size() + 1);
    for (auto x = 0; x < n; ++x)
    {
        auto y = s.order_of_key(v[x]);
        tree_2d.add(x, y, v[x]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    v.push_back(1 << 30);

    auto q = 0;
    cin >> q;

    auto h = 0ll;
    for (auto i = 0; i < q; ++i)
    {
        auto l = 0ll, r = 0ll, t = 0ll;
        cin >> l >> r >> t;
        l ^= h, r ^= h, t ^= h;
        auto f = [&](i32 p)
        {
            return p <= t;
        };
        auto q = partition_point(v.begin(), v.end(), f) - v.begin();
        h = tree_2d.sum(static_cast<i32>(--l), 0, static_cast<i32>(r), q);
        cout << h << '\n';
    }

    return 0;
}
