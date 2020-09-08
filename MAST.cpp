#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>   
#include <stdlib.h> 


struct Drzewo
{
    Drzewo* syn;
    Drzewo* rodzic;
    Drzewo* brat;
    int liczba;
    int wezly;
    Drzewo() : syn(nullptr),rodzic(nullptr),brat(nullptr),liczba(NULL),wezly(0) {
}
};

struct Kolejka
{
    Drzewo* wezel;
    Kolejka* nast;
    Kolejka(Drzewo* d, Kolejka* k) : wezel(d), nast(k) {
}
    Kolejka() : wezel(nullptr), nast(nullptr) {
}
};

struct Dzieci
{
    Dzieci* next;
    int i;
    Dzieci(Dzieci* n, int i) : next(n), i(i) {
}
    Dzieci() : next(nullptr), i(NULL) {
}
};

void nowy(Drzewo*& drzewo, Drzewo*& znacznik, bool relacja)
{
    Drzewo* nowy = new Drzewo();
   
    if (drzewo)
    {
        if (relacja)
        {
            znacznik->syn = nowy;
            znacznik->syn->rodzic = znacznik;
        
}
        else
        {
            znacznik->brat = nowy;
            if (znacznik->rodzic)
                znacznik->brat->rodzic = znacznik->rodzic;

        
}
    
}
    else
        drzewo = znacznik = nowy;
}

void wierzcholki(Drzewo*& D, Kolejka* K, int& x)
{
    if (D)
    {
        if (D == K->wezel) {
            D->liczba = x + 10;
            x++;
        
}
        if (D->syn) wierzcholki(D->syn, K, x);

        wierzcholki(D->brat, K, x);

    
}
}

void search(Drzewo* D, int key, int& q)
{
    if (D)
    {

        if (D->liczba == key)
        {
            q = 1;
            return;
        
}
        if (D->syn) search(D->syn, key, q);
        search(D->brat, key, q);

    
}

}
void s_nod(Drzewo* D, int nod, int key, int& q)
{
    if (D)
    {
        if (D->liczba == nod)
        {
            
            if (D->syn)search(D->syn, key, q);
            else search(D, key, q);
            return;
        
}
        else {
            if (D->syn) s_nod(D->syn, nod, key, q);
            s_nod(D->brat, nod, key, q);
        
}
    
}
}

void bfs(Drzewo*& D, Kolejka* K, int& x)
{
    Kolejka* tmp2;
    while (K)
    {
        tmp2 = K;
        if (K->wezel->liczba == 0)
        {
            wierzcholki(D, K, x);
        
}
        while (K->nast)
            K = K->nast;

        if (tmp2->wezel->syn)
        {
            K->nast = new Kolejka(tmp2->wezel->syn, nullptr);
            K = K->nast;
            while (K->wezel->brat)
            {
                K->nast = new Kolejka(K->wezel->brat, nullptr);
                K = K->nast;
            
}
        
}
        K = tmp2->nast;
    
}
}

int silnia(int x)
{
    if (x == 0) return 1;
    else return x * silnia(x - 1);   
}

void perm(int** tab, int x)
{
    int y = silnia(x - 1);    
    if (x == 2)
    {
        tab[1][0] = tab[0][1];
        tab[1][1] = tab[0][0];
        return;
    
}
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
            tab[j + (i * y)][0] = tab[0][i];

        int** p = (int**)malloc(y*sizeof(int*));

        for (int j = 0; j < y; j++)
            p[j] = (int*)malloc((x-1)*sizeof(int));


        for (int j = 0; j < x - 1; j++)
        {
            int k = (i + 1 + j) % x;
            p[0][j] = tab[0][k];
        
}
        perm(p, x - 1);

        for (int j = 0; j < y; j++)
        {
            for (int l = 1; l < x; l++)
            {
                tab[j + (i * y)][l] = p[j][l - 1];
            
}
        
}

        for (int j = 0; j < y; j++)
            free(p[j]);
        free(p);

    
}
}

void komb(int** tab, int* liczby, int x, int y)
{
   
    int* tmp = new int[x];
    int pom = 0, z = 0, q = 0;
    for (int i = (1 << x); --i;)
    {
        for (int k = 0; k < x; ++k)
        {
            if ((i >> k) & 1) {
                tmp[k] = liczby[k];
                pom++;
            
}
        
}
        if (pom == y)
        {
            q = 0;
            for (int l = 0; l < x; l++)
            {
                if (tmp[l] != 0) {
                    tab[z][q] = tmp[l];
                    q++;
                
}
            
}
            z++;
        
}
        pom = 0;
        for (int l = 0; l < x; l++)
            tmp[l] = 0;

    
}
    delete[] tmp;
}

void dzieci(Drzewo* D, int w, int*& tab, int& i)
{
    if (D)
    {
        if (D->liczba == w)
        {
            i = 1;
            int k = 0;
            D = D->syn;
            Dzieci* d = new Dzieci(nullptr, D->liczba);
            Dzieci* tmp = d;
            while (D)
            {
                D = D->brat;
                if (D)
                {
                    d->next = new Dzieci(nullptr, D->liczba);
                    d = d->next;
                    i++;
                
}
            
}
            d = tmp;
            tab = (int*)malloc(i*sizeof(int));           
           
            k = 0;
            while (d)
            {
                tab[k] = d->i;
                d = d->next;
                k++;
            
}            

            return;
        
}
        if (D->syn) dzieci(D->syn, w, tab, i);
        dzieci(D->brat, w, tab, i);
    
}

}

int porownanie_2(int** tab, int* w1, int* w2, int i1, int i2)
{
    int l = 0, m = 0, y;
    

        if (i1==i2)
        {         
            y = silnia(i1);
            int** pom = (int**)malloc(y * sizeof(int*));
            for (int i = 0; i < y; i++)
                pom[i] = (int*)malloc(i1 * sizeof(int));
            for (int i = 0; i < i1; i++)
                pom[0][i] = w1[i];

            perm(pom, i1);
            for (int i = 0; i < silnia(i1); i++)
            {
                for (int j = 0; j < i2; j++)
                    l += tab[pom[i][j]][w2[j]];


                if (l > m) m = l;
                l = 0;
            
}
            for (int i = 0; i < y; i++)
                free(pom[i]);
            free(pom);

        
}
        else if (i1>i2)
        {
            int w = silnia(i1) / (silnia(i2) * silnia(i1 - i2));
            int** pom1 = new int* [w];
            for (int i = 0; i < w; i++)
                pom1[i] = new int[i2];
            int* kopia = new int[i1];
            for (int i = 0; i < i1; i++)
                kopia[i] = w1[i];
            komb(pom1, kopia, i1, i2);
            for (int k = 0; k < w; k++)
            {
                y = silnia(i2);
                int** pom = (int**)malloc(y * sizeof(int*));
                for (int j = 0; j < y; j++)
                    pom[j] = (int*)malloc(i2 * sizeof(int));
                for (int j = 0; j < i2; j++)
                    pom[0][j] = pom1[k][j];

                perm(pom, i2);
                for (int i = 0; i < y; i++)
                {
                    for (int j = 0; j < i2; j++)
                        l += tab[pom[i][j]][w2[j]];



                    if (l > m) m = l;
                    l = 0;
                
}
                for (int i = 0; i < y; i++)
                    free(pom[i]);
                free(pom);

            
}
            delete[] kopia;
            for (int i = 0; i < w; i++)
                delete[] pom1[i];
            delete[] pom1;
        
}
        else
        {

            int w = silnia(i2) / (silnia(i1) * silnia(i2 - i1));
            int** pom1 = new int* [w];
            for (int i = 0; i < w; i++)
                pom1[i] = new int[i1];
            int* kopia = new int[i2];
            for (int i = 0; i < i2; i++)
                kopia[i] = w2[i];
            komb(pom1, kopia, i2, i1);            
            for (int k = 0; k < w; k++)
            {
                y = silnia(i1);                               
                int** pom = (int**)malloc(y * sizeof(int*));
                for (int j = 0; j < y; j++)
                    pom[j] = (int*)malloc(i1 * sizeof(int));
                for (int j = 0; j < i1; j++)
                    pom[0][j] = pom1[k][j];

                perm(pom, i1);
                for (int i = 0; i < y; i++)
                {
                    
                    for (int j = 0; j < i1; j++)
                        l += tab[w1[j]][pom[i][j]];

                    if (l > m) m = l;
                    l = 0;
                
}
                for (int i = 0; i < y; i++)
                    free(pom[i]);
                free(pom);
            
}
            delete[] kopia;
            for (int i = 0; i < w; i++)
                delete[] pom1[i];
            delete[] pom1;

        
}
    
    return m;
}
int porownanie_1(int** tab, int* w1, int i1, int w_1, int i2, int w_2, int* w2)
{
    int l1 = 0, l2 = 0, l3, t, i;
    for (i = 0; i < i1; i++)
    {
        t = tab[w1[i]][w_2];
        if (t > l1) l1 = t;
    
}
    for (i = 0; i < i2; i++)
    {
        t = tab[w_1][w2[i]];
        if (t > l2) l2 = t;
    
}
    l3 = porownanie_2(tab, w1, w2, i1, i2);
    if (l1 > l2) t = l1;
    else t = l2;
    if (l3 > t) return l3;
    else return t;
}

int main(void)
{
    int n = 0, tmp, x = 1;
    int* tab1, * tab2;
    Drzewo* drzewo = nullptr;
    Drzewo* znacznik = nullptr;
    scanf("%d", &n);
    Drzewo** drzewa =(Drzewo**)malloc(n*sizeof(Drzewo*));
    tmp = getchar() - 48;
    for (int i = 0; i < n; i++)
    {
        
        bool jeden = false;
        nowy(drzewo, znacznik, true);
        while (1)
        {

            tmp = getchar() - 48;
            if (tmp == 11)
            {
                getchar();
                break;
            
}
            else if (tmp == -8)
            {
                nowy(drzewo, znacznik, true);
                znacznik = znacznik->syn;
                drzewo->wezly++;
            
}
            else if (tmp == -7) {

                if (znacznik->rodzic)
                    znacznik = znacznik->rodzic;

            
}
            else if (tmp == -4)
            {
                nowy(drzewo, znacznik, false);
                znacznik = znacznik->brat;
            
}
            else {
                if (tmp == 1)
                {
                    jeden = true;
                    znacznik->liczba = tmp;
                
}
                else if ((jeden) && (tmp == 0))
                {
                    znacznik->liczba = 10;
                    jeden = false;
                
}
                else
                {
                    znacznik->liczba = tmp;
                    jeden = false;
                
}

            
}

        
}
        drzewa[i] = drzewo;       
        drzewo = nullptr;
        znacznik = nullptr;
        Kolejka* kolejka = new Kolejka(drzewa[i], nullptr);
        bfs(drzewa[i], kolejka, x);
        delete kolejka;
        x = 1;
    
}
    delete drzewo;
    delete znacznik;


    for (int i = 0; i < n; i++)
    {

        for (int j = i + 1; j < n; j++)
        {
            int** tablica = (int**)malloc((drzewa[i]->wezly + 11)*sizeof(int*));

            for (int k = 0; k < drzewa[i]->wezly + 11; k++)
                tablica[k] = (int*)malloc((drzewa[j]->wezly + 11)*sizeof(int));
           


            for (int k = 0; k < drzewa[i]->wezly + 11; k++)
            {
                for (int l = 0; l < drzewa[j]->wezly + 11; l++)
                {
                    if (l == 0) tablica[k][l] = k;
                    else if ((k == 0)&&(l<11)) tablica[k][l] = l;
                    else if ((k == 0)&&(l>=11)) tablica[k][l] = l+10;
                    else if ((k==l)&&(k<11)&&(l<11))
                        tablica[k][l] = 1;
                    else if((k!=0)&&(l!=0)&&(k!=l)) tablica[k][l] = 0;
                
}
            
}           
            for (int k = 11; k < drzewa[i]->wezly + 11; k++)
            {
                for (int l = 1; l < 11; l++)
                {
                    tablica[k][l] = 0;
                    s_nod(drzewa[i], tablica[k][0], tablica[0][l], tablica[k][l]);
                
}
            
}
            for (int k = 11; k < drzewa[j]->wezly + 11; k++)
            {
                for (int l = 1; l < 11; l++)
                {
                    tablica[l][k] = 0;
                    s_nod(drzewa[j], tablica[0][k] - 10, tablica[l][0], tablica[l][k]);
                
}
            
}
            int usun = 0;
            for (int k = drzewa[i]->wezly + 10; k > 10; k--)
            {
                int ile_d1, ile_d2;

                dzieci(drzewa[i], k, tab1, ile_d1);
                for (int l = drzewa[j]->wezly + 10; l > 10; l--)
                {

                    dzieci(drzewa[j], l, tab2, ile_d2);
                    
                    tablica[k][l] = porownanie_1(tablica, tab1, ile_d1, k, ile_d2, l, tab2);                   
                    if (tablica[k][l] > usun) usun = tablica[k][l];
                    free(tab2);
                
}
               
                free(tab1);
            
}           
            

            usun = 10 - usun;
            printf("%d\n", usun);
            for (int z = 0; z < drzewa[i]->wezly + 11; z++)
                free(tablica[z]);
            free(tablica);
        
}
    
}

    for (int i = 0; i < n; i++)
        free(drzewa[i]);
    free(drzewa);
    return 0;
}