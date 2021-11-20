#include <iostream>
#include <vector>
#include <stdexcept>
#include <math.h>
using namespace std;

class ArrayList
{
    private:
        // Constructor
        int *data;
        int size = 0;
        int capacity = 1;
        int growth = 2;

        // private method resizing new array by increasing capacity with factor of 2
        void resize() 
        {
            int newCapacity = growth * capacity;
            int *newData = new int[newCapacity];
            for (int i = 0; i < capacity; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

    // class objects
    public:
        // creating new empty array if ArrayList() is called
        ArrayList() {
            data = new int[capacity];
        }
        
        // creating array from input
        ArrayList(vector<int> newData)
        {
            data = new int[capacity];
            for (int x : newData) {
                append(x);
            }
        }

        // Deconstructor deallocating storage array
        ~ArrayList()
        {
            delete []data;
        }

        // returning length of array
        int length() {
            return size;
        }

        // object adding integer to array
        void append(int x)
        {
            if (size >= capacity) {
                resize();
            }
            data[size] = x;
            size++;
        }

        // object printing array in order on a single line
        void print()
        {
            cout << "[";
            for (int i = 0; i < size - 1; i++) {
                cout << data[i] << ", ";
            }
            cout << data[size - 1] << "]\n";
        }

        // overloading the square-bracketing operator
        int &operator[](int index)
        {
            if ((index >= size) || (index < 0)) {
                throw out_of_range("Index " + to_string(index) + " is out of range to array with size " + to_string(size));
            }
            return data[index];
        }

        // insert integer in to array at given index
        void insert(int val, int index)
        {
            if(index <= size){
                size++;
                
                for (int i = 0; i < (size - index); i++) {
                    data[size-i] = data[size-i-1];
                }
                data[index] = val;
            }
            else {
                throw out_of_range("Index " + to_string(index) + " is out of range to array with size " + to_string(size));
            }
        }

        // remove index from array
        void remove(int index){
            size--;

            int i = index;
            while(i < (size)){
                data[i] = data[i+1];
                i++;
            }
            if (size < capacity/4) {
                shrink_to_fit();
            }
        }

        // removes index from array and stores it as an integer
        int pop(int index){
            int removed_value = data[index];
            remove(index);
            if (size < capacity / 4) {
                shrink_to_fit();
            }
            return removed_value;
        }

        // removes last index from array and stores it as an integer
        int pop(){
            int last_value = pop(size-1);
            if (size < capacity/4) {
                shrink_to_fit();
            }
            return last_value;
        }

        // reducing capacity to fit new size
        void shrink_to_fit(){
            int closest_exp = ceil(log(size)/log(2));
            capacity = pow(2, closest_exp);

            int* newData = new int[capacity];
            for(int i=0; i<size; i++){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;

        }
};


// finding if a number is prime
bool is_prime(int n) 
{
    if (n <= 1) {
        return false;
    }
    for (int d = 2; d < n; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

// function appending primenumbers to ArrayList
ArrayList find_primes()
{
    ArrayList primes{};
    int x = 0;
    // while loop finding 10 primenumbers
    int i = 0;
    while (i < 10) {
        // checking if x is a prime number
        bool prime = is_prime(x);
        if (prime == true) {
            primes.append(x);
            i += 1;
        }
        x++;
    }
    return primes;
}

// function testing
void test_ArrayList()
{
    ArrayList primes = find_primes();
    int expected[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    for(int i=0; i<10; i++){
        if(expected[i] != primes[i]){
            throw out_of_range("index is out of range and or the value does not equal");
        }
    }

    primes.print();
    /*
    The function returns:
    $ ./array
    [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]

    */
}

int main()
{
    test_ArrayList();
    return 0;
}











