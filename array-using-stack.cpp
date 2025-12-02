/*
bits/stdc++.h contains:

* initializer_list - for using initializer list
* iostream         - for cout and cin
* stdexcept        - for runtime_exception

*/

#include <bits/stdc++.h>
using namespace std;


struct IndexOutOfRangeException: runtime_error {
    IndexOutOfRangeException(): runtime_error("Index out of range.") {}
};


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
    stackarray(const initializer_list<T>& l)
    {
        length = l.size();
        for (const T &value : l)
        {
            originalStack.push(value);
        }
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= length)
        {
            throw IndexOutOfRangeException();
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

    void add(const T& value) { 
        originalStack.push(value);
        length++;
    }

    void remove(int index) {
        if (index < 0 || index >= length) {
            throw IndexOutOfRangeException();
        }

        if (index == length - 1) {
            originalStack.pop();
            return;
        }

        stack<T> auxStack;
        int required_pops = length - index;
        
        for (int i = 1; i <= required_pops; i++) {
            // T el = originalStack.top();
            // cout << el << endl;
            auxStack.push(originalStack.top());
            originalStack.pop();
        }

        
        // The last pushed element is the one which we
        // want to remove
        if (!auxStack.empty())
            auxStack.pop();

        while (!auxStack.empty())
        {
            originalStack.push(auxStack.top());
            auxStack.pop();
        }

        length--;
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