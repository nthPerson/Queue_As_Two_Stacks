#include <iostream>
using namespace std;

// TicketItem Class : this class contains the details of the items in the queue
class TicketItem {
private:
    string personName;
    string reserveCode;
public:
//    string personName;
//    string reserveCode;

    TicketItem(string personName, string reserveCode) {
        this->reserveCode = reserveCode;
        this->personName = personName;
    }

    void print() {
        cout << personName << ", " << reserveCode << endl;
    }
    // TicketItem class does not allocate memory using the 'new' operator,
    // and memory management of string objects is managed by the std::sting library.
    // Memory will be managed properly using the default destructor
    ~TicketItem() = default;
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

     /*
     Node class does not allocate memory with the 'new' operator,
     memory will be properly managed using the default destructor.
     Deleting the T *data pointer in this destructor causes the TicketItem
     to be deleted, which causes a segmentation fault in the printQ() method
     because that method moves nodes (that contain TicketItem objects that are
     deleted if the T *data pointer is manually deleted) between enQStack, deQStack
     and the temporary print stacks.  When print tries to move a node that
     contains a deleted ticketItem, a segmentation fault occurs.
      */
    ~Node() = default;

//    ~Node() {
//        delete data;
//    }
};

//LLStack Class : Container for Nodes
template<typename T>
class LLStack {
private:
    Node<T> *top;
    int stackSize;
    const int SMAXITEMS = 10;

public:

    // no-arg constructor
    LLStack() {
        top = nullptr;
        stackSize = 0;
    }

    // constructor
    LLStack(T *value) {
        Node<T> *newNode = new Node<T>(value);
        top = newNode;
        stackSize = 1;
    }

    // destructor
    ~LLStack() {
        Node<T> *temp = top;
        while (top) {
            top = top->nextNode;
            delete temp;
            temp = top;
        }
    }


    void print() {
        if (this->isEmpty()) {
            cout << "Stack is empty." << endl;
        }

        auto *printStack = new LLStack<T>;
        // print stack
        while (!this->isEmpty()) {
            printStack->push(this->peek());
            top->print();
            this->pop();
        }
        // return items to stack
        while (!printStack->isEmpty()) {
            this->push(printStack->peek());
            printStack->pop();
        }
        delete printStack;

    }

    int getSMAXITEMS() {
        return SMAXITEMS;
    }

    void printTopData() {
        top->print();
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
            // removed print statement to avoid over-printing nodes in the print method
//            cout << "Popped from the stack: ";
//            top->print();
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
//    Node<T> *getTop() {
//        if (top == nullptr) {
//            cout << "Top: nullptr" << endl;
//        } else {
//            cout << "Top: " << top->value << endl;
//        }
//        return top;
//    }

    int getStackSize() {
        return stackSize;
    }

    // used for stack push
    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (isEmpty()) { // stackSize == 0
            top = newNode;
//            tail = newNode;
        } else {
            newNode->nextNode = top;
            top = newNode;
        }
    }

    // used for stack pop
    void deleteFirst() {
        if (isEmpty()) { // stackSize == 0
            cout << "Stack is empty, cannot pop from empty stack. (Underflow condition)" << endl;
            return;
        }
        Node<T> *temp = top;
        if (stackSize == 1) {
            top = nullptr;
        } else {
            top = top->nextNode;
        }
        delete temp;
    }

};

template<typename T>
class StackQ {
private:
    LLStack<T> *enQStack;
    LLStack<T> *deQStack;
    int queueSize;
    const int QMAXITEMS = 20;

public:
    // constructor
    StackQ() {
        enQStack = new LLStack<T>();
        deQStack = new LLStack<T>();
        queueSize = 0;
    }

    StackQ(LLStack<T> *enQStack, LLStack<T> *deQStack) {
        this->enQStack = enQStack;
        this->deQStack = deQStack;
        queueSize = 0;
    }

    // destructor
    ~StackQ() {
        delete enQStack;
        delete deQStack;
    }

    int getQueueSize() {
        return queueSize;
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

    void enqueue(T *item) {
        if (isFull()) {
            cout << "Queue is full, cannot enqueue. (Overflow condition)" << endl;
            return;

        // if the enQStack is full, handle cases where deQStack is empty and where deQStack is not empty
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
                // calculate the number of items that can be moved to deQStack and
                // only move that many items from tempEnqueueStack to deQStack
                // number of items able to be moved = deQStack->getSMAXITEMS() - tempDQStack->getStackSize()
                for (int i = 0; i < deQStack->getSMAXITEMS() - tempDQStack->getStackSize(); ++i) {
                    deQStack->push(tempEnqueueStack->peek());
                    tempEnqueueStack->pop();
                }
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
            // if the deQStack is empty and enQStack is full, move enQStack's items to deQStack to make room for new item
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

    T* peek() {
        if (deQStack->isEmpty()) {
            while (!enQStack->isEmpty()) {
                deQStack->push(enQStack->peek());
                enQStack->pop();
            }
            return deQStack->peek();

        } else {
            return deQStack->peek();
        }
    }

    // time complexity O(n)
    void print() {
        auto *printStack = new LLStack<T>;

        // print deQStack by moving it to printStack
        while (!deQStack->isEmpty()) {
            printStack->push(deQStack->peek());
            deQStack->printTopData();
            deQStack->pop();
        }
        // return items to deQStack
        while (!printStack->isEmpty()) {
            deQStack->push(printStack->peek());
            printStack->pop();
        }
        // move enQStack's items to printStack for printing
        while (!enQStack->isEmpty()) {
            printStack->push(enQStack->peek());
            enQStack->pop();
        }
        // return items back to enQStack, print on the way
        while (!printStack->isEmpty()) {
            enQStack->push(printStack->peek());
            printStack->printTopData();
            printStack->pop();
        }
        delete printStack;
    }

    void printEnQStack() {
        if (enQStack->isEmpty()) {
            cout << "enQStack is empty." << endl;
        }

        auto *printStack = new LLStack<T>;
        // print enQStack while moving to printStack
        while (!enQStack->isEmpty()) {
            printStack->push(enQStack->peek());
            enQStack->printTopData();
            enQStack->pop();
        }
        // return items to enQStack
        while (!printStack->isEmpty()) {
            enQStack->push(printStack->peek());
            printStack->pop();
        }
        delete printStack;
    }

    void printDeQStack() {
        if (deQStack->isEmpty()) {
            cout << "deQStack is empty." << endl;
        }

        auto *printStack = new LLStack<T>;
        // print enQStack while moving to printStack
        while (!deQStack->isEmpty()) {
            printStack->push(deQStack->peek());
            deQStack->printTopData();
            deQStack->pop();
        }
        // return items to enQStack
        while (!printStack->isEmpty()) {
            deQStack->push(printStack->peek());
            printStack->pop();
        }
        delete printStack;
    }

};

int main() {
    /*
     * main method requirements
     * create StackQ object
     * display menu to perform the following options:
     * a. Add item to the ticket queue
     * b. Delete from ticket queue
     * c. Peek from the ticket queue
     * d. Display the ticket queue
     * e. Display ticket queue size
     * f. Display enQStack and deQStack
     * g. Exit
     */
    // changed from int userNum = 0;
    int userNum = 0;
//    StackQ<Node<TicketItem>> *stackQueue;
    auto *stackQueue = new StackQ<Node<TicketItem>>();
//    auto *queue = new StackQ<TicketItem>();
    string personName;
    string reserveCode;
    TicketItem *ticketItem;
    Node<TicketItem> *newNode;
//    auto *newQueueItem = new Node<TicketItem>();

    cout << "Welcome to the Ticket Queue Program!\n" << endl;
    cout << "Here is a list of the available options that can be performed on the queue:" << endl;

    // while (userNum >= 0)
    while (userNum != -10000) {
        cout << "Enter a number from 1 to 7 and the corresponding operation will be performed.\n" << endl;

        cout << "1: Add item to the ticket queue." << endl;
        cout << "2: Delete item from the ticket queue." << endl;
        cout << "3: Peek an item from the ticket queue." << endl;
        cout << "4: Display the ticket queue." << endl;
        cout << "5: Display the ticket queue size." << endl;
        cout << "6: Display the contents of enQStack and DeQStack." << endl;
        cout << "7: Exit the program." << endl;

        cin >> userNum;


        switch (userNum) {
            case 1:
                cout << "Enter the name of the person you want to add to the queue and their reserve code, separated by a space:" << endl;
                cin >> personName;
                cin >> reserveCode;

                ticketItem = new TicketItem(personName, reserveCode);
                newNode = new Node(ticketItem);
                stackQueue->enqueue(newNode);

                cout << "Current contents of queue:" << endl;
                stackQueue->print();
                cout << endl;
                break;
            case 2:
                cout << "Queue contents before delete:" << endl;
                stackQueue->print();

                stackQueue->dequeue();

                cout << "Queue contents after delete:" << endl;
                stackQueue->print();
                cout << endl;
                break;
            case 3:
                cout << "Item at the front of the queue:" << endl;
                stackQueue->peek()->print();
                cout << endl;
                break;
            case 4:
                cout << "Current contents of queue:" << endl;
                stackQueue->print();
                cout << endl;
                break;
            case 5:
                cout << "Current ticket queue size: " << stackQueue->getQueueSize() << endl << endl;
                break;
            case 6:
                cout << "Current contents of enQStack:" << endl;
                stackQueue->printEnQStack();

                cout << endl << "Current contents of deQStack:" << endl;
                stackQueue->printDeQStack();
                cout << endl;
                break;
            case 7:
                cout << "Thanks for using the Ticket Queue Program!  Have a nice day!" << endl;
                userNum = -10000;
                break;
            default:
                cout << "Invalid choice.  Please enter a number from 1 to 7" << endl;

        }

    }


    // test components
//    auto *t1 = new TicketItem("Joe", "1");
//    auto *t2 = new TicketItem("Amy", "2");
//    auto *t3 = new TicketItem("Dave", "3");
//    auto *t4 = new TicketItem("Larry", "4");
//    auto *t5 = new TicketItem("Robert", "5");
//    auto *node1 = new Node<TicketItem>(t1);
//    auto *node2 = new Node<TicketItem>(t2);
//    auto *node3 = new Node<TicketItem>(t3);
//    auto *node4 = new Node<TicketItem>(t4);
//    auto *node5 = new Node<TicketItem>(t5);
//    auto *testStack = new LLStack<Node<TicketItem>>(node1);
//    auto *testStack = new LLStack<Node<TicketItem>>();

    // StackQ components
//    auto *testQ = new StackQ<Node<TicketItem>>();

//    testEnqueueUntilFull();
//    cout << "\nTesting creation of StackQ instance, memory location of StackQ testQ: " << testQ << endl;

    // testing enqueue method
//    testQ->enqueue(node1);
//    testQ->enqueue(node2);
//    testQ->enqueue(node3);
//    testQ->dequeue();
//    testQ->enqueue(node4);
//    testQ->enqueue(node5);

    // testing isFull() method
//    for (int i = 0; i < 20; ++i) {
//        testQ->enqueue(node1);
//    }
//    testQ->print();


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