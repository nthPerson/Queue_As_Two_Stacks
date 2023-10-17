
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

    void print() {
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

    int getSMAXITEMS() {
        return SMAXITEMS;
    }
    
    void printList() {
        Node<T> *temp = top;
        while (temp != nullptr) {
            temp->print();
            temp = temp->nextNode;
        }
//        delete temp;
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

    // get and set
    Node<T> *getTop() {
        if (top == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            // commented out for use in printQ()
//            cout << "Head: " << top->value << endl;
        }
        return top;
    }

    int getStackSize() {
//        cout << "Length: " << stackSize << endl;
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
        // removed stackSize increment because it is being incremented in push()
//        stackSize++;
    }

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
        // removed decrement to stackSize because it's being done in pop()
//        stackSize--;
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


    void enqueue(T *item) {
        if (isFull()) {
            cout << "Queue is full, cannot enqueue. (Overflow condition)" << endl;
            return;

        // if the enQStack is full
        } else if (enQStack->isFull()) {
            // if there are items in deQStack, move them to tempDQStack to preserve FIFO
            if (!deQStack->isEmpty()) {
                auto *tempDQStack = new LLStack<T>();
                while (!deQStack->isEmpty()) {
                    tempDQStack->push(deQStack->peek());
                    deQStack->pop();
                }
                // move enQStack's items to tempEnqueueStack so oldest members will be moved to deQStack
                auto *tempEnqueueStack = new LLStack<T>();
                while (!enQStack->isEmpty()) {
                    tempEnqueueStack->push(enQStack->peek());
                    enQStack->pop();
                }
                // move tempEnqueueStack's items to deQStack until deQStack is full
                for (int i = 0; i < deQStack->getSMAXITEMS() - tempDQStack->getStackSize(); ++i) {
                    deQStack->push(tempEnqueueStack->peek());
                    tempEnqueueStack->pop();
                }
                // here are some changes
                // move tempEnqueueStack's items back to enQStack
                while (!tempEnqueueStack->isEmpty()) {
                    enQStack->push(tempEnqueueStack->peek());
                    tempEnqueueStack->pop();
                }
                // move tempDQStack's items back to enQStack, preserving FIFO
                while (!tempDQStack->isEmpty()) {
                    deQStack->push(tempDQStack->peek());
                    tempDQStack->pop();
                }
                // now enqueue item
                enQStack->push(item);
                ++queueSize;
                delete tempEnqueueStack;
                delete tempDQStack;

            // if the deQStack is empty, move enQStack's items to deQStack to make room for new enqueue
            } else {
                while (!enQStack->isEmpty()) {
                    deQStack->push(enQStack->peek());
                    enQStack->pop();
                }
                enQStack->push(item);
                ++queueSize;
            }

        // if the enQStack is not full, enqueue
        } else {
            enQStack->push(item);
            ++queueSize;
        }
    }

    void dequeue() {
        if (deQStack->isEmpty()) {
            while (!enQStack->isEmpty()) {
//                deQStack->push(enQStack->pop());
                deQStack->push(enQStack->peek());
                enQStack->pop();
            }
            // after enQStack has been moved to deQStack, pop FIFO
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
//                deQStack->push(enQStack->pop());
                deQStack->push(enQStack->peek());
                enQStack->pop();
            }
            return deQStack->peek();

        } else {
            return deQStack->peek();
        }
    }

    bool isFull() {
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


    // time complexity O(n)
    void printQ() {
        auto *printStack = new LLStack<T>;

        // print deQStack
        deQStack->printList();

        // move enQStack's items to printStack for printing
        while (!enQStack->isEmpty()) {
            printStack->push(enQStack->peek());
            enQStack->pop();
        }
        // print printStack
        printStack->printList();

        // return items back to enQStack
        while (!printStack->isEmpty()) {
            enQStack->push(printStack->peek());
            printStack->pop();
        }

        delete printStack;
    }

};

int main() {
    // LLStack components
    auto *t1 = new TicketItem("Joe", "1");
    auto *t2 = new TicketItem("Amy", "2");
    auto *t3 = new TicketItem("Dave", "3");
    auto *t4 = new TicketItem("Larry", "4");
    auto *t5 = new TicketItem("Robert", "5");
    auto *node1 = new Node<TicketItem>(t1);
    auto *node2 = new Node<TicketItem>(t2);
    auto *node3 = new Node<TicketItem>(t3);
    auto *node4 = new Node<TicketItem>(t4);
    auto *node5 = new Node<TicketItem>(t5);
//    auto *testStack = new LLStack<Node<TicketItem>>(node1);
    auto *testStack = new LLStack<Node<TicketItem>>();

    // StackQ components
    auto *testQ = new StackQ<Node<TicketItem>>();

//    testEnqueueUntilFull();
//    cout << "\nTesting creation of StackQ instance, memory location of StackQ testQ: " << testQ << endl;

    // testing enqueue method
    testQ->enqueue(node1);
    testQ->enqueue(node2);
    testQ->enqueue(node3);
    testQ->dequeue();
    testQ->enqueue(node4);
    testQ->enqueue(node5);

    // testing isFull() method
//    for (int i = 0; i < 20; ++i) {
//        testQ->enqueue(node1);
//    }
    testQ->printQ();


//    // testing pop from empty stack
//    cout << "testing pop from empty stack" << endl;
//    testStack->pop();
//
//    // testing peek from empty stack
//    cout << "testing peek from empty stack" << endl;
//    testStack->peek();
//
//    // testing push
//    testStack->push(node1);
//    testStack->printList();
//    cout << endl;
//    testStack->push(node1);
//    testStack->push(node1);
//    testStack->printList();
//    cout << endl;
//
//    // testing pop
//    testStack->pop();
//    testStack->printList();
//    cout << endl;
//
//    // testing peek
//    cout << "testing peek" << endl;
//    testStack->peek()->print();
//
//    // testing push onto full stack
//    cout << "testing push onto full stack" << endl;
//    for (int i = 0; i < 20; ++i) {
//        cout << "i = " << i << endl;
//        testStack->push(node1);
//    }
//    testStack->push(node1);
//    testStack->printList();

    return 0;
}