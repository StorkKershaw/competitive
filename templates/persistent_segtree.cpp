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

// Persistent segment tree over a monoid (S, op, e), mirroring atcoder::segtree.
// The mutating operations (`set`, `build`) do NOT modify state: they return a
// NEW root that shares every untouched node with the source version via path
// copying, so any past version stays queryable. That immutability is what makes
// snapshot / order-statistic queries answerable online.
//
//   S op(S, S)  : associative product     S e()        : identity
//
//   set(root, p, x)        -> new root with a[p] = x           O(log n)
//   get(root, p)           -> a[p]                             O(log n)
//   prod(root, l, r)       -> op over a[l, r)                  O(log n)
//   all_prod(root)         -> op over a[0, n)                  O(1)
//   max_right(root, l, f)  -> largest r with f(prod[l, r))     O(log n)
//   min_left (root, r, f)  -> smallest l with f(prod[l, r))    O(log n)
//
// Each `set`/leaf of `build` allocates O(log n) nodes.
template <typename S, S (*op)(S, S), S (*e)()>
struct persistent_segtree
{
    i32 n;
    vector<S> value;
    vector<i32> left;
    vector<i32> right;

    persistent_segtree() : n(0) {}

    // `n` is the array length; `capacity` hints the number of `set` calls.
    explicit persistent_segtree(i32 n, usize capacity = 0) : n(n)
    {
        auto bits = 0;
        while ((i32(1) << bits) < n)
        {
            ++bits;
        }
        auto reserve = (capacity + 1) * (bits + 2) + 2;
        value.reserve(reserve);
        left.reserve(reserve);
        right.reserve(reserve);
        // node 0 is the shared null subtree: entirely identity, its own child.
        make(e(), 0, 0);
    }

    // the all-identity version.
    auto empty_root() const -> i32 { return 0; }

    // a fresh version whose contents are `a` (|a| must equal n).
    auto build(const vector<S> &a) -> i32 { return build(0, n, a); }

    auto set(i32 root, i32 p, S x) -> i32 { return set(root, 0, n, p, x); }

    auto get(i32 root, i32 p) const -> S { return get(root, 0, n, p); }

    auto prod(i32 root, i32 l, i32 r) const -> S { return prod(root, 0, n, l, r); }

    auto all_prod(i32 root) const -> S { return value[root]; }

    template <typename F>
    auto max_right(i32 root, i32 l, F f) const -> i32
    {
        auto sm = e();
        auto r = max_right(root, 0, n, l, f, sm);
        return r == -1 ? n : r;
    }

    template <typename F>
    auto min_left(i32 root, i32 r, F f) const -> i32
    {
        auto sm = e();
        auto l = min_left(root, 0, n, r, f, sm);
        return l == -1 ? 0 : l;
    }

    auto make(S v, i32 l, i32 r) -> i32
    {
        value.emplace_back(v);
        left.emplace_back(l);
        right.emplace_back(r);
        return i32(value.size()) - 1;
    }

    // nodes cover the half-open interval [lo, hi).
    auto build(i32 lo, i32 hi, const vector<S> &a) -> i32
    {
        if (hi - lo == 1)
        {
            return make(a[lo], 0, 0);
        }
        auto mid = lo + (hi - lo) / 2;
        auto l = build(lo, mid, a);
        auto r = build(mid, hi, a);
        return make(op(value[l], value[r]), l, r);
    }

    auto set(i32 node, i32 lo, i32 hi, i32 p, S x) -> i32
    {
        if (hi - lo == 1)
        {
            return make(x, 0, 0);
        }
        auto mid = lo + (hi - lo) / 2;
        if (p < mid)
        {
            auto l = set(left[node], lo, mid, p, x);
            return make(op(value[l], value[right[node]]), l, right[node]);
        }
        auto r = set(right[node], mid, hi, p, x);
        return make(op(value[left[node]], value[r]), left[node], r);
    }

    auto get(i32 node, i32 lo, i32 hi, i32 p) const -> S
    {
        if (hi - lo == 1)
        {
            return value[node];
        }
        auto mid = lo + (hi - lo) / 2;
        return p < mid ? get(left[node], lo, mid, p) : get(right[node], mid, hi, p);
    }

    auto prod(i32 node, i32 lo, i32 hi, i32 l, i32 r) const -> S
    {
        if (r <= lo || hi <= l)
        {
            return e();
        }
        if (l <= lo && hi <= r)
        {
            return value[node];
        }
        auto mid = lo + (hi - lo) / 2;
        return op(prod(left[node], lo, mid, l, r), prod(right[node], mid, hi, l, r));
    }

    template <typename F>
    auto max_right(i32 node, i32 lo, i32 hi, i32 l, F &f, S &sm) const -> i32
    {
        if (hi <= l)
        {
            return -1;
        }
        if (l <= lo)
        {
            auto next = op(sm, value[node]);
            if (f(next))
            {
                sm = next;
                return -1;
            }
            if (hi - lo == 1)
            {
                return lo;
            }
        }
        auto mid = lo + (hi - lo) / 2;
        auto res = max_right(left[node], lo, mid, l, f, sm);
        if (res != -1)
        {
            return res;
        }
        return max_right(right[node], mid, hi, l, f, sm);
    }

    template <typename F>
    auto min_left(i32 node, i32 lo, i32 hi, i32 r, F &f, S &sm) const -> i32
    {
        if (r <= lo)
        {
            return -1;
        }
        if (hi <= r)
        {
            auto next = op(value[node], sm);
            if (f(next))
            {
                sm = next;
                return -1;
            }
            if (hi - lo == 1)
            {
                return hi;
            }
        }
        auto mid = lo + (hi - lo) / 2;
        auto res = min_left(right[node], mid, hi, r, f, sm);
        if (res != -1)
        {
            return res;
        }
        return min_left(left[node], lo, mid, r, f, sm);
    }
};

auto op(i64 a, i64 b) -> i64 { return a + b; }
auto e() -> i64 { return 0; }

enum keys
{
    snapshot,
    start,
    size,
};

using state = tuple<i32, i64, i64>;

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0ll, m = 0ll;
    cin >> n >> m;

    auto v = vector(n, 0ll);
    auto bucket = vector(m + 1, 0ll);
    for (auto &x : v)
    {
        cin >> x;
        ++bucket[x];
    }

    auto groups = map<i64, vector<i64>>();
    for (auto i = 1ll; i <= m; ++i)
    {
        auto c = bucket[i];
        groups[c].emplace_back(i);
    }

    auto tree = persistent_segtree<i64, op, e>(static_cast<i32>(m), static_cast<usize>(m));
    auto states = vector<triplet<i64>>();

    auto root = tree.empty_root();
    auto lo = n;
    auto total = 0ll;
    for (auto x = groups.begin(), y = next(groups.begin()); x != groups.end(); ++x, ++y)
    {
        auto count = x->first;
        for (auto value : x->second)
        {
            auto p = static_cast<i32>(value - 1);
            root = tree.set(root, p, tree.get(root, p) + 1);
            ++total;
        }

        states.emplace_back(root, lo, total);

        if (y != groups.end())
        {
            lo += (y->first - count) * total;
        }
    }

    reverse(states.begin(), states.end());

    auto answer = [&](i64 x) -> i64
    {
        if (x < n)
        {
            return v[x];
        }

        auto phase = *partition_point(states.begin(), states.end(),
                                      [&](state const &s)
                                      { return get<keys::start>(s) > x; });
        auto order = (x - get<keys::start>(phase)) % get<keys::size>(phase);
        return tree.max_right(get<keys::snapshot>(phase), 0, [&](i64 s)
                              { return s <= order; }) +
               1;
    };

    auto q = 0ll;
    cin >> q;

    auto out = ""s;
    while (q--)
    {
        auto x = 0ll;
        cin >> x;
        out += to_string(answer(--x));
        out += '\n';
    }
    cout << out;

    return 0;
}
