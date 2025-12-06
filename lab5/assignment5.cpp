#include <iostream>
#include <vector>

using namespace std;


// Binary Search

vector<int>::iterator my_binary_search(
    vector<int>::iterator begin,
    vector<int>::iterator end,
    int target)
{
    while (begin != end)
    {
        auto mid = begin + (end - begin) / 2;

        if (*mid == target)
        {
            return mid;
        }
        else if (*mid < target)
        {
            begin = mid + 1;
        }
        else
        {
            end = mid;
        }
    }

    return end; // Not found
}

// my_unique

vector<int>::iterator my_unique(
    vector<int>::iterator begin,
    vector<int>::iterator end)
{
    if (begin == end)
        return end;

    auto new_end = begin;

    for (auto it = begin + 1; it != end; ++it)
    {
        if (*it != *new_end)
        {
            ++new_end;
            *new_end = *it;
        }
    }

    return new_end + 1;
}


// Main Testing

int main()
{
    //  Binary Search Test 
    vector<int> v = {1, 3, 5, 7, 9};

    auto it = my_binary_search(v.begin(), v.end(), 7);
    if (it != v.end())
        cout << "Found: " << *it << endl;
    else
        cout << "Not Found" << endl;

    it = my_binary_search(v.begin(), v.end(), 2);
    if (it != v.end())
        cout << "Found: " << *it << endl;
    else
        cout << "Not Found" << endl;

    // my_unique Test
    vector<int> v2 = {1, 1, 2, 2, 2, 3, 4, 4};

    auto new_end = my_unique(v2.begin(), v2.end());

    cout << "After removing duplicates: ";
    for (auto it2 = v2.begin(); it2 != new_end; ++it2)
        cout << *it2 << " ";

    cout << endl;

    return 0;
}
