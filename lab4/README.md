This program demonstrates basic C++ object-oriented programming concepts: classes, constructors, destructors, inheritance, and polymorphism.

1 – Basic Person Class
In this part we create a simple Person class.
It stores an ID, a name, and an email.
We also add:
a default constructor
a constructor that sets all values
getter functions to read the data
a setter to change the email
a to_string() function to print a Person in one line
This problem focuses on learning how to build and use a basic class.

2 – Dynamic Memory and Deep Copy
Here we add a new member: char* bio, which must be stored on the heap.
Because the bio is dynamic memory, we must safely manage it.
We add:
a destructor to free the memory
a copy constructor
a copy assignment operator
These make sure that every Person gets its own copy of the bio string.
This avoids memory leaks, double deletes, and shared pointers.
This part teaches how to correctly manage dynamic memory in C++.

3 – Inheritance (Student & Teacher)
We create two classes that extend Person:
Student adds a major and a year
Teacher adds a department and a salary
Each class has its own introduce() method, but at this stage the function is not virtual, so calling it through a Person* uses the base class version.
This shows static binding.

4 – Virtual Functions and Polymorphism
Now we mark introduce() as virtual in Person.
This allows C++ to choose the correct version at runtime.
So when a Person* points to a Student or Teacher, it calls the version that belongs to the actual object.
This demonstrates dynamic binding and true polymorphism.