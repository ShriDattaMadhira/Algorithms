#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

struct node{
    int value;
    int degree;
    node* parent;
    node* child;
    node* sibling;
};

class BinomialHeap{
public:
    node *H;
    node *Hr;
    
    node* Make_heap();
    node* init_node(int);
    void link(node*, node*);
    node* Union(node*, node*);
    node* Insert(node*, node*);
    node* Merge(node*, node*);
    node* Extract_Min(node*, int);
    node* Minimum(node*);
    void child_to_root(node*);
    void print(node*);
    node* Search(node*, int);
    void decrease_key(node*, int, int);
    void Delete(node*, int);

    BinomialHeap(){
        H = Make_heap();
        Hr = Make_heap();
    }
};

// Initialize Heap
node* BinomialHeap::Make_heap(){
    node* head;
    head = NULL;
    return head;
}

// Linking nodes in Binomial Heap
void BinomialHeap::link(node* n1, node* n2){
    n1->parent = n2;
    n1->sibling = n2->child;
    n2->child = n1;
    n2->degree = n2->degree + 1;
}

// Create Nodes in Binomial Heap
node* BinomialHeap::init_node(int val){
    node* newNode = new node;
    newNode->value = val;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->degree = 0;
    return newNode;
}

// Insert Nodes in Binomial Heap
node* BinomialHeap::Insert(node* H, node* n){
    node* H1 = Make_heap();
    H1 = n;
    H = Union(H, H1);
    return H;
}

// Union Nodes in Binomial Heap.
// Link the trees with the same degrees.
node* BinomialHeap::Union(node* H1, node* H2){
    node *H = Make_heap();
    
    H = Merge(H1, H2);
    if (H == NULL){
        return H;
    }
    
    node* prev;
    node* next;
    node* curr;
    
    prev = NULL;
    curr = H;
    next = curr->sibling;
    // If we are not at the end.
    while (next != NULL){
        // If the degrees are not same then move forward.
        if ((curr->degree != next->degree) || ((next->sibling != NULL)
            && (next->sibling)->degree == curr->degree)){
            prev = curr;
            curr = next;
        }
        else{
            // If the degrees are same, we will check the values to determine the parent.
            if (curr->value <= next->value){
                curr->sibling = next->sibling;
                link(next, curr);
            }
            else{
                // If there are no previous nodes, new heap contains next.
                if (prev == NULL){
                    H = next;
                }
                // Else, we will link prev and next because we will be making curr the child of next.
                else{
                    prev->sibling = next;
                }
                // Make curr the child of next.
                link(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return H;
}

// Merge Nodes in Binomial Heap
// Merge two heaps to create one heap. Doesn't care about degrees.
node* BinomialHeap::Merge(node* H1, node* H2){
    node* H = Make_heap();
    node* y;
    node* z;
    node* a;
    node* b;
    
    y = H1;
    z = H2;
    // Creates a new heap for the old heap and new element.
    // Chooses the element with least degree if both H1 and H2 are not null.
    if (y != NULL){
        if (z != NULL){
            if (y->degree <= z->degree){
                H = y;
            }
            else if (y->degree > z->degree){
                H = z;
            }
        }
        else{
            H = y;
        }
    }
    else{
        H = z;
    }
    // Rearranging the siblings.
    while (y != NULL && z != NULL){
        // Move forward.
        if (y->degree < z->degree){
            y = y->sibling;
        }
        // Make new element the sibling of the head of main heap.
        else if (y->degree == z->degree){
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        // Make the sibling of head of main heap the sibling of new element.
        else{
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

// Display Binomial Heap
void BinomialHeap::print(node* H){
    if (H == NULL){
        cout << "The Heap is empty" << endl;
    }
    node* currPtr = H;
    while (currPtr != nullptr) {
        cout<<"B"<<currPtr->degree<<endl;
        cout<<"There are "<<pow(2, currPtr->degree)<<" nodes in this tree"<<endl;
        cout<<"The level order traversal is"<<endl;
        queue<node*> q;
        q.push(currPtr);
        while (!q.empty()) {
            node* p = q.front();
            q.pop();
            cout<<p->value<<" ";

            if (p->child != nullptr) {
                node* tempPtr = p->child;
                while (tempPtr != nullptr) {
                    q.push(tempPtr);
                    tempPtr = tempPtr->sibling;
                }
            }
        }
        currPtr = currPtr->sibling;
        cout<<endl<<endl;
    }
}

// Extract Minimum
node* BinomialHeap::Extract_Min(node* H1, int c)
{
    Hr = NULL;
    node* t = NULL;
    node* minNode = H1;

    if (minNode == NULL){
        cout << "Nothing to Extract" << endl;
        return minNode;
    }

    int min = minNode->value;
    node* p = minNode;
    // See the minimum of the root nodes.
    while (p->sibling != NULL){
        if ((p->sibling)->value < min){
            min = (p->sibling)->value;
            t = p;
            minNode = p->sibling;
        }
        p = p->sibling;
    }
    
    if(c == 0){
        return minNode;
    }
    else{
        // Extracting the minimum and re-arranging the sibling links.
        // If x is the only root node in the heap.
        if (t == NULL && minNode->sibling == NULL){
            H1 = NULL;
        }
        // If x has siblings and x is the smallest. So, we make x's sibling the head of the heap.
        else if (t == NULL){
            H1 = minNode->sibling;
        }
        // End of the root node list.
        else if (t->sibling == NULL){
            t = NULL;
        }
        // We connect t and x's sibling as x is the smallest and have to be extracted.
        else{
            t->sibling = minNode->sibling;
        }
        // Make children the root nodes.
        if (minNode->child != NULL){
            child_to_root(minNode->child);
            (minNode->child)->sibling = NULL;
        }
        // Remove violations in Hr after making x's children as root nodes.
        H = Union(H1, Hr);
    }
    return minNode;
}

// Makes children of MinNode as root nodes.
void BinomialHeap::child_to_root(node* y){
    if (y->sibling != NULL){
        child_to_root(y->sibling);
        (y->sibling)->sibling = y;
    }
    else{
        Hr = y;
    }
}

// Search Nodes in Binomial Heap
node* BinomialHeap::Search(node* H, int k)
{
    node* x = H;
    node* p = NULL;

    if (x->value == k){
        p = x;
        return p;
    }

    if (x->child != NULL && p == NULL){
        p = Search(x->child, k);
    }
    if (x->sibling != NULL && p == NULL){
        p = Search(x->sibling, k);
    }
    return p;
}

// Decrease key of a node
void BinomialHeap::decrease_key(node* H, int i, int k)
{
    int temp;
    node* target;
    node* y;
    node* z;
    target = Search(H, i);

    if (target == NULL)
    {
        cout<<"ERROR: No such node in heap."<<endl;
    }
    else{
        if (k > target->value)
        {
            cout<<"ERROR: New value is greater than the current value."<<endl;
        }
        else{
            target->value = k;
            y = target;
            z = target->parent;
            // Swim the modified value up to its new position.
            while (z != NULL && y->value < z->value)
            {
                temp = y->value;
                y->value = z->value;
                z->value = temp;
                y = z;
                z = z->parent;
            }
            cout<<"Key reduced successfully"<<endl;
        }
    }
}

// Delete Nodes in Binomial Heap
void BinomialHeap::Delete(node* H, int k)
{
    node* np;
    
    if (H == NULL)
    {
        cout<<"\nHEAP EMPTY!!!!!";
    }
    else{
        decrease_key(H, k, -1000);
        np = Extract_Min(H, 1);
        if (np != NULL){
            cout<<"Node Deleted Successfully"<<endl;
        }
        else{
            cout << "Some error occured in Delete." << endl;
        }
    }
}

int main()
{
    int choice;
    BinomialHeap bh;
    node* n;
    int vals[8] = {3,6,4,8,5,2,1,7};
    
    bh.H = bh.Make_heap();
    for (int i=0; i<(sizeof(vals)/sizeof(*vals)); i++) {
        n = bh.init_node(vals[i]);
        bh.H = bh.Insert(bh.H, n);
    }

    while(1){
        cout << "1.INsert || 2.Extract_Min & Minimum || 3.delete || 4.print || 5. Decrease Key || 99.exit" << endl;
        cout << "Enter your choice:";
        cin >> choice;
        switch(choice){
            case 1:
            {
                int val;
                cout << "Enter the value of the element you want to insert:";
                cin >> val;
                n = bh.init_node(val);
                bh.H = bh.Insert(bh.H, n);
                break;
            }
            case 2:
            {
                int ch;
                cout << "Press '1' to EXTRACT-MIN or '0' to find MINIMUM" << endl;
                cin >> ch;
                n = bh.Extract_Min(bh.H, ch);
                if (n != nullptr) {
                    cout << "Result: " << n -> value << endl;
                } else {
                    cout << "Heap is empty." << endl;
                }
                break;
            }
            case 3:
            {
                int val;
                cout << "Enter key to be deleted:";
                cin >> val;
                bh.Delete(bh.H, val);
                break;
            }
            case 4:
            {
                bh.print(bh.H);
                break;
            }
            case 5:
            {
                int target;
                cout << "Enter the target node:";
                cin >> target;
                
                int c;
                cout << "Do u want to decrease the value by a certain amount? [1-YES | 0-NO] -- ";
                cin >> c;
                if (c == 0) {
                    bh.decrease_key(bh.H, target, 1);
                }
                else if(c == 1){
                    int new_val;
                    cout << "Enter the new Value:";
                    cin >> new_val;
                    bh.decrease_key(bh.H, target, new_val);
                }
                break;
            }
            case 99:
                exit(0);
        }
    }
    return 0;
}
