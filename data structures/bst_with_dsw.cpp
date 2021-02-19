#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

class Node
{

public:
    int key;
    Node *left;
    Node *right;
    char tab[10];

    Node(int newKey)
    {
        key = newKey;
        sprintf(tab, "%d", newKey);
        left = NULL;
        right = NULL;
    };
    Node()
    {
        key = NULL;
        sprintf(tab, "%d", key);
        left = NULL;
        right = NULL;
    };

    void preorder(Node *node, int &n, bool reset = false)
    {
        if (reset)
            n = 0;
        if (node != NULL)
        {
            n++;
            cout << node->key << ", ";
            preorder(node->left, n);
            preorder(node->right, n);
        }
    }

    void inorder(Node *node, int &n, bool reset = false)
    {
        if (reset)
            n = 0;
        if (node != NULL)
        {
            n++;
            inorder(node->left, n);
            cout << node->key << ", ";
            inorder(node->right, n);
        }
    }

    void postorder(Node *node, int &n, bool reset = false)
    {
        if (reset)
            n = 0;
        if (node != NULL)
        {
            n++;
            postorder(node->left, n);
            postorder(node->right, n);
            cout << node->key << ", ";
        }
    }

    Node *find(Node *root, int searchKey)
    {
        Node *p = root;
        while (p != NULL)
        {
            if (p->key == searchKey)
            {
                cout << "Znaleziono klucz o wartosci: " << searchKey << endl;
                return p;
            }
            if (p->key < searchKey)
                p = p->right;
            else
                p = p->left;
        }
        cout << "Nie znaleziono klucz o podanej wartosci" << endl;
        return NULL;
    }

    Node *insert(Node *root, int key)
    {
        Node *prev = NULL;
        Node *p = root;
        Node *newNode = new Node(key);

        while (p != NULL)
        {
            if (p->key == key)
            {
                break;
            }
            prev = p;

            if (p->key < key)
                p = p->right;
            else
                p = p->left;
        }

        if (prev == NULL)
        {
            root = newNode;
            return root;
        }
        else if (prev->key < key)
            prev->right = newNode;
        else
            prev->left = newNode;
    };

    Node *add(Node *root, int nodes, bool flag = false)
    {
        srand(time(NULL));
        vector<int> vec;
        if (root)
        {

            for (int i = -10000; i < 10000; i++)
            {
                vec.push_back(i);
            }
            random_shuffle(vec.begin(), vec.end());

            if (!flag)
                for (int i = 0; i < nodes; i++)
                    insert(root, vec.at(i));
            else
                for (int i = 0; i < nodes - 1; i++)
                    insert(root, vec.at(i));
        }
        else
        {
            root = insert(root, rand() % 20000 - 10000);
            add(root, nodes, true);
        };
        return root;
    }

    void remove(Node *root, int key)
    {
        Node *p = root;
        Node *prev = NULL;

        while (p != NULL && p->key != key)
        {
            prev = p;

            if (key < p->key)
                p = p->left;
            else if (key > p->key)
                p = p->right;
        };
        if (p == NULL)
        {
            // cout << "Key not found" << endl;
            return;
        }

        if (p->left == NULL || p->right == NULL)
        {
            Node *temp;

            if (p->left == NULL)
                temp = p->right;
            else if (p->right == NULL)
                temp = p->left;

            if (prev == NULL)
                return;

            if (p == prev->left)
                prev->left = temp;
            else
                prev->right = temp;
            free(p);
        }
        else
        {

            Node *node = NULL;
            Node *temp;

            temp = p->right;
            while (temp->left != NULL)
            {
                node = temp;
                temp = temp->left;
            }

            if (node != NULL)
                node->left = temp->right;
            else
                p->right = temp->right;
            p->key = temp->key;
            free(temp);
        }
        if (root->left && root->right && root->key == key)
        {
            root = NULL;
        }
        return;
    }

    void removeAll(Node *root)
    {
        if (root == NULL)
            return;

        removeAll(root->left);
        removeAll(root->right);
        delete root;
    }

    Node *minValue(Node *root)
    {
        Node *current = root;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    Node *rotate_right(Node *root, Node *grandfather, Node *parent, Node *child)
    {
        if (grandfather != NULL)
        {
            if (grandfather->right == parent)
                grandfather->right = child;
            else
                grandfather->left = child;
        }
        else
            root = child; // Zmiana korzenia drzewa
        Node *temp = child->right;
        child->right = parent;
        parent->left = temp;
        return root;
    }

    Node *rotate_left(Node *root, Node *grandfather, Node *parent, Node *child)
    {
        if (grandfather != NULL)
        {
            if (grandfather->left == parent)
                grandfather->left = child;
            else
                grandfather->right = child;
        }
        else
            root = child; // Zmiana korzenia drzewa
        Node *temp = child->left;
        child->left = parent;
        parent->right = temp;
        return root;
    }

    Node *make_backbone(Node *root)
    {
        Node *grandfather = NULL;
        Node *temp = root;
        while (temp != NULL)
        {
            if (temp->left != NULL)
            {
                Node *temp2 = temp->left;
                root = rotate_right(root, grandfather, temp, temp->left);
                temp = temp2;
            }
            else
            {
                grandfather = temp;
                temp = temp->right;
            }
        }
        return root;
    }

    Node *make_perfect_tree(Node *root, int n) //n = reczywista liczba węzłów na liście
    {
        Node *grandfather = NULL;
        Node *temp = root;
        Node *temp2 = temp->right;
        int m = 1;
        while (m <= n)
            m = 2 * m + 1;
        m = m / 2;
        for (int i = 0; i < n - m; i++)
        {
            temp2 = temp->right;

            if (temp2 != NULL)
            {
                root = rotate_left(root, grandfather, temp, temp->right);
                grandfather = temp2;
                temp = temp2->right;
            }
        }
        while (m > 1)
        {
            m = m / 2;
            grandfather = NULL;
            temp = root;
            for (int i = 0; i < m; i++)
            {
                temp2 = temp->right;
                root = rotate_left(root, grandfather, temp, temp->right);
                grandfather = temp2;
                temp = temp2->right;
            }
        }
        return root;
    }

    void printLevelOrder(Node *root)
    {
        int h = tree_height(root);
        int i;
        for (i = 1; i <= h; i++)
        {
            printGivenLevel(root, i);
            printf("\n");
        }
    }

    /* Print nodes at a given level */
    void printGivenLevel(Node *root, int level)
    {
        if (root == NULL)
            return;
        if (level == 1)
            printf("%d ", root->key);
        else if (level > 1)
        {
            printGivenLevel(root->left, level - 1);
            printGivenLevel(root->right, level - 1);
        }
    }
    int tree_height(Node *root)
    {
        if (root == NULL)
            return 0;
        else
        {
            // Find the height of left, right subtrees
            int left_height = tree_height(root->left);
            int right_height = tree_height(root->right);

            // Find max(subtree_height) + 1 to get the height of the tree
            return max(left_height, right_height) + 1;
        };
    }
};

int main()
{
    int ilosc = 0;
    srand(time(NULL));
    int X1, X2;
    FILE *fp = fopen("inlab04.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%d %d", &X1, &X2);
    fclose(fp);

    auto start = chrono::high_resolution_clock::now();

    Node *root = NULL;

    root = root->add(root, X1);
    cout << "Wysokosc drzewa wynosi: " << root->tree_height(root) << endl;
    root = root->make_backbone(root);
    root = root->make_perfect_tree(root, X1);
    cout << "Wysokosc drzewa wynosi: " << root->tree_height(root) << endl;
    root->removeAll(root);
    root = NULL;
    root = root->add(root, X2);
    cout << "Wysokosc drzewa wynosi: " << root->tree_height(root) << endl;
    root = root->make_backbone(root);
    root = root->make_perfect_tree(root, X2);
    cout << "Wysokosc drzewa wynosi: " << root->tree_height(root) << endl;

    auto koniec = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::milliseconds>(koniec - start);
    cout << "\n Czas wykonania skryptu: " << czas.count() << "ms" << endl;

    return 0;
}