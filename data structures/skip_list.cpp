#include <iostream>
#include <cstring>
#include <time.h>
#include <chrono>
using namespace std;
//lista z przeskokami

class Node
{
public:
    int key;
    double n;
    char c;

    Node **next;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;
    this->n = rand();
    this->c = 'T';
    next = new Node *[level + 1];
    memset(next, 0, sizeof(Node *) * (level + 1));
}

class SkipList
{
    int LMAX;
    int level;
    Node *head;

public:
    SkipList(int);
    int random_level();
    Node *createNode(int, int);
    void insert(int);
    void displayList();
    void random(int);
    Node *search(int);
    bool del(int);
    void prezentacja(int, int);
    void wypisz(int);
    void delAll();
};

SkipList::SkipList(int LMAX)
{
    this->LMAX = LMAX;
    level = 0;
    head = new Node(-1, LMAX);
};

int SkipList::random_level()
{
    int level = 1;
    while ((rand() % 100 < 0.5 * 100) && (level < LMAX))
    {
        level++;
    }
    return (level);
};

Node *SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
}

void SkipList::insert(int key)
{

    Node *current = head;
    Node **update;
    update = new Node *[LMAX + 1];
    memset(update, 0, sizeof(Node *) * (LMAX + 1));

    for (int i = level; i >= 0; i--)
    {
        while (current->next[i] != NULL &&
               current->next[i]->key < key)
            current = current->next[i];

        update[i] = current;
    }

    current = current->next[0];

    if (current == NULL || current->key != key)
    {
        int rlevel = random_level();

        if (rlevel > level)
        {
            for (int i = level + 1; i < rlevel + 1; i++)
                update[i] = head;

            level = rlevel;
        }

        Node *n = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; i++)
        {
            n->next[i] = update[i]->next[i];
            update[i]->next[i] = n;
        }
        // cout << "Successfully Inserted key " << key << "\n";
    }

    else if (current->key == key)
    {
        current->c = 'D';
        // cout << "Unsuccessfully Inserted key " << key << " " << current->c << "\n";
    }
}

void SkipList::random(int x)
{
    srand(time(NULL));
    for (int i = 0; i < x; i++)
    {

        insert(rand() % 99999 + 99);
        // cout << i << endl;
    };
}

void SkipList::displayList()
{
    cout << "\n**SKIP LIST**" << endl;
    for (int i = 0; i < level; i++)
    {
        Node *node = head->next[i];
        cout << "level" << i << ": ";
        while (node != NULL)
        {
            cout << "K:" << node->key << ":" << node->n << "(" << node->c << ") ";
            node = node->next[i];
        }
        cout << "\n";
    }
}

Node *SkipList::search(int key)
{

    Node *current = head;

    for (int i = level; i >= 0; i--)
    {
        while (current->next[i] != NULL &&
               current->next[i]->key < key)
            current = current->next[i];
    }

    current = current->next[0];

    if (current != NULL && current->key == key)
        return current;
    else
        return NULL;
}

bool SkipList::del(int key)
{
    Node *current = head;
    Node **update;
    update = new Node *[LMAX + 1];
    memset(update, 0, sizeof(Node *) * (LMAX + 1));

    for (int i = level; i >= 0; i--)
    {
        while (current->next[i] != NULL &&
               current->next[i]->key < key)
            current = current->next[i];

        update[i] = current;
    }

    current = current->next[0];

    if (current->key == key)
    {
        for (int i = 0; i <= level; i++)
        {
            if (update[i]->next[i] != current)
                break;
            update[i]->next[i] = current->next[i];
        }
        while (level > 0 && head->next[level] == 0)
            level--;
        return true;
    }
    else
        return false;
}

void SkipList::prezentacja(int y, int n)
{
    cout << "\n**prezentacja**" << endl;
    cout << "K=Key:double(char)"
         << "\n"
         << endl;
    Node *node = head->next[n];
    int i = 0;
    bool wyslano = false;
    for (int j = 0; j < level; j++)
    {
        if (j == n)
        {
            wyslano = true;
            cout << "Wysokosc " << n << ": ";
        }
        else if (level < n + 1 && !wyslano)
        {
            cout << "Brak wynikow o wysokosci: " << n;
            wyslano = true;
        }
        while (node != NULL && i < y && j == n)
        {
            cout << "K=" << node->key << ":" << node->n << "(" << node->c << ") ";
            node = node->next[n];
            i++;
        }
    }

    cout << "\n";
}

void SkipList::wypisz(int n)
{
    cout << "\n**Ilosc wezlow na wysokosci " << n << "**" << endl;
    Node *node = head->next[n];
    int i = 0;
    for (int j = 0; j < level; j++)
    {
        while (node != NULL && j == n)
        {
            node = node->next[n];
            i++;
        }
    }
    cout << i << endl;
}

void SkipList::delAll()
{

    Node *node = head->next[0];
    while (node != NULL)
    {
        del(node->key);
        node = node->next[0];
    }
    cout << "Lista usunieta" << endl;
}

int main()
{

    int X, N, K1, K2, K3, K4, K5;
    FILE *fp = fopen("inlab02.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%d %d %d %d %d %d %d", &X, &N, &K1, &K2, &K3, &K4, &K5);
    fclose(fp);

    auto start = chrono::high_resolution_clock::now();

    SkipList lista(N);
    lista.search(K1);
    lista.random(X);
    // lista.displayList();
    for (int i = 0; i < N - 1; i++)
    {
        lista.wypisz(i);
    }
    lista.insert(K2);
    for (int i = 0; i < N - 1; i++)
    {
        lista.prezentacja(20, i);
    }
    lista.insert(K3);
    lista.prezentacja(20, 0);
    lista.insert(K4);
    lista.prezentacja(20, 0);
    lista.insert(K5);
    for (int i = 0; i < N - 1; i++)
    {
        lista.wypisz(i);
    }
    for (int i = 0; i < N - 1; i++)
    {
        lista.prezentacja(20, i);
    }
    lista.del(K3);
    lista.del(K2);
    lista.del(K5);
    for (int i = 0; i < N - 1; i++)
    {
        lista.wypisz(i);
    }
    for (int i = 0; i < N - 1; i++)
    {
        lista.prezentacja(20, i);
    }

    auto koniec = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::milliseconds>(koniec - start);
    cout << " Czas wykonania skryptu: " << czas.count() << "ms" << endl;

    return 0;
};