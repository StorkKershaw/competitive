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

template <typename T>
struct segment
{
    segment(T l, T r) : l(l), r(r) {}

    auto overlaps(segment<T> &other) -> bool
    {
        return max(l, other.l) < min(r, other.r);
    }

    template <char true_side, i32 iteration = 100>
    auto bisect(function<bool(T)> test) -> optional<segment>
    {
        static_assert(true_side == 'L' || true_side == 'R', "true_side must be either 'L' or 'R'");

        auto l = this->l, r = this->r;
        if constexpr (true_side == 'L')
        {
            if (!test(l))
            {
                return nullopt;
            }
        }
        else
        {
            if (!test(r))
            {
                return nullopt;
            }
        }

        for (auto i = 0; i < iteration; ++i)
        {
            if constexpr (is_integral_v<T>)
            {
                if (r - l <= 1)
                {
                    break;
                }
            }

            auto m = (l + r) / 2;
            if constexpr (true_side == 'L')
            {
                if (test(m))
                {
                    l = m;
                }
                else
                {
                    r = m;
                }
            }
            else
            {
                if (test(m))
                {
                    r = m;
                }
                else
                {
                    l = m;
                }
            }
        }

        if constexpr (true_side == 'L')
        {
            return segment(this->l, r);
        }
        else
        {
            return segment(r, this->r);
        }
    }

    template <i32 iteration = 100>
    auto trisect(function<T(T)> loss) -> T
    {
        auto l = this->l, r = this->r;

        for (auto i = 0; i < iteration; ++i)
        {
            if constexpr (is_integral_v<T>)
            {
                if (r - l <= 2)
                {
                    break;
                }
            }

            auto p = l + (r - l) / 3;
            auto q = r - (r - l) / 3;
            if (loss(p) < loss(q))
            {
                r = q;
            }
            else
            {
                l = p;
            }
        }

        if constexpr (is_integral_v<T>)
        {
            return min({loss(l), loss(l + 1), loss(r)});
        }
        else
        {
            return min(loss(l), loss(r));
        }
    }

    auto left() const -> T
    {
        return l;
    }

    auto right() const -> T
    {
        return r;
    }

private:
    T l, r;
};

template <typename Fn>
struct defer
{
    static_assert(is_invocable_v<Fn>, "Fn must be invocable");

    defer(Fn fn) : fn(fn) {}
    ~defer() { fn(); }

private:
    Fn fn;
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto v = vector(n, 0ll);
    for (auto &x : v)
    {
        cin >> x;
    }

    auto test = [&](i64 m) -> bool
    {
        return false;
    };

    auto s = segment(-1ll, 1ll << 30);

    return 0;
}
