#include <iostream>
#include <algorithm>
#include <vector>
#include <execution>
#include <functional>
#include <random>

/*
 * ALGORYTMY SEKWENCYJNE MODYFIKUJACE (MUTUJACE)
 */

using namespace std;

bool pred(int a) { return true; }
bool predb(int a, int b) { return true; }
bool compb(int a, int b) { return a < b; }
int func(int& a) { return a * 10; }
int funcb(int& a, int& b) { return a + b; }
int gener_rand() { return rand()%6; }
int gener() { return 9; }

void print(vector<int> vec)
{
	for (auto i : vec) cout << i << ", ";
	cout << endl;
}

int main()
{
	/*
	 * copy				DONE	DONE	DONE	1
	 * copy_if			DONE	DONE	DONE	3
	 * copy_n			DONE	DONE	DONE	2
	 * copy_backward	DONE	DONE	DONE	4
	 * move				DONE	DONE	DONE	5
	 * move_backward	DONE	DONE	DONE	6
	 * swap				DONE	DONE	DONE	DONE
	 * iter_swap		DONE	DONE	DONE	DONE
	 * swap_ranges		DONE	DONE	DONE	DONE
	 * transform		DONE	DONE	DONE	DONE
	 * replace			DONE	DONE	DONE	DONE
	 * replace_if		DONE	DONE	DONE	DONE
	 * replace_copy		DONE	DONE	DONE	DONE
	 * replace_copy_if	DONE	DONE	DONE	DONE
	 * fill				DONE	DONE	DONE	DONE
	 * fill_n			DONE	DONE	DONE	DONE
	 * generate			DONE	DONE	DONE	DONE
	 * generate_n		DONE	DONE	DONE	DONE
	 * remove			DONE	DONE	DONE	DONE
	 * remove_if		DONE	DONE	DONE	DONE
	 * remove_copy		DONE	DONE	DONE	DONE
	 * remove_copy_if	DONE	DONE	DONE	DONE
	 * unique			DONE	DONE	DONE	DON
	 * unique_copy		DONE	DONE	DONE	DIN
	 * reverse			DONE	DONE	DONE	DON
	 * reverse_copy		DONE	DONE	DONE	DONE
	 * rotate			DONE	DONE	DONE	DONE
	 * rorate_copy		DONE	DONE	DONE	DONE
	 * shuffle			DONE	DONE	DONE
	 * random_shuffle	DONE	DONE	DONE
	 */

	 // kontenery
	vector<int> vec = { 1, 2, 3, 4, 5 };
	vector<int> vec2 = { 1, 2, 3, 4, 5 };
	vector<int> vec3 = { 1, 2, 3, 4, 5 };
	vector<int> rvec = { 1, 2, 3, 4, 5 };

	// iteratory
	auto first = vec.begin();
	auto last = vec.end();
	auto middle = vec.begin() + 2;
	auto first2 = vec2.begin();
	auto last2 = vec2.end();
	auto first3 = vec3.begin();
	auto last3 = vec3.end();
	auto rfirst = rvec.begin();
	auto rlast = rvec.end();
	auto iter1 = vec.begin();
	auto iter2 = vec.begin() + 1;

	// dane
	auto policy = std::execution::par;
	int n = 2;
	int val = 3;
	int& val1 = vec.at(0);
	int& val2 = vec.at(1);

	// copy() COPY-LEFT
	// kopiuje elementy z [first, last) do [first2, ...)
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	copy(first, last, first2);					// (I, I, O)		iterator
	copy(policy, first, last, first2);			// (-, F, F, F)		iterator
	
	// copy_n()	COPY-OK
	// kopiuje elementy z [first, first+n) do [first, ...)
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	copy_n(first, n, first2);					// (I, -, O)		iterator
	copy_n(policy, first, n, first2);			// (-, F, -, F)		iterator

	// copy_if() COPY-LEFT
	// kopiuje tylko te elementy z [first, last) do [first2, ...)
	// spelniajace predykat pred,
	// zwraca iterator za ostani skopiowany element w zakresie docelowym
	copy_if(first, last, first2, pred);			// (I, I, O, 1)		iterator
	copy_if(policy, first, last, first2, pred);	// (-. F, F, F, 1)	iterator

	// copy_backward() COPY-RIGHT
	// kopiuje elementy z [first, last) do [..., last2),
	// kopiowanie rozpoczyna sie od konca zaresu,
	// do przenoszenia elementow kozysta z funkcji move()
	// zwraca iterator na ostatni skopiowany element w zakresie docelowym
	// (element na pierwszej pozycji)
	copy_backward(first, last, last2);			// (B, B, B)		iterator
	copy_backward(policy, first, last, last2);	// (- B, B, B)		iterator
	
	// move() COPY-LEFT
	// przenosi elementy z [first, last) do [first2, ...)
	// zwraca iterator za ostatni przeniesiony element w zakresie docelowym
	move(first, last, first2);					// (I, I, O)		iterator
	move(policy, first, last, first2);			// (-, F, F, F)		iterator

	// move_backward() COPY-RIGHT
	// przenosi elementy z [first, last) do [..., last2),
	// przenoszenie rozpoczyna od konca zaresu,
	// do przenoszenia elementow kozysta z funkcji move()
	// zwraca iterator na ostatni przeniesiony element w zakresie docelowym
	// (element na pierwszej pozycji)
	move_backward(first, last, last2);			// (B, B, B)		iterator
	move_backward(policy, first, last, last2);	// (-, B, B, B)		iterator

	// swap()
	// zamienia miejscami elementy okreslone referencjami
	swap(val1, val2);							// void
	
	// iter_swap()
	// zamienia miejscami elementy okreslone iteratorami
	iter_swap(iter1, iter2);					// (F, F)		void

	// swap_ranges() COPY-NOT
	// zamienia miejscami odpowiadajace sobie elementy
	// w [first, last) oraz [first2, ...)
	// zwraca iterator za ostatni zamieniony element w drugim zakresie
	swap_ranges(first, last, first2);			// (F, F, F)	iterator
	swap_ranges(policy, first, last, first2);	// (-, F, F, F)	iterator

	// transform()
	// stosuje funktor func do kazdego elementu w [first, last), przypisuje
	// zwrocona wartosc odpowiedniemu elementowi w [first2, ...)
	// zwraca itarator za ostatni przeksztalcony element w zakresie docelowym
	transform(first, last, first2, func);					// (I, I, O, 1)		iterator
	transform(policy, first, last, first2, func);			// (-, F, F, F,1)	iterator
	// stosuje funktor binarny do kazdej pary elementow z [first, last) 
	// oraz [first2, ...), przypisuje zwrocona wartosc odpowiedniemu 
	// elementowi w [first3, ...), zwraca iterator za ostatni
	// przeksztalcony element w zakresie docelowym
	transform(first, last, first2, first3, funcb);			// (I, I, I, O, 2)	iterator
	transform(policy, first, last, first2, first3, funcb);	// (-, F, F, F, F, 2)	iterator

	// replace()
	// zastepuje wszystkie wystapienia val w [first, last) na
	// element val2
	replace(first, last, val, val2);			// (F, F) void
	replace(policy, first, last, val, val2);	// (F, F) void

	// replace_if()
	// zastepuje wszystkie elementy w [first, last) spelniajace
	// predykat pred na val2
	replace_if(first, last, pred, val2);			// (F, F, 1)	void
	replace_if(policy, first, last, pred, val2);	// (-, F, F, 1) void

	// replace_copy() COPY-NOT
	// kopiuje elementy z [first, last) do [first2, ...)
	// zastepuje wszystkie wystapienia val na val2
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	replace_copy(first, last, first2, val, val2);			// (I, I, O)	iterator
	replace_copy(policy, first, last, first2, val, val2);	// (-, F, F, F)	iterator

	// replace_copy_if() COPY-NOT
	// kopiuje elementy z [first, last) do [first2, ...)
	// zastepuje wszystkie elementy spelniajace predykat pred na val2,
	// zwraca iterator za ostani skopiowany element w zakresie docelowym
	replace_copy_if(first, last, first2, pred, val2);			// (I, I, O, 1)		iterator
	replace_copy_if(policy, first, last, first2, pred, val2);	// (-, F, F, F, 1)	iterator

	// fill()
	// przypisuje kazdemu elementowi w [first, last) wartosc val
	fill(first, last, val);					// (F, F)		void
	fill(policy, first, last, val);			// (-, F, F)	void
	
	// fill_n()
	// przypisauje kazdemu elementowi w [first, first+n) wartosc val
	// zwraca iterator za ostatni przypisany element
	fill_n(first, n, val);					// (O)			iterator
	fill_n(policy, first, n, val);			// (-, F)		iterator

	// generate()
	// przypisuje kazdemu elementowi w [first, last) wartosc
	// zwrocona przez generator gener
	generate(first, last, gener);			// F, F)		void
	generate(policy, first, last, gener);	// (-, F, F)	void

	// generate_n()
	// przypisuje kazdemu elementowi w [first, first+n) wartosc
	// zwrocona przed generator gener, zwraca iterator za ostatni
	// przypisany element
	generate_n(first, n, gener);			// (O)			iterator
	generate_n(policy, first, n, gener);	// (- F)		iterator

	// remove() STABLE
	// usuwa wszystkie wystapienia val w [first, last)
	// nie zmienia rozmiaru kontenera, elementy nieusuwane sa
	// przesuwane na poczatek zakresu
	// zwraca iterator za ostatni element nowego zakresu po przesunieciu
	remove(first, last, val);				// (F, F)		iterator
	remove(policy, first, last, val);		// (-, F, F)	iterator

	// remove_if() STABLE
	// usuwa wszystkie elementy w [first, last) spelniajace
	// predykat pred, 
	// nie zmienia rozmiaru kontenera, elementy nieusuwane sa
	// przesuwane na poczatek zakresu
	// zwraca iterator za ostatni element nowego zakresu po przesunieciu
	remove_if(first, last, pred);			// (F, F, 1)	iterator
	remove_if(policy, first, last, pred);	// (-, F, F, 1)	iterator

	//remove_copy() COPY-NOT | STABLE
	// kopiuje elementy z [first, last) do [first2, ...)
	// pomija wszystkie wystapienia val
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	remove_copy(first, last, first2, val);			// (I, I, O)	iterator
	remove_copy(policy, first, last, first2, val);	// (-, F, F, F)	iterator

	// remove_copy_if() COPY-NOT | STABLE
	// kopiuje elementy z [first, last) do [first2, ...)
	// pomija elementy spelniajace predykat pred,
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	remove_copy_if(first, last, first2, pred);			// (I, I, O, 1)		iterator
	remove_copy_if(policy, first, last, first2, pred);	// (-, I, I, O, 1)	iterator

	// unique()
	// usuwa rownowazne sasiednie elementy w [first, last)
	// nie zmienia rozmiaru kontenera, elementy 
	// nieusuwane sa przesuwane na poczatek zakresu
	// zwraca iterator za ostatni element nowego zakresu po przesunieciu
	unique(first, last);				// (F, F)		iterator	==
	unique(policy, first, last);		// (-, F, F)	iterator	==
	unique(first, last, compb);			// (F, F, 2)	iterator	compb
	unique(policy, first, last, compb);	// (-, F, F, 2)	iterator	compb

	// unique_copy()
	// kopiuje elementy z [first, last) do [first2, ...)
	// pomija rownowazne elementy sasiednie
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	unique_copy(first, last, first2);				// (I, I, O)	iterator		==
	unique_copy(policy, first, last, first2);		// (-, F, F, F)	iterator		==
	unique_copy(first, last, first2, compb);		// (I, I, O, 2)	iterator		compb
	unique_copy(policy, first, last, first2, compb);// (-, F, F, F, 2)	iterator	compb

	// reverse()
	// odwraca kolejnosc elementow w [first, last)
	reverse(first, last);				// (B, B)	void
	reverse(policy, first, last);		// (B, B)	void
	
	// reverse_copy()
	// kopiuje elementy z [first, last) do [first2, ...) w odwrotnej kolejnosci
	// zwraca iterator za ostatni skopiowany element w zakresie docelowym
	reverse_copy(first, last, first2);			// (B, B, O)	iterator
	reverse_copy(policy, first, last, first2);	// (-, B, B, F)	iterator
	
	// rotate()
	// wykonuje przesuniecie cykliczne w lewo, zamienia miejscami
	// zakresy [first, middle) oraz [middle, last)
	// zwraca iterator na nowa pozycje pierwszego elementu z pierwotnego zakresu
	rotate(first, middle, last);				// (F, F, F)	iterator
	rotate(policy, first, middle, last);		// (-, F, F, F) iterator

	// rotate_copy()
	// kopiuje elementy z[first, last) do [first2, ...)
	// wykonuje przesuniecie cykliczne w lewo, zamienia miejscami
	// zakresy [first, middle) oraz [middle, last)
	// zwraca iterator na nowa pozycje pierwszego elementu
	// z pierwotnego zakresu w zakresie docelowym
	rotate_copy(first, middle, last, first2);			// (F, F, F, O)		iterator
	rotate_copy(policy, first, middle, last, first2);	// (-, F, F, F, F)	iterator
	
	// shuffle
	// tasuje elementy w zakresie [first, last)
	// do generowania liczb losowych uzywa generatora gener_rand
	// dla n elementow w zakresie, gener_rand powinno zwracac wartosc
	// z przedzialu [0, n)
	//shuffle(first, last, gener_rand);				// (R, R)	void

	// random_shuffle
	// tasuje elementy w zakresie [first, last)
	// do generowania liczb losowych uzywa funkcji rand, lub jesli
	// podano generatora gener_rand,
	// dla n elementow w zakresie, func_rand powinno zwracac wartosc
	// z przedzialu [0, n)
	//random_shuffle(first, last);					// (R, R)	void
	//random_shuffle(first, last, func_rand);		// (R, R)	void

	// TEST
	vector<int> v1 = { 0, 1, 2, 3, 4};
	vector<int> v2 = { 5, 6, 7, 8, 9};
	
	random_device rd;
	mt19937 g(rd());

	print(v1);
	print(v2);
	cout << endl;
	swap_ranges(v1.begin(), v1.end()-1, v1.begin()+1);
	print(v1);
	print(v2);

	return 0;
}