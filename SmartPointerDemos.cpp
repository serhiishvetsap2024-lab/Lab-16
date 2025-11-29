#include "SmartPointerDemos.h"
#include "Signal.h"
#include <iostream>
#include <memory>
#include <string>



class ChildB; 

class ChildA {
private:
    std::string name;
public:
    std::shared_ptr<ChildB> childB;

    ChildA(const std::string& n) : name(n) {
        std::cout << "[ChildA] Created " << name << std::endl;
    }

    ~ChildA() {
        std::cout << "[ChildA] Destroyed " << name << std::endl;
    }

    std::string getName() const { return name; }
};

class ChildB {
private:
    std::string name;
public:
    std::weak_ptr<ChildA> childA; 

    ChildB(const std::string& n) : name(n) {
        std::cout << "[ChildB] Created " << name << std::endl;
    }

    ~ChildB() {
        std::cout << "[ChildB] Destroyed " << name << std::endl;
    }

    std::string getName() const { return name; }
};



class ListNode {
public:
    Signal data;
    std::shared_ptr<ListNode> next;
    std::weak_ptr<ListNode> prev;

    ListNode(const Signal& s) : data(s) {
        std::cout << "[ListNode] Created\n";
    }

    ~ListNode() {
        std::cout << "[ListNode] Destroyed\n";
    }
};



void uniquePtrDemo() {
    std::cout << "\n=== unique_ptr demo ===\n";

    auto p1 = std::make_unique<Signal>("Sine", 1000.0, true);
    std::cout << "p1.get() = " << p1.get() << std::endl;

   
    std::unique_ptr<Signal> p2 = std::move(p1);

    std::cout << "After std::move:\n";
    std::cout << "  p1.get() = " << p1.get() << " (expected nullptr)\n";
    std::cout << "  p2.get() = " << p2.get() << " (address of object)\n";

    if (p2) {
        std::cout << "Access through p2: ";
        p2->printInfo();
    }

    std::cout << "When uniquePtrDemo() ends, p2 goes out of scope\n"
        "and the Signal object is destroyed automatically.\n";
}



void sharedPtrDemo() {
    std::cout << "\n=== shared_ptr demo ===\n";

    auto s1 = std::make_shared<Signal>("Square", 500.0, false);
    auto s2 = s1;
    auto s3 = s1;

    std::cout << "Initial use_count: " << s1.use_count() << std::endl;

    {
        std::cout << "--- Entering inner block ---\n";
        auto s4 = s1;
        std::cout << "Inside block use_count: " << s1.use_count() << std::endl;
        std::cout << "--- Leaving inner block ---\n";
    }

    std::cout << "After block use_count: " << s1.use_count() << std::endl;
    std::cout << "When the last shared_ptr is destroyed, the Signal object\n"
        "is destroyed as well.\n";
}



void weakPtrDemo() {
    std::cout << "\n=== weak_ptr demo (breaking cyclic dependency) ===\n";

    {
        auto a = std::make_shared<ChildA>("ChildA");
        auto b = std::make_shared<ChildB>("ChildB");

        a->childB = b;
        b->childA = a; 

        std::cout << "use_count(a) = " << a.use_count() << std::endl;
        std::cout << "use_count(b) = " << b.use_count() << std::endl;

        if (auto lockedA = b->childA.lock()) {
            std::cout << "Locked ChildA from ChildB: " << lockedA->getName() << std::endl;
        }
        else {
            std::cout << "ChildA no longer exists.\n";
        }

        std::cout << "At the end of this block a and b will go out of scope.\n"
            "Because ChildB holds only weak_ptr to ChildA,\n"
            "there is no cyclic ownership and both objects are destroyed.\n";
    }

    std::cout << "You should see destructors of ChildA and ChildB above.\n"
        "If we used shared_ptr in ChildB instead of weak_ptr,\n"
        "we would create a reference cycle and objects would not be destroyed.\n";
}



void listDemo() {
    std::cout << "\n=== Doubly linked list demo (shared_ptr + weak_ptr) ===\n";

    auto first = std::make_shared<ListNode>(Signal("Sine", 1000.0, true));
    auto second = std::make_shared<ListNode>(Signal("Triangle", 2000.0, false));
    auto third = std::make_shared<ListNode>(Signal("Sawtooth", 1500.0, true));

   
    first->next = second;
    second->next = third;

    
    second->prev = first;
    third->prev = second;

    std::cout << "\nTraverse forward:\n";
    std::shared_ptr<ListNode> current = first;
    while (current) {
        current->data.printInfo();
        current = current->next;
    }

    std::cout << "\nTraverse backward:\n";
    current = third;
    while (current) {
        current->data.printInfo();
        auto prev = current->prev.lock();
        current = prev;
    }

    std::cout << "\nAt the end of listDemo(), all nodes go out of scope.\n"
        "Because backward links are weak_ptr, there is no reference cycle\n"
        "and all nodes are destroyed correctly.\n";
}
