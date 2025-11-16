# Implementing array using stack
***
I once saw a problem state that
"Consider a language that does not have arrays but does have stacks as a data type. That is, one can declare

```c
stack s; 
```

and the `push`, `pop`, `top` operations are defined. Show how a one-dimensional array can be implemented by using these operations on two stacks."

So i thought of building just that.
***
## Algorithms

### Retreiving element at given index

Assuming the given array is `{1, 2, 3, 4}`. So the resulting stack would look like:

<img width="2012" height="1026" alt="Pasted image 20251116101646" src="https://github.com/user-attachments/assets/86d003db-4fca-4372-9538-5ddf9832ec28" />



The right side of the image shows "indexes" of element, that will be used by the user to access elements by our algorithm.

We will be using another stack, an auxillary stack, which will be used to store popped elements before getting access to required element accessing.

Now, in order to retrieve the element at index `1`, we have to do following steps:
1. Pop from stack. This removes 4. Push this into auxilliary stack.
2. Again, pop from the stack. This removes 3. Push 3 into the auxilliary stack.
3. We can now access the required element, by issuing top() fucntion on "original" stack. Store this value into a temporary variable.
4. Now, pop all elements from auxilliary stack back into the original stack.
5. Return the value from temporary variable.

Look, in above process, we popped 2 times i.e. we popped `size - (index + 1) => 4 - 2 = 2` times. So we can generalize it in the following way.

Generalized algorithm:
```
required_pops = size - (index + 1)

for (int i = 0; i < required_pops; i++)
	auxStack.push(originalStack.pop());

temp_var = originalStack.top();

while (auxStack is not empty)
	originalStack.push(auxStack.pop());
	
return temp_var
```

***
### Modifying element at given index

Assuming the given array is `{1, 2, 3, 4}`. So the resulting stack would look like:

<img width="2012" height="1026" alt="Pasted image 20251116101646" src="https://github.com/user-attachments/assets/64b75202-9180-40df-b7ff-de87ccbceec9" />



The right side of the image shows "indexes" of element, that will be used by the user to access elements by our algorithm.

Now, the method is all the same. But the change is in how many times we pop from original stack and push into it.

In order to modify the index `1`, we have to do following steps:
1. Pop from stack. This removes 4. Push this into auxilliary stack.
2. Again, pop from the stack. This removes 3. Push 3 into the auxilliary stack.
3. Again, pop from the stack. This removes 2. Discard it.
4. Push the new value onto the original stack.
5. Now, pop all elements from auxilliary stack back into the original stack.

Look, in above process, we popped 3 times i.e. we popped `size - index => 4 - 1 = 3` times. So we can generalize it in the following way.

Generalized algorithm:
```
required_pops = size - index

for (int i = 0; i < required_pops; i++)
	auxStack.push(originalStack.pop());

originalStack.push(new_value)

while (auxStack is not empty)
	originalStack.push(auxStack.pop());
```

***

## C++ Implementation detail

The above algorithm was for languages that do not allow c++-like references. But since C++ allows references to be returned, we can do both retrieval and modification through same process i.e. the process of retrieving the element. This will allow the usage of this statement

```c++
arr[1] = 4; // operator overload for operator[]
```

We do this by returning reference to the required_index. Since this array implementation is designed to be fixed and elements of original-stack do not change memory locations, the returned reference will not be dangling until the stackarray object is destroyed, after which it can't be used of-course.
