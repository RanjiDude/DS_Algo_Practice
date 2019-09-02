#include <iostream>
#include <vector>
#include <queue>
#include <functional>

// using namespace std;

class my_comparator
{
    public:
    // queue elements are vectors so we need to compare those
    bool operator()(std::vector<int> const& a, std::vector<int> const& b)
    {
        return a[0] > b[0];
    }
};

// for usability wrap this up in a type alias:

int main()
{
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> mpq;

    mpq.push({1, 2});
    mpq.push({2, 3});
    mpq.push({3, 4});

    while(!mpq.empty())
    {
        std::vector<int> temp = mpq.top();
        std::cout << temp[0] << ", " << temp[1] << std::endl;
        mpq.pop();
    }
}
