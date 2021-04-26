#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

typedef Node *NodePtr;

class RedBlackTree {
   private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->color = 0;
  }

  // Preorder
  void preOrderHelper(NodePtr node) {
    if (node != TNULL) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        // Case 1: If sibling is RED.
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }
        // Case 2: If sibling is BLACK, and its children are BLACK
        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == NULL) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    // Finding the appropriate node.
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
        break;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }
    // Node not found.
    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    // If the node being removed 'z' has only one child.
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    }
    // If the node being removed 'z' has two children.
    else {
      y = minimum(z->right); // Then the node replacing 'z' should be z's successor.
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right); // Assiging y->right to y's parent
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y); // Assinging y to z's parent.
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    // If it was a black node, it can induce some violations to RB properties.
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  void printHelper(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "Right-";
        indent += "   ";
      } else {
        cout << "Left-";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = NULL;
    TNULL->right = NULL;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        // Case 1: Uncle 'u' is RED.
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          // Case 2: Uncle is Black, k->parent is right and k is left child
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          // Case 3: Uncle is black, k->parent is left and k is right child
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;
        // Case 1 : Uncle is RED
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          // Case 2: Uncle is Black, and k->parent is left and k is right child.
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          // Case 3: Uncle is Black, and k->parent is left and k is left child.
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  // Inserting a node
  void insert(int key) {
    NodePtr node = new Node;
    node->parent = NULL;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = NULL;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == NULL) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == NULL) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == NULL) {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }

  void printTree() {
    //   cout << "In printTree" << endl;
    //   cout << "Root: " << this->root << endl;
    if (root) {
        // cout << "In printTree If" << endl;
      printHelper(this->root, "", true);
    }
  }
    
    int height(Node *node){
        if(node == TNULL){
            return 0;
        }
        if(height(node->left) <= height(node->right)){
            return 1+height(node->right);
        }
        else{
            return 1+height(node->left);
        }
    }
};

int main() {
  RedBlackTree bst;
  std::string line;
  int val;
    ifstream myfile;
    myfile.open("rbtree.txt");
    if(myfile.is_open()){
              while ( getline (myfile,line) )
              {
                  stringstream ss(line);
                  ss >> val;
                  bst.insert(val);
              }
              myfile.close();
    }
    else{
        cout << "Unable to open the file" << endl;
        exit(0);
    }
  int choice;
    cout << "Choices available:" << endl;
    cout << "1.insert 2.delete 3.print 4.min 5.max 6.successor 7.predecessor 8.search 9.height 0.exit" << endl;
    do{
        cout << "Enter any option above: ";
        cin >> choice;
        Node* root = bst.getRoot();
    switch (choice) {
        case 1:
        {
            cout << "Enter a value to insert:";
            cin >> val;
            bst.insert(val);
            break;
            // cout << endl
            //   << "After inserting" << endl;
            // bst.printTree();
        }
        case 2:
        {
            cout << "Enter a value to delete:";
            cin >> val;
            bst.deleteNode(val);
            break;
            // cout << endl
            //   << "After deleting" << endl;
            // bst.printTree();
        }
        case 3:
            bst.inorder();
            break;
            
        case 4:
        {
            Node* min = bst.minimum(root);
            cout << "Minimum of Tree:" << min->data << endl;
            break;
        }
        case 5:
        {
            Node* max = bst.maximum(root);
            cout << "Maximum of Tree:" << max->data << endl;
            break;
        }
        case 6:
        {
            cout << "Enter the element you want successor for:";
            cin >> val;
            Node* suc = bst.successor(bst.searchTree(val));
            cout << "Successor is:" << suc->data << endl;
            break;
        }
        case 7:
        {
            cout << "Enter the element you want predecessor for:";
            cin >> val;
            Node* pred = bst.predecessor(bst.searchTree(val));
            cout << "Predecessor is:" << pred->data << endl;
            break;
        }
        case 8:
        {
            cout << "Enter the element you want to search for:";
            cin >> val;
            Node* item = bst.searchTree(val);
            cout << "0 - BLACK 1-RED" << endl;
            cout << "The key is " << item->data << " Color:" << item->color << endl;
            break;
        }
        case 9:
        {
            cout << "The height of the tree is:" << bst.height(root) << endl;
            break;
        }
        case 0:
            exit(0);
        default:
            cout << "Please choose a relevant option" << endl;
            break;
    }
    }while(choice != 0);
}
