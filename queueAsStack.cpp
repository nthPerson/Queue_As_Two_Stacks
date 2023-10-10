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

        cout << personName << " " << endl;
        cout << reserveCode << " " << endl;
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
        this->value = value;
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
    Node<T> *tail;
    int stackSize;
    const int SMAXITEMS = 20; //TODO determine if Prof Manju had a number for this in mind



public:
// Constructor
    LLStack(T *value) {
        Node<T> *newNode = new Node<T>(value);
        top = newNode;
        tail = newNode;
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

    void push(T *item) { // TODO write stack push method

    }

    void pop() { // TODO write stack pop method

    }

    T *peek() { // TODO write stack peek method

    }

//get and set
    Node<T> *getHead() {
        if (top == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << top->value << endl;
        }
        return top;
    }

    Node<T> *getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() {
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
    void append(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (stackSize == 0) {
            top = newNode;
            tail = newNode;
        } else {
            tail->nextNode = newNode;
            tail = newNode;
        }
        stackSize++;
    }

//Insert at beginning

    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (stackSize == 0) {
            top = newNode;
            tail = newNode;
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

    void deleteLast() {
        if (stackSize == 0)
            return;
        Node<T> *temp = top;
        if (stackSize == 1) {
            top = nullptr;
            tail = nullptr;
        } else {
            Node<T> *pre = top;
            while (temp->nextNode) {
                pre = temp;
                temp = temp->nextNode;
            }
            tail = pre;
            tail->nextNode = nullptr;
        }
        delete temp;
        stackSize--;
    }

//Delete Head

    void deleteFirst() {
        if (stackSize == 0)
            return;
        Node<T> *temp = top;
        if (stackSize == 1) {
            top = nullptr;
            tail = nullptr;
        } else {
            top = top->nextNode;
        }
        delete temp;
        stackSize--;
    }

//Delete at Index

    void deleteNode(int index) {
        if (index < 0 || index >= stackSize)
            return;
        if (index == 0)
            return deleteFirst();
        if (index == stackSize - 1)
            return deleteLast();

        Node<T> *prev = get(index - 1);
        Node<T> *temp = prev->nextNode;

        prev->nextNode = temp->nextNode;
        delete temp;
        stackSize--;
    }
};

template<typename T>
class StackQ {
private:
    LLStack<T> *enQStack;
    LLStack<T> *deQStack;
    int queueSize;
    const int QMAXITEMS = 20; //TODO determine if Prof Manju had a number for this in mind

public:
    bool isFull() {
        if (queueSize == QMAXITEMS)
            return true;
        else
            return false;
    }

    bool isEmpty() {
        if (queueSize == 0)
            return true;
        else
            return false;
    }

    void enqueue(T *item) { // TODO write enqueue method

    }

    void dequeue() { // TODO write dequeue method

    }

    T* peek() { // TODO write peek method

    }

    void print() { // TODO write print method

    }

};

//Main Program

int main() {
//creating TicketItem object
//    data * d1 = new TicketItem(10, "a");

//Creating Linked List
//    LLStack<TicketItem> *ll1 = new LLStack<TicketItem>(d1);

//Calling operations on Linked List
//    ll1->printList();

    return 0;
}