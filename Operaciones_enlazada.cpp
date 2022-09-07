#include <iostream>
using namespace std;

template <class R>
class Nodo {
public:
	R val;
	Nodo* sig;
public:
	Nodo(R valor) {
		val = valor;
		sig = nullptr;
	}
	
	~Nodo() {}
};

template <class R>
class Lista {
public:
	Nodo<R>* head;
public:
	Lista() {
		head = nullptr;
	}
	
	~Lista() {
		Nodo<R>* temp1 = head;
		Nodo<R>* temp2;
		while (temp2 != nullptr) {
			temp2 = temp1->sig;
			delete temp1;
			temp1 = temp2;
		}
	}
	
	void push_back(R val) {
		Nodo<R>* pnew = new Nodo<R>(val);
		if (head != nullptr) {
			Nodo<R>* temp = head;
			while (temp->sig != nullptr) {
				temp = temp->sig;
			}
			temp->sig = pnew;
		} else {
			head = pnew;
		}
		
	}
	
	void push_front(R val) {
		Nodo<R>* pnew = new Nodo<R>(val);
		if (head != nullptr) {
			pnew->sig = head;
		}
		head = pnew;
	}
	
	void delete_front() {
		Nodo<R>* temp = head;
		head = temp->sig;
		delete temp;
	}
	
	void delete_last() {
		Nodo<R>* temp1 = head;
		
		if (head->sig == nullptr) {
			delete head;
			head = nullptr;
		}
		
		Nodo<R>* temp2 = temp1->sig;
		while (temp2->sig != nullptr) {
			temp1 = temp2;
			temp2 = temp2->sig;
		}
		temp1->sig = nullptr;
		delete temp2;
	}
	
	bool find_it(R valor) {
		Nodo<R>* temp = head;
		while (temp != nullptr) {
			if (temp->val == valor) {
				return true;
			}
			temp = temp->sig;
		}
		return false;
	}
	
	bool find_rec(R valor) {
		return findrec(valor,head);
	}
	
	bool findrec(R valor, Nodo<R>* temp) {
		if (temp->sig == nullptr) {
			return valor == temp->val;
		}
		
		if (valor == temp->val) {
			return true;
		} else {
			return findrec(valor,temp->sig);
		}
	}
	
	R hallar_max_it() {
		Nodo<R>* temp = head;
		R max = temp->val;
		temp = temp->sig;
		while (temp != nullptr) {
			if (temp->val > max) {
				max = temp->val;
			}
			temp = temp->sig;
		}
		return max;
	}
	
	R hallar_max_rec() {
		return hallar_max_rec(head->val, head);
	}
	
	R hallar_max_rec(R max, Nodo<R>* temp) {
		if (temp->sig == nullptr) {
			return temp->val > max? temp->val : max;
		} else {
			return hallar_max_rec(temp->val > max? temp->val : max,temp->sig);
		}
	}
	
	void insert_it(R valor, int pos) {
		Nodo<R>* pnew = new Nodo<R>(valor);
		if (pos == 0) {
			pnew->sig = head;
			head = pnew;
			return;
		}
		
		Nodo<R>* temp = head;
		while (pos != 0) {
			if (pos == 1) {
				pnew->sig = temp->sig;
				temp->sig = pnew;
				break;
			} else if (pos > 1 && temp->sig == nullptr) {
				pos = 1;
				continue;
			}
			pos--;
			temp = temp->sig;
		}
	}
	
	void insert_rec(R valor, int pos) {
		Nodo<R>* pnew = new Nodo<R>(valor);
		insert_rec(pos,pnew,head);
	}
	
	void insert_rec(int pos, Nodo<R>* pnew, Nodo<R>* temp) {
		if (pos == 0) {
			pnew->sig = temp;
			if (temp == head) {
				head = pnew;
			}
		} else if (pos == 1) {
			insert_rec(pos-1,pnew,temp->sig);
			temp->sig = pnew;
		} else {
			if (temp->sig == nullptr && pos > 1) {
				insert_rec(1,pnew,temp);
			} else  {
				insert_rec(pos-1,pnew,temp->sig);
			}
		}
	}
	
	void print() {
		Nodo<R>* temp = head;
		cout << temp->val;
		temp = temp->sig;
		while (temp != nullptr) {
			cout << " - " << temp->val;
			temp = temp->sig;
		}
		cout << endl;
	}
	
	void print_reverse_it() {
		Nodo<R>* temp = head;
		string datos = "";
		datos += to_string(temp->val) + "\n";
		temp = temp->sig;
		
		while (temp != nullptr) {
			datos = to_string(temp->val) + " - " + datos;
			temp = temp->sig;
		}
		cout << datos;
	}
	
	void print_reverse_rec() {
		print_reverse_rec(head);
		cout << endl;
	}
	
	void print_reverse_rec(Nodo<R>* temp) {
		if (temp->sig == nullptr) {
			cout << temp->val;
		} else {
			print_reverse_rec(temp->sig);
			cout << " - " << temp->val;
		}
	}
	
	
};

int main() {
	Lista<int>* lis1 = new Lista<int>();
	
	lis1->push_front(3);
	lis1->push_back(5);
	lis1->push_front(8);
	lis1->push_back(7);
	lis1->print();
	lis1->insert_rec(6,2);
	lis1->insert_rec(9,4);
	lis1->print();
	lis1->insert_it(4,0);
	lis1->insert_it(1,2);
	lis1->print();
	lis1->delete_front();
	lis1->delete_last();
	lis1->print();
	lis1->print_reverse_it();
	lis1->print_reverse_rec();
	cout << lis1->hallar_max_it() << endl;
	cout << lis1->hallar_max_rec() << endl;
	
	if (lis1->find_it(10)) {
		cout << "Encontrado\n";
	} else {
		cout << "No Encontrado\n";
	}
	
	if (lis1->find_rec(8)) {
		cout << "Encontrado\n";
	} else {
		cout << "No Encontrado\n";
	}
	
	delete lis1;
	return 0;
}

