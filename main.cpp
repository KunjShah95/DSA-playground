#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/* =======================
   Custom Dynamic Array
   ======================= */
template <typename T>
class DynamicArray
{
private:
    T *arr;
    int capacity;
    int size;
    void resize()
    {
        int newCapacity = capacity * 2;
        T *temp = new T[newCapacity];
        for (int i = 0; i < size; ++i)
            temp[i] = arr[i];
        delete[] arr;
        arr = temp;
        capacity = newCapacity;
    }

public:
    DynamicArray(int cap = 4) : capacity(cap), size(0)
    {
        arr = new T[capacity];
    }
    ~DynamicArray() { delete[] arr; }
    void push_back(const T &val)
    {
        if (size == capacity)
            resize();
        arr[size++] = val;
    }
    T get(int index) const
    {
        if (index >= 0 && index < size)
            return arr[index];
        throw out_of_range("Index out of range.");
    }
    int getSize() const { return size; }
    void display() const
    {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }
};

/* =======================
   Singly Linked List
   ======================= */
template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node *head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void push_front(T val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    void push_back(T val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *cur = head;
        while (cur->next)
            cur = cur->next;
        cur->next = newNode;
    }
    bool search(T val)
    {
        Node *cur = head;
        while (cur)
        {
            if (cur->data == val)
                return true;
            cur = cur->next;
        }
        return false;
    }
    void display()
    {
        Node *cur = head;
        while (cur)
        {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL" << endl;
    }
};

/* =======================
   Stack Implementation
   (Using Linked List)
   ======================= */
template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val, Node *nxt = nullptr) : data(val), next(nxt) {}
    };
    Node *topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack()
    {
        while (topNode)
        {
            Node *temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
    void push(T val)
    {
        topNode = new Node(val, topNode);
    }
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        Node *temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
    T top()
    {
        if (isEmpty())
            throw runtime_error("Stack is empty!");
        return topNode->data;
    }
    bool isEmpty() const { return topNode == nullptr; }
    void display()
    {
        Node *cur = topNode;
        cout << "Stack top -> ";
        while (cur)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

/* =======================
   Queue Implementation
   (Using Linked List)
   ======================= */
template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node *frontNode;
    Node *rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}
    ~Queue()
    {
        while (frontNode)
        {
            Node *temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }
    void enqueue(T val)
    {
        Node *newNode = new Node(val);
        if (!rearNode)
        {
            frontNode = rearNode = newNode;
            return;
        }
        rearNode->next = newNode;
        rearNode = newNode;
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node *temp = frontNode;
        frontNode = frontNode->next;
        if (!frontNode)
            rearNode = nullptr;
        delete temp;
    }
    T front()
    {
        if (isEmpty())
            throw runtime_error("Queue is empty!");
        return frontNode->data;
    }
    bool isEmpty() const { return frontNode == nullptr; }
    void display()
    {
        Node *cur = frontNode;
        cout << "Queue front -> ";
        while (cur)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << "<- rear" << endl;
    }
};

/* =======================
   Binary Search Tree
   ======================= */
class BST
{
private:
    struct Node
    {
        int key;
        Node *left;
        Node *right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };
    Node *root;
    Node *insert(Node *node, int key)
    {
        if (!node)
            return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        // Duplicate keys are not inserted.
        return node;
    }
    bool search(Node *node, int key)
    {
        if (!node)
            return false;
        if (node->key == key)
            return true;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }
    void inorder(Node *node)
    {
        if (node)
        {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }
    void destroy(Node *node)
    {
        if (node)
        {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }
    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key); }
    void inorder()
    {
        inorder(root);
        cout << endl;
    }
};

/* =======================
   Interactive Menu
   ======================= */
void printMenu()
{
    cout << "\n------ DSA Playground Menu ------\n";
    cout << "1. Test Dynamic Array\n";
    cout << "2. Test Linked List\n";
    cout << "3. Test Stack\n";
    cout << "4. Test Queue\n";
    cout << "5. Test Binary Search Tree\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

void testDynamicArray()
{
    cout << "\n-- Testing Dynamic Array --\n";
    DynamicArray<int> arr;
    for (int i = 1; i <= 10; ++i)
        arr.push_back(i * 10);
    cout << "Array elements: ";
    arr.display();
}

void testLinkedList()
{
    cout << "\n-- Testing Linked List --\n";
    LinkedList<string> list;
    list.push_back("Hello");
    list.push_back("DSA");
    list.push_back("World");
    list.push_front("Start:");
    cout << "Linked List content: ";
    list.display();
    cout << "Searching for \"DSA\": "
         << (list.search("DSA") ? "Found" : "Not Found") << endl;
}

void testStack()
{
    cout << "\n-- Testing Stack --\n";
    Stack<int> s;
    for (int i = 1; i <= 5; ++i)
    {
        s.push(i);
        cout << "Pushed " << i << endl;
    }
    s.display();
    cout << "Top element: " << s.top() << endl;
    s.pop();
    cout << "After one pop: ";
    s.display();
}

void testQueue()
{
    cout << "\n-- Testing Queue --\n";
    Queue<int> q;
    for (int i = 1; i <= 5; ++i)
    {
        q.enqueue(i * 5);
        cout << "Enqueued " << i * 5 << endl;
    }
    q.display();
    cout << "Front element: " << q.front() << endl;
    q.dequeue();
    cout << "After one dequeue: ";
    q.display();
}

void testBST()
{
    cout << "\n-- Testing Binary Search Tree --\n";
    BST tree;
    int keys[] = {50, 30, 20, 40, 70, 60, 80};
    for (int k : keys)
    {
        tree.insert(k);
        cout << "Inserted " << k << " into BST.\n";
    }
    cout << "Inorder traversal: ";
    tree.inorder();
    int searchKey = 40;
    cout << "Searching for key " << searchKey << ": "
         << (tree.search(searchKey) ? "Found" : "Not Found") << endl;
}

/* =======================
   Main Function
   ======================= */
int main()
{
    int choice;
    while (true)
    {
        printMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            testDynamicArray();
            break;
        case 2:
            testLinkedList();
            break;
        case 3:
            testStack();
            break;
        case 4:
            testQueue();
            break;
        case 5:
            testBST();
            break;
        case 6:
            cout << "Exiting DSA Playground. Goodbye!\n";
            exit(0);
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}