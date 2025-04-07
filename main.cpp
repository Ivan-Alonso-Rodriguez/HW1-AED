#include <iostream>
template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
class List {
private:
    Node<T> * head;
public:
    T front() {
        Node<T>* temp = head;
        return temp->data;
    }

    T back() {
        Node<T>* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        return temp->data;
    }

    void push_front(int x) {
        Node<T>* node = new Node<T>;
        node->data = x;
        node->next = head;
        head = node;
    }

    void push_back(int x) {
        Node<T>* node = new Node<T>;
        node->data = x;
        Node<T>* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
        node->next = NULL;
    }

    void pop_front() {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if (head->next == NULL) {
            delete head;
            head = NULL;
        }
        else {
            Node<T>* temp = head;
            while (temp->next->next != NULL) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = NULL;
        }
    }

    T operator[](int pos) {
        Node<T>* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        Node<T>* temp = head;
        int count = 0;
        while (temp != NULL) {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void clear() {
        while (head->next != NULL) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse() {
        if (!head || head->next == NULL) {
            return;
        }

        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }


};



int main() {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.push_front(40);
    list.push_back(8);
    std::cout<<list.front()<<std::endl;
    std::cout<<list.back()<<std::endl;
    list.pop_back();
    std::cout<<list.back()<<std::endl;
    list.reverse();
    std::cout<<list.front()<<std::endl;
    std::cout<<list.back()<<std::endl;
    return 0;
}