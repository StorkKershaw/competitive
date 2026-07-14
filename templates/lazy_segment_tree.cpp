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

// A monoid (S, op, e), described by one type instead of loose function pointers.
//
//   using S = ...;                  the carrier
//   static auto e() -> S;           identity
//   static auto op(S, S) -> S;      associative product
template <typename M>
concept monoid =
    requires(const typename M::S &a, const typename M::S &b) {
        typename M::S;
        { M::e() } -> convertible_to<typename M::S>;
        { M::op(a, b) } -> convertible_to<typename M::S>;
    };

// A monoid action: maps F acting on S, closed under composition.
// This is the C++ analogue of `impl MapMonoid for M` in ac-library-rs --
// the concept plays the role of Rust's trait bound, so a type that forgets a
// member (or gets a signature wrong) is rejected at the point of instantiation
// with a readable message rather than deep inside the tree.
//
//   using F = ...;                      the maps
//   static auto id() -> F;              identity map
//   static auto map(F, S) -> S;         apply f to x
//   static auto compose(F f, F g) -> F; f after g
//
// Laws the tree relies on (unchecked, as in Rust):
//   op is associative with identity e;
//   compose is associative with identity id;
//   map(f, op(x, y)) == op(map(f, x), map(f, y));
//   map(compose(f, g), x) == map(f, map(g, x)).
template <typename M>
concept lazy_monoid =
    monoid<M> &&
    requires(const typename M::F &f, const typename M::F &g, const typename M::S &x) {
        typename M::F;
        { M::id() } -> convertible_to<typename M::F>;
        { M::map(f, x) } -> convertible_to<typename M::S>;
        { M::compose(f, g) } -> convertible_to<typename M::F>;
    };

// Segment tree with lazy propagation over `M`, mirroring atcoder::lazy_segtree.
//
//   set(p, x) / get(p)                a[p] = x / a[p]                 O(log n)
//   prod(l, r) / all_prod()           op over a[l, r) / a[0, n)       O(log n) / O(1)
//   apply(p, f) / apply(l, r, f)      f on a[p] / on a[l, r)          O(log n)
//   max_right(l, g)                   largest r with g(prod(l, r))    O(log n)
//   min_left(r, g)                    smallest l with g(prod(l, r))   O(log n)
template <lazy_monoid M>
struct lazy_segment_tree
{
    using S = typename M::S;
    using F = typename M::F;

    lazy_segment_tree() : lazy_segment_tree(0) {}

    explicit lazy_segment_tree(i32 n) : lazy_segment_tree(vector<S>(n, M::e())) {}

    explicit lazy_segment_tree(const vector<S> &v)
        : n(static_cast<i32>(v.size())),
          width(static_cast<i32>(bit_ceil(static_cast<u32>(v.size())))),
          height(countr_zero(static_cast<u32>(width))),
          d(2 * static_cast<usize>(width), M::e()),
          lz(static_cast<usize>(width), M::id())
    {
        for (auto i = 0; i < n; ++i)
        {
            d[width + i] = v[i];
        }
        for (auto i = width - 1; i >= 1; --i)
        {
            update(i);
        }
    }

    auto size() const -> i32 { return n; }

    auto set(i32 p, S x) -> void
    {
        p += width;
        for (auto i = height; i >= 1; --i)
        {
            push(p >> i);
        }
        d[p] = x;
        for (auto i = 1; i <= height; ++i)
        {
            update(p >> i);
        }
    }

    auto get(i32 p) -> S
    {
        p += width;
        for (auto i = height; i >= 1; --i)
        {
            push(p >> i);
        }
        return d[p];
    }

    auto prod(i32 l, i32 r) -> S
    {
        if (l == r)
        {
            return M::e();
        }

        l += width, r += width;
        for (auto i = height; i >= 1; --i)
        {
            if (((l >> i) << i) != l)
            {
                push(l >> i);
            }
            if (((r >> i) << i) != r)
            {
                push((r - 1) >> i);
            }
        }

        auto sml = M::e(), smr = M::e();
        while (l < r)
        {
            if (l & 1)
            {
                sml = M::op(sml, d[l++]);
            }
            if (r & 1)
            {
                smr = M::op(d[--r], smr);
            }
            l >>= 1, r >>= 1;
        }

        return M::op(sml, smr);
    }

    auto all_prod() const -> S { return d[1]; }

    auto apply(i32 p, F f) -> void
    {
        p += width;
        for (auto i = height; i >= 1; --i)
        {
            push(p >> i);
        }
        d[p] = M::map(f, d[p]);
        for (auto i = 1; i <= height; ++i)
        {
            update(p >> i);
        }
    }

    auto apply(i32 l, i32 r, F f) -> void
    {
        if (l == r)
        {
            return;
        }

        l += width, r += width;
        for (auto i = height; i >= 1; --i)
        {
            if (((l >> i) << i) != l)
            {
                push(l >> i);
            }
            if (((r >> i) << i) != r)
            {
                push((r - 1) >> i);
            }
        }

        {
            auto lo = l, hi = r;
            while (lo < hi)
            {
                if (lo & 1)
                {
                    all_apply(lo++, f);
                }
                if (hi & 1)
                {
                    all_apply(--hi, f);
                }
                lo >>= 1, hi >>= 1;
            }
        }

        for (auto i = 1; i <= height; ++i)
        {
            if (((l >> i) << i) != l)
            {
                update(l >> i);
            }
            if (((r >> i) << i) != r)
            {
                update((r - 1) >> i);
            }
        }
    }

    // g must hold for the identity; the boundary it describes must be monotone.
    template <typename G>
        requires predicate<G, S>
    auto max_right(i32 l, G g) -> i32
    {
        if (l == n)
        {
            return n;
        }

        l += width;
        for (auto i = height; i >= 1; --i)
        {
            push(l >> i);
        }

        auto sm = M::e();
        do
        {
            while (l % 2 == 0)
            {
                l >>= 1;
            }
            if (!g(M::op(sm, d[l])))
            {
                while (l < width)
                {
                    push(l);
                    l = 2 * l;
                    if (g(M::op(sm, d[l])))
                    {
                        sm = M::op(sm, d[l]);
                        ++l;
                    }
                }
                return l - width;
            }
            sm = M::op(sm, d[l]);
            ++l;
        } while ((l & -l) != l);

        return n;
    }

    template <typename G>
        requires predicate<G, S>
    auto min_left(i32 r, G g) -> i32
    {
        if (r == 0)
        {
            return 0;
        }

        r += width;
        for (auto i = height; i >= 1; --i)
        {
            push((r - 1) >> i);
        }

        auto sm = M::e();
        do
        {
            --r;
            while (r > 1 && (r % 2))
            {
                r >>= 1;
            }
            if (!g(M::op(d[r], sm)))
            {
                while (r < width)
                {
                    push(r);
                    r = 2 * r + 1;
                    if (g(M::op(d[r], sm)))
                    {
                        sm = M::op(d[r], sm);
                        --r;
                    }
                }
                return r + 1 - width;
            }
            sm = M::op(d[r], sm);
        } while ((r & -r) != r);

        return 0;
    }

private:
    i32 n;
    i32 width;
    i32 height;
    vector<S> d;
    vector<F> lz;

    auto update(i32 k) -> void { d[k] = M::op(d[2 * k], d[2 * k + 1]); }

    auto all_apply(i32 k, F f) -> void
    {
        d[k] = M::map(f, d[k]);
        if (k < width)
        {
            lz[k] = M::compose(f, lz[k]);
        }
    }

    auto push(i32 k) -> void
    {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = M::id();
    }
};

using mint = modint998244353;

// range affine (x <- a * x + b), range sum.
// The width is carried in S so that `map` knows how many terms `b` hits.
struct M
{
    struct S
    {
        mint value;
        i64 game;
    };

    struct F
    {
        mint a, b;
    };

    static auto e() -> S { return {0, 0}; }

    static auto op(S l, S r) -> S { return {l.value + r.value, l.game + r.game}; }

    static auto id() -> F { return {1, 0}; }

    static auto map(F f, S x) -> S { return {f.a * x.value + f.b * x.game, x.game}; }

    static auto compose(F f, F g) -> F { return {f.a * g.a, f.a * g.b + f.b}; }
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0, q = 0;
    cin >> n >> q;

    auto v = vector<M::S>(n);
    for (auto &[value, width] : v)
    {
        auto x = 0ll;
        cin >> x;
        value = x, width = 1;
    }

    auto tree = lazy_segment_tree<M>(v);

    auto out = ""s;
    while (q--)
    {
        auto t = 0, l = 0, r = 0;
        cin >> t >> l >> r;
        if (t == 0)
        {
            auto b = 0ll, c = 0ll;
            cin >> b >> c;
            tree.apply(l, r, {b, c});
        }
        else
        {
            out += to_string(tree.prod(l, r).value.val());
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
