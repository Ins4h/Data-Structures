#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

const int SIZE = 997;
class Item
{
public:
    int key;

    Item(int key)
    {
        this->key = key;
    }
};

class HashTable
{
private:
    Item **items;

public:
    HashTable()
    {
        items = new Item *[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            items[i] = NULL;
        }
    }
    int hashFunction(int key)
    {
        return ((key % 1000) + (2 << key % 10) + 1) % 997;
    }
    int hashFunction2(int key)
    {
        return (3 * key) % 19 + 1;
    }

    bool insert(int key)
    {
        int h = hashFunction(key);
        while (items[h] != NULL && items[h]->key != key)
        {
            h = hashFunction(h + 1);
        }
        if (items[h] != NULL)
        {
            delete items[h];
            return false;
        }
        items[h] = new Item(key);
        return true;
    }

    void insert2(int key)
    {
        int h = hashFunction(key);
        if (items[h] == NULL)
        {
            items[h] = new Item(key);
        }
        else if (items[h]->key = !key)
        {
            int h = hashFunction2(key);
            items[h] = new Item(key);
        }
        else
            delete items[h];
    }

    int searchKey(int key)
    {
        int h = hashFunction(key);
        while (items[h] != NULL && items[h]->key != key)
        {
            h = hashFunction(h + 1);
        }
        if (items[h] == NULL)
            return -1;
        else
            return items[h]->key;
    }

    int searchKey2(int key)
    {
        int h = hashFunction(key);
        if (items[h] == NULL)
            return -1;
        else if (items[h] != NULL && items[h]->key == key)
            return items[h]->key;
        else
        {
            int h = hashFunction2(key);
            if (items[h] == NULL)
                return -1;
            else
                return items[h]->key;
        }
    }

    bool remove(int key)
    {
        int h = hashFunction(key);
        while (items[h] != NULL)
        {
            if (items[h]->key == key)
                break;
            h = hashFunction(h + 1);
        }
        if (items[h] == NULL)
        {
            // cout << "No element found at key: " << key << endl;
            return false;
        }
        else
        {
            delete items[h];
        }
        // cout << "element deleted" << endl;
        return true;
    }

    bool remove2(int key)
    {
        int h = hashFunction(key);
        if (items[h] == NULL)
        {
            // cout << "No element found at key: " << key << endl;
            return false;
        }
        else if (items[h] != NULL && items[h]->key == key)
        {
            delete items[h];
            // cout << "element deleted" << endl;
            return true;
        }
        else
        {
            int h = hashFunction2(key);
            if (items[h] == NULL)
            {
                // cout << "No element found at key: " << key << endl;
                return false;
            }
            else
            {
                delete items[h];
                // cout << "element deleted" << endl;
                return true;
            }
        }
    }

    void addRandom(int x)
    {
        for (int i = 0; i < x; i++)
        {
            int rn = rand() % 20000 + 20000;
            while (searchKey(rn) != -1)
            {
                rn = rand() % 20000 + 20000;
            }
            insert(rn);
        }
    }

    void addRandom2(int x)
    {
        for (int i = 0; i < x; i++)
        {
            int rn = rand() % 20000 + 20000;
            while (searchKey2(rn) != -1)
            {
                rn = rand() % 20000 + 20000;
            }
            insert2(rn);
        }
    }

    void display(int start, int end)
    {
        for (int i = start; i < end; i++)
        {
            cout << items[i]->key << ", ";
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (items[i] != NULL)
                delete items[i];
            delete[] items;
        }
    }
};

int main()
{
    srand(time(NULL));
    int X, K1, K2, K3, K4;
    FILE *fp = fopen("inlab05.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%d %d", &X, &K1, &K2, &K3, &K4);
    fclose(fp);

    auto start = chrono::high_resolution_clock::now();
    HashTable hash;
    // hash.remove(K1);
    // hash.insert(K1);
    // hash.display(1, 100);
    hash.addRandom(X);
    // hash.display(0, 100);
    // hash.insert(K1);
    // hash.insert(K2);
    // hash.insert(K3);
    // hash.display(0, 100);
    // hash.display(500, 600);
    // cout << hash.searchKey(K1) << endl;
    int ile = 0;
    for (int i = 20000; i < 40000; i++)
    {
        if (hash.searchKey(i) != -1)
        {
            ile++;
            cout << hash.searchKey(i) << endl;
        }
    }
    cout << ile << endl;

    auto koniec = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::milliseconds>(koniec - start);
    cout << "\n Czas wykonania skryptu: " << czas.count() << "ms" << endl;

    return 0;
}