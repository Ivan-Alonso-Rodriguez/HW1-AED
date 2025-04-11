#include <iostream>
#include <functional>

template<typename T>
struct Node {
    T data;
    Node* next;
};
template<typename T>
class List {
private:
    Node<T>* head;
public:
    List() : head(nullptr) {}

    T front() {
        return head->data;
    }

    T back() {
        Node<T>* temp = head;
        while (temp->next != nullptr)
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
        node->next = nullptr;

        if (!head) {
            head = node;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    void pop_front() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
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
        while (temp != nullptr) {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void reverse() {
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

    void sort() {
        head = sortList(head);
    }

private:
    Node<T>* sortList(Node<T>* node) {
        if (node == nullptr || node->next == nullptr) return node;

        // Split list into two halves
        Node<T>* temp = nullptr;
        Node<T>* slow = node;
        Node<T>* fast = node;

        while (fast != nullptr && fast->next != nullptr) {
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        temp->next = nullptr;

        Node<T>* l1 = sortList(node);
        Node<T>* l2 = sortList(slow);

        return mergeSort(l1, l2);
    }

    Node<T>* mergeSort(Node<T>* l1, Node<T>* l2) {
        Node<T> dummy;
        Node<T>* temp = &dummy;

        while (l1 && l2) {
            if (l1->data <= l2->data) {
                temp->next = l1;
                l1 = l1->next;
            } else {
                temp->next = l2;
                l2 = l2->next;
            }
            temp = temp->next;
        }

        temp->next = l1 ? l1 : l2;

        return dummy.next;
    }

public:
    void print() {
        Node<T>* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
};

int main() {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.push_front(40);
    list.push_back(8);

    std::cout << "Front: " << list.front() << std::endl;
    std::cout << "Back: " << list.back() << std::endl;

    list.pop_back();
    std::cout << "Back after pop_back: " << list.back() << std::endl;

    list.reverse();
    std::cout << "Front after reverse: " << list.front() << std::endl;
    std::cout << "Back after reverse: " << list.back() << std::endl;

    List<int> list2;
    list2.push_front(10);
    list2.push_front(20);
    list2.push_front(30);
    list2.push_front(40);
    list2.push_back(8);

    std::cout << "Original list: ";
    list2.print();

    list2.sort();
    std::cout << "Sorted list: ";
    list2.print();
    std::cout << std::endl;

    return 0;
}
