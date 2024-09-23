#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<limits>
using namespace std;

class House
{
private:
	string owner;
	string address;
	string city;
	int bedrooms;
	float price;

public:
	static int ptr;
	void SetOwnerName(string n)
	{
		owner = n;
	}
	void SetAddress(string a)
	{
		address = a;
	}
	void SetCity(string c)
	{
		city = c;
	}
	void SetBedrooms(int b)
	{
		bedrooms = b;
	}
	void SetPrice(float p)
	{
		price = p;
	}
	string GetOwner()
	{
		return owner;
	}
	string GetAddress()
	{
		return address;
	}
	string GetCity()
	{
		return city;
	}
	int GetBedrooms()
	{
		return bedrooms;
	}
	float GetPrice()
	{
		return price;
	}

	bool isfull()
	{
		if (ptr >= 100)
		{
			cout << "No Slot Available" << endl;
			return true;
		}
		return false;
	}

	bool isempty()
	{
		if (ptr == 0)
		{
			return true;
		}
		return false;
	}

	void SaveToFile(ofstream& outfile)
	{
		outfile << owner << endl;
		outfile << address << endl;
		outfile << city << endl;
		outfile << bedrooms << endl;
		outfile << price << endl;
	}

	void LoadFromFile(ifstream& infile)
	{
		string temp;
		if (getline(infile, owner) &&
			getline(infile, address) &&
			getline(infile, city) &&
			infile >> bedrooms &&
			infile >> price)
		{
			infile.ignore();
		}
		else
		{
			cout << "Error reading data from file!" << endl;
		}
	}
};

int House::ptr = 0;

void SaveAllHouses(House available[], int count)
{
	ofstream outfile("houses.txt");
	if (outfile.is_open())
	{
		for (int i = 0; i < count; i++)
		{
			available[i].SaveToFile(outfile);
		}
		outfile.close();
		cout << "Houses saved successfully!" << endl;
	}
	else
	{
		cout << "Error opening file for writing!" << endl;
	}
}

void LoadAllHouses(House available[])
{
	ifstream infile("houses.txt");
	if (infile.is_open())
	{
		while (infile.peek() != EOF && House::ptr < 100)
		{
			available[House::ptr].LoadFromFile(infile);
			House::ptr++;
		}
		infile.close();
		cout << "Houses loaded successfully!" << endl;
	}
	else
	{
		cout << "Error opening file for reading!" << endl;
	}
}

void SearchHouses(House available[], int count)
{
searchhouse:

	system("cls");
	string city_pref;
	int price_pref, beds_pref;

	cout << "Enter your budget : ";
	cin >> price_pref;

	cout << "Enter minimum number of bedrooms : ";
	cin >> beds_pref;

	cout << "Enter city preference : ";
	cin.ignore();
	getline(cin, city_pref);

	cout << left << setw(20) << "Owner"
		<< setw(30) << "House Address"
		<< setw(15) << "City"
		<< setw(10) << "Bedrooms"
		<< setw(10) << "Price" << endl;

	for (int i = 0; i < count; i++)
	{
		bool meets_criteria = true;

		if (available[i].GetPrice() >= price_pref)
		{
			meets_criteria = true;
		}
		if (available[i].GetBedrooms() <= beds_pref)
		{
			meets_criteria = true;
		}
		if (available[i].GetCity() != city_pref)
		{
			meets_criteria = false;
		}

		if (meets_criteria)
		{


			cout << left << setw(20) << available[i].GetOwner()
				<< setw(30) << available[i].GetAddress()
				<< setw(15) << available[i].GetCity()
				<< setw(10) << available[i].GetBedrooms()
				<< setw(10) << available[i].GetPrice() << endl;

			char option;
			cout << "To Search Again(Y) OR Go back to Main Menu(M) : ";
			cin >> option;
			if (option == 'Y' || option == 'y')
			{
				goto searchhouse;
			}
			else if (option == 'M' || option == 'm')
			{
				break;
			}
		}
		else
		{
			system("cls");
			char option;
			cout << "No Houses Found for your budget:(.....To Search Again(Y) OR Go back to Main Menu(M) : ";
			cin >> option;
			if (option == 'Y' || option == 'y')
			{
				goto searchhouse;
			}
			else if (option == 'M' || option == 'm')
			{
				break;
			}
		}
	}
}

int main()
{
	House available[100];
	string owner, address, city;
	int beds, select;
	float price;
	LoadAllHouses(available);

start:
	system("cls");
	cout << "1. Enter New House\n2. Display Houses\n3. Search Houses\n4. Exit\nSelect Option: ";
	cin >> select;

	if (select == 1)
	{
		if (!available->isfull())
		{
			char answer;
			do
			{
				cin.ignore();
				cout << "Enter Owner Name: ";
				getline(cin, owner);
				cout << "Enter Address: ";
				getline(cin, address);
				cout << "Enter City: ";
				getline(cin, city);
				cout << "Enter Bedrooms: ";
				cin >> beds;
				cout << "Enter Price: ";
				cin >> price;

				available[House::ptr].SetOwnerName(owner);
				available[House::ptr].SetAddress(address);
				available[House::ptr].SetCity(city);
				available[House::ptr].SetBedrooms(beds);
				available[House::ptr].SetPrice(price);
				House::ptr++;
				SaveAllHouses(available, House::ptr);
				cout << "Add another house? (Y/N): ";
				cin >> answer;
				if (answer == 'N' || answer == 'n')
				{
					goto start;
				}
			} while (answer == 'Y' || answer == 'y');
		}
	}
	else if (select == 2)
	{
		system("cls");
		cout << left << setw(20) << "Owner"
			<< setw(30) << "House Address"
			<< setw(15) << "City"
			<< setw(10) << "Bedrooms"
			<< setw(10) << "Price" << endl;

		for (int i = 0; i < House::ptr; i++)
		{
			cout << left << setw(20) << available[i].GetOwner()
				<< setw(30) << available[i].GetAddress()
				<< setw(15) << available[i].GetCity()
				<< setw(10) << available[i].GetBedrooms()
				<< setw(10) << available[i].GetPrice() << endl;
		}

		system("pause");
	}
	else if (select == 3)
	{
		SearchHouses(available, House::ptr);
	}
	else if (select == 4)
	{
		SaveAllHouses(available, House::ptr);
		exit;
	}

	goto start;

	return 0;
}
