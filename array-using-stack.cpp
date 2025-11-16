#include <bits/stdc++.h>
#include <initializer_list>
using namespace std;

template <typename T>
class stackarray
{
    stack<T> originalStack;
    int length;

public:
    stackarray()
    {
        length = 0;
    }

    // This will allow intialize using array-like syntax
    stackarray(initializer_list<T> l)
    {
        length = 0;
        for (const T &value : l)
        {
            originalStack.push(value);
            length += 1;
        }
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= length)
        {
            cout << "Out of bounds!" << endl;
            exit(1);
        }

        stack<T> auxStack;
        int required_pops = length - (index + 1);
        for (int i = 1; i <= required_pops; i++)
        {
            auxStack.push(originalStack.top());
            originalStack.pop();
        }

        // required_value is a reference, which will be
        // returned at the operator[]  called place.

        // When we return a reference, we are giving
        // out a way to not only "get" (read) the value, but also
        // modify it.

        // since the size of the original stack (THE ARRAY tm)
        // is not going to be changed, the reference is going to
        // be alive till our stackarray object is alive.
        T &required_value = originalStack.top();

        while (!auxStack.empty())
        {
            originalStack.push(auxStack.top());
            auxStack.pop();
        }

        return required_value;
    }

    int size() const { return length; }
};

template <typename T>
void print(stackarray<T> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
}

int main()
{
    stackarray<int> arr{1, 2, 3, 4};

    /* outputs:
        1
        2
        3
        4
    */
    print(arr);

    arr[1] = 99;

    cout << endl;

    /* outputs:
        1
        99
        3
        4
    */
    print(arr);

    return 0;
}