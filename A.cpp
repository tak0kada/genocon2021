#include <algorithm>
#include <iostream>
#include <string>

std::string read_sequence()
{
    std::string str;
    std::cin >> str;
    return str;
}

std::string reverse_complement(const std::string &seq)
{
    std::string ret;
    ret.reserve(seq.size());
    for (auto it = seq.crbegin(); it != seq.crend(); ++it)
    {
        switch (*it)
        {
            case 'A':
                ret.push_back('T');
                break;
            case 'C':
                ret.push_back('G');
                break;
            case 'G':
                ret.push_back('C');
                break;
            case 'T':
                ret.push_back('A');
                break;
            default:
                break;  // this line will not be reached
        }
    }
    return ret;
}

int main()
{
    const int m = []()
    {
        int m;
        std::cin >> m;
        return m;
    }();
    for (int i = 0; i < m; ++i)
    {
        std::cout << reverse_complement(read_sequence()) << std::endl;
    }

    return 0;
}
