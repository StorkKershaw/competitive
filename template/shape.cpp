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

template <char C>
struct shape
{
    shape(i32 h, i32 w) : cells(h, vector<bool>(w, false)), positions() {}
    shape(vector<string> &v) : cells(), positions()
    {
        for (auto &s : v)
        {
            auto &r = cells.emplace_back();
            for (auto c : s)
            {
                r.push_back(c == C);
            }
        }
        trim();
        for (auto i = 0; i < height(); ++i)
        {
            for (auto j = 0; j < width(); ++j)
            {
                if (cells[i][j])
                {
                    positions.emplace_back(i, j);
                }
            }
        }
        pad();
    }

    static auto read() -> shape<C>
    {
        auto h = 0, w = 0;
        cin >> h >> w;
        auto v = vector<string>(h);
        for (auto &s : v)
        {
            cin >> s;
        }
        return shape<C>(v);
    }

    auto trim() -> void
    {
        while (cells.size() > 0 && all_of(cells.back().begin(), cells.back().end(), [](bool x)
                                          { return !x; }))
        {
            cells.pop_back();
        }

        while (cells.size() > 0 && all_of(cells.front().begin(), cells.front().end(), [](bool x)
                                          { return !x; }))
        {
            cells.erase(cells.begin());
        }

        while (cells.size() > 0 && all_of(cells.begin(), cells.end(), [](vector<bool> &v)
                                          { return !v.back(); }))
        {
            for (auto &v : cells)
            {
                v.pop_back();
            }
        }

        while (cells.size() > 0 && all_of(cells.begin(), cells.end(), [](vector<bool> &v)
                                          { return !v.front(); }))
        {
            for (auto &v : cells)
            {
                v.erase(v.begin());
            }
        }
    }

    auto pad() -> void
    {
        for (auto &v : cells)
        {
            v.resize(10, false);
        }

        while (cells.size() < 10)
        {
            cells.emplace_back(10, false);
        }
    }

    auto translated(i32 dy, i32 dx) -> optional<shape<C>>
    {
        auto r = shape<C>(height(), width());
        for (auto i = 0; i < height(); ++i)
        {
            for (auto j = 0; j < width(); ++j)
            {
                if (!cells[i][j])
                {
                    continue;
                }

                if (i + dy < 0 || i + dy >= height() || j + dx < 0 || j + dx >= width())
                {
                    return nullopt;
                }

                r.cells[i + dy][j + dx] = cells[i][j];
            }
        }
        return r;
    }

    auto contains(shape<C> &other) const -> bool
    {
        for (auto i = 0; i < height(); ++i)
        {
            for (auto j = 0; j < width(); ++j)
            {
                if (!cells[i][j] && other.cells[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    auto operator+(shape<C> &other) const -> shape<C>
    {
        auto r = shape<C>(height(), width());
        for (auto i = 0; i < height(); ++i)
        {
            for (auto j = 0; j < width(); ++j)
            {
                r.cells[i][j] = cells[i][j] || other.cells[i][j];
            }
        }
        return r;
    }

    auto operator==(shape<C> &other) const -> bool
    {
        return cells == other.cells;
    }

    auto width() const -> i32
    {
        return static_cast<i32>(cells[0].size());
    }

    auto height() const -> i32
    {
        return static_cast<i32>(cells.size());
    }

    vector<vector<bool>> cells;
    vector<twin<i32>> positions;
};

template <char C>
auto movements(shape<C> &s, shape<C> &x) -> vector<shape<C>>
{
    auto v = vector<shape<C>>();
    auto [i, j] = s.positions.front();
    for (auto [p, q] : x.positions)
    {
        auto t = s.translated(p - i, q - j);
        if (t && x.contains(t.value()))
        {
            v.push_back(t.value());
        }
    }
    return v;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto p = shape<'#'>::read(), q = shape<'#'>::read(), x = shape<'#'>::read();
    auto v = movements(p, x), w = movements(q, x);

    for (auto &a : v)
    {
        for (auto &b : w)
        {
            if (a + b == x)
            {
                cout << "Yes" << '\n';
                return 0;
            }
        }
    }
    cout << "No" << '\n';

    return 0;
}
