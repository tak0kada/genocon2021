#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template<typename T>
std::string vec_tostr(const T t, const int indent)
{
    std::ostringstream os;
    os << t;
    return os.str();
}

template<typename T>
std::string vec_tostr(const std::vector<T> vec, const int indent)
{
    std::ostringstream os;
    os << std::string(2 * indent, ' ');

    if (vec.size() == 0)
    {
        os << "{}";
        return os.str();
    }

    os << "{";
    for (std::size_t i = 0; i < vec.size() - 1; ++i)
    {
        os << vec[i] << ", ";
    }
    os << *vec.crbegin() << "}";
    return os.str();
}

template<typename T>
std::string vec_tostr(const std::vector<std::vector<T>> vec,
                      const int indent = 0)
{
    const std::string tab = std::string(2 * indent, ' ');

    if (vec.size() == 0)
    {
        return tab + "{" + vec_tostr(std::vector<T>{}, 0) + "}";
    }

    std::string ret = tab + "{\n";
    for (std::size_t i = 0; i < vec.size() - 1; ++i)
    {
        ret += vec_tostr(vec[i], indent + 1) + ",\n";
    }
    ret += vec_tostr(*vec.crbegin(), indent + 1) + "\n";
    ret += tab + "}";
    return ret;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> vec)
{
    os << vec_tostr(vec, 0);
    return os;
}

int w(const char x, const char y)
{
    assert(x == 'A' || x == 'C' || x == 'G' || x == 'T' || x == '-');
    assert(y == 'A' || y == 'C' || y == 'G' || y == 'T' || y == '-');

    if (x == '-' || y == '-')
    {
        return -5;
    }
    else if (x != y)
    {
        return -3;
    }
    else  // x == y
    {
        return 1;
    }
}

enum class direction
{
    x,
    y,
    xy
};

std::ostream &operator<<(std::ostream &os, const direction d)
{
    switch (d)
    {
        case direction::x:
            os << " x";
            break;
        case direction::y:
            os << " y";
            break;
        case direction::xy:
            os << "xy";
            break;
    }
    return os;
}

std::pair<direction, int> which_max(const int x, const int y, const int xy)
{
    if (x < y)
    {
        if (y < xy)
        {
            return {direction::xy, xy};
        }
        else
        {
            return {direction::y, y};
        }
    }
    else
    {
        if (x < xy)
        {
            return {direction::xy, xy};
        }
        else
        {
            return {direction::x, x};
        }
    }
}

int main()
{
    const std::string s = []()
    {
        std::string str;
        std::cin >> str;
        return str;
    }();
    const std::string t = []()
    {
        std::string str;
        std::cin >> str;
        return str;
    }();

    std::vector<std::vector<int>> dp(s.size() + 1,
                                     std::vector<int>(t.size() + 1));
    std::vector<std::vector<direction>> log(
        s.size() + 1, std::vector<direction>(t.size() + 1));
    for (std::size_t i = 1; i < s.size() + 1; ++i)
    {
        dp[i][0] = dp[i - 1][0] + w('-', '-');
        log[i][0] = direction::x;
    }
    for (std::size_t j = 1; j < t.size() + 1; ++j)
    {
        dp[0][j] = dp[0][j - 1] + w('-', '-');
        log[0][j] = direction::y;
    }
    for (std::size_t i = 1; i < s.size() + 1; ++i)
    {
        for (std::size_t j = 1; j < t.size() + 1; ++j)
        {
            const auto [which, max] =
                which_max(dp[i - 1][j] + w(s[i - 1], '-'),
                          dp[i][j - 1] + w('-', t[j - 1]),
                          dp[i - 1][j - 1] + w(s[i - 1], t[j - 1]));
            dp[i][j] = max;
            log[i][j] = which;
        }
    }
    // std::cout << dp << std::endl;
    // std::cout << log << std::endl;

    const std::vector<direction> res = [&]()
    {
        std::vector<direction> ret;
        for (int i = static_cast<int>(s.size()), j = static_cast<int>(t.size());
             i != 0 || j != 0;)
        {
            ret.push_back(log[i][j]);
            switch (log[i][j])
            {
                case direction::x:
                    --i;
                    break;
                case direction::y:
                    --j;
                    break;
                case direction::xy:
                    --i;
                    --j;
                    break;
            }
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }();
    // std::cout << res << std::endl;

    std::string s_mod;
    std::string t_mod;
    {
        int i = 0;
        int j = 0;
        for (const auto &r : res)
        {
            switch (r)
            {
                case direction::x:
                    s_mod += s[i];
                    t_mod += '-';
                    ++i;
                    break;
                case direction::y:
                    s_mod += '-';
                    t_mod += t[j];
                    ++j;
                    break;
                case direction::xy:
                    s_mod += s[i];
                    t_mod += t[j];
                    ++i;
                    ++j;
                    break;
            }
        }
    }
    std::cout << s_mod << std::endl;
    std::cout << t_mod << std::endl;
    return 0;
}
