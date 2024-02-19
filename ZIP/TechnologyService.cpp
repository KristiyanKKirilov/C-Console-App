#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
const unsigned short MAX_ORDER_SIZE = 100;
const unsigned short CLIENT_NAME_LENGTH = 23;
const unsigned short TECH_TYPE_LENGTH = 18;
const unsigned short SERIAL_NUMBER_LENGTH = 15;
const unsigned short PROBLEM_LENGTH = 23;
const unsigned short TECHNICIAN_NAME_LENGTH = 23;
const unsigned short RENOVATION_LENGTH = 25;
const unsigned short STATUS_SIZE = 15;
const unsigned short ORDER_TYPE_SIZE = 14;
const char INVALID_CHOICE_ERROR[] = "Invalid choice!";
const char* PROBLEMS[] = { "watered" , "broken screen","audio issue", "black screen", "connection problem", "lack of capacity",
"cannot be charged", "low battery life", "overheating", "broken keyboard" };
const char* RENOVATIONS[] = { "dried and changed parts", "replaced screen", "replaced audio system", "replaced old parts", "drivers update",
"added memory", "new adapter", "replaced battery", "cooling added","replaced keycaps" };


struct ServiceOrder {
	int number;
	int dayOfMonth;
	char client[CLIENT_NAME_LENGTH];
	char typeOfTech[TECH_TYPE_LENGTH];
	char techSerialNumber[SERIAL_NUMBER_LENGTH];
	char problem[PROBLEM_LENGTH];
	char nameOfTechnician[TECHNICIAN_NAME_LENGTH] = "empty";
	char renovation[RENOVATION_LENGTH] = "empty";
	double price = 0.0;
	int daysInService = 0;
	char status[STATUS_SIZE] = "accepted";
	char orderType[ORDER_TYPE_SIZE] = "empty";
};


void displayMenu();
void addOrders(ServiceOrder orders[], int& countOfExistingOrders);
void displayHeadInformation();
void displayCurrentOrder(ServiceOrder orders[], int i);
void displayAllDevices(ServiceOrder orders[], int countOfExisingOrders);
void lowerCharArray(char arr[], int size);
void searchAndDisplayByType(ServiceOrder orders[], int countOfExistingOrders);
void searchAndDisplayByStatus(ServiceOrder orders[], int countOfExistingOrders);
void sortOrdersByDatetime(ServiceOrder orders[], int countOfExistingOrders);
void sortOrdersByTechTypeDescending(ServiceOrder orders[], int countOfExistingOrders);
void importFromTextFile(ServiceOrder orders[], int& countOfExistingOrders);
void exportToTextFile(ServiceOrder orders[], int& countOfExistingOrders);
void importFromBinaryFile(ServiceOrder orders[], int& countOfExistingOrders);
void exportToBinaryFile(ServiceOrder orders[], int& countOfExistingOrders);
void filterOptions(ServiceOrder orders[], int countOfExistingOrders);
void printTechnicianSortedOrders(ServiceOrder orders[], int countOfExistingOrders, char technicianName[]);
void printOrdersWithGivenProblem(ServiceOrder orders[], int countOfExistingOrders, char problem[]);
void configureOptions(ServiceOrder orders[], int countOfExistingOrders);
void addOrderType(ServiceOrder orders[], int countOfExistingOrders);
void insertUpdateData(ServiceOrder orders[], int countOfExistingOrders);
void changeStatusOfOrder(ServiceOrder orders[], int countOfExistingOrders);
void copyArr(ServiceOrder orders[], ServiceOrder ordersCopy[], int countOfExistingOrders);


int main()
{
	ServiceOrder orders[MAX_ORDER_SIZE];
	int countOfExistingOrders = 0;
	int menuChoice, importExportChoice;
	char exitChoice = 'n';
	char innerMenuChoice;


	importFromTextFile(orders, countOfExistingOrders);

	do
	{
		displayMenu();
		do
		{
			cout << "Enter your choice: ";
			cin >> menuChoice;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Invalid input. Please enter a number." << endl;
			}
			else {
				break;
			}
		} while (true);


		switch (menuChoice)
		{
		case 1:
			addOrders(orders, countOfExistingOrders);
			break;
		case 2:
			displayAllDevices(orders, countOfExistingOrders);
			break;
		case 3:
			cout << "\nA.Search and display devices by type of technology" << endl;
			cout << "B.Search and display devices by status of technology" << endl;
			do
			{
				cout << "Enter your choice: ";
				cin >> innerMenuChoice;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "Invalid input. Please enter char." << endl;
				}
				else {
					break;
				}
			} while (innerMenuChoice != 'a' && innerMenuChoice != 'b');
			

			if (tolower(innerMenuChoice) == 'a') {
				searchAndDisplayByType(orders, countOfExistingOrders);

			}
			else if (tolower(innerMenuChoice) == 'b') {
				searchAndDisplayByStatus(orders, countOfExistingOrders);
			}
			else {
				cout << INVALID_CHOICE_ERROR << endl;
			}
			break;
		case 4:
			sortOrdersByDatetime(orders, countOfExistingOrders);
			
			break;
		case 5:
			cout << "\nA.Text file" << endl;
			cout << "B.Binary file" << endl;
			cout << "Enter your choice: ";
			cin >> innerMenuChoice;

			if (tolower(innerMenuChoice) == 'a') {
				cout << "\n1.Import from text file" << endl;
				cout << "2.Export in text file" << endl;
				cout << "Enter your choice: ";
				cin >> importExportChoice;

				if (importExportChoice == 1) {
					importFromTextFile(orders, countOfExistingOrders);
				}
				else if (importExportChoice == 2) {
					exportToTextFile(orders, countOfExistingOrders);
				}
				else {
					cout << INVALID_CHOICE_ERROR << endl;
				}
			}
			else if (tolower(innerMenuChoice) == 'b') {
				cout << "\n1.Import from binary file" << endl;
				cout << "2.Export to binary file" << endl;
				cout << "Enter your choice: ";
				cin >> importExportChoice;
				if (importExportChoice == 1) {
					importFromBinaryFile(orders, countOfExistingOrders);
				}
				else if (importExportChoice == 2) {
					exportToBinaryFile(orders, countOfExistingOrders);
				}
				else {
					cout << INVALID_CHOICE_ERROR << endl;
				}
			}
			else {
				cout << INVALID_CHOICE_ERROR << endl;
				continue;
			}
			break;
		case 6:
			cout << "\nA.Filter options" << endl;
			cout << "B.Insert/Update data options" << endl;
			cout << "Enter your choice: ";
			cin >> innerMenuChoice;

			if (tolower(innerMenuChoice) == 'a') {
				filterOptions(orders, countOfExistingOrders);
			}
			else if (tolower(innerMenuChoice) == 'b') {
				configureOptions(orders, countOfExistingOrders);
			}
			else {
				cout << INVALID_CHOICE_ERROR << endl;
			}



			break;
		case 7:
			cout << "\nAre you sure you want to exit the program?" << endl;
			cout << "Press Y to exit" << endl << "Press N to stay" << endl;
			cout << "Enter your choice: ";

			cin >> exitChoice;
			if (tolower(exitChoice) == 'y') {
				cout << "Exiting program." << endl;
				exportToTextFile(orders, countOfExistingOrders);
			}
			else if (tolower(exitChoice) == 'n') {
				cout << "Program continues..." << endl;
			}
			else {
				cout << INVALID_CHOICE_ERROR << endl;

			}

			break;
		default:
			cout << INVALID_CHOICE_ERROR << endl;
			break;
		}

	} while (exitChoice != 'y');
	return 0;
}

void displayMenu() {
	cout << "\n1.Add orders" << endl;
	cout << "2.Display all devices" << endl;
	cout << "3.Display devices by type or status" << endl;
	cout << "4.Sort orders by date" << endl;
	cout << "5.Import/Export data" << endl;
	cout << "6.Filter/Configure data" << endl;
	cout << "7.Exit" << endl;
}
void addOrders(ServiceOrder orders[], int& countOfExistingOrders) {
	int ordersToAdd;

	cout << "\nHow many orders would you like to add?" << endl;
	do
	{
		cout << "Enter your choice: ";
		cin >> ordersToAdd;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input. Please enter a number." << endl;
		}
		else if (ordersToAdd < 1) {
			cout << "Count of orders to add cannot be a negative number!" << endl;
		}
		else if (ordersToAdd > 100) {
			cout << "Count of orders to add cannot be more than 100" << endl;
		}
		else {

			break;
		}

	} while (ordersToAdd < 1 || ordersToAdd > 100);

	if (ordersToAdd + countOfExistingOrders > 100) {
		cout << "There isn't enough space to add so many orders!" << endl;
		return;
	}
	if (countOfExistingOrders == 1) {
		cout << "There is " << countOfExistingOrders << " order." << endl;
	}
	else {
		cout << "There are " << countOfExistingOrders << " orders." << endl;
	}

	for (int i = 0; i < ordersToAdd; i++)
	{
		cout << "Enter information about order " << countOfExistingOrders + 1 << ":" << endl;
		ServiceOrder orderToAdd = {};
		
		orderToAdd.number = countOfExistingOrders + 1;

		do
		{
			cout << "Day of month: ";
			cin >> orderToAdd.dayOfMonth;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Invalid input. Please enter a number." << endl;
			}
			else if (orderToAdd.dayOfMonth < 1 || orderToAdd.dayOfMonth > 31) {
				cout << "Invalid day of month!" << endl;
			}
			else {
				break;
			}

		} while (orderToAdd.dayOfMonth < 1 || orderToAdd.dayOfMonth > 31);

		cin.ignore();
		cout << "Client's name: ";
		cin.getline(orderToAdd.client, CLIENT_NAME_LENGTH);
		cout << "Tech's type: ";
		cin.getline(orderToAdd.typeOfTech, TECH_TYPE_LENGTH);
		lowerCharArray(orderToAdd.typeOfTech, TECH_TYPE_LENGTH);
		cout << "Technology serial number: ";
		cin.getline(orderToAdd.techSerialNumber, SERIAL_NUMBER_LENGTH);

		if (strcmp(orderToAdd.typeOfTech, "phone") == 0) {
			int randomProblem = rand() % 9;
			strcpy_s(orderToAdd.problem, PROBLEMS[randomProblem]);
		}
		else if (strcmp(orderToAdd.typeOfTech, "tv") == 0) {
			int randomProblem = rand() % 5;
			strcpy_s(orderToAdd.problem, PROBLEMS[randomProblem]);
		}
		else {
			int randomProblem = rand() % 10;
			strcpy_s(orderToAdd.problem, PROBLEMS[randomProblem]);
		}

		cout << endl;
		orders[countOfExistingOrders] = orderToAdd;
		countOfExistingOrders++;
	}
}

void displayHeadInformation() {
	cout << setw(6) << "Order" << '|'
		<< setw(7) << "Day" << '|'
		<< setw(23) << "Client" << '|'
		<< setw(18) << "Tech's type" << '|'
		<< setw(15) << "Serial number" << '|'
		<< setw(23) << "Problem" << '|'
		<< setw(23) << "Technician" << '|'
		<< setw(25) << "Renovation" << '|'
		<< setw(11) << "In service" << '|'
		<< setw(12) << "Status" << '|'
		<< setw(14) << "Order type" << '|'
		<< setw(10) << "Price" << "|" << endl
		<< setfill('-') << setw(199) << ""
		<< setfill(' ') << endl;
}

void displayCurrentOrder(ServiceOrder orders[], int i) {
	cout << setw(6) << orders[i].number << '|'
		<< setw(7) << orders[i].dayOfMonth << '|'
		<< setw(23) << orders[i].client << '|'
		<< setw(18) << orders[i].typeOfTech << '|'
		<< setw(15) << orders[i].techSerialNumber << '|'
		<< setw(23) << orders[i].problem << '|'
		<< setw(23) << orders[i].nameOfTechnician << '|'
		<< setw(25) << orders[i].renovation << '|'
		<< setw(11) << orders[i].daysInService << '|'
		<< setw(12) << orders[i].status << '|'
		<< setw(14) << orders[i].orderType << '|'
		<< setw(7) << orders[i].price << " lv|"
		<< endl;
}
void displayAllDevices(ServiceOrder orders[], int countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}
		displayHeadInformation();

		for (int i = 0; i < countOfExistingOrders; i++)
		{
			displayCurrentOrder(orders, i);
		}
	
	

}
void lowerCharArray(char arr[], int size) {

	for (int i = 0; i < size; i++)
	{
		arr[i] = tolower(arr[i]);
	}
}
void searchAndDisplayByType(ServiceOrder orders[], int countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}

		char filterByTypeOfTech[TECH_TYPE_LENGTH];
		bool isExisting = false;
		bool isHeadInfoDisplayed = false;

		cout << "Enter type of technology: ";
		cin >> filterByTypeOfTech;
		lowerCharArray(filterByTypeOfTech, ORDER_TYPE_SIZE);


		for (int i = 0; i < countOfExistingOrders; i++)
		{

			if (strcmp(orders[i].typeOfTech, filterByTypeOfTech) == 0) {

				if (!isHeadInfoDisplayed) {
					cout << "\nThere are all orders from this type of technology (" << filterByTypeOfTech << "):" << endl;

					displayHeadInformation();
					isHeadInfoDisplayed = true;
				}
				displayCurrentOrder(orders, i);
				isExisting = true;
			}
		}
		if (!isExisting) {
			cout << "There aren't any orders from this type of technology!" << endl;
		}
	
	
}
void searchAndDisplayByStatus(ServiceOrder orders[], int countOfExistingOrders) {

	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}

	char filterByStatusOfTech[TECH_TYPE_LENGTH];
	bool isExisting = false;
	bool isHeadInfoDisplayed = false;

	do
	{
		cout << "Enter status of technology (accepted, declined, completed): ";
		cin.ignore();
		cin >> filterByStatusOfTech;
		lowerCharArray(filterByStatusOfTech, STATUS_SIZE);

		if (strcmp(filterByStatusOfTech, "declined") != 0
			&& (strcmp(filterByStatusOfTech, "accepted")) != 0 && (strcmp(filterByStatusOfTech, "completed")) != 0)
		{
			cout << "Invalid status of order has been entered." << endl;
		}

	} while (strcmp(filterByStatusOfTech, "declined") != 0
		&& (strcmp(filterByStatusOfTech, "accepted") != 0 && (strcmp(filterByStatusOfTech, "completed") != 0)));



	for (int i = 0; i < countOfExistingOrders; i++)
	{
		if (strcmp(orders[i].status, filterByStatusOfTech) == 0) {

			if (!isHeadInfoDisplayed) {
				cout << "There are all orders with this status of order (" << filterByStatusOfTech << "):" << endl;

				displayHeadInformation();
				isHeadInfoDisplayed = true;
			}
			displayCurrentOrder(orders, i);
			isExisting = true;
		}
	}
	if (!isExisting) {
		cout << "There aren't any orders with this status of order!" << endl;
	}


}

void sortOrdersByDatetime(ServiceOrder orders[], int countOfExistingOrders) {

	bool isSorted = false;
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}
	for (int i = 0; i < countOfExistingOrders; i++)
	{
		if (isSorted) {
			break;
		}
		else {
			isSorted = true;
		}
		for (int j = 0; j < countOfExistingOrders - 1; j++)
		{
			if (orders[j].dayOfMonth > orders[j + 1].dayOfMonth) {
				ServiceOrder tempOrder = orders[j];
				orders[j] = orders[j + 1];
				orders[j + 1] = tempOrder;
				isSorted = false;
			}
		}
	}
	cout << "Orders have been successfully sorted by date." << endl;
}

void sortOrdersByTechTypeDescending(ServiceOrder orders[], int countOfExistingOrders) {
	bool isSorted = false;

	for (int i = 0; i < countOfExistingOrders; i++)
	{
		if (isSorted) {
			break;
		}
		else {
			isSorted = true;
		}
		for (int j = 0; j < countOfExistingOrders - 1; j++)
		{
			if (orders[j].typeOfTech < orders[j + 1].typeOfTech) {
				ServiceOrder tempOrder = orders[j];
				orders[j] = orders[j + 1];
				orders[j + 1] = tempOrder;
				isSorted = false;
			}
		}
	}
}

void importFromTextFile(ServiceOrder orders[], int& countOfExistingOrders) {
	ifstream file;
	int count = 0;

	file.open("Orders.txt", ios::in);
	if (file.is_open()) {
		while (!file.eof()) {
			orders[count].number = countOfExistingOrders + 1;
			file >> orders[count].dayOfMonth;
			file.ignore();
			file.getline(orders[count].client, CLIENT_NAME_LENGTH);
			file.getline(orders[count].typeOfTech, TECH_TYPE_LENGTH);
			file.getline(orders[count].techSerialNumber, SERIAL_NUMBER_LENGTH);
			file.getline(orders[count].problem, PROBLEM_LENGTH);
			file.getline(orders[count].nameOfTechnician, TECHNICIAN_NAME_LENGTH);
			file.getline(orders[count].renovation, RENOVATION_LENGTH);
			file.clear();
			file >> orders[count].price;
			file.clear();
			file >> orders[count].daysInService;
			file.ignore();
			file.getline(orders[count].status, STATUS_SIZE);
			file.getline(orders[count].orderType, ORDER_TYPE_SIZE);
			count++;
			countOfExistingOrders++;



		}
		countOfExistingOrders--;
		cout << "Successfully imported from text file." << endl;
		file.close();
	}
	else {
		cout << "Text file couldn't open!" << endl;
	}
}

void exportToTextFile(ServiceOrder orders[], int& countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}
	ofstream file;
	file.open("Orders.txt", ios::out);
	if (file.is_open()) {
		for (int i = 0; i < countOfExistingOrders; i++)
		{
			file << orders[i].dayOfMonth << endl;
			file << orders[i].client << endl;
			file << orders[i].typeOfTech << endl;
			file << orders[i].techSerialNumber << endl;
			file << orders[i].problem << endl;
			file << orders[i].nameOfTechnician << endl;
			file << orders[i].renovation << endl;
			file << orders[i].price << endl;
			file << orders[i].daysInService << endl;
			file << orders[i].status << endl;
			file << orders[i].orderType << endl;
		}
		cout << "Successfully exported into text file." << endl;
	}
	else {
		cout << "Text file couldn't open." << endl;
	}
}
void importFromBinaryFile(ServiceOrder orders[], int& countOfExistingOrders) {
	ifstream file;
	long position = 0;
	int countOfElements = 0;

	file.open("Orders.bin", ios::binary | ios::in);
	if (file.is_open()) {
		file.seekg(0l, ios::end);
		position = (long)file.tellg();
		file.close();
	}
	else {
		cout << "File couldn't open!" << endl;
	}

	countOfElements = position / sizeof(ServiceOrder);

	file.open("Orders.bin", ios::binary | ios::in | ios::app);
	if (file.is_open()) {
		if (countOfElements <= MAX_ORDER_SIZE) {
			file.read((char*)orders, sizeof(ServiceOrder) * countOfElements);
		}
		else {
			file.read((char*)orders, sizeof(ServiceOrder) * MAX_ORDER_SIZE);
		}
		cout << "Successfully imported from binary file." << endl;
		countOfExistingOrders += countOfElements;
		file.close();
	}
	else {
		cout << "Binary file couldn't open!" << endl;
	}
}
void exportToBinaryFile(ServiceOrder orders[], int& countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}

	ofstream file;
	file.open("Orders.bin", ios::binary | ios::out);
	if (file.is_open()) {
		file.write((char*)orders, countOfExistingOrders * sizeof(ServiceOrder));
		cout << "Successfully exported into binary file." << endl;
		file.close();
	}
	else {
		cout << "Binary file couldn't open!" << endl;
	}
}


void filterOptions(ServiceOrder orders[], int countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}
	cout << "\n1.Filter completed orders by a technician" << endl;
	cout << "2.Filter orders by problem" << endl;
	int innerMenuChoice;
	do
	{
		cout << "Enter your choice: ";
		cin >> innerMenuChoice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input. Please enter a number." << endl;
		}
		else {
			break;
		}
	} while (innerMenuChoice != 1 && innerMenuChoice != 2);


	if (tolower(innerMenuChoice) == 1) {
		char technicianName[TECHNICIAN_NAME_LENGTH];
		cout << "Enter a name of technician: ";
		cin.ignore();
		cin.getline(technicianName, TECHNICIAN_NAME_LENGTH);

		printTechnicianSortedOrders(orders, countOfExistingOrders, technicianName);
	}
	else if (tolower(innerMenuChoice) == 2) {
		char problem[PROBLEM_LENGTH];

		cout << "Enter a problem of technology: ";
		cin.ignore();
		cin.getline(problem, PROBLEM_LENGTH);
		lowerCharArray(problem, PROBLEM_LENGTH);
		printOrdersWithGivenProblem(orders, countOfExistingOrders, problem);
	}
	else {
		cout << INVALID_CHOICE_ERROR << endl;
	}
}
void printTechnicianSortedOrders(ServiceOrder orders[], int countOfExistingOrders, char technicianName[]) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}

	bool isExisting = false;	
	bool isHeadInfoDisplayed = false;
	ServiceOrder ordersCopy[MAX_ORDER_SIZE];
	copyArr(orders, ordersCopy, countOfExistingOrders);
	

	for (int i = 0; i < countOfExistingOrders; i++)
	{
		if (strcmp(ordersCopy[i].nameOfTechnician, technicianName) == 0 && strcmp(ordersCopy[i].status, "completed") == 0) {

			if (!isHeadInfoDisplayed) {
				sortOrdersByDatetime(ordersCopy, countOfExistingOrders);
				cout << "\nThere are all orders completed by " << technicianName << ":" << endl;
				cout << endl;
				displayHeadInformation();
				isHeadInfoDisplayed = true;
			}
			displayCurrentOrder(ordersCopy, i);
			isExisting = true;
		}
	}
	if (!isExisting) {
		cout << "There aren't any orders completed by this technician!" << endl;
	}
}
void printOrdersWithGivenProblem(ServiceOrder orders[], int countOfExistingOrders, char problem[]) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}
	bool isExisting = false;
	bool isHeadInfoDisplayed = false;

	sortOrdersByTechTypeDescending(orders, countOfExistingOrders);


	for (int i = 0; i < countOfExistingOrders; i++)
	{
		if (strcmp(orders[i].problem, problem) == 0) {

			if (!isHeadInfoDisplayed) {
				cout << "\nThere are all orders that have problem (" << problem << "):" << endl << endl;

				displayHeadInformation();
				isHeadInfoDisplayed = true;
			}
			displayCurrentOrder(orders, i);
			isExisting = true;
		}
	}
	if (!isExisting) {
		cout << "There aren't any orders with this problem!" << endl;
	}
}
void configureOptions(ServiceOrder orders[], int countOfExistingOrders) {
	cout << "\n1.Add type of order" << endl;
	cout << "2.Insert/Update order's data" << endl;
	cout << "3.Change status of order" << endl;

	int innerMenuChoice;
	cin >> innerMenuChoice;
	if (tolower(innerMenuChoice) == 1) {
		addOrderType(orders, countOfExistingOrders);

	}
	else if (tolower(innerMenuChoice) == 2) {
		insertUpdateData(orders, countOfExistingOrders);
	}
	else if (tolower(innerMenuChoice) == 3) {
		changeStatusOfOrder(orders, countOfExistingOrders);
	}
	else {
		cout << INVALID_CHOICE_ERROR << endl;
	}
}

void addOrderType(ServiceOrder orders[], int countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}

	int numberOfOrder;	
	do
	{
		cout << "Enter number of order to modify: ";
		cin >> numberOfOrder;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input. Please enter a number." << endl;
		}

		else if (numberOfOrder < 1 || numberOfOrder > 100) {
			cout << "Order number should be in range (1-100)!" << endl;

		}
		else if (numberOfOrder > countOfExistingOrders) {
			cout << "Number of order doesn't exists!" << endl;

		}
		else {
			break;
		}


	} while (numberOfOrder < 1 || numberOfOrder > 100 || numberOfOrder > countOfExistingOrders);

	if (strcmp(orders[numberOfOrder - 1].orderType, "empty") == 0) {
		do
		{
			cout << "\nChoose type of order between normal, fast and express: ";
			cin.ignore();
			cin >> orders[numberOfOrder - 1].orderType;
			lowerCharArray(orders[numberOfOrder - 1].orderType, ORDER_TYPE_SIZE);
			if (strcmp(orders[numberOfOrder - 1].orderType, "normal") != 0 &&
				strcmp(orders[numberOfOrder - 1].orderType, "fast") != 0 &&
				strcmp(orders[numberOfOrder - 1].orderType, "express") != 0) {
				cout << INVALID_CHOICE_ERROR;
			}
		} while (strcmp(orders[numberOfOrder - 1].orderType, "normal") != 0 &&
			strcmp(orders[numberOfOrder - 1].orderType, "fast") != 0 &&
			strcmp(orders[numberOfOrder - 1].orderType, "express") != 0);

		if (strcmp(orders[numberOfOrder - 1].orderType, "normal") == 0) {
			orders[numberOfOrder - 1].daysInService = 10;
		}
		else if (strcmp(orders[numberOfOrder - 1].orderType, "fast") == 0) {
			orders[numberOfOrder - 1].daysInService = 5;
		}
		else {
			orders[numberOfOrder - 1].daysInService = 2;
		}
		cout << "Type has been successfully modified." << endl;
	}
	else {
		cout << "This order already has type." << endl;

	}

}

void insertUpdateData(ServiceOrder orders[], int countOfExistingOrders) {

	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}
	int numberOfOrder, indexOfProblem;
	do
	{
		cout << "Enter number of order to modify: ";
		cin >> numberOfOrder;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input. Please enter a number." << endl;
		}
		else if (numberOfOrder < 1 || numberOfOrder > 100) {
			cout << "Order number should be in range (1-100)!" << endl;
		}
		else if (numberOfOrder > countOfExistingOrders) {
			cout << "Number of order doesn't exists" << endl;
		}
		else {
			break;
		}

	} while (numberOfOrder < 1 || numberOfOrder > 100 || numberOfOrder > countOfExistingOrders);

	if (strcmp(orders[numberOfOrder - 1].orderType, "empty") == 0) {
		cout << "The order does not have type! Please enter type of order before you enter more details!" << endl;
		return;
	}
	if (strcmp(orders[numberOfOrder - 1].status, "accepted") == 0) {

		cout << "Enter technician name: ";
		cin.ignore();
		cin.getline(orders[numberOfOrder - 1].nameOfTechnician, TECHNICIAN_NAME_LENGTH);

		for (int i = 0; i < 10; i++)
		{
			if (strcmp(orders[numberOfOrder - 1].problem, PROBLEMS[i]) == 0) {
				indexOfProblem = i;
				break;
			}
		}
		strcpy_s(orders[numberOfOrder - 1].renovation, RENOVATIONS[indexOfProblem]);

		if (strcmp(orders[numberOfOrder - 1].orderType, "normal") == 0) {
			orders[numberOfOrder - 1].price = (indexOfProblem + 1) * 10;
		}
		else if (strcmp(orders[numberOfOrder - 1].orderType, "fast") == 0) {
			double price = (indexOfProblem + 1) * 10;
			orders[numberOfOrder - 1].price = price * 1.2;
		}
		else if (strcmp(orders[numberOfOrder - 1].orderType, "express") == 0) {
			double price = (indexOfProblem + 1) * 10;
			orders[numberOfOrder - 1].price = price * 1.5;
		}
		else {
			cout << "Order has invalid type!" << endl;
		}


		if (strcmp(orders[numberOfOrder - 1].orderType, "normal") == 0) {
			orders[numberOfOrder - 1].daysInService = 10;
		}
		else if (strcmp(orders[numberOfOrder - 1].orderType, "fast") == 0) {
			orders[numberOfOrder - 1].daysInService = 5;
		}
		else if (strcmp(orders[numberOfOrder - 1].orderType, "express") == 0) {
			orders[numberOfOrder - 1].daysInService = 2;
		}
		else {
			cout << "Order has invalid type!" << endl;
		}


		cout << "Order's additional data has been successfully added." << endl;
	}
	else {
		cout << "Declined or completed order cannot be modified!" << endl;
	}
}

void changeStatusOfOrder(ServiceOrder orders[], int countOfExistingOrders) {
	if (countOfExistingOrders <= 0) {
		cout << "There aren't any orders. Please enter orders!" << endl;
		return;
	}

	int numberOfOrder;
	do
	{
		cout << "Enter number of order to modify: ";
		cin >> numberOfOrder;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input. Please enter a number." << endl;
		}


		else if (numberOfOrder < 1 || numberOfOrder > 100) {
			cout << "Order number should be in range (1-100)!" << endl;
		}
		else if (numberOfOrder > countOfExistingOrders) {
			cout << "Number of order doesn't exists" << endl;
		}
		else {
			break;
		}

	} while (numberOfOrder < 1 || numberOfOrder > 100 || numberOfOrder > countOfExistingOrders);

	if (strcmp(orders[numberOfOrder - 1].status, "accepted") == 0 && strcmp(orders[numberOfOrder - 1].nameOfTechnician, "empty") != 0) {
		do
		{
			cout << "Enter status of order (accepted, declined, completed): ";
			cin.ignore();
			cin.getline(orders[numberOfOrder - 1].status, STATUS_SIZE);

			if (strcmp(orders[numberOfOrder - 1].status, "declined") != 0
				&& (strcmp(orders[numberOfOrder - 1].status, "accepted")) != 0 && (strcmp(orders[numberOfOrder - 1].status, "completed")) != 0)
			{
				cout << "Invalid status of order has been entered." << endl;
			}

		} while (strcmp(orders[numberOfOrder - 1].status, "declined") != 0
			&& (strcmp(orders[numberOfOrder - 1].status, "accepted") != 0 && (strcmp(orders[numberOfOrder - 1].status, "completed") != 0)));

		cout << "Status has been successfully changed." << endl;
	}
	else {
		cout << "Declined or completed order cannot be modified! Order without technician cannot be modified too!" << endl;

	}

}
void copyArr(ServiceOrder orders[], ServiceOrder ordersCopy[], int countOfExistingOrders) {
	for (int i = 0; i < countOfExistingOrders; i++)
	{
		ordersCopy[i] = orders[i];
	}
}

