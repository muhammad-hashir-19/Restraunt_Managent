#include <iostream>
#include <string>
#include <fstream>
#include<queue>
#include <ctime>
#include <cstdlib>
#include<conio.h>
using namespace std;
int cut = 0;
bool boo = false;
bool boo1 = false;
struct readme {
	string name;
	readme() {
		name = "read_me.txt";
	}

	void reading() {
		string myText;
		ifstream MyReadFile(name);

		if (MyReadFile.is_open()) {
			while (getline(MyReadFile, myText)) {
				cout << myText << endl;
			}
			MyReadFile.close();
		}
		else {
			cout << "Unable to open the file" << endl;
		}
	}
	void writing() {
		string text;
		ofstream MyWriteFile(name, ios::app);
		if (MyWriteFile.is_open()) {
			cout << "Enter the new lines";
			cin >> text;
			MyWriteFile << text << endl;
			MyWriteFile.close();
		}
		else {
			cout << "Unable to open the file for writing" << endl;
		}
	}
};
struct dish {
	int id;
	string name;
	string type;
	int price;
	dish* next;
	dish* left;
	dish* right;
	dish* parent;
	dish() {
		srand(time(0));
		id = 9999 + (rand() % 100000);
		type = "";
		price = 0;
		name = "";
		right = NULL;
		next = NULL;
		left = NULL;
		parent = NULL;
	}
	dish(string nam, int pri, string t, dish* temp) {
		srand(time(0));
		id = 9999 + (rand() % 100000);
		type = t;
		price = pri;
		name = nam;
		right = NULL;
		next = NULL;
		left = NULL;
		parent = temp;
	}
};
struct menu {
	int Id;
	string Name;
	int Total_dishes;
	dish* root;
	menu() {
		root = NULL;
		srand(time(0));
		Id = 9999 + (rand() % 100000);
		Name = "";
		Total_dishes = 0;
	}
	void add_dish(string name, string type, int price) {
		root = insertLevelOrder(root, name, price, type);
	}
	dish* insertLevelOrder(dish* root, string name, int price, string type) {
		if (!root) {
			return new dish(name, price, type, NULL);
		}
		dish** queue = new dish * [100];
		int front = 0;
		int rear = 0;
		queue[rear] = root;
		rear++;

		while (front < rear) {
			dish* temp = queue[front];
			front++;
			if (temp->left == NULL) {
				temp->left = new dish(name, price, type, temp);
				temp->left->parent = temp;
				delete[] queue;
				return root;
			}
			else {
				queue[rear] = temp->left;
				rear++;
			}

			if (temp->right == NULL) {
				temp->right = new dish(name, price, type, temp);
				temp->right->parent = temp;
				delete[] queue;
				return root;
			}
			else {
				queue[rear] = temp->right;
				rear++;
			}
		}
		delete[] queue;
		return root;
	}
	void edit_dish() {
		string name;
		cout << "Enter the name of dish in which you want to edit : ";
		cin >> name;
		dish* temp = searching_dish(root, name);
		int choice = 7;
		while (choice != 0) {
			cout << "what do you want to change : \nPress0: Exit\nPress1: Name\nPress2: Type\nPress3: price\nEnter Your choice : ";
			cin >> choice;
			if (choice == 1) {
				cout << "Enter name of the restaurant : ";
				cin >> temp->name;
			}
			else if (choice == 2) {
				cout << "Enter type of the restaurant : ";
				cin >> temp->type;
			}
			else if (choice == 3) {
				cout << "Enter price of the restaurant : ";
				cin >> temp->price;
				cout << "\n";
			}
		}
	}
	dish* searching_dish(dish* root, string name) {
		if (root == nullptr) {
			return nullptr;
		}
		if (root->name == name) {
			return root;
		}

		dish* found_dish = searching_dish(root->left, name);
		if (found_dish != nullptr) {
			return found_dish;
		}
		return searching_dish(root->right, name);
	}

	void remove_dish() {
		string name;
		cout << "Enter the dish which you want to remove : ";
		cin >> name;
		deletenode(root, name);
	}
	dish* deletenode(dish* root, string data)
	{
		if (root == NULL)
			return NULL;
		if (root->left == NULL && root->right == NULL) {
			if (root->name == data) {
				return NULL;
			}
			else
				return root;
		}
		queue<dish*> q;
		q.push(root);
		dish* temp = NULL;
		dish* nodetodelete = NULL;
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			if (temp->name == data) {
				nodetodelete = temp;
			}
			if (temp->left) {
				q.push(temp->left);
			}
			if (temp->right) {
				q.push(temp->right);
			}
		}
		if (nodetodelete != NULL) {
			if (temp != nodetodelete) {
				string t = temp->name;
				deletedeepest(root, temp);
				nodetodelete->name = t;
			}
			else {
				deletedeepest(root, temp);
			}
		}
		return root;
	}
	void deletedeepest(dish* root, dish* temp)
	{
		queue<dish*> q;
		q.push(root);
		while (!q.empty()) {
			dish* T = q.front();
			q.pop();
			if (T->right == temp) {
				T->right = NULL;
				delete (temp);
				return;
			}
			else
				q.push(T->right);
			if (T->left == temp) {
				T->left = NULL;
				delete (temp);
				return;
			}
			else
				q.push(T->left);

		}
	}
	int height(dish* node) {
		if (node == NULL) {
			return 0;
		}
		return max(height(node->left), height(node->right)) + 1;
	}
	void levelOrderTraversal() {
		if (root == NULL) {
			cout << "Menu is empty\n";
		}
		else {
			int h = height(root);
			for (int i = 1; i <= h; i++) {
				displaymenuw(root, i);
			}
			cout << endl;
		}
	}
	void displaymenuw(dish* node, int level) {
		if (node == NULL) {
			return;
		}
		if (level == 1) {
			cout << " Name = " << node->name << " ( " << " Price = " << node->price << " ) " << endl;
		}
		else if (level > 1) {
			displaymenuw(node->left, level - 1);
			displaymenuw(node->right, level - 1);
		}
	}
};
struct dishi {
	string name;
	int price;
	string type;
	dishi* next;
	dishi() {
		name = "";
		price = 0;
		type = "";
		next = NULL;
	}
};
struct Customer {
	int Id;
	string Name;
	string Email;
	string Password;
	Customer* next;
	Customer() {
		int I = 9999 + (rand() % 100000);
		Id = I;
		Name = "";
		Email = "";
		Password = "";
		next = NULL;
	}
	Customer(string name, string email, string pass) {
		int I = 9999 + (rand() % 100000);
		Id = I;
		cut = I;
		Name = name;
		Email = email;
		Password = pass;
		next = NULL;
	}
};
struct Customer_Hashmap {
	Customer* array[100];
	string n;
	string p;
	Customer_Hashmap() {
		for (int i = 0; i < 100; i++) {
			array[i] = NULL;
		}
		n = "";
		p = "";
	}
	void insert(Customer* temp) {
		int Position = temp->Id % 100;
		if (array[Position] == NULL) {
			array[Position] = temp;
		}
		else {
			Customer* Hold = array[Position];
			while (Hold->next != NULL) {
				Hold = Hold->next;
			}
			Hold->next = temp;
		}
	}
	bool checking(string pass) {
		if (pass.length() < 8 && pass.length() > 12) {
			return true;
		}
		else {
			bool ch = true;
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] <= 'Z' && pass[i] >= 'A') {
					ch = false;
				}
			}
			if (ch) {
				return true;
			}
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] <= 'z' && pass[i] >= 'a') {
					ch = false;
				}
			}
			if (ch) {
				return true;
			}
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] >= '1' && pass[i] <= '9') {
					ch = false;
				}
			}
			if (ch) {
				return true;
			}
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] == '#' || (pass[i] == '@') || (pass[i] == '*') || (pass[i] == '!')) {
					ch = false;
				}
			}
			if (ch) {
				return true;
			}
			return ch;
		}
	}
	void signup() {
		string name, email, pass = "", pass1 = "";
		cout << "Enter your User name : ";
		cin >> name;
		cout << "Enter your User email : ";
		cin >> email;
		bool checked = true;
		while (pass != pass1 || checked) {
			cout << "Enter your User Password : ";
			char ch;
			while (true) {
				ch = _getch();
				if (ch == 13) {
					break;
				}
				else if (ch == 8) {
					cout << "\b \b";
					pass.pop_back();
				}
				else {
					cout << "*";
					pass.push_back(ch);
				}
			}
			cout << "Renter your User Password : ";
			while (true) {
				ch = _getch();

				if (ch == 13) {
					break;
				}
				else if (ch == 8) {
					cout << "\b \b";
					pass1.pop_back();
				}
				else {
					cout << "*";
					pass1.push_back(ch);
				}
			}
			checked = checking(pass);
		}
		Customer* temp = new Customer(name, email, pass);
		n = temp->Name;
		p = temp->Password;
		insert(temp);
	}
	Customer* search(string name, string pass) {
		int i = 0;
		Customer* Hold = array[i];
		while (i != 100) {
			if (Hold == NULL) {
				i++;
				Hold = array[i];
			}
			else {
				while (Hold != NULL) {
					if (Hold->Name == name && Hold->Password == pass) {
						return Hold;
					}
					Hold = Hold->next;
				}
			}
		}
		return NULL;
	}
	void Loginin() {
		string name, pass;
		cout << "Enter your User name : ";
		cin >> name;
		cout << "Enter your User pasword: ";
		char ch;
		while (true) {
			ch = _getch();

			if (ch == 13) {
				break;
			}
			else if (ch == 8) {
				cout << "\b \b";
				pass.pop_back();
			}
			else {
				cout << "*";
				pass.push_back(ch);
			}
		}
		Customer* Hold = search(name, pass);
		if (Hold == NULL) {
			int choice = 0;
			cout << "You don't have an account";
			while (choice != 2 && choice != 1) {
				cout << "Do you in \nPress1: want to sign\nPress2: Exit\nEnter your choice : ";
				cin >> choice;
			}
			if (choice == 1) {
				signup();
				return;
			}
			else {
				exit(0);
			}
		}
		n = name;
		p = pass;
	}
	void updating() {
		cout << endl;
		int choice = 0;
		while (choice != 1 && choice != 2) {
			cout << "Which data do you want to update : \nPress1: name\nPress2: password\n Enter your choice : ";
			cin >> choice;
		}
		if (choice == 1) {
			string name;
			Customer* Hold = search(n, p);
			cout << "Enter new name : ";
			cin >> name;
			Hold->Name = name;
			n = name;
		}
		if (choice == 2) {
			string pass = "";
			Customer* Hold = search(n, p);
			while (pass != p) {
				cout << "Enter old password : ";
				cin >> pass;
			}
			cout << "Enter new password : ";
			cin >> pass;
			Hold->Password = pass;
			p = pass;
		}
		return;
	}
	void display() {
		int i = 0;
		Customer* Hold = array[i];
		while (i != 100) {
			if (Hold == NULL) {
				i++;
				Hold = array[i];
			}
			else {
				cout << Hold->Id << " , " << Hold->Name << ", " << Hold->Email << " , " << Hold->Password << endl;
				Hold = Hold->next;
			}
		}
	}
};

struct Employees {
	string restraunt_Name;
	int Id;
	string Name;
	string Type;
	string Email;
	string Password;
	Employees* next;
	Employees() {
		Id = 9999 + (rand() % 100000);
		Name = "";
		Type = "";
		Email = "";
		restraunt_Name = "";
		Password = "";
		next = NULL;
	}
	Employees(string name, string email, string pass, string type, string rs) {
		int I = 9999 + (rand() % 100000);
		Id = I;
		cut = I;
		Name = name;
		Type = type;
		Email = email;
		restraunt_Name = rs;
		Password = pass;
		next = NULL;
	}
};
struct orders {
	int Id;
	dishi* dishes;
	int Total;
	string Type;
	orders* next;
	Customer* Customr;
	Employees* Employee;
	orders() {
		srand(time(0));
		Id = 9999 + (rand() % 100000);
		dishes = NULL;
		next = NULL;
		Customr = new Customer;
		Total = 0;
		Employee = NULL;
		Type = "";
	}
	void add_dish(dish* temp) {
		if (dishes == NULL) {
			dishes = new dishi;
			dishes->name = temp->name;
			dishes->type = temp->type;
			dishes->price = temp->price;
		}
		else {
			dishi* hold = dishes;
			while (hold->next != NULL) {
				hold = hold->next;
			}
			hold->next = new dishi;
			hold->next->name = temp->name;
			hold->next->price = temp->price;
			hold->next->type = temp->type;
		}
	}
	void remove_dish(string nam) {
		if (dishes == NULL) {
			cout << "No dish to remove!!" << endl;
		}
		else {
			dishi* hold = dishes;
			if (hold->name == nam && hold->next != NULL) {
				dishes = hold->next;
				Total -= hold->price;
				delete hold;
			}
			else if (hold->name == nam && hold->next == NULL) {
				dishes = NULL;
				Total = 0;
				delete hold;
			}
			else {
				dishi* prev = NULL;
				while (hold != NULL) {
					if (hold->name == nam) {
						prev->next = hold->next;
						Total -= hold->price;
						delete hold;
						return;
					}
					prev = hold;
					hold = hold->next;
				}
				cout << "Dish not found!!";
			}
		}
	}
	void display() {
		if (dishes == NULL) {
			cout << "No dish to remove!!" << endl;
		}
		else {
			dishi* hold = dishes;
			cout << "<----------------------------" << Id << "------------------------------->\n";
			cout << "Order Type : " << Type << endl;
			while (hold != NULL) {
				cout << "Name : " << hold->name << " Type : " << hold->type << "Price : " << hold->price << endl;
				hold = hold->next;
			}
			cout << "your total price is : " << Total << endl;
		}
	}
};
struct permotions {
	int Id;
	string Name;
	float Discount;
	int Limit;
	int limit_applied;
	permotions* next;
	permotions() {
		srand(time(0));
		Id = 9999 + (rand() % 100000);
		Discount = 0.0;
		Limit = 0;
		limit_applied = 0;
		Name = "";
	}
	permotions(float dis, int lim, string name) {
		srand(time(0));
		Id = 9999 + (rand() % 100000);
		Discount = dis;
		Limit = lim;
		limit_applied = 0;
		Name = name;
	}
};
class Stack_permotions {
	permotions* top;
	int limit;
	int length;
public:
	Stack_permotions(int lmit) {
		top = NULL;
		limit = lmit;
		length = 0;
	}
	~Stack_permotions() {
		while (!isEmpty()) {
			pop();
		}
	}
	bool isEmpty()
	{
		if (top == NULL)
		{
			cout << "There are no promotions in our list!!" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isFull()
	{
		if (length == limit)
		{
			cout << "The promotion list is full" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	void push(string name, int lim, float dis)
	{
		if (!isFull())
		{
			if (top == NULL) {
				top = new permotions(dis, lim, name);
				length++;
			}
			else {
				permotions* temp = new permotions(dis, lim, name);
				temp->next = top;
				top = temp;
				length++;
			}
		}
	}
	void pop()
	{
		permotions* temp = top;
		length--;
		if (length == 0) {
			delete temp;
			top = NULL;
			return;
		}
		else {
			top = top->next;
		}
		delete temp;
	}
	void peek()
	{
		if (!isEmpty())
		{
			cout << "Top of the stack: " << top->Name << endl;
		}
	}
	void display()
	{
		if (!isEmpty())
		{
			cout << "Promotions left are : " << endl;
			permotions* temp = top;
			while (temp != NULL)
			{
				cout << temp->Name << endl;
				temp = temp->next;
			}
			cout << endl;
		}
	}
	void execution(orders* o) {
		if (top != NULL) {
			o->Total -= ((o->Total * top->Discount) / 100);
			top->limit_applied++;
			if (top->limit_applied == top->Limit) {
				pop();
			}
			cout << "promotion applied" << endl;
		}
		else {
			cout << "promotion not applied" << endl;
		}
	}
};
struct Employees_hashmap {
	Employees* array[100];
	string n;
	string p;
	void newresname(string oldname,string newname){
		int i = 0;
		Employees* Hold = array[i];
		while (i != 100) {
			if (Hold == NULL) {
				i++;
				Hold = array[i];
			}
			else {
				while (Hold != NULL) {
					if (Hold->restraunt_Name == oldname) {
						Hold->restraunt_Name=newname;
					}
					Hold = Hold->next;
				}
			}
		}
	}
	Employees_hashmap() {
		for (int i = 0; i < 100; i++) {
			array[i] = NULL;
		}
		n = "";
		p = "";
	}
	void insert(Employees* temp) {
		int Position = temp->Id % 100;
		if (array[Position] == NULL) {
			array[Position] = temp;
		}
		else {
			Employees* Hold = array[Position];
			while (Hold->next != NULL) {
				Hold = Hold->next;
			}
			Hold->next = temp;
		}
	}
	bool checking(string pass) {
		if (pass.length() < 8 && pass.length() > 12) {
			return true;
		}
		else {
			bool ch = true;
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] <= 'Z' && pass[i] >= 'A') {
					ch = false;
					break;
				}
			}
			if (ch) {
				return true;
			}
			ch = true;
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] <= 'z' && pass[i] >= 'a') {
					ch = false;
					break;
				}
			}
			if (ch) {
				return true;
			}
			ch = true;
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] >= '1' && pass[i] <= '9') {
					ch = false;
					break;
				}
			}
			if (ch) {
				return true;
			}
			ch = true;
			for (int i = 0; i < pass.length(); i++) {
				if (pass[i] == '#' || (pass[i] == '@') || (pass[i] == '*') || (pass[i] == '!')) {
					ch = false;
					break;
				}
			}
			if (ch) {
				return true;
			}
			return ch;
		}
	}
	void signup(string type) {
		if (type == "manager") {
			string name, email, pass = "", pass1 = "", res, type1;
			cout << "Enter your User name : ";
			cin >> name;
			cout << "Enter your User email : ";
			cin >> email;
			cout << "Enter your Type : ";
			cin >> type1;
			if (type1 == "simple") {
				cout << "Enter your User restraunt name : ";
				cin >> res;
			}
			else {
				res = "";
			}
			char ch;
			bool checked = true;
			while (pass != pass1 || checked) {
				cout << "Enter your User Password : ";
				while (true) {
					ch = _getch();
					if (ch == 13) {
						break;
					}
					else if (ch == 8) {
						cout << "\b \b";
						pass.pop_back();
					}
					else {
						cout << "*";
						pass.push_back(ch);
					}
				}
				cout << "\nRenter your User Password : ";
				while (true) {
					ch = _getch();

					if (ch == 13) {
						break;
					}
					else if (ch == 8) {
						cout << "\b \b";
						pass1.pop_back();
					}
					else {
						cout << "*";
						pass1.push_back(ch);
					}
				}
				checked = checking(pass);
			}
			Employees* temp = new Employees(name, email, pass, type1, res);
			n = temp->Name;
			p = temp->Password;
			insert(temp);
		}
		else {
			cout << "\n\nYou are not allowed to sign up!!" << endl;
			boo1 = true;
		}
	}
	Employees* search(string name, string pass) {
		int i = 0;
		string name1;
		string name2;
		Employees* Hold = array[i];
		while (i != 100) {
			if (Hold == NULL) {
				i++;
				Hold = array[i];
			}
			else {
				while (Hold != NULL) {
					if (Hold->Name == name && Hold->Password == pass) {
						return Hold;
					}
					Hold = Hold->next;
				}
			}
		}
		return NULL;
	}
	void Loginin() {
		string name, pass, type;
		int I;
		cout << "Enter your User name : ";
		cin >> name;
		cout << "Enter your User pass : ";
		char ch;
		while (true) {
			ch = _getch();

			if (ch == 13) {
				break;
			}
			else if (ch == 8) {
				cout << "\b \b";
				pass.pop_back();
			}
			else {
				cout << "*";
				pass.push_back(ch);
			}
		}
		Employees* Hold = search(name, pass);
		if (Hold == NULL) {
			int choice = 0;
			cout << "\nYou don't have an account";
			while (choice != 2 && choice != 1) {
				cout << "Do you in \nPress1: want to sign\nPress2: Exit\nEnter your choice : ";
				cin >> choice;
			}
			if (choice == 1) {
				signup(type);
				return;
			}
			else {
				exit(0);
			}
		}
		n = name;
		p = pass;
	}
	void updating() {
		cout << endl;
		int choice = 0;
		while (choice != 1 && choice != 2) {
			cout << "Which data do you want to update : \nPress1: name\nPress2: password\nEnter your choice : ";
			cin >> choice;
		}
		if (choice == 1) {
			string name;
			Employees* Hold = search(n, p);
			cout << "Enter new name : ";
			cin >> name;
			Hold->Name = name;
			n = name;
		}
		if (choice == 2) {
			string pass = "";
			Employees* Hold = search(n, p);
			while (pass != p) {
				cout << "Enter old password : ";
				cin >> pass;
			}
			cout << "Enter new name : ";
			cin >> pass;
			Hold->Password = pass;
			p = pass;
		}
		return;
	}
	Employees* make_manager(string name) {
		cout << "You must choose a manager for your restaurant!!\n" << endl;
		int i = 0;
		Employees* Hold = array[i];
		boo = false;
		while (i != 100) {
			if (Hold == NULL) {
				i++;
				Hold = array[i];
			}
			else {

				if (Hold->Type == "manager" && Hold->restraunt_Name == "") {
					cout << Hold->Name << " is available at index " << i << endl;
					boo = true;

				}
				Hold = Hold->next;
			}
		}
		if (boo == true) {
			string name1;
			cout << "Enter the index of employee which you want to add : ";
			cin >> i;
			cout << "Enter the Name of employee which you want to add : ";
			cin >> name1;
			Hold = array[i];
			while (Hold != NULL) {
				if (Hold->Name == name1) {
					Hold->restraunt_Name = name;
					return Hold;
				}
				Hold = Hold->next;
			}
		}
		else {
			cout << "No manager is available!!";
		}
	}
	void display() {
		int i = 0;
		Employees* Hold = array[i];
		while (i != 100) {
			if (Hold == NULL) {
				i++;
				Hold = array[i];
			}
			else {
				cout << Hold->Id << " , " << Hold->Name << ", " << Hold->Email << " , " << Hold->Password << endl;
				Hold = Hold->next;
			}
		}
	}
};
struct Restaurants_node {
	Stack_permotions* p;
	orders* start;
	orders* completed;
	int Id;
	string Name;
	string Type;
	Employees* Manager; //pointer to the employee who is the manager of the restaurant.
	menu* menue; //a tree of the menu of the restaurant. 
	Restaurants_node* next; //linklist of restraunts
	Restaurants_node() {
		int i;
		srand(time(0));
		Id = 9999 + (rand() % 100000);
		Name = "";
		Type = "";
		Manager = NULL;
		start = NULL;
		menue = new menu;
		completed = NULL;
		p = new Stack_permotions(2);
		p->push("A", 1, 10);
		next = NULL;
	}
};
struct Restraunt_working {
	Restaurants_node* start;
	Restraunt_working() {
		start = NULL;
	}
	void display_completed_employee(Employees* e, string res_name) {
		Restaurants_node* n = search_restraunt(res_name);
		if (n->completed == NULL) {
			cout << "No order has been processed!!" << endl;
		}
		else {
			int choice;
			cout << "Do you want to see the orders completed :\nPress1: By this employee\nPress2: By the restaurant\nEnter your choice : ";
			cin >> choice;
			if (choice == 1) {
				orders* k = n->completed;
				while (k != NULL) {
					if (k->Employee == e) {
						k->display();
					}
					k = k->next;
				}
			}
			else {
				orders* k = n->completed;
				while (k != NULL) {
					k->display();
					k = k->next;
				}
			}
		}
	}
	bool check_id(Restaurants_node* temp) {
		if (start == NULL) {
			return false;
		}
		else {
			Restaurants_node* hold = start;
			while (hold->next != NULL) {
				if (hold->Id == temp->Id) {
					return true;
				}
				hold = hold->next;
			}
			if (hold->Id == temp->Id) {
				return true;
			}
			return false;
		}
	}
	void Add_restraunt(Employees_hashmap* e) {
		Restaurants_node* temp = new Restaurants_node;
		cout << "Enter name of the restaurant : ";
		cin >> temp->Name;
		cout << "Enter type of the restaurant : ";
		cin >> temp->Type;
		while (check_id(temp)) {
			srand(time(0));
			temp->Id = 9999 + (rand() % 100000);
		}
		temp->Manager = e->make_manager(temp->Name);
		if (boo == true) {
			if (temp == NULL) {
				cout << "memory not allocated!!" << endl;
				return;
			}
			else {
				if (start == NULL) {
					start = temp;
				}
				else {
					Restaurants_node* hold = start;
					while (hold->next != NULL) {
						hold = hold->next;
					}
					hold->next = temp;
				}
			}
		}
		else {
			temp->Manager = NULL;
			if (temp == NULL) {
				cout << "memory not allocated!!" << endl;
				return;
			}
			else {
				if (start == NULL) {
					start = temp;
				}
				else {
					Restaurants_node* hold = start;
					while (hold->next != NULL) {
						hold = hold->next;
					}
					hold->next = temp;
				}
			}
		}
	}
	void Add_restraunt_data(Employees* e1, string name, string type) {
		Restaurants_node* temp = new Restaurants_node;
		temp->Name = name;
		temp->Type = type;
		while (check_id(temp)) {
			srand(time(0));
			temp->Id = 9999 + (rand() % 100000);
		}
		e1->restraunt_Name = temp->Name;
		temp->Manager = e1;
		if (temp == NULL) {
			cout << "memory not allocated!!" << endl;
			return;
		}
		else {
			if (start == NULL) {
				start = temp;
			}
			else {
				Restaurants_node* hold = start;
				while (hold->next != NULL) {
					hold = hold->next;
				}
				hold->next = temp;
			}
		}
	}
	Restaurants_node* search_restraunt(string name) {
		if (start == NULL) {
			cout << "Restaurant not found!!" << endl;
			return NULL;
		}
		else {
			Restaurants_node* hold = start;
			bool not_found = true;
			while (hold->next != NULL && not_found) {
				if (hold->Name == name) {
					return hold;
				}
				hold = hold->next;
			}
			if (hold->Name == name) {
				return hold;
			}
			cout << "Restaurant not found!!" << endl;
			return NULL;
		}
	}
	void display_restraunt() {
		if (start == NULL) {
			cout << "No restaurant found!!" << endl;
			return;
		}
		else {
			Restaurants_node* hold = start;
			while (hold != NULL) {
				cout << " Name : " << hold->Name << " , Type : " << hold->Type << " , Manager : ";
				if (hold->Manager != NULL) {
					cout << hold->Manager->Name << endl;
				}
				else {
					cout << "No manager alocated" << endl;
				}
				hold = hold->next;
			}
		}
	}
	void Editing_restraunt(Employees_hashmap*e){
		if (start == NULL) {
			cout << "No restraunt to Edit!!";
		}
		else {
			string name;
			cout << "Enter name of the restaurant : ";
			cin >> name;
			int choice=0;
			Restaurants_node* hold = search_restraunt(name);
			cout << "What do you want to edit :\nPress 1. For Name\nPress 2. For Type\nPress 3. For Manager\nPress 4.To add a Permotion\nEnter your choice : ";
			cin >> choice;
			if (choice == 1) {
				cout << "Enter the new name : ";
				cin >> hold->Name;
				e->newresname(name, hold->Name);
			}
			else if (choice == 2) {
				cout << "Enter the new name : ";
				cin >> hold->Type;
			}
			else if (choice == 3) {
				if (hold->Manager == NULL) {
					hold->Manager = e->make_manager(hold->Name);
					if(boo==false){
						hold->Manager = NULL;
					}
				}
				else {
					hold->Manager->restraunt_Name = "";
					hold->Manager = NULL;
					hold->Manager = e->make_manager(hold->Name);
					if (boo == false) {
						hold->Manager = NULL;
					}
				}
			}
			else if (choice == 4){
				string nam = "";
				int lim, dis;
				cout << "Enter the name of the new permotion : ";
				cin >> nam;
				cout << "Enter the limit of the new permotion : ";
				cin >> lim;
				cout << "Enter the discount of the new permotion : ";
				cin >> dis;
				hold->p->push(nam, lim, dis);
			}
		}
	}

	void delete_restraunt() {
		if (start == NULL) {
			cout << "No restraunt to delete!!";
		}
		else {
			string name;
			cout << "Enter name of the restaurant : ";
			cin >> name;
			Restaurants_node* hold = search_restraunt(name);
			Restaurants_node* temp = start;
			if (hold != NULL) {
				if (hold == start && start->next == NULL) {
					start = NULL;
					hold->Manager->restraunt_Name = "";
					delete hold;
					return;
				}
				if (hold == start && start->next != NULL) {
					start = start->next;
					hold->Manager->restraunt_Name = "";
					delete hold;
					return;
				}
				while (temp->next != NULL) {
					if (temp->next == hold) {
						hold->Manager->restraunt_Name = "";
						temp->next = hold->next;
						delete hold;
						break;
					}
					temp = temp->next;
				}
				return;
			}
		}
	}
	void choose_restraunt(Customer* temp) {
		orders* o = new orders;
		string name;
		cout << "Enter name of the restaurant : ";
		cin >> name;
		Restaurants_node* hold = search_restraunt(name);
		if (hold) {
			int choice = 8;
			while (choice != 3) {
				cout << "\nWhich of the following do you want to do in your order : \nPress1: To Add dish in order\nPress2: remove a dish from your order\nPress3: finish your order\nEnter your choice : ";
				cin >> choice;
				cout << "Your current order is : \n";
				o->display();
				if (choice == 1) {
					hold->menue->levelOrderTraversal();
					if (hold->menue->root != NULL) {
						string name;
						cout << "Enter a dish name : ";
						cin >> name;
						dish* temp1 = hold->menue->searching_dish(hold->menue->root, name);
						if (temp1) {
							o->add_dish(temp1);
						}
						else {
							cout << "Dish not found";
						}
					}
				}
				else if (choice == 2) {
					string name;
					cout << "Enter a Dish name : ";
					cin >> name;
					dish* temp1 = hold->menue->searching_dish(hold->menue->root, name);
					if (temp1) {
						o->remove_dish(name);
					}
				}
				else if (choice == 3) {
					if (o->dishes != NULL) {
						cout << "Enter Type of your order (Premium, express & normal) : ";
						cin >> o->Type;
						dishi* d = o->dishes;
						while (d->next != NULL) {
							o->Total += d->price;
							d = d->next;
						}
						o->Total += d->price;
						hold->p->execution(o);
						if (o->Type == "Premium") {
							o->Total += ((o->Total * 50) / 100);;
						}
						else if (o->Type == "express") {
							o->Total += ((o->Total * 20) / 100);
						}
						o->display();
						o->Customr = temp;
						if (hold->start == NULL) {
							hold->start = o;
						}
						else {
							orders* temp1 = hold->start;
							while (temp1->next != NULL) {
								temp1 = temp1->next;
							}
							temp1->next = o;
						}
					}
				}
			}
		}
	}
	void execute_orders(string name, Employees* e) {
		Restaurants_node* hold = search_restraunt(name);
		orders* ord = hold->start;
		if (ord == NULL) {
			cout << "No order in the queue to process.\n";
			return;
		}
		else {
			string p = "Premium";
			do {
				if (ord->Type == p) {
					dishi* d = ord->dishes;
					dishi* temp1 = ord->dishes->next;
					while (d != NULL) {
						dish* k = hold->menue->searching_dish(hold->menue->root, d->name);
						if (k == NULL) {
							ord->remove_dish(d->name);
						}
						d = temp1;
						if (temp1 != NULL) {
							temp1 = temp1->next;
						}
					}
					if (hold->completed == NULL) {
						hold->completed = new orders;
						ord->Employee = e;
						hold->completed->Customr = ord->Customr;
						hold->completed->dishes = ord->dishes;
						hold->completed->Employee = ord->Employee;
						hold->completed->Id = ord->Id;
						hold->completed->Total = ord->Total;
						hold->completed->Type = ord->Type;
					}
					else {
						orders* cu = hold->completed;
						while (cu->next != NULL) {
							cu = cu->next;
						}
						cu->next = new orders;
						ord->Employee = e;
						cu->next->Customr = ord->Customr;
						cu->next->dishes = ord->dishes;
						cu->next->Employee = ord->Employee;
						cu->next->Id = ord->Id;
						cu->next->Total = ord->Total;
						cu->next->Type = ord->Type;
					}
					cout << "\n\n<---------------Order " << ord->Id << " has been Processed------------------>\n\n";
					if (ord == hold->start && ord->next != NULL) {
						hold->start = hold->start->next;
						delete ord;
						ord = hold->start;
					}
					else if (ord == hold->start && ord->next == NULL) {
						delete hold->start;
						hold->start = NULL;
						ord = hold->start;
						return;
					}
					else {
						orders* current = hold->start;
						while (current->next != ord) {
							current = current->next;
						}
						current->next = ord->next;
						delete ord;
						ord = current->next;
					}
				}
				else {
					ord = ord->next;
				}
			} while (ord != NULL);
			ord = hold->start;
			p = "express";
			do {
				if (ord->Type == p) {
					dishi* d = ord->dishes;
					dishi* temp1 = ord->dishes->next;
					while (d != NULL) {
						dish* k = hold->menue->searching_dish(hold->menue->root, d->name);
						if (k == NULL) {
							ord->remove_dish(d->name);
						}
						d = temp1;
						if (temp1 != NULL) {
							temp1 = temp1->next;
						}
					}
					if (hold->completed == NULL) {
						hold->completed = new orders;
						ord->Employee = e;
						hold->completed->Customr = ord->Customr;
						hold->completed->dishes = ord->dishes;
						hold->completed->Employee = ord->Employee;
						hold->completed->Id = ord->Id;
						hold->completed->Total = ord->Total;
						hold->completed->Type = ord->Type;
					}
					else {
						orders* cu = hold->completed;
						while (cu->next != NULL) {
							cu = cu->next;
						}
						cu->next = new orders;
						ord->Employee = e;
						cu->next->Customr = ord->Customr;
						cu->next->dishes = ord->dishes;
						cu->next->Employee = ord->Employee;
						cu->next->Id = ord->Id;
						cu->next->Total = ord->Total;
						cu->next->Type = ord->Type;
					}
					cout << "\n\n<---------------Order " << ord->Id << " has been Processed------------------>\n\n";
					if (ord == hold->start && ord->next != NULL) {
						hold->start = hold->start->next;
						delete ord;
						ord = hold->start;
					}
					else if (ord == hold->start && ord->next == NULL) {
						delete hold->start;
						hold->start = NULL;
						ord = hold->start;
						return;
					}
					else {
						orders* current = hold->start;
						while (current->next != ord) {
							current = current->next;
						}
						current->next = ord->next;
						delete ord;
						ord = current->next;
					}
				}
				else {
					ord = ord->next;
				}
			} while (ord != NULL);
			ord = hold->start;
			p = "normal";
			do {
				if (ord->Type == p) {
					dishi* d = ord->dishes;
					dishi* temp1 = ord->dishes->next;
					while (d != NULL) {
						dish* k = hold->menue->searching_dish(hold->menue->root, d->name);
						if (k == NULL) {
							ord->remove_dish(d->name);
						}
						d = temp1;
						if (temp1 != NULL) {
							temp1 = temp1->next;
						}
					}
					orders* temp = ord;
					if (hold->completed == NULL) {
						hold->completed = new orders;
						ord->Employee = e;
						hold->completed->Customr = ord->Customr;
						hold->completed->dishes = ord->dishes;
						hold->completed->Employee = ord->Employee;
						hold->completed->Id = ord->Id;
						hold->completed->Total = ord->Total;
						hold->completed->Type = ord->Type;
					}
					else {
						orders* cu = hold->completed;
						while (cu->next != NULL) {
							cu = cu->next;
						}
						cu->next = new orders;
						ord->Employee = e;
						cu->next->Customr = ord->Customr;
						cu->next->dishes = ord->dishes;
						cu->next->Employee = ord->Employee;
						cu->next->Id = ord->Id;
						cu->next->Total = ord->Total;
						cu->next->Type = ord->Type;
					}
					cout << "\n\n<---------------Order " << ord->Id << " has been Processed------------------>\n\n";
					if (ord == hold->start && ord->next != NULL) {
						hold->start = hold->start->next;
						delete ord;
						ord = hold->start;
					}
					else if (ord == hold->start && ord->next == NULL) {
						delete hold->start;
						hold->start = NULL;
						ord = hold->start;
						return;
					}
					else {
						orders* current = hold->start;
						while (current->next != ord) {
							current = current->next;
						}
						current->next = ord->next;
						delete ord;
						ord = current->next;
					}
				}
				else {
					ord = ord->next;
				}
			} while (ord != hold->start);
		}
	}
	void display_completed(Customer* cu) {
		string name;
		cout << "Enter name of the restaurant : ";
		cin >> name;
		Restaurants_node* hold = search_restraunt(name);
		if (hold != NULL) {
			orders* c = hold->completed;
			while (c != NULL) {
				if (c->Customr == cu) {
					c->display();
				}
				c = c->next;
			}
		}
	}
	void display_current(Customer* cu) {
		string name;
		cout << "Enter name of the restaurant of ehich you want to see your orders: ";
		cin >> name;
		Restaurants_node* hold = search_restraunt(name);
		if (hold != NULL) {
			orders* c = hold->start;
			while (c != NULL) {
				if (c->Customr == cu) {
					c->display();
				}
				c = c->next;
			}
		}
	}
};
struct reviews_node {
	int Id;
	int Rating;
	string Description;
	Restaurants_node* restaurant;
	string c;

	reviews_node() {
		srand(time(0));
		Id = 9999 + (rand() % 100000);
		Rating = 0;
		Description = "";
		c = "";
		restaurant = nullptr;
	}
};

struct heap_reviews {
	reviews_node** reviews1;
	int size;

	heap_reviews() {
		size = 0;
		reviews1 = new reviews_node * [1];
	}

	void swap(reviews_node* a, reviews_node* b) {
		reviews_node* temp = a;
		a = b;
		b = temp;
	}

	void heapifyMin(int i) {
		int smallest = i;
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		if (l < size && reviews1[l]->Rating < reviews1[smallest]->Rating) smallest = l;
		if (r < size && reviews1[r]->Rating < reviews1[smallest]->Rating) smallest = r;
		if (smallest != i) {
			swap(reviews1[i], reviews1[smallest]);
			heapifyMin(smallest);
		}
	}
	void insertMin(string newNum, int rating, Restaurants_node* r, string s) {

		reviews_node** newArr = new reviews_node * [size + 1];

		for (int i = 0; i < size; i++) {
			newArr[i] = reviews1[i];
		}

		reviews_node* newReview = new reviews_node();
		newReview->Rating = rating;
		newReview->Description = newNum;
		newReview->restaurant = r;
		newReview->c = s;

		newArr[size] = newReview;
		delete[] reviews1;
		reviews1 = newArr;
		size++;

		for (int i = size / 2 - 1; i >= 0; i--) {
			heapifyMin(i);
		}
	}

	~heap_reviews() {
		for (int i = 0; i < size; i++) {
			delete reviews1[i];
		}
		delete[] reviews1;
	}

	void deleteNode(int rating)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			if (rating == reviews1[i]->Rating)
				break;
		}
		if (i == size)
			return;
		swap(reviews1[i], reviews1[size - 1]);
		size--;
		reviews_node* newArr = new reviews_node[size];
		for (int i = 0; i < size; i++) {
			newArr[i].Id = reviews1[i]->Id;
			newArr[i].Description = reviews1[i]->Description;
			newArr[i].Rating = reviews1[i]->Rating;
			newArr[i].restaurant = reviews1[i]->restaurant;
			newArr[i].c = reviews1[i]->c;
		}
		delete[] reviews1;
		for (int i = 0; i < size; i++) {
			reviews1[i]->Id = newArr[i].Id;
			reviews1[i]->Rating = newArr[i].Rating;
			reviews1[i]->restaurant = newArr[i].restaurant;
			reviews1[i]->Description = newArr[i].Description;
			reviews1[i]->c = newArr[i].c;
		}
		for (int i = size / 2 - 1; i >= 0; i--)
		{
			heapifyMin(i);

		}
		delete[] newArr;
	}
	void add_reviwe(Restaurants_node* r, string c, string des, int rat) {
		insertMin(des, rat, r, c);
	}
	void printminArray()
	{
		for (int i = 0; i < size; ++i) {
			if (size < 5) {
				cout << reviews1[i] << " ";
				cout << "\n";
			}
			else {
				break;
			}
		}
	}
	void print_custom(Customer* cu)
	{
		cout << endl << endl;
		for (int i = 0; i < size; i++) {
			if (reviews1[i]->c == cu->Name) {
				cout << "<--------Review # " << reviews1[i]->Id << "---------->\n";
				cout << "Ratings : " << reviews1[i]->Rating << endl;
				cout << "Restraunt name: " << reviews1[i]->restaurant->Name << endl;
				cout << "Description : " << reviews1[i]->Description << endl;
				cout << "Customer name : " << reviews1[i]->c << endl;
			}
		}
	}
	void print_custom_res(Restaurants_node* cu)
	{
		cout << endl << endl;
		for (int i = 0; i < size; i++) {
			if (reviews1[i]->restaurant->Name == cu->Name) {
				cout << "<--------Review # " << reviews1[i]->Id << "---------->\n";
				cout << "Ratings : " << reviews1[i]->Rating << endl;
				cout << "Restraunt name: " << reviews1[i]->restaurant->Name << endl;
				cout << "Description : " << reviews1[i]->Description << endl;
				cout << "Customer name : " << reviews1[i]->c << endl;
			}
		}
	}
};
struct Admin {
	string name;
	string password;
	Admin() {
		name = "Admin";
		password = "1234";
	}
	void updating() {
		int choice = 0;
		string pass;
		cout << "What do you want to change : \nPress1: name\nPress2: Password\nEnter you choice : ";
		cin >> choice;
		if (choice == 1) {
			cout << "\nEnter you password : ";
			cin >> pass;
			if (pass == password) {
				cout << "Enter your new name : ";
				cin >> name;
			}
			else {
				cout << "Wrong Password!!\n";
				return;
			}
		}
		if (choice == 2) {
			cout << "\nEnter you password : ";
			cin >> pass;
			if (pass == password) {
				cout << "Enter you new password : ";
				cin >> password;
			}
			else {
				cout << "Wrong Password!!";
				return;
			}
		}
	}
};
int main() {
	srand(0);
	//previous data
	Restraunt_working* res = new Restraunt_working;
	int choice, option = 1;
	cout << "\"A\" Admin is added into the system with names and password" << endl;
	cout << "Name: Admin, Password: 1234\n" << endl;
	Admin* A = new Admin;
	cout << "Two customers are added into the system with following names,password" << endl;
	cout << "   Name      Password  \n";
	cout << "1. cust1   12345678Aa@" << endl;
	cout << "2. cust2   12345678Bb@" << endl;
	cout << "\nTwo employee managers are added into the system with following name,type and password" << endl;
	cout << "   Name    Type         Password      restraunt\n";
	cout << "1. emp1   manager     12345678Aa@     res1" << endl;
	cout << "2. emp2   simple      12345678Bb@     res1" << endl;
	cout << "3. emp3   manager     12345678Cc@     res2" << endl;
	cout << "4. emp4   simple      12345678Dd@     res2" << endl;
	cout << "\nA permotion named \"A\" with limit 1 and discount 10% is put in stack\n";
	cout << "\n\tRestraunts\n  name\tType\tmanager\n1.res1\tdesi\temp1\n2.res2\tdesi\temp3" << endl;
	cout << "\n ___________________________";
	cout << "\n |       menu of res1      |";
	cout << "\n |_________________________|" << endl;
	Customer_Hashmap* temp = new Customer_Hashmap;
	Customer* c1 = new Customer("cust1", "cust1@gmail.com", "12345678Aa@");
	temp->insert(c1);
	Customer* c2 = new Customer("cust2", "cust2@gmail.com", "12345678Bb@");
	temp->insert(c2);
	Employees_hashmap* temp1 = new Employees_hashmap;
	Employees* e1 = new Employees("emp1", "emp1@gmail.com", "12345678Aa@", "manager", "");
	temp1->insert(e1);
	Employees* e2 = new Employees("emp2", "emp2@gmail.com", "12345678Bb@", "simple", "res1");
	temp1->insert(e2);
	Employees* e3 = new Employees("emp3", "emp3@gmail.com", "12345678Cc@", "manager", "");
	temp1->insert(e3);
	Employees* e4 = new Employees("emp4", "emp4@gmail.com", "12345678Dd@", "simple", "res2");
	temp1->insert(e4);
	res->Add_restraunt_data(e1, "res1", "desi");
	res->search_restraunt("res1")->menue->add_dish("roti", "desi", 10);
	res->search_restraunt("res1")->menue->add_dish("Kabab", "desi", 20);
	res->search_restraunt("res1")->menue->add_dish("Andashami", "desi", 30);
	res->search_restraunt("res1")->menue->levelOrderTraversal();
	res->Add_restraunt_data(e3, "res2", "Fast_Food");
	cout << "\n ___________________________";
	cout << "\n |       menu of res2      |";
	cout << "\n |_________________________|" << endl;
	res->search_restraunt("res2")->menue->add_dish("Paratha", "desi", 10);
	res->search_restraunt("res2")->menue->add_dish("Naan", "desi", 20);
	res->search_restraunt("res2")->menue->add_dish("Pizza", "Italian", 30);
	res->search_restraunt("res2")->menue->levelOrderTraversal();
	cout << "<-------------------------Reviews-------------------------------->\n";
	cout << "  customer      restraunt    description                             ratings\n1.cust1	        res1	     This restraunt has good desi food       5\n2.cust2	        res2	     This restraunt has good western food    4\n\n";
	heap_reviews* h = new heap_reviews;
	h->add_reviwe(res->search_restraunt("res1"), "cust1", "This restraunt has good desi food", 5);
	h->add_reviwe(res->search_restraunt("res2"), "cust1", "This restraunt has good western food", 4);
	int choice1 = 5;
	while (choice1 != 0) {
		cout << "Which user are you : \nPress1: Customer \nPress2: Employee\nPress3: Admin\nPress4: Instructions\nEnter your choice : ";
		cin >> choice1;
		//customer
		switch (choice1) {
		case 1:
		{
			option = 0;
			while (option != 1 && option != 2) {
				cout << "\n\nAre you signed in : \nPress1: Yes\nPress1: No\nEnter your choice : ";
				cin >> option;
			}
			//login
			if (option == 1) {
				temp->Loginin();
			}
			//signup
			if (option == 2) {
				temp->signup();
			}
			//checking
			Customer* c = temp->search(temp->n, temp->p);
			option = 1;
			while (option != 0) {
				cout << "\n\nWhich of the following do you want to do : \nPress0: Exit\nPress1: Change your data\nPress2: Place your Order\nPress3: Place a review\nPress4: View order history\nPress5: view current order\nPress6: view all your reviews\nEnter your choice : ";
				cin >> option;
				switch (option) {
					//Updating info
				case 1:
					temp->updating();
					break;
					//Making order
				case 2: {
					Customer* c = temp->search(temp->n, temp->p);
					res->choose_restraunt(c);
				}
					  break;
					  //Adding a review
				case 3: {
					string name;
					Restaurants_node* r = NULL;
					while (r == NULL) {
						cout << "Enter the restaurant name : ";
						cin >> name;
						r = new Restaurants_node;
						r = res->search_restraunt(name);
					}
					string des;
					int rat;
					cout << "Enter the description of review : ";
					cin >> des;
					cout << "Enter the rating of review : ";
					cin >> rat;
					h->add_reviwe(r, c->Name, des, rat);
				}
					  break;
				case 4:
					//displaying orders which are completed
					res->display_completed(c);
					break;
				case 5:
					////displaying orders which are uncompleted
					res->display_current(c);
					break;
				case 6:
					//displaying reviews
					h->print_custom(c);
					break;
				default:
					break;
				}
			}
			break;
		}
		//employee
		case 2:
		{
			string type;
			option = 0;
			while (option != 1 && option != 2) {
				cout << "\nAre you signed in?\nPress1: Yes\nPress2: No\nEnter your choice : ";
				cin >> option;
			}
			//login
			if (option == 1) {
				temp1->Loginin();
			}
			//signup
			if (option == 2) {
				cout << "\nEnter your type : ";
				cin >> type;
				temp1->signup(type);
			}
			if (boo1 == false) {
				Employees* c = temp1->search(temp1->n, temp1->p);
				option = 1;
				while (option != 0) {
					cout << "\nWhich of the following do you want to do : \nPress0: Exit\nPress1: Change your data\nPress2: View your restaurant Order\nPress3: View your restaurant review\nPress4: View Processed order history\nPress5: Process orders\nPress6: Add a dish to menu\nPress7: Remove a dish\nPress8: Add an employee\nEnter your choice : ";
					cin >> option;
					switch (option) {
						//Updating info
					case 1: {
						temp1->updating();
						break;
					}
						  //displaying orders which are uncompleted
					case 2: {
						if (c->restraunt_Name != "") {
							Restaurants_node* n = res->search_restraunt(c->restraunt_Name);
							orders* hold = n->start;
							while (hold != NULL) {
								hold->display();
								hold = hold->next;
							}
						}
						else {
							cout << "You have no restraunt!!\n";
						}
						break;
					}
						  //displaying reviews
					case 3:
					{
						if (c->restraunt_Name != "") {
							Restaurants_node* n = res->search_restraunt(c->restraunt_Name);
							h->print_custom_res(n);
						}
						else {
							cout << "You have no restraunt!!\n";
						}
						break;
					}
					//displaying orders which are completed
					case 4: {
						if (c->restraunt_Name != "") {
							Restaurants_node* n = res->search_restraunt(c->restraunt_Name);
							res->display_completed_employee(c, n->Name);
						}
						else {
							cout << "You have no restraunt!!\n";
						}
						break;
					}
						  //excuting orders
					case 5: {
						if (c->restraunt_Name != "") {
							res->execute_orders(c->restraunt_Name, c);
						}
						else {
							cout << "You have no restraunt!!\n";
						}
						break;
					}
						  //adding dish in menu
					case 6: {
						if (c->restraunt_Name != "") {
							cout << "\nCurrent menu : \n";
							int choice2 = 2;
							res->search_restraunt(c->restraunt_Name)->menue->levelOrderTraversal();
							if (c->Type == "manager") {
								while (choice2 != 0) {
									string name, type;
									int price;
									cout << "Enter the Name of the dish which you want to add : ";
									cin >> name;
									cout << "Enter the Price of the dish which you want to add : ";
									cin >> price;
									cout << "Enter the Type of the dish which you want to add : ";
									cin >> type;
									res->search_restraunt(c->restraunt_Name)->menue->add_dish(name, type, price);
									cout << "\nDo you want to add more dishes(1/0) : ";
									cin >> choice2;
								}
							}
							else {
								cout << "Sorry you are an not an manager!!\n";
							}
						}
						else {
							cout << "You have no restraunt!!\n";
						}
						break;
					}
						  //removing dish from menue
					case 7: {
						if (c->restraunt_Name != "") {
							Restaurants_node* Hold = res->search_restraunt(c->restraunt_Name);
							cout << "\nCurrent menu : \n";
							Hold->menue->levelOrderTraversal();
							int choice2 = 2;
							if (c->Type == "manager") {
								while (choice2 != 0) {
									Hold->menue->remove_dish();
									cout << "\nDo you want to add more dishes(1/0) : ";
									cin >> choice2;
								}
							}
							else {
								cout << "Sorry you are an not an manager!!\n";
							}
						}
						else {
							cout << "You have no restraunt!!\n";
						}
						break;
					}
						  //adding employee
					case 8: {
						if (c->Type == "manager") {
							temp1->signup(c->Type);
						}
						break;
					}
					default:
						break;
					}
				}
			}
			boo1 = false;
			break;
		}
		//for admin
		case 3:
		{
			//name and pass
			string name, pass;
			cout << "Enter your user name : ";
			cin >> name;
			cout << "Enter your password : ";
			cin >> pass;
			option = 1;
			//checking
			if (A->name == name && A->password == pass) {
				while (option != 0) {
					cout << "\nWhich of the following do you want to do : \nPress0: Exit\nPress1: Change your data\nPress2: View all restaurant\nPress3: View all employees\nPress4: View all Customers\nPress5: Add a restaurant\nPress6: remove a restaurant\nPress7: Edit a restaurant\nEnter your choice : ";
					cin >> option;
					switch (option) {
						//updating info
					case 1: {
						A->updating();
						break;
					}
						  //seeing restraunts
					case 2: {
						res->display_restraunt();
						break;
					}
						  //seeing employees
					case 3:
					{
						temp1->display();
						break;
					}
					//seeing Customers
					case 4: {
						temp->display();
						break;
					}
						  //Adding restraunts
					case 5: {
						res->Add_restraunt(temp1);
						break;
					}
						  //removing
					case 6: {
						res->delete_restraunt();
						break;
					}
						  //editing
					case 7: {
						res->Editing_restraunt(temp1);
						break;
					}
					default:
						break;
					}
				}
			}
			break;
		}
		//for reading instructions
		case 4:
		{
			cout << endl;
			int op = 1;
			readme* r = new readme;
			while (op != 0) {
				cout << "What do you want to do : \nPress0: Exit\nPress1: Read the instructions\nEnter your choice : ";
				cin >> op;
				cout << endl;
				if (op == 1) {
					r->reading();
				}
				cout << endl;
			}
			break;
		}
		default:
			break;
		}
	}
}
