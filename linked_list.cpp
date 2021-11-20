#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Dobbel linked list node
struct Node {
    int value;
    Node* next; // node pointer to the next
    Node* prev; // node pointer to the previous

    Node(int new_value) {
    value = new_value;
    next = nullptr;
    prev = nullptr;
    }

    Node(int new_value, Node *n, Node *p) {
    value = new_value;
    next = n;
    prev = p;
    }
};

// class LinkedList
class LinkedList {
    private:
        Node* head; // Node-pointer to head
        Node* tail; // Node-pointer to tail
        int size;

        Node* get_node(int index) {
            if (index < 0 or index > size) {
                throw range_error("Index out of range");
            }
            Node* current = head;
            for (int i=0; i<index; i++) {
                current = current->next;
            }
            return current;
        }

    public:
        LinkedList() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
            //Overloaded constructor to initialize list with elements
            LinkedList(vector<int> vec) {
                head = nullptr;
                tail = nullptr;
                size = 0;
                for (int i = 0; i < vec.size(); i++) {
                    append(vec[i]);
                }
            }

    // Methode for append to the end of the list
    void append(int value) {
        if (head == nullptr) {
            head = new Node(value, nullptr, nullptr);
            size++;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
                current = current->next;
        }
        current->next = new Node(value, nullptr,nullptr);
        size++;
    }

    // Return lenght of elements in list
    // size get updated through the different operations
    int lenght() {
    return size;
    }

    // Methode for printing
    void print() {
        Node* current = head;
        cout << "[";
        while (current->next !=nullptr) {
            cout << current->value;
            cout << ", ";
            current = current->next;
        }
        cout << current->value << "]" << endl;
    }
    //destructor that deallocates all the nodes in the list
    ~LinkedList() {
        Node* current;
        Node* next;
        current = head;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
            }
    }
    //overloads the square bracket operator to access elements by index
    int& operator[](int index) {
        return get_node(index)->value;
    }

    //insert element into list at given index
    void insert(int value, int index) {
      if (index == 0) {
        Node* next = get_node(index);
        head = new Node(value, next, nullptr);
        size++;
        return;
        }
      Node* prev = get_node(index-1);
      Node* next = prev->next;
      prev->next = new Node(value, next, prev);
      size++;
    }

    //removes element at given index
    void remove(int index) {
      Node* prev = get_node(index-1);
      Node* current = get_node(index);
      if (current->next == nullptr) {
        delete current;
        prev->next = nullptr;
        size --;
        return;
        }
      delete current;
      prev->next = get_node(index+1);
      size --;
    }

    //removes element at given index, returning it
    int pop(int index){
      int removed_value;
      removed_value = get_node(index)-> value;
      remove(index);
      return removed_value;
    }

    //pop last element of the list
    int pop(){
        int removed_value;
        removed_value = get_node(size-1)->value;
        remove(size-1);
        return removed_value;
    }

};

int main() {
    LinkedList list;

    //Testing the class
    cout << "Legger til 5, 10, 15, 20 og 25 i slik at vi får følgende liste: " << endl;
    list.append(5);
    list.append(10);
    list.append(15);
    list.append(20);
    list.append(25);
    list.print();

    cout << "Fjerne 15 fra listen med remove slik at listen blir:" << endl;
    list.remove(2);
    list.print();

    cout << "Legger til 15 på index 2 med insert slik at listen blir : " << endl;
    list.insert(15, 2);
    list.print();

    cout << "Fjerner siste tall i listen med pop. Tallet fjernet er " <<list.pop() << endl;
    cout << "Slik at listen blir: " << endl;
    list.print();

    cout << "Lengden til listen er nå: " <<list.lenght()<< endl;
    return 0;
}
