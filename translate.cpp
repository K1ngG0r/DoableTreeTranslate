#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class DoableLinkedList {
private:
    class Node {
    public:
        T value;//значение
        Node* next;//ссылка на след. элемент
        Node* prev;//ссылка на пред. элемент
        Node(T value)
            : value{ value }, next{ nullptr }, prev{ nullptr } {}

    };
    Node* first;
    Node* last;
public:
    DoableLinkedList() :first{ nullptr }, last{ nullptr } {}
    ~DoableLinkedList() {
        if (!IsEmpty()) {
            Node* current = first->next;

            while (current != nullptr) {
                delete current->prev;
                current = current->next;
            }
            delete last;

            first = nullptr;
            last = nullptr;
        }
    }

    bool IsEmpty() const {
        return first == nullptr;
    }

    DoableLinkedList& Push(T value) {
        Node* node = new Node(value);
        if (IsEmpty()) {
            first = node;
            last = node;
            return *this;
        }
        last->next = node;
        node->prev = last;
        last = node;
        return *this;
    }

    Node& Pop() {
        if (IsEmpty()) {
            std::cout << "List is empty!" << std::endl;
            return *this;
        }

        Node* current = last;
        last = current->prev;
        last->next = nullptr;
        delete current;

        return current;
    }

    DoableLinkedList& Sort(int size) {
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size - 1 - i; j++)
            {
                if (this[j] > this[j + 1]) {
                    Swap(this[j], this[j + 1]);
                }
            }
        }
    }

    void Swap(Node* first, Node* second) {
        Node* tmp = first->prev;
        first->next = second->next;
        first->prev = second;
        second->prev = first;
    }

    T operator[](int index) {
        Node* current = first;
        for (size_t i = 0; i < index; i++)
            current = current->next;
        return current->value;
    }

    void Correct() {
        DoableLinkedList <Node>* list = new DoableLinkedList<Node>;
        CreateList();
    }

private:
    void CreateList(Node* node, DoableLinkedList<Node>* list) {
        list->Push(node);
        if(node->)
    }

};

template<typename T>
class TranslateTree {
private:
    class Node {
    public:
        int count;
        T key;
        T translate;
        Node* parent;
        Node* left;
        Node* right;
        Node(T key, T translate) : key{ key }, count{ 0 }, translate { translate },
            parent{nullptr}, left{ nullptr }, right{ nullptr } {}

        void Print(int indent, std::string name) {
            for (int i = 0; i < indent - 1; i++)
            {
                std::cout << '\t';
            }
            std::cout << name << (indent > 0 ? "\t" : "");

            std::cout << key << "--" << translate << ": " << count <<  std::endl;
        }

    };
    Node* root;
public:
    TranslateTree() : root{ nullptr } {}

    ~TranslateTree()
    {
        DeleteNode(root);
    }

    bool IsEmpty() {
        return root == nullptr;
    }
    int GetSize() {
        if (IsEmpty()) {
            return 0;
        }
        return GetSizeOnCascade(root);
    }

    TranslateTree& Push(T key, T translate) {
        Node* node = new Node(key, translate);
        if (IsEmpty()) {
            root = node;
            return *this;
        }

        Node* current = root;

        while (current != nullptr) {
            node->parent = current;
            current = node->key > current->key ?
                current = current->right : current = current->left;
        }

        if (node->key > node->parent->key)
            node->parent->right = node;
        else
            node->parent->left = node;

        return *this;
    }

    bool ElementCheck(T element) {
        Node* current = root;

        while (current != nullptr) {
            if (current->key == element)
                return true;
            current = element > current->key ?
                current = current->right : current = current->left;

        }
        return false;
    }

    TranslateTree& Translate(T key) {
        if (ElementCheck(key)) {
            Node* current = root;

            while (current != nullptr) {
                if (current->key == key) {
                    std::cout << current->translate << std::endl;
                    current->count++;
                }
                current = key > current->key ?
                    current = current->right : current = current->left;
            }
            return *this;
        }
        std::cout << "Element is missing" << std::endl;

        return *this;
    }

    void Print() {
        if (root == nullptr) 
            std::cout << "Empty" << std::endl;
        else
            PrintNode(root, 0, "");
    }

    
    TranslateTree& Education(T name_file) {
        std::ifstream in(name_file);
        if (in.is_open()) {
            char* str = new char[50];
            while (in.getline(str, 100))
            {
                char* c = strchr(str, ' ');
                if (c != 0)
                {
                    char s1[46], s2[40];
                    strcpy_s(s1, 46, str);
                    s1[c - str] = 0;
                    strcpy_s(s2, 40, c + 1);
                    Push(s1, s2);
                }
            }

        }
        in.close();
    }

    TranslateTree& Revers() {

    }



private:
    int GetSizeOnCascade(Node* node) {
        return 1 + (node->left ? GetSizeOnCascade(node->left) : 0) +
                   (node->right ? GetSizeOnCascade(node->right) : 0);
    }

    void DeleteNode(Node* node) {
        if (root != nullptr) {
            if (node->left)
                DeleteNode(node->left);
            if (node->right)
                DeleteNode(node->right);
            delete node;
        }
    }

    void PrintNode(Node* node, int indent, std::string name) {
        node->Print(indent, name);
        if (node->left)
            PrintNode(node->left, indent + 1, "left");
        if (node->right)
            PrintNode(node->right, indent + 1, "right");
    }

};


int main()
{
    srand(time(nullptr));
    setlocale(LC_ALL, "ru");
    TranslateTree<std::string> tree;

    tree.Education("edu.txt");
    tree.Print();
    tree.Translate("apple");
    tree.Translate("tree");
    tree.Translate("hello");
    tree.Print();
    std::cout << tree.GetSize() << std::endl;
}
