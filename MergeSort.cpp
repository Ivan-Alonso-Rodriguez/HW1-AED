#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct ListNode {
    T val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode *next) : val(x), next(next) {}
};

template <typename T>
class Solution {
public:
    ListNode<T>* sortList(ListNode<T>* head){
        //Casos cuando es vacio o uno
        if(head == NULL || head->next == NULL){return head;}
        //Iniciamos los diferentes nodos con el metodo de slow and fast
        ListNode<T>* temp = NULL;
        ListNode<T>* slow = head;
        ListNode<T>* fast = head;
        //Encontramos la mitad para hacer la particion y ayudarnos en el metodo MergeSort
        while(fast != NULL && fast->next != NULL){
            temp = slow;
            //Cuando fast llegue a NULL slow estara en la mitad de este
            slow = slow->next;          //slow aumenta en 1
            fast = fast->next->next;      //fast aumenta en 2
        }
        //Cortamos la lista a la mitad
        temp->next = NULL;
        //Lo volvemos recursivo y enviamos la parte izquierda
        ListNode<T>* l1 = sortList(head);
        //Enviamos la parte derecha
        ListNode<T>* l2 = sortList(slow);
        //Llamamos a mergeSort con ambas partes ya cortadas
        return mergeSort(l1, l2);
    }

    //MergeSort
    ListNode<T>* mergeSort(ListNode<T>* l1, ListNode<T>* l2){
        //Ptr sera la cabeza de nuestra nueva lista ordenada que devolveremos
        ListNode<T>* ptr = new ListNode<T>(0);
        ListNode<T>* temp = ptr;
        //Hacemos la iteracion hasta poder terminar de ordenar ambas listas
        while(l1 != NULL && l2 != NULL){
            //Compara l1 con l2
            if(l1->val <= l2->val){
                //Se guarda el orden
                temp->next = l1;
                //Se avanza l1 para seguir comparando con los otros numeros
                l1 = l1->next;
            }
            else{
                //Se guarda el orden
                temp->next = l2;
                //Se avanza l2 para seguir comparando con los otros numeros
                l2 = l2->next;
            }

            //Avanzamos al siguiente nodo
            temp = temp->next;
        }

        //Cuando quedan restos simplemente los guardamos
        if(l1 != NULL){
            temp->next = l1;
            l1 = l1->next;
        }
        if(l2 != NULL){
            temp->next = l2;
            l2 = l2->next;
        }
        //Retornamos la lista ya ordenada
        return ptr->next;
    }
};

//Funcion para crear una lista enlazada a partir de un vector
//PARA PODER TESTEAR Y DEMOSTRAR FUNCIONAMIENTO
ListNode<int>* createList(const vector<int>& vals) {
    ListNode<int>* head = nullptr;
    ListNode<int>* tail = nullptr;
    for (int val : vals) {
        if (!head) {
            head = new ListNode<int>(val);
            tail = head;
        } else {
            tail->next = new ListNode<int>(val);
            tail = tail->next;
        }
    }
    return head;
}

//Funcion para imprimir
void printList(ListNode<int>* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Casos de prueba de LeetCode
    vector<vector<int>> testCases = {
        {4, 2, 1, 3},
        {-1, 5, 3, 4, 0},
        {}
    };

    Solution<int> sol;
    cout << "---------------------------------------------------" << endl;
    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Lista orginal nr " << i + 1 << ": ";
        ListNode<int>* head = createList(testCases[i]);
        printList(head);

        head = sol.sortList(head);

        cout << "Lista ordenada nr " << i + 1 << ": ";
        printList(head);
        cout << "---------------------------------------------------" << endl;
    }

    return 0;
}
