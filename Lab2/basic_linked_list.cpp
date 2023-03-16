#include <iostream>
#include <string>

using namespace std;

class DLL{
public:
    void IH(int);
    void IT(int);
    void RH();
    void RT();
    void S(int);
    void O();

private:
    struct node{
        int data;
        node *prev, *next;
    };
    node *end;
    
public: 
    // Constructer
    DLL(){
        end = new node;
        end->next = end;
        end->prev = end;
    }
};

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int num_of_op, value;
    string op;
    DLL list;

    // Read operation numbers
    cin >> num_of_op;

    // Output
    for(int i = 0; i < num_of_op; i++){
        cin >> op;
        if (op == "IT" || op == "IH" || op == "S") cin >> value;

        if (op == "IH") {list.IH(value);}
        else if (op == "IT") {list.IT(value);}
        else if (op == "RH") {list.RH();}
        else if (op == "RT") {list.RT();}
        else if (op == "S") {list.S(value);}
        else if (op == "O") {list.O();}
    }
}

void DLL::IH(int value){
    // Allocate memory for new node
    node *tmp = new node;

    // Set value of new node
    tmp->data = value;
    tmp->next = end->next;
    tmp->prev = end;

    // Set original head node prev point to new node
    end->next->prev = tmp;

    // Set end next point to new node
    end->next = tmp;
}

void DLL::IT(int value){
    // Allocate memory for new node
    node *tmp = new node;

    // Set value of new node
    tmp->data = value;
    tmp->next = end;
    tmp->prev = end->prev;

    // Set original tail node next point to new node
    end->prev->next = tmp;

    // Set end prev point to new node
    end->prev = tmp;
}

void DLL::RH(){
    // If list is empty, do nothing
    if (end->next == end) return;

    // Temporary store head node
    node *tmp = end->next;

    // Set new head node prev point to end
    tmp->next->prev = end;

    // Set end next point to new head
    end->next = tmp->next;

    // Delete original head node
    delete tmp;
}

void DLL::RT(){
    // If list is empty, do nothing
    if (end->next == end) return;

    // Temporary store head node
    node *tmp = end->prev;

    // Set new tail node next point to end
    tmp->prev->next = end;

    // Set end prev point to new tail
    end->prev = tmp->prev;

    // Delete original tail node
    delete tmp;
}

void DLL::S(int value){
    // If list is empty, print E and terminate
    if (end->next == end) {
        cout << "E\n";
        return;
    }

    // Initally point to head
    node *ptr = end->next;

    // Check the value of point node equal to input
    // If not, point to next node
    // If yes, print Y and terminate the function
    while (ptr != end){
        if (ptr->data == value) {
            cout << "Y\n";
            return;
        }
        ptr = ptr->next;
    }
    cout << "N\n";
}

void DLL::O(){
    // If list is empty, print E and terminate
    if (end->next == end) {
        cout << "E\n";
        return;
    }

    // Initally point to head
    node *ptr = end->next;

    // Print the value of point node, and point to next node
    while (ptr != end){
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << "\n";
}