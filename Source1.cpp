#include<bits/stdc++.h>
using namespace std;
struct ArrayNode {
	int data{};
	int idx{};
	ArrayNode* prv{};
	ArrayNode* next{};
	ArrayNode(int d, int i) { data = d; idx = i; prv = nullptr; next = nullptr; }
};
class SparseArray {
private:
	ArrayNode* Head{};
	ArrayNode* Tail{};
	int len{};
	int capacity{};

	int idx;

public:
	SparseArray(int c,int id) {
		capacity = c; Head = nullptr; Tail = nullptr; len = 0;
		next = nullptr; prv = nullptr; idx = id;
	}
	void link(ArrayNode* first, ArrayNode* second) {
		if (first)first->next = second;
		if (second)second->prv = first;

	}
	void setvalue(int val, int id) {
		ArrayNode* x = new ArrayNode(val, id);
		if (id >= capacity) { cout << "cannot find\n"; return; }
		if (len == 0) { Head = x; Tail = x; len++; return; }
		else {
			if (Tail->idx < id) { link(Tail, x); Tail = x; len++; }
			else if (Head->idx > id){link(x, Head);  Head = x; len++; }
			else {
				for (ArrayNode* cur = Head; cur; cur = cur->next) {
					if (cur->idx == id) { cur->data += val; break; }

					else if (cur->idx > id) {
						link(cur->prv, x); link(x, cur); break;
					}
				}
			}
		}
	}
	void set_value_with_another_list( SparseArray & x) {
		for (ArrayNode* cur = x.Head; cur; cur = cur->next) {
			setvalue(cur->data, cur->idx);
		}

	}
		void print_nonzeros() {
			for (ArrayNode* cur = Head; cur; cur = cur->next) {
				cout << cur->data <<" ";
		}
			cout << "\n";
	}
		void print_n_zeros(int n) {
			while (n--) {
				cout << "0 ";
			}
		}
		void print_with_zeros() {
			print_n_zeros(Head->idx);
			for (ArrayNode* cur = Head; cur; cur=cur->next) {
				cout << cur->data << " ";
				if (cur->next) {
					print_n_zeros(cur->next->idx - cur->idx - 1);
			}
			}
			print_n_zeros(capacity - Tail->idx -1 );
			cout << "\n";
		}
		void get_val(int id) {
			if (id > capacity||id<0) { cout << "doesn't exist"; return; }
			for (ArrayNode* cur = Head; cur; cur = cur->next) {
				if (id == cur->idx) { cout << cur->data << "\n"; return; }
			}
		}
		void set_next(SparseArray* x) {
			next = x;
		}
		void set_prv(SparseArray* x) { prv = x; }


		int get_idx() { return idx;}
		SparseArray* next{};
		SparseArray* prv{};

};

class SparseMatrix {
private:
	SparseArray* Head{};
	SparseArray* Tail{};
	int len{}; int capacity{}; int width{};
public:
	SparseMatrix(int rows, int cols) { capacity = rows; Head = nullptr; Tail = nullptr; len = 0; width = cols; }
	void link(SparseArray* first, SparseArray* second) {
		if (first) first->set_next(second);
		if (second)second->set_prv(first);
	}
	void set_values(int val, int r, int c) {
		SparseArray* sp = new SparseArray(width, r);
		sp->setvalue(val, c);
		if (r >= capacity) {
			cout << "too_big for the matrix\n"; return;
		}
			if (len == 0) {
				Head = sp; Tail = sp; len++; return;
			}
			if (r < Head->get_idx()) {
				link(sp, Head); Head = sp;

				len++;
			}
			else if (r > Tail->get_idx()) {

				link(Tail, sp); Tail = sp;
							len++;
			}
			else {

				for (SparseArray* cur = Head; cur; cur = cur->next) {
					if (cur->get_idx() == r) { cur->setvalue(val, c); break; }


					if (cur->get_idx() > r) {
						link(cur->prv, sp); link(sp, cur);
						 break;
					}
				}

			}
		}


	void printNonZeros() {
		for (SparseArray* cur = Head; cur; cur = cur->next) {
			cur->print_nonzeros();
		}
	}
	void printNzeros(int n) {
		while (n--)cout << "0 ";
		cout << "\n";
	}
	void printWithZeros() {
		printNzeros(Head->get_idx());
		for (SparseArray* cur = Head; cur; cur = cur->next) {
			cur->print_with_zeros();
			if (cur->next) {
				printNzeros(cur->next->get_idx() - cur->get_idx() - 1);
			}
		}
		printNzeros(capacity - Tail->get_idx() - 1);

	}
	/*void set_value_with_another_matrix(SparseMatrix& mx) {
		for (SparseArray* cur = mx.Head; cur; cur = cur->next) {
			for(ArrayNode* cur2=cur2->Head)
		}
	}*/
};




	int main() {
		//SparseArray sa = SparseArray(15, 0);
		//sa.setvalue(1, 2);
		//sa.setvalue(4, 5);
		//sa.setvalue(6, 3);
		//sa.setvalue(10, 7);

		////sa.setvalue(5, 5);
		//sa.print_nonzeros();
		//SparseArray sa2 = SparseArray(5, 3);
		//sa2.setvalue(20, 0);
		//sa2.setvalue(2, 3);
		//sa.set_value_with_another_list(sa2);
		//sa.print_with_zeros();
		//sa.get_val(7);
		//test::
		SparseMatrix mx = SparseMatrix(3, 3);
		mx.set_values(3, 0, 1);
		mx.set_values(15, 2, 2);
		mx.set_values(10, 1, 1);
		mx.set_values(2, 1, 2);
		mx.set_values(2, 1, 2);
		//mx.set_values()
		mx.printWithZeros();




		return 0;
	}
