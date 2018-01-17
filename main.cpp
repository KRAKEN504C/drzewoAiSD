#include <iostream>
#include <list>
#include <fstream>
#include <time.h>

/*
Wyszukiwawcze Drzewo binarne u¿yte z:
https://gist.github.com/harish-r/a7df7ce576dda35c9660
*/

using namespace std;

long long int Sumawstaw = 0;
long long int szukaj = 0;
long long int wstaw = 0;
long long int usun = 0;

list <int> lista;

class BST
{
	struct node
	{
		int data;
		node* left;
		node* right;
		//https://gist.github.com/harish-r/a7df7ce576dda35c9660
	};

	node* root;

	node* makeEmpty(node* t)
	{
		if (t == NULL)
			return NULL;
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		return NULL;
	}

	node* insert(int x, node* t)
	{
		if (t == NULL)
		{
			wstaw++;
			t = new node;
			t->data = x;
			t->left = t->right = NULL;
		}
		else if (x <= t->data)
		{
			wstaw++;
			t->left = insert(x, t->left);
		}
		else if (x > t->data)
		{
			wstaw++;
			t->right = insert(x, t->right);
		}
		return t;
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int x, node* t)
	{
		node* temp;
		if (t == NULL)
			return NULL;
		else if (x < t->data)
		{
			usun++;
			t->left = remove(x, t->left);
		}
		else if (x > t->data)
		{
			usun++;
			t->right = remove(x, t->right);
		}
		else if (t->left && t->right)
		{
			usun++;
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = remove(t->data, t->right);
		}
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}

		return t;
	}

	void inorder(node* t)
	{
		if (t == NULL)
			return;
		inorder(t->left);
		cout << t->data << " ";
		inorder(t->right);
	}

	node* find(node* t, int x)
	{
		if (t == NULL)
			return NULL;
		else if (x < t->data)
		{
			szukaj++;
			return find(t->left, x);
		}
		else if (x > t->data)
		{
			szukaj++;
			return find(t->right, x);
		}
		else
			return t;
	}

public:
	BST()
	{
		root = NULL;
	}

	~BST()
	{
		root = makeEmpty(root);
	}

	void insert(int x)
	{
		root = insert(x, root);
	}

	void remove(int x)
	{
		root = remove(x, root);
	}

	void display()
	{
		inorder(root);
		cout << endl;
	}

	void search(int x)
	{
		root = find(root, x);
	}
};

int Losowanie(int x, int y)
{
	int los = rand() % (y - x + 1) + x;
	return los;
}

int main()
{
	fstream plik;
	srand(time(NULL));
	int min = 1;
	int max = 30000;
	int n = 10000;
	//N = 100, N = 200, N = 400, N = 800

	for (int i = 0; i < 20; i++)
	{
		BST t;
		int szukana = 0;
		int del = 0;
		int pomoc;

		for (int i = 0; i < n; i++)
		{
			lista.push_back(Losowanie(min, max));
		}

		int szukana2;
		szukana2 = Losowanie(0, n - 1);

		int del2;
		do
		{
			del2 = Losowanie(0, n - 1);
		} while (szukana2 == del2);

		pomoc = 0;
		for (list<int>::iterator j = lista.begin(); j != lista.end(); j++)
		{
			//cout<<*j<<endl;
			t.insert(*j);
			if (pomoc == szukana2) szukana = *j;
			else if (pomoc == del2) del = *j;
			pomoc++;
		}
		if (szukana == 0)
		{
			cout << "ERROR" << endl;
			cout << "szukana jest rowna 0!" << endl;
			system("pause");
		}
		if (del == 0)
		{
			cout << "ERROR" << endl;
			cout << "usuwana jest rowna 0!" << endl;
			system("pause");
		}

		//t.display();

		wstaw = 0;
		int wstw;
		wstw = Losowanie(min, max);
		t.insert(wstw);
		//cout << "Wstawianie " << wstw << ":\n";
		//t.display();
		Sumawstaw += wstaw;

		t.remove(del); // ok juz dziala

		//cout << "Usuwanie " << del << ":\n";
		//t.display();

		t.search(szukana); // ok 

		//cout << "Szukanie " << szukana << ":\n";
		//t.display();

		//cout << endl;
		//t.display();


		t.~BST();
		lista.clear();
	}

	plik.open("wyniki.txt", ios::out);
	plik << n << endl;
	plik << "Wstawienie: " << Sumawstaw << endl;
	plik << "Szukanie: " << szukaj << endl;
	plik << "Usuwanie: " << usun << endl << endl;
	//plik << "Wstawienie œrednio: " << wstaw/20 << endl << "Szukanie œrednio: " << szuk/20 << endl << "Usuwanie œrednio: " << usun/20 << endl;

	plik.close();
	plik.clear();
	system("pause");
	return 0;
}