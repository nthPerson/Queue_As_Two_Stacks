#include <iostream>

using namespace std;

// TicketItem Class : this class will contain the details of the items in the queue
class TicketItem {
public:
//    int value;
    string personName;
    string reserveCode;

    TicketItem(string personName, string reserveCode) {
        this->reserveCode = reserveCode;
        this->personName = personName;
    }

    void print() { // TODO change print output
        cout << personName << ", " << reserveCode << endl;

//        cout << personName << " " << endl;
//        cout << reserveCode << " " << endl;
    }
};

// Node Class : Node for the LLStack
template<typename T>
class Node {
public:
//    T *value;
    T *data;
    Node<T> *nextNode;

    Node(T *value) {
        this->data = value;
        nextNode = nullptr;
    }

    void print() {
        data->print();
    }
};

//LLStack Class : Container for Nodes
template<typename T>
class LLStack {
private:
    Node<T> *top;
//    Node<T> *tail;
    int stackSize;
    const int SMAXITEMS = 10; //TODO determine if Prof Manju had a number for this in mind

public:
    // no-arg constructor
    LLStack() {
        top = nullptr;
        stackSize = 0;
    }

// Constructor
    LLStack(T *value) {
        Node<T> *newNode = new Node<T>(value);
        top = newNode;
//        tail = newNode;
        stackSize = 1;
    }

//Destructor
    ~LLStack() {
        Node<T> *temp = top;
        while (top) {
            top = top->nextNode;
            delete temp;
            temp = top;
        }
    }

    void printList() {
        Node<T> *temp = top;
        while (temp != nullptr) {
            temp->print();
            temp = temp->nextNode;
        }
    }

    // stack methods
    bool isFull() {
        if (stackSize == SMAXITEMS)
            return true;
        else
            return false;
    }

    bool isEmpty() {
        if (stackSize == 0)
            return true;
        else
            return false;
    }

    void push(T *item) {
        if (isFull()) {
            cout << "Stack is full, cannot push onto a full stack. (Overflow condition)" << endl;
            return;
        }
        prepend(item);
        ++stackSize;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop from empty stack. (Underflow condition)" << endl;
        }
        else {
            cout << "Popped from the stack: ";
            top->print();
            deleteFirst();
            --stackSize;
        }
    }

    T *peek() {
        if (isEmpty()) {
            cout << "Stack is empty, nothing to peek." << endl;
            return nullptr;
        }
        return top->data;  // returns pointer to top's data member.  Print member with llStack->peek()->print()
    }

//    int getStackSize(LLStack<T> *llStack) {
//        return llStack->stackSize;
//    }

//get and set
    Node<T> *getTop() {
        if (top == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << top->value << endl;
        }
        return top;
    }

//    Node<T> *getTail() {
//        if (tail == nullptr) {
//            cout << "Tail: nullptr" << endl;
//        } else {
//            cout << "Tail: " << tail->value << endl;
//        }
//        return tail;
//    }

    int getStackSize() {
        cout << "Length: " << stackSize << endl;
        return stackSize;
    }

    Node<T> *get(int index) {
        if (index < 0 || index >= stackSize)
            return nullptr;
        Node<T> *temp = top;
        for (int i = 0; i < index; ++i) {
            temp = temp->nextNode;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

//All insert methods
//Insert at end
//    void append(T *value) {
//        Node<T> *newNode = new Node<T>(value);
//        if (stackSize == 0) {
//            top = newNode;
//            tail = newNode;
//        } else {
//            tail->nextNode = newNode;
//            tail = newNode;
//        }
//        stackSize++;
//    }

//Insert at beginning

    // used for stack push
    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (stackSize == 0) {
            top = newNode;
//            tail = newNode;
        } else {
            newNode->nextNode = top;
            top = newNode;
        }
        stackSize++;
    }

//Insert at Index

    bool insert(int index, T *value) {
        if (index < 0 || index > stackSize)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == stackSize) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *temp = get(index - 1);
        newNode->nextNode = temp->nextNode;
        temp->nextNode = newNode;
        stackSize++;
        return true;
    }

//All delete Methods
//Delete Tail

//    void deleteLast() {
//        if (stackSize == 0)
//            return;
//        Node<T> *temp = top;
//        if (stackSize == 1) {
//            top = nullptr;
//            tail = nullptr;
//        } else {
//            Node<T> *pre = top;
//            while (temp->nextNode) {
//                pre = temp;
//                temp = temp->nextNode;
//            }
//            tail = pre;
//            tail->nextNode = nullptr;
//        }
//        delete temp;
//        stackSize--;
//    }

//Delete Head

    // used for stack pop
    void deleteFirst() {
        if (stackSize == 0)
//            cout << "Stack is empty, cannot pop from empty stack. (Underflow condition)" << endl;
            return;
        Node<T> *temp = top;
        if (stackSize == 1) {
            top = nullptr;
//            tail = nullptr;
        } else {
            top = top->nextNode;
        }
        delete temp;
        stackSize--;
    }

//Delete at Index

//    void deleteNode(int index) {
//        if (index < 0 || index >= stackSize)
//            return;
//        if (index == 0)
//            return deleteFirst();
//        if (index == stackSize - 1)
//            return deleteLast();
//
//        Node<T> *prev = get(index - 1);
//        Node<T> *temp = prev->nextNode;
//
//        prev->nextNode = temp->nextNode;
//        delete temp;
//        stackSize--;
//    }
};

template<typename T>
class StackQ {
private:
    LLStack<T> *enQStack;
    LLStack<T> *deQStack;
    int queueSize;
    const int QMAXITEMS = 20; //TODO determine if Prof Manju had a number for this in mind

public:
    // constructor
    StackQ() {
        enQStack = new LLStack<T>();
        deQStack = new LLStack<T>();
        queueSize = 0;
    }

    // destructor
    ~StackQ() {
        delete enQStack;
        delete deQStack;
    }


    void enqueue(T *item) { // TODO test enqueue method
        if (isFull()) {
            cout << "Queue is full, cannot enqueue. (Overflow condition)" << endl;
            return;
        } else {
            enQStack->push(item);
            ++queueSize;
        }
    }

    void dequeue() { // TODO test dequeue method
        if (deQStack->isEmpty()) {
            while (!enQStack->isEmpty()) {
                deQStack->push(enQStack->pop());
            }
            deQStack->pop();
            --queueSize;
            return;
        } else {
            deQStack->pop();
            --queueSize;
        }
    }

    T* peek() { // TODO test peek method
        if (deQStack->isEmpty()) {
            while (!enQStack->isEmpty()) {
                deQStack->push(enQStack->pop());
            }
            return deQStack->peek();

        } else {
            return deQStack->peek();
        }
    }

    bool isFull() { // TODO test isFull method
        if (enQStack->getStackSize() + deQStack->getStackSize() == QMAXITEMS)
            return true; // can simplify method with return enQStack->getStackSize() + deQStack->getStackSize() == QMAXITEMS;
        else
            return false;
    }

    bool isEmpty() {
        if (enQStack->getStackSize() + deQStack->getStackSize() == 0)
            return true; // can simplify method with return enQStack->getStackSize() + deQStack->getStackSize() == 0;
        else
            return false;
    }

    void print() { // TODO write print method

    }



};

//Main Program

int main() {
    auto *t1 = new TicketItem("Joe", "1");
    auto *node1 = new Node<TicketItem>(t1);
//    auto *testStack = new LLStack<Node<TicketItem>>(node1);
    auto *testStack = new LLStack<Node<TicketItem>>();

    // testing pop from empty stack
    cout << "testing pop from empty stack" << endl;
    testStack->pop();

    // testing peek from empty stack
    cout << "testing peek from empty stack" << endl;
    testStack->peek();

    // testing push
    testStack->push(node1);
    testStack->printList();
    cout << endl;
    testStack->push(node1);
    testStack->push(node1);
    testStack->printList();
    cout << endl;

    // testing pop
    testStack->pop();
    testStack->printList();
    cout << endl;

    // testing peek
    cout << "testing peek" << endl;
    testStack->peek()->print();

    // testing push onto full stack
    cout << "testing push onto full stack" << endl;
    for (int i = 0; i < 20; ++i) {
        cout << "i = " << i << endl;
        testStack->push(node1);
    }
    testStack->push(node1);
    testStack->printList();






//creating TicketItem object
//    data * d1 = new TicketItem(10, "a");

//Creating Linked List
//    LLStack<TicketItem> *ll1 = new LLStack<TicketItem>(d1);

//Calling operations on Linked List
//    ll1->printList();

    return 0;
}