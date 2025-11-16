#include <iostream>
#include <string>
#include <cstring>

class Person {
private:
    int id_;
    std::string name_;
    std::string email_;

// bio is a C-string on the heap
    char* bio;

public:
    // constructor
    Person() {
        id_ = 0;
        name_ = "";
        email_ = "";
        bio = nullptr;
    }

    Person(int id, std::string name, std::string email) {
        id_ = id;
        name_ = name;
        email_ = email;
        bio = nullptr;
    }

    // Destructor
    ~Person() {
        delete[] bio;
    }

    // Copy constructor
    Person(const Person& other) {
        id_ = other.id_;
        name_ = other.name_;
        email_ = other.email_;

        if (other.bio != nullptr) {
            bio = new char[strlen(other.bio) + 1];
            strcpy(bio, other.bio);
        } else {
            bio = nullptr;
        }
    }

    // Copy assignment operator 
    Person& operator=(const Person& other) {
        if (this == &other) {
            return *this;
        }

        id_ = other.id_;
        name_ = other.name_;
        email_ = other.email_;

        delete[] bio;
        if (other.bio != nullptr) {
            bio = new char[strlen(other.bio) + 1];
            strcpy(bio, other.bio);
        } else {
            bio = nullptr;
        }

        return *this;
    }

    int id() const { return id_; }
    const std::string& name() const { return name_; }
    const std::string& email() const { return email_; }

    void set_email(const std::string& e) { email_ = e; }

    // Bio setter
    void set_bio(const char* s) {
        delete[] bio;
        if (s != nullptr) {
            bio = new char[strlen(s) + 1];
            strcpy(bio, s);
        } else {
            bio = nullptr;
        }
    }

    // Bio getter
    const char* get_bio() const {
        if (bio == nullptr) return "";
        return bio;
    }

    // to_string
    std::string to_string() const {
        return "Person{id=" + std::to_string(id_) +
               ", name=" + name_ +
               ", email=" + email_ + "}";
    }

    // virtual function
    virtual void introduce() {
        std::cout << "I'm a Person named " << name_ << ".\n";
    }
};


// Student class

class Student : public Person {
private:
    std::string major;
    int year;

public:
    Student(int id, std::string name, std::string email,
            std::string m, int y)
        : Person(id, name, email)
    {
        major = m;
        year = y;
    }

    void introduce() override {
        std::cout << "I'm a Student named " << name()
                  << ". Major: " << major
                  << ", Year: " << year << ".\n";
    }
};


// Teacher class

class Teacher : public Person {
private:
    std::string dept;
    double salary;

public:
    Teacher(int id, std::string name, std::string email,
            std::string d, double s)
        : Person(id, name, email)
    {
        dept = d;
        salary = s;
    }

    void introduce() override {
        std::cout << "I'm a Teacher named " << name()
                  << ". Dept: " << dept
                  << ", Salary: " << salary << ".\n";
    }
};

// polymorphism function
void callIntro(Person* p) {
    p->introduce();
}

int main() {

    // Problem 1 test
    Person p1(1001, "Alice", "alice@u.edu");
    p1.set_email("alice.cs@u.edu");
    std::cout << p1.to_string() << "\n\n";

    // Problem 2 test
    Person a(1001, "Alice", "a@u.edu");
    a.set_bio("Loves CS and coffee.");

    Person b = a;
    a.set_bio("Changed.");

    std::cout << a.get_bio() << "\n";
    std::cout << b.get_bio() << "\n\n";

    // Problem 3 & 4 test
    Student s(1001, "Alice", "a@u.edu", "CS", 2);
    Teacher t(2001, "Bob", "b@u.edu", "Math", 8000.0);

    callIntro(&s);
    callIntro(&t);

    return 0;
}
