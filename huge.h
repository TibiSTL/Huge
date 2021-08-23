#pragma on
/*
Proiect : Aritmetica numerelor mari v2.0
Data : 09/07/2020
Credits : TibiNyte ( m-am inspirat putin de pe https://www.geeksforgeeks.org/ si https://infoarena.ro/lucrul-cu-nr-mari )
Descriere : Poti sa faci calcule cu numere mari fara a folosi 1000 de functii , ai operatori specifici !
In plus , numerele sunt retinute ca stringuri , adica vei putea sa citesti numarul din consola fara sa pui spatii intre cifre
Si de asemenea daca numerele sunt retinute ca stringuri vei putea folosi toti operatorii/functiile predefinite ptr stringuri
Website : nytesite.tech
*/
#include <iostream>
#include <string>
#include <vector>
#define valoaretibi const
using namespace std;
int Sgn(int H1[], int H2[]) {
	while (H1[0] && !H1[H1[0]]) H1[0]--;
	while (H2[0] && !H2[H2[0]]) H2[0]--;

	if (H1[0] < H2[0]) {
		return -1;
	}
	else if (H1[0] > H2[0]) {
		return +1;
	}

	for (int i = H1[0]; i > 0; --i) {
		if (H1[i] < H2[i]) {
			return -1;
		}
		else if (H1[i] > H2[i]) {
			return +1;
		}
	}
	return 0;
}
void Subtract(int A[], int B[])
{
	int i, T = 0;
	for (i = B[0] + 1; i <= A[0];) B[i++] = 0;
	for (i = 1; i <= A[0]; i++)
		A[i] += (T = (A[i] -= B[i] + T) < 0) ? 10 : 0;
	while (!A[A[0]] && A[0] > 1) A[0]--;
}
void Shl(int H[], int Count)
{
	memmove(&H[Count + 1], &H[1], sizeof(int) * H[0]);
	memset(&H[1], 0, sizeof(int) * Count);
	H[0] += Count;
}
void DivideHuge(int A[], int B[], int C[], int R[])
{
	int i;

	R[0] = 0; C[0] = A[0];
	for (i = A[0]; i; i--)
	{
		Shl(R, 1); R[1] = A[i];
		C[i] = 0;
		while (Sgn(B, R) != 1)
		{
			C[i]++;
			Subtract(R, B);
		}
	}
	while (!C[C[0]] && C[0] > 1) C[0]--;
}
bool isSmaller(string str1, string str2)
{
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2)
		return true;
	if (n2 < n1)
		return false;

	for (int i = 0; i < n1; i++)
		if (str1[i] < str2[i])
			return true;
		else if (str1[i] > str2[i])
			return false;

	return false;
}
bool isSmallerorequal(string str1, string str2)
{
	int n1 = str1.length(), n2 = str2.length();
	if (n1 > n2)
		return false;
	if (n2 > n1)
		return true;
	for (int i = 0; i < n1; i++) {
		if (str1[i] > str2[i])
			return false;
	}
	return true;
}
void Add(int A[], int B[])
{
	int i, T = 0;

	if (B[0] > A[0])
	{
		for (i = A[0] + 1; i <= B[0];) A[i++] = 0;
		A[0] = B[0];
	}
	else for (i = B[0] + 1; i <= A[0];) B[i++] = 0;
	for (i = 1; i <= A[0]; i++)
	{
		A[i] += B[i] + T;
		T = A[i] / 10;
		A[i] %= 10;
	}
	if (T) A[++A[0]] = T;
}
void MultHuge(int A[], int B[], int C[])
{
	int i, j, T = 0;

	C[0] = A[0] + B[0] - 1;
	for (i = 1; i <= A[0] + B[0];) C[i++] = 0;
	for (i = 1; i <= A[0]; i++)
		for (j = 1; j <= B[0]; j++)
			C[i + j - 1] += A[i] * B[j];
	for (i = 1; i <= C[0]; i++)
	{
		T = (C[i] += T) / 10;
		C[i] %= 10;
	}
	if (T) C[++C[0]] = T;
}
string checkvalue(string s1, string s2, string r) {
	for (int i = 0; i < s1.size(); ++i)
		if (s1[i] > '9' or s1[i] < '0')
			return "String invalid ! Parametrul 1 !";
	for (int i = 0; i < s2.size(); ++i)
		if (s2[i] > '9' or s2[i] < '0')
			return "String invalid ! Parametrul 2 !";
	return r;
}
void stringtovect(string s, int C[]) {
	C[0] = s.size();
	int contor = 0;
	for (int i = s.size() - 1; i >= 0; --i) {
		C[++contor] = (int)(s[i] - '0');
	}
}
void vectstring(string& s, int C[]) {
	s.resize(C[0]);
	int contor = 0;
	for (int i = s.size() - 1; i >= 0; --i)
		s[contor++] = C[i + 1] + '0';
}
string inmultire(string a, string b) {
	int A[50001], B[50001], C[50001];
	stringtovect(a, A);
	stringtovect(b, B);
	MultHuge(A, B, C);
	string raspuns;
	vectstring(raspuns, C);
	return raspuns;
}
string suma(string a, string b) {
	int A[1001], B[1001];
	stringtovect(a, A);
	stringtovect(b, B);
	Add(A, B);
	string raspuns;
	vectstring(raspuns, A);
	return raspuns;
}
string diferenta(string a, string b) {
	int A[1001], B[1001];
	stringtovect(a, A);
	stringtovect(b, B);
	Subtract(A, B);
	string raspuns;
	vectstring(raspuns, A);
	return raspuns;
}
string factorial(int n)
{
	string s = "1";
	for (int i = 2; i <= n; i++)
		s = inmultire(s, to_string(i));
	return s;
};
string devidebytibinyte(string s1, string s2, int hash_key) {
	int A[1001], B[1001], C[1001], R[1001];
	string rezultat;
	stringtovect(s1, A);
	stringtovect(s2, B);
	DivideHuge(A, B, C, R);
	if (hash_key == 1) {
		vectstring(rezultat, C);
		return rezultat;
	}
	vectstring(rezultat, R);
	if (rezultat.size() == 0)
		return "0";
	return rezultat;
}
typedef std::basic_ostream<char, std::char_traits<char> > std_ostream;;
struct numarmare {
	string val = "0";
	numarmare operator +(valoaretibi string a) valoaretibi { numarmare x; x.val = checkvalue(val, a, suma(val, a)); return x; }
	numarmare operator +(valoaretibi numarmare a) valoaretibi { numarmare x; x.val = checkvalue(val, a.val, suma(val, a.val)); return x; }
	numarmare operator *(valoaretibi numarmare a) valoaretibi { numarmare x; x.val = checkvalue(val, a.val, inmultire(val, a.val)); return x; }
	numarmare operator *(valoaretibi string a) valoaretibi { numarmare x; x.val = checkvalue(val, a, inmultire(val, a)); return x; }
	numarmare operator -(valoaretibi numarmare a) valoaretibi { numarmare x; x.val = checkvalue(val, a.val, diferenta(val, a.val)); return x; }
	numarmare operator -(valoaretibi string a) valoaretibi { numarmare x; x.val = checkvalue(val, a, diferenta(val, a)); return x; }
	numarmare operator !() valoaretibi { numarmare x; x.val = factorial(atoi((char*)val.c_str())); return x; }
	numarmare operator /(valoaretibi numarmare a) valoaretibi { numarmare x; x.val = checkvalue(val, a.val, devidebytibinyte(val, a.val, 1)); return x; }
	numarmare operator /(valoaretibi string a) valoaretibi { numarmare x; x.val = checkvalue(val, a, devidebytibinyte(val, a, 1)); return x; }
	numarmare operator %(valoaretibi numarmare a) valoaretibi { numarmare x; x.val = checkvalue(val, a.val, devidebytibinyte(val, a.val, 2)); return x; }
	numarmare operator %(valoaretibi string a) valoaretibi { numarmare x; x.val = checkvalue(val, a, devidebytibinyte(val, a, 2)); return x; }
	void operator =(string a) { val = a; }
	void operator ++() { val = suma(val, "1"); }
	void operator --() { val = diferenta(val, "1"); }
	void operator +=(string x) { val = suma(val, x); }
	void operator +=(numarmare x) { val = suma(val, x.val); }
	void operator -=(string x) { val = diferenta(val, x); }
	void operator -=(numarmare x) { val = diferenta(val, x.val); }
	void operator /=(valoaretibi string x) { val = devidebytibinyte(val, x, 1); }
	void operator /=(numarmare x) { val = devidebytibinyte(val, x.val, 1); }
	void operator %=(string x) { val = devidebytibinyte(val, x, 2); }
	void operator %=(numarmare x) { val = devidebytibinyte(val, x.val, 2); }
	void operator *=(string x) { val = inmultire(val, x); }
	void operator *=(numarmare x) { val = inmultire(val, x.val); }
	bool operator !=(string x) { return val == x; }
	bool operator !=(numarmare x) { return val == x.val; }
	bool operator ==(valoaretibi numarmare a) valoaretibi { numarmare t; t.val = val; return t.val == a.val; }
	bool operator ==(valoaretibi string a) valoaretibi { numarmare t; t.val = val; return t.val == a; }
	bool operator >(valoaretibi numarmare a) valoaretibi { return isSmaller(a.val, val); }
	bool operator >(valoaretibi string a) valoaretibi { return isSmaller(a, val); }
	bool operator <(valoaretibi numarmare a) valoaretibi { return isSmaller(val, a.val); }
	bool operator <(valoaretibi string a) valoaretibi { return isSmaller(val, a); }
	bool operator >=(valoaretibi numarmare a) valoaretibi { return isSmallerorequal(a.val, val); }
	bool operator >=(valoaretibi string a) valoaretibi { return isSmallerorequal(a, val); }
	bool operator <=(valoaretibi numarmare a) valoaretibi { return isSmallerorequal(val, a.val); }
	bool operator <=(valoaretibi string a) valoaretibi { return isSmallerorequal(val, a); }
	friend ostream& operator << (ostream& os, valoaretibi numarmare& a) { os << a.val; return os; }
	friend istream& operator >>(istream& is, numarmare& a) { is >> a.val; return is; }
	numarmare power(int n) {
		if (n == 0) {
			numarmare aux;
			aux.val = "1";
			val = aux.val;
			return aux;
		}
		string baza = val;
		string ss = "1";
		for (int i = 1; i <= n; i++)
			ss = inmultire(baza, ss);
		numarmare aux;
		aux.val = ss;
		val = aux.val;
		return aux;
	}
	numarmare log(int baza) {
		numarmare aux;
		aux.val = val;
		numarmare aux2;
		aux2.val = to_string(baza);
		int contor = 0;
		while (aux.val > "1") {
			aux = aux / aux2;
			contor++;
		}
		numarmare tibi;
		tibi.val = to_string(contor);
		return tibi;
	}
	numarmare limit() { numarmare x; x.val = to_string(val.max_size()); return x; };
	int to_i() {
		int posible = atoi(val.c_str());
		if (posible < INT_MAX and posible > INT_MIN)
			return posible;
		else
			return INT_MAX;
	}
	string to_s() {
		return val;
	}
	string sqrt() {

	}
	auto begin() {
		return val.begin();
	}
	auto end() {
		return val.end();
	}
	int size() {
		return val.size();
	}
	string to_bin() {
		numarmare a;
		a.val = val;
		string binar;
		while (a > "0") {
			binar = binar + (a % "2").val;
			a /= "2";
		}
		return _strrev((char*)binar.c_str());
	}
	bool valid() {
		for (int i = 0; i < val.size(); ++i) {
			if (!isdigit(val[i]))
				return false;
		}
		return true;
	}
	void clear() {
		val.erase(val.begin(), val.end());
		val = "0";
	}
	void trim() {
		while ((val[0] - '0') == 0) {
			val.erase(val.begin());
		}
	}
	numarmare(int x) {
		val = to_string(x);
	}
	numarmare() {}
};
numarmare maxi(numarmare a, numarmare b) {
	if (isSmaller(a.val, b.val))
		return b;
	return a;
}