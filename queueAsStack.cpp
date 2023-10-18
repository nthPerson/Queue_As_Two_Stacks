
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

    void printData() {
        top->print();
    }


//    void printList() {
//        Node<T> *temp = top;
//        while (temp != nullptr) {
//            temp->print();
//            temp = temp->nextNode;
//        }
////        delete temp;
//    }

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

    // TODO pop cannot output 'popped from the stack:..." for the printQ method to work properly
    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop from empty stack. (Underflow condition)" << endl;
        }
        else {
            // removed print statement to avoid over-printing nodes in the printQ method
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

    // used for stack pop
    void deleteFirst() {
        if (stackSize == 0)
//            cout << "Stack is empty, cannot pop from empty stack. (Underflow condition)" << endl;
            return;
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

    // destructor
    ~StackQ() {
        delete enQStack;
        delete deQStack;
    }

    int getQueueSize() {
        return queueSize;
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

        // print deQStack by moving it to printStack
        while (!deQStack->isEmpty()) {
            printStack->push(deQStack->peek());
            deQStack->printData();
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
            printStack->printData();
            printStack->pop();
        }
        delete printStack;
    }

    void printEnQStack() {
        auto *printStack = new LLStack<T>;

        if (enQStack->isEmpty()) {
            cout << "enQStack is empty." << endl;
        }

        // print enQStack while moving to printStack
        while (!enQStack->isEmpty()) {
            printStack->push(enQStack->peek());
            enQStack->printData();
            enQStack->pop();
        }
        // return items to enQStack
        while (!printStack->isEmpty()) {
            enQStack->push(printStack->peek());
            printStack->pop();
        }
    }

    void printDeQStack() {
        auto *printStack = new LLStack<T>;

        if (deQStack->isEmpty()) {
            cout << "deQStack is empty." << endl;
        }

        // print enQStack while moving to printStack
        while (!deQStack->isEmpty()) {
            printStack->push(deQStack->peek());
            deQStack->printData();
            deQStack->pop();
        }
        // return items to enQStack
        while (!printStack->isEmpty()) {
            deQStack->push(printStack->peek());
            printStack->pop();
        }
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

    while (userNum >= 0) {
        cout << "Enter a number from 1 to 7 and the corresponding operation will be perfomed.\n" << endl;

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
                stackQueue->printQ();
                cout << endl;
                break;
            case 2:
                cout << "Queue contents before delete:" << endl;
                stackQueue->printQ();

                stackQueue->dequeue();

                cout << "Queue contents after delete:" << endl;
                stackQueue->printQ();
                cout << endl;
                break;
            case 3:
                cout << "Item at the front of the queue:" << endl;
                stackQueue->peek()->print();
                cout << endl;
                break;
            case 4:
                cout << "Current contents of queue:" << endl;
                stackQueue->printQ();
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
                cout << "Thanks for using the Ticket Queue Program!  Have a great day!" << endl;
                userNum = -1;
                break;
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
//    testQ->printQ();


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