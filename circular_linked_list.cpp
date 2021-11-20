#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// node structure
struct Node{
    int data;
    Node* next;
    Node* prev;

    Node(int n){
        data = n;
        next = nullptr;
        prev = nullptr;
    }

};

class CircLinkedList
{
	private:
		Node* head; // node pointer to head
		int size; // length of list

	public:
		// initial value of head and size
		CircLinkedList()
		{
			head = nullptr;
			size = 0;
		}

		// Creating a circular linked list with n elements from 0 to n
		CircLinkedList(int n)
		{
			head = nullptr;
			size = 0;
			// creating a list with append
			for (int i = 0; i < n; i++) {
				append(i);
			}
		}

		// linked list deconstructor
		~CircLinkedList(){
            Node* current=head;
            Node* temp;

            for(int i = 0; i < size; i++){
                temp = current->next;
                delete current;
                current = temp;
            }

        }    

		// appned methode adding value to linked list
		void append(int val)
		{
			// if the list is empty, first node is the new val
			if (head == nullptr) {
				head = new Node(val);
				head->next = head;
				head->prev = head;
			} else {
				// node temp points to new val
				Node* temp = new Node(val);
			
			head->prev->next = temp;
            temp->prev = head->prev;
            head->prev = temp;
            temp->next = head;
            }
            size += 1;
		}

		// overload square bracket operator
		int& operator[](int index)
		{
			if (size <= 0) {
				throw out_of_range("List is empty");
			}
			while (index >= size) {
				index -= size;
			}
			Node* current = head;
			for (int i = 0; i < index; i++) {
				current = current->next;
			}
			return current->data;
		}

		// methode printing circular
		void print()
		{
			Node* current = head;
		    cout << "[";
		    for (int i = 0; i < size-1; i++) {
		        cout << current->data;
		        cout << ", ";
		        current = current->next;
		    }
		    cout << current->data << "]" << endl;
		}

		// methode for josephus_sequence problem
		vector<int> josephus_sequence(int k)
		{
			vector<int> vec;
			Node* current = head;
			int count = 1;

		// while loop takes k data from the list and adds them to a vector vec
			while(size > 0) {
				count++;
                current = current->next;
                if(count == k){
                    vec.push_back(current->data);
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                    delete current;
                    count = 0;
                    size --;
                }
			}
			return vec;
		}

};

// function that calls calss whit n list integers and k numbers
// for josephus_sequence problem
int last_man_standing(int n, int k)
{
	CircLinkedList cll(n);
	vector<int> killed = cll.josephus_sequence(k);
	return killed[n-1];
};

int main()
{
	CircLinkedList clist;
	clist.append(0);
	clist.append(2);
	clist.append(4);
	clist.print();
	cout << last_man_standing(67, 7) << endl;
	return 0;
}






