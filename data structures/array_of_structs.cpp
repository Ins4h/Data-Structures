#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iomanip>
using namespace std;

struct lab1
{
    int x;
    float y;
    char z;
};
void wyswietl(lab1 *pointer, int n, int x = 0)
{
    if (pointer == NULL)
    {
        cout << "puste" << endl;
    }
    if (x == 0)
        x = n;
    cout << "poczatek" << endl;
    for (int i = 0; i < n && i < x; i++)
    {
        cout << pointer[i].x << " " << pointer[i].z << " " << pointer[i].y << "\n";
    };
    cout << "koniec" << endl;
}

lab1 *losowanie(int n)
{
    srand(time(NULL));
    lab1 *tab;
    tab = new lab1[n];

    bool check;
    for (int i = 0; i < n; i++)
    {
        check = false;
        do
        {
            tab[i].x = rand() % 10000 - 1000;

            check = true;
            for (int j = 0; j < i && check; j++)
            {
                check = tab[i].x != tab[j].x;
            }
        } while (check == false);

        tab[i].z = 'b' + (rand() % 18);
        tab[i].y = 1000 + i;
    };
    // wyswietl(tab, n);
    return tab;
};

void kasowanie(lab1 *pointer, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete &pointer[i];
    };
    delete[] pointer;
    pointer = NULL;
}

void sortowanie(lab1 *pointer, int n)
{
    // wyswietl(pointer, n);
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n - i; j++) //pętla wewnętrzna
            if (pointer[j - 1].x > pointer[j].x)
            {
                //zamiana miejscami
                lab1 temp = pointer[j - 1];
                pointer[j - 1] = pointer[j];
                pointer[j] = temp;
            }
    // wyswietl(pointer, n);
}

int zliczanieZnakow(lab1 *pointer, int n, char znak)
{
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        if (pointer[i].z == tolower(znak))
            x++;
    }

    return x;
}

int main()
{

    int N;
    char X;
    int znaki;
    FILE *fp = fopen("inlab01.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%d %c", &N, &X);
    fclose(fp);

    auto start = chrono::high_resolution_clock::now();

    lab1 *tab = losowanie(N); // powinno być **tab
    sortowanie(tab, N);
    znaki = zliczanieZnakow(tab, N, X);
    kasowanie(tab, N);

    auto koniec = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::milliseconds>(koniec - start);

    wyswietl(tab, N, 20);
    cout << "Liczba wystapien znaku " << X << ": " << znaki << endl;
    cout << " Czas wykonania skryptu: " << czas.count() << "ms" << endl;
    return 0;
}