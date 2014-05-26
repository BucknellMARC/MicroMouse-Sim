Coding Convention
==================

Below is the coding convention that we will use for this project.  Please take the time to read this to ensure that you write code in an understandable format.

C
--------

C coding convention is a modified version of the standard Linux convention.  Functions will be lower case and have function-specific arguments before the object that is typically associated with that class of functions.  In addition, functions have a prefix common to the module / file that the function is in.

Variables are in the typical C++ camel case convention.

Objects are typedeffed and are referenced as that object.  Pointers to objects and fundamental data types have the asterisk immediately following the type.

```C
typedef struct {
     ...
} Object;

int someVar;
int* somePtr;
void explore_some_function(int var1, int var2, Object anObj);
```

C++
----------

Standard C++ coding convention applies.  When laying out an object, put private class members first, followed by methods, and then static class functions.

```C++
class Object {
private:
     int privateVar;

public:
     Object();

     int publicFunction();

public:
     static helperFunction();
}
```

In the C++ files, try to keep all functions and variables within the class.  Use static members on functions that don't need anything from a specific instance of that variable.
