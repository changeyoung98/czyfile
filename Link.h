#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node(int v) : value(v), next(NULL) {}
};

class List {
	Node* head;
	int size;
public:
	List(const vector<int>& v);
	List(int* array, int array_size);
	int length() const;
	bool insert(int pos, int value);
	int find(int value);
	int remove(int value);
	bool split(int pos, List& new_list);
	Node* getHead();                      //return the head of a list
	void combine(List& append_list);
	void printAll();
	~List();
};


List::List(const vector<int>& v) {
	head = new Node(v[0]);
	Node* current = head;
	int i = 0;
	while(i<v.size()-1) {
		current->next = new Node(v[i+1]);
		current = current->next;
		i++;
	}
	size = v.size();
}
List::List(int* array, int array_size) {
    head = new Node(array[0]);
	Node* current = head;
	for (int i = 0; i < array_size ; i++) {
		current->next = new Node(array[i+1]);
		current = current->next;
	}
	size = array_size; 
}                                        //construction
int List::length() const {
	return size;
}
bool List::insert(int pos, int value) {
	Node* node;
	node = new Node(value);
	if (pos<0 || pos>size) {
		return false;
	}
	else { 
		if (head == NULL&&pos==0) {
			head = node;
		}                          //when it is a null list
		else if (pos == 0) {
			node->next = head;
			head = node;
		}                      //when inserting a head
		else{
			Node* current = head;
			int i = 0;
			while (current->next != NULL && i < pos - 1) {
				current = current->next;
				i++;
			}                          //find the node before the inserting position
			if (i == pos - 1) {
				node->next = current->next;
				current->next = node;
			}
		}
		size += 1;                   //change the size
		return true;
	}
}

int List::find(int value) {
	Node* current = head;
	int i = 0;
	while (current->next != NULL) {
		if (current->value == value) {
			return i;
		}
		current = current->next;
		i++;
	}
	return -1;
	
	
}
int List::remove(int value) {
	Node* current = head;
	Node* del;
	int i = 0;
	if (head == NULL) {
		return -1;
	}
	else if (head->value == value) {
		del = head;
		head = head->next;
		delete del;
		i++;
		size--;
	}
	while (current->next != NULL) {
		if (current->next->value == value) {                     //find the node before 
			del = current->next;
			current->next = del->next;
			delete del;
			i++;
			size--;
		}
		else {
			current = current->next;
		}
	}
	return i;
}


bool List::split(int pos, List& new_list) {
	Node* current = head;
	if (head == NULL) {
		return false;
	}
	else {
		if (0 <= pos <= size - 1) {
			for (int i = 0; i < pos; i++) {
				current = current->next;
			}
			Node* new_node = current->next;
			while (new_node->next != NULL) {
				int posi = new_list.length();
				new_list.insert(posi, new_node->value);
				new_node = new_node->next;
			}                                      //append the nodes to the new list
			Node* current = head;
			Node* del;
			for (int i = 0; i < pos+1; i++) {
				 current = current->next;
			}
			while (current->next != NULL) {
				del = current->next;
				current->next = del->next;
				delete del;                //delete the nodes from the previous list
				size--;
			}

			return true;
		}
	}
	return false;
}
Node* List::getHead() {
	return head;
}
void List::combine(List& append_list) {
    Node* new_head = append_list.getHead();
	while (new_head->next!=NULL) {
		List::insert(size, new_head->value);
		new_head = new_head->next;
	}                            //append the new list to the previous one
	Node* current = append_list.getHead();
	Node* del;
	while (current->next!= NULL) {
		del = current->next;
		current->next = del->next;
		delete del;                //delete the append_list
	}
}
void List::printAll() {
	Node* current = head;
	int i = 0;
	while (current->next != NULL) {
		cout << current->value << '\t';
		current = current->next;
		i++;
	}
	cout << '\n';
}
List::~List() {
	Node *node;
	while (head->next != NULL)
	{
		node = head;
		head = head->next;
		delete node;
		node = NULL;
	}
	delete head;
	head = NULL;
}
