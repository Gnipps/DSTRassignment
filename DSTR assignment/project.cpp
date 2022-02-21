#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct transaction
{
	int cus_id;
	string cus_name;
	int ticket_count;
	int price;
	string movie;
	transaction* next;
	transaction* prev;
}* head, * tail;



void insertintosortedlist(int cus_id, string cus_name, int ticket_count, int price, string movie)
{
	transaction* receipt = new transaction;
	receipt->cus_id = cus_id;
	receipt->cus_name = cus_name;
	receipt->ticket_count = ticket_count;
	receipt->price = price;
	receipt->movie = movie;
	receipt->next = NULL;
	receipt->prev = NULL;

	if (head == NULL)
	{
		head = tail = receipt;
	}
	else if (price > head->price)
	{
		receipt->next = head;
		head->prev = receipt;
		head = receipt;
	}
	else if (price < head->price)
	{
		tail->next = receipt;
		receipt->prev = tail;
		tail = receipt;
	}
	else
	{
		transaction* current = head->next;

		while (current != NULL)
		{
			if (price < current->price)
			{
				break;
			}
			current = current->next;
		}

		
		current->prev->next = receipt;
		
		receipt->prev = current->prev;
		
		current->prev = receipt;
		
		receipt->next = current;
	}
	
}

void displayFromTop() {
	transaction* temp = head;

	while (temp != NULL)
	{
		cout << temp->cus_id << " - " << temp->cus_name << " - " << temp->price << endl;
		temp = temp->next;
	}
	cout << "List ended here! " << endl;
}

void search_based_on_cus_id(int cus_id)
{
	transaction* temp = head; int decision = 1;

	while (temp != NULL) 
	{
		if (cus_id == temp->cus_id) 
		{
			cout << "Receipt is found! \nThe details as below: \n";
			cout << string(30, '-') << endl;
			cout << "Customer ID : " << temp->cus_id << endl;
			cout << "Customer Name : " << temp->cus_name << endl;
			cout << "Ticket Purchase : " << temp->ticket_count << endl;
			cout << "Total Price : " << temp->price << endl;
			cout << "Movie Name : " << temp->movie << endl;
		}
		temp = temp->next;
	}
	
}

void t_menu()
{
	head = tail = NULL;  int decision = 0;
	int cus_id, ticket_count, price; string cus_name, movie;

	string receipt[7][5] = {
		{"01", "Eric", "4", "40","A"},
		{"03", "James", "1","10","B"},
		{"04", "Nick", "6","60","C"},
		{"07", "John", "7","70","D"},
		{"02", "Samuel", "3","30","E"},
		{"05", "Jason", "4", "40", "A"},
		{"06", "Cindy", "2", "20", "B"}
	};


	for (int i = 0; i < size(receipt); i++)
	{
		insertintosortedlist(stoi(receipt[i][0]), receipt[i][1], stoi(receipt[i][2]), stoi(receipt[i][3]), receipt[i][4]);
	}

	
	cout << "=================================================================================" << endl;
	cout << "Transaction Menu" << endl;
	cout << "\t 1. Add new transaction \n \t 2. View all transaction " << endl;
	cout << endl;
	cout << "Select your option: ";
	cin >> decision;

	switch (decision)
	{
	case 1:
		do
		{
			cout << "Enter Cus ID: ";
			cin >> cus_id;
			cin.ignore();

			cout << "Enter first name: ";
			getline(cin, cus_name);

			cout << "Enter amount of ticket bought: ";
			cin >> ticket_count;

			cout << "Enter total price: ";
			cin >> price;

			cout << "Enter movie purchase: ";
			getline(cin, movie);
			cin.ignore();

			cout << endl;

			insertintosortedlist(cus_id, cus_name, ticket_count, price, movie);

			cout << "Do you still want to continue add a new book record? 1 -Yes, 0 - No : ";
			cin >> decision;

		} while (decision != 0);

		displayFromTop();
		t_menu();
		break;

	case 2:
		displayFromTop();
		decision = 1;
		while (decision != 0)
		{
			cout << "Enter Customer ID to view in detail :";
			cin >> cus_id;

			//step 2: search
			search_based_on_cus_id(cus_id);

			//last step: ask whether want to search again?
			cout << "Do you still want to view customer transaction? 1-Yes, 0-No : ";
			cin >> decision;
		}
		t_menu();
		break;


	default:
		cout << "Enter valid option!" << endl;
		exit;
		break;
	}
}

int main() {
	t_menu();
	return 0;
}