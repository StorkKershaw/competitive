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

template <typename T, typename F, i32 iteration = 100>
    requires invocable<F, T>
auto trisect(T l, T r, F loss) -> invoke_result_t<F, T>
{
    for (auto i = 0; i < iteration; ++i)
    {
        if constexpr (is_integral_v<T>)
        {
            if (r - l <= 2)
            {
                break;
            }
        }

        auto p = l + (r - l) / T(3);
        auto q = r - (r - l) / T(3);
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

auto scan(complex<f64> &p, complex<f64> &q, complex<f64> &e, f64 &d) -> void
{
    auto px = 0.0, py = 0.0, qx = 0.0, qy = 0.0;
    cin >> px >> py >> qx >> qy;

    p = complex(px, py);
    q = complex(qx, qy);
    d = abs(q - p);
    e = (q - p) / d;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0ll;
    cin >> n;

    auto p0 = 0.0i, q0 = 0.0i, e0 = 0.0i;
    auto p1 = 0.0i, q1 = 0.0i, e1 = 0.0i;
    auto d0 = 0.0, d1 = 0.0;

    while (n--)
    {
        scan(p0, q0, e0, d0);
        scan(p1, q1, e1, d1);

        if (d0 > d1)
        {
            swap(p0, p1);
            swap(q0, q1);
            swap(e0, e1);
            swap(d0, d1);
        }

        auto loss0 = [=](f64 t) -> f64
        {
            auto r0 = e0 * t + p0;
            auto r1 = e1 * t + p1;
            return norm(r1 - r0);
        };

        auto loss1 = [=](f64 t) -> f64
        {
            auto r0 = q0;
            auto r1 = e1 * t + p1;
            return norm(r1 - r0);
        };

        cout << fixed << setprecision(15)
             << sqrt(min(trisect(0.0, d0, loss0), trisect(d0, d1, loss1))) << '\n';
    }

    return 0;
}
