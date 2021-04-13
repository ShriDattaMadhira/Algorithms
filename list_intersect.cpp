#include <iostream>
#include <cmath>
using namespace std;

class Node {
public:
    int data;
    Node* next;    
};

int intersect(Node* currA, Node* currB)
{
    while(currA != NULL && currB != NULL)
    {
        if(currA == currB)
            return currA->data;
        currA = currA->next;
        currB = currB->next;
    }
    return -1;
}

int count(Node* headA, Node* headB)
{
    Node* currA = headA;
    Node* currB = headB;
    int m = 0, n = 0;
    
    while(currA != NULL)
    {
        m++;
        currA = currA->next;
    }
    while(currB != NULL)
    {
        n++;
        currB = currB->next;
    }
        
    if(m>n)
    {
        currA = headA, currB = headB;
    }
    else if(m<n)
    {
        currA = headB, currB = headA;
    }
    else
    {
        currA = headA, currB = headB;
        return intersect(currA, currB);
    }
    for(int i = 0; i<abs(m-n); i++)
    {
        if(currA == NULL) return -1;
        currA = currA->next;
    }
    
    return intersect(currA, currB);
}

int main()
{
    
    Node* headA = new Node();
    headA->data = 1;
    
    Node* headB = new Node();
    headB->data = 0;
    
    Node* temp = new Node();
    temp->data = 2;
    headB->next = temp;
    
    temp = new Node();
    temp->data = 3;
    headA->next = temp;
    
    temp = new Node();
    temp->data = 5;
    headA->next->next = temp;
    
    temp = new Node();
    temp->data = 4;
    headB->next->next = temp;
    
    temp = new Node();
    temp->data = 7;
    headA->next->next->next = temp;
    
    temp = new Node();
    temp->data = 6;
    headB->next->next->next = temp;
    headB->next->next->next->next =  headA->next->next->next;
    
    temp = new Node();
    temp->data = 9;
    headA->next->next->next->next = temp;
    
    temp = new Node();
    temp->data = 9;
    headA->next->next->next->next->next = temp;
    
    if(count(headA, headB) == -1)
        cout << "Something is wrong";
    else
        cout << "The intersection point is " << count(headA, headB);
    return 1;
}