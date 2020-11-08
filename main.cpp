#include <iostream>
#include <string>
#include <vector>

class Person {
public:

    Person() {}

    Person(int age, const std::string &name) : age(age), name(name) {}

    virtual void greetings() {
        std::cout << "Hello!" << std::endl;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        Person::age = age;
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Person::name = name;
    }

    //Дружественные функции - это функции, которые не являются членами класса,
    // однако имеют доступ к его private членам
    friend std::ostream &operator<<(std::ostream &os, const Person &person) {
        os << "age: " << person.age << " name: " << person.name;
        return os;
    }

    bool operator==(const Person &rhs) const {
        return age == rhs.age &&
               name == rhs.name;
    }

    bool operator!=(const Person &rhs) const {
        return !(rhs == *this);
    }

    Person operator+(const Person &another) const {
        return Person(0, this->getName() + "'s and " + another.getName() + "'s child");
    }

private:
    int age;
    std::string name;

};

class Citizen : public Person {
public:

    Citizen(int age, const std::string &name, int id) : Person(age, name), id(id) {}

    void doubleGreeting() {
        this->greetings();
        Person::greetings();
    }

    void greetings() override {
        std::cout << "Dobrogo chasu doby." << std::endl;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        Citizen::id = id;
    }

    friend std::ostream &operator<<(std::ostream &ostream, const Citizen &citizen) {
        ostream << "name = " << citizen.getName() << " age = " << citizen.getAge() << " id = " << citizen.getId();
    }

private:
    int id;
};

template<typename T>
void swap(T &a, T &b) {
    T temp(a);
    a = b;
    b = temp;
}

template<typename T>
int myHash(T &a) {
    std::hash<T> defaultHash;
    int out = defaultHash(a) + 5;
    return out;
}

template<typename T, typename U>
int getCombinedHash(T &a, U &b) {
    return myHash<T>(a) + myHash<U>(b);
}

class CollectionOverflowException:std::exception{
public:
    CollectionOverflowException(const std::string &message) : message(message) {}

    const std::string &getMessage() const {
        return message;
    }

    void setMessage(const std::string &message) {
        CollectionOverflowException::message = message;
    }

private:
        std::string message;

    };

template<typename T>
class ElementCapturer {
public:
    void add(T element) {
        if(size() == 100){
            throw CollectionOverflowException("Too much elements!!!");
        }
        elements.push_back(element);
    }

    int size() {
        return elements.size();
    }

    T getElement(int index) {
        return elements[index];
    }

private:
    std::vector<T> elements;

};

int main() {
//    Citizen alex(25, "Alex", 0);
//    std::cout << alex << std::endl;
//    alex.greetings();
//    std::cout << "Hello, World!" << std::endl;
//    alex.doubleGreeting();
//    Person alice(24, "Alice");
//    std::cout << (alex + alice) << std::endl;
//    Citizen stepan{31, "Stepan", 1};
//    std::cout << stepan << std::endl;
//    int a = 5;
//    int b = 5;
//    int res = getCombinedHash<int, int>(a, b);
//    std::cout << res << std::endl;
//    std::string first = "alice";
//    std::string second = "8";
//    int res2 = getCombinedHash<std::string, std::string>(first, second);
//    std::cout << res2 << std::endl;
    ElementCapturer<Citizen> elementCapturer;
    Citizen alex(25, "Alex", 0);
    Citizen stepan(31, "Stepan", 1);
    Citizen alice(18, "Alice", 2);
    elementCapturer.add(alex);
    elementCapturer.add(stepan);
    elementCapturer.add(alice);
    for (int i = 0; i < elementCapturer.size(); i++) {
        std::cout << elementCapturer.getElement(i) << std::endl;
    }

    ElementCapturer<int> intElementCapturer;
    intElementCapturer.add(5);
    intElementCapturer.add(7);
    intElementCapturer.add(13);
    for(int i = 0; i < intElementCapturer.size(); i++){
        std::cout << intElementCapturer.getElement(i)<< std::endl;
    }

    ElementCapturer<Person> peopleInRoom;
    try{
        for(int i = 0; i< 1000; i++){
            peopleInRoom.add(Person(i, "name"+std::to_string(i)));
        }
    } catch (CollectionOverflowException e) {
        std::cout<<e.getMessage()<<std::endl;
    }

    return 0;
}

