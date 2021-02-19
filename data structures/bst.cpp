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
                return p;
            }
            if (p->key < searchKey)
                p = p->right;
            else
                p = p->left;
        }
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
        return;
    }

    Node *minValue(Node *root)
    {
        Node *current = root;
        while (current && current->left != NULL)
            current = current->left;
        return current;
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
}

;

int main()
{
    int ilosc = 0;
    srand(time(NULL));
    int X, K1, K2, K3, K4;
    FILE *fp = fopen("inlab03.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%d %d %d %d %d %d %d", &X, &K1, &K2, &K3, &K4);
    fclose(fp);

    auto start = chrono::high_resolution_clock::now();

    Node *root = NULL;

    root->remove(root, K1);
    root = root->insert(root, K1);
    root->add(root, X);
    root->inorder(root, ilosc, true);
    cout << " \n inorder: " << ilosc << "\n\n";
    root->preorder(root, ilosc, true);
    cout << " \n preorder: " << ilosc << "\n\n";
    root->insert(root, K2);
    root->inorder(root, ilosc, true);
    cout << " \n inorder: " << ilosc << "\n\n";
    root->insert(root, K3);
    root->insert(root, K4);
    root->remove(root, K1);
    root->preorder(root, ilosc, true);
    cout << " \n preorder: " << ilosc << "\n\n";
    root->find(root, K1);
    root->remove(root, K2);
    root->inorder(root, ilosc, true);
    cout << " \n inorder: " << ilosc << "\n\n";
    root->remove(root, K3);
    root->remove(root, K4);

    auto koniec = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::milliseconds>(koniec - start);
    cout << "\n Czas wykonania skryptu: " << czas.count() << "ms" << endl;

    return 0;
}