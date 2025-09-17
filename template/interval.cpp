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

constexpr auto pi = numbers::pi_v<f80>;

template <typename T>
struct interval
{
    interval(T l, T r) : l(l), r(r) {}

    template <char true_side, i32 iteration = 100>
    auto bisect(function<bool(T)> test) -> optional<interval<T>>
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
            return interval(this->l, r);
        }
        else
        {
            return interval(r, this->r);
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

    auto intersection(const interval<T> &other) const -> optional<interval<T>>
    {
        auto p = max(l, other.l);
        auto q = min(r, other.r);
        if (p < q)
        {
            return interval(p, q);
        }
        else
        {
            return nullopt;
        }
    }

    friend auto operator&(const interval<T> &lhs, const interval<T> &rhs) -> optional<interval<T>>
    {
        return lhs.intersection(rhs);
    }

    auto left() const -> T
    {
        return l;
    }

    auto right() const -> T
    {
        return r;
    }

    auto length() const -> T
    {
        return r - l;
    }

private:
    T l, r;
};

auto solve(f80 a, f80 b, f80 c, f80 d) -> bool
{
    auto alpha = atan(b / a);

    auto v = vector<interval<f80>>();
    auto f = [&](f80 t) -> bool
    {
        return a * cos(t) + b * sin(t) <= c;
    };

    if (auto s = interval(0.0l, alpha).bisect<'L'>(f))
    {
        v.push_back(s.value());
    }
    if (auto s = interval(alpha, pi / 2.0l).bisect<'R'>(f))
    {
        v.push_back(s.value());
    }

    auto w = vector<interval<f80>>();
    auto g = [&](f80 t) -> bool
    {
        return a * sin(t) + b * cos(t) <= d;
    };

    if (auto s = interval(0.0l, pi / 2.0l - alpha).bisect<'L'>(g))
    {
        w.push_back(s.value());
    }
    if (auto s = interval(pi / 2.0l - alpha, pi / 2.0l).bisect<'R'>(g))
    {
        w.push_back(s.value());
    }

    for (auto &s : v)
    {
        for (auto &t : w)
        {
            if (s & t)
            {
                return true;
            }
        }
    }

    return false;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0ll;
    auto a = 0.0l, b = 0.0l;
    cin >> a >> b >> n;
    if (b < a)
    {
        swap(a, b);
    }

    while (n--)
    {
        auto c = 0.0l, d = 0.0l;
        cin >> c >> d;
        cout << (solve(a, b, c, d) ? "YES" : "NO") << '\n';
    }

    return 0;
}
