#include <iostream>
#include <string>
#include <chrono>
#include <list>
#include <algorithm>

using namespace std;

const int MAX_FLIGHTS = 10;

struct Flight {
	int flightNumber;
	string destination;
	string pilotName;
	double firstClassTicketPrice;
	double secondClassTicketPrice;
	int flightDay;
	list<string> passangerList;
};

int mainMenu();
void addFlightMenu(Flight* flights);
Flight createFlight();
void addFlight(Flight* flights, Flight newFlight);
void addListOfFlights(Flight* flights);
void printMenu(Flight* flights);
void printFlight(Flight flight);
void printAllFlight(Flight* flights);
void printLowestFirstClassPriceFlight(Flight* flights);
void printFlightByPilot(Flight* flights);
void buyTicket(Flight* flights);

void cancelTicket(Flight* flights);
//bool isValidVacation(Flight flight);

//int extractDayFromDate(string date);


int main()
{
	Flight flight1{ 10011 ,"Bulgaria", "Pilot One", 100, 80,  1 };
	Flight flight2{ 10012 ,"Madagascar", "Pilot Two", 120, 90,  6 };
	Flight flight3{ 10013 ,"Canada", "Pilot Three", 200, 150, 11 };
	Flight flight4{ 10014 ,"Japan", "Pilot Four", 140, 130, 14 };

	Flight flights[MAX_FLIGHTS];
	flights[0] = flight1;
	flights[1] = flight2;
	flights[2] = flight3;
	flights[3] = flight4;

	int option;
	while ((option = mainMenu()) != 0) {
		if (option == 1) {
			addFlightMenu(flights);
			continue;
		}
		if (option == 2)
		{
			printMenu(flights);
			continue;
		}
		if (option == 3)
		{
			buyTicket(flights);
		}
		if (option == 4) {
			cancelTicket(flights);
		}
		if (option == 0)
		{
			break;
		}
	}
}

int mainMenu() {
	cout << "-------Main menu--------" << endl
		<< "1 - Add flight" << endl
		<< "2 - Print flight" << endl
		<< "3 - Buy Ticket" << endl
		<< "4 - Cancel Ticket" << endl
		<< "0 - Exit" << endl;

	int option;
	cin >> option;
	return option;
}

void addFlightMenu(Flight* flights) {
	cout << "-----New flight menu------" << endl
		<< "1 - Add new flight" << endl
		<< "2 - Add list of flights" << endl
		<< "0 - Back to main menu" << endl;

	int option;
	cin >> option;

	if (option == 1) {
		Flight newFlight = createFlight();
		addFlight(flights, newFlight);
		cout << "New flight was successfully added" << endl;
		return;
	}
	if (option == 2)
	{
		addListOfFlights(flights);
		return;
	}
	if (option == 0)
	{
		return;
	}

	cout << "Invalid option!" << endl;
	addFlightMenu(flights);

}

Flight createFlight() {

	cout << "Enter Flight Number: ";
	cin.ignore(256, '\n');
	int flightNumber;
	cin >> flightNumber;

	cout << "Enter Destination: ";
	cin.ignore(256, '\n');
	string destination;
	getline(cin, destination);

	cout << "Enter Pilot Name: ";
	string pilotName;
	getline(cin, pilotName);

	cout << "Enter first class ticket price: ";
	double firstClassTicketPrice;
	cin >> firstClassTicketPrice;

	cout << "Enter second class ticket price: ";
	double secondClassTicketPrice;
	cin >> secondClassTicketPrice;

	cout << "Enter flight date: ";
	int flightDay;
	cin >> flightDay;

	Flight flight{ flightNumber, destination, pilotName, firstClassTicketPrice, secondClassTicketPrice, flightDay };
	return flight;
}

void addFlight(Flight* flights, Flight newFlight) {
	for (int i = 0; i < MAX_FLIGHTS; i++) {
		if (flights[i].destination.empty()) {
			flights[i] = newFlight;
			return;
		}
	}
}

void addListOfFlights(Flight* flights) {
	cout << "Enter count of the flights that you want to add: ";
	int n;
	cin >> n;

	if (n < 0) {
		cout << "Entered value must be a postive number!" << endl;
		addListOfFlights(flights);
		return;
	}

	for (int i = 0; i < n; i++)
	{
		cout << "Enter new flight " << i + 1 << endl << endl;
		Flight newFlight = createFlight();
		addFlight(flights, newFlight);
		cout << endl;
	}
}

void printMenu(Flight* flights) {
	cout << "---Print menu----" << endl
		<< "1 - Print all flights" << endl
		<< "2 - Print flight with lowest price for first class" << endl
		<< "3 - Print all flights for a pilot" << endl
		<< "0 - Back to main menu" << endl;
	int option;
	cin >> option;

	if (option == 1) {
		printAllFlight(flights);
		return;
	}
	if (option == 2) {
		printLowestFirstClassPriceFlight(flights);
		return;
	}
	if (option == 3) {
		printFlightByPilot(flights);
		return;
	}
	if (option == 0) {
		return;
	}

	cout << "Invalid option!" << endl;
	printMenu(flights);
}

void printFlight(Flight flight) {
	cout << "Flight number: " << flight.flightNumber << endl
		<< "Vacation destination: " << flight.destination << endl
		<< "Pilot Name: " << flight.pilotName << endl
		<< "First class ticket price:" << flight.firstClassTicketPrice << endl
		<< "Second class ticket price: " << flight.secondClassTicketPrice << endl
		<< "Take off date: " << flight.flightDay << endl;
}

void printAllFlight(Flight* flights) {

	cout << "Printing all flights!" << endl;

	for (int i = 0; i < MAX_FLIGHTS; i++) {
		if (!flights[i].destination.empty()) {
			cout << endl;
			printFlight(flights[i]);
			cout << endl;
		}
	}
}

void printLowestFirstClassPriceFlight(Flight* flights) {

	int lowestFirstClassPrice = 1000000;
	for (int i = 0; i < MAX_FLIGHTS; i++)
	{
		Flight currentFlight = flights[i];
		if (currentFlight.destination.empty()) {
			continue;
		}

		if (currentFlight.firstClassTicketPrice < lowestFirstClassPrice) {
			lowestFirstClassPrice = currentFlight.firstClassTicketPrice;
		}
	}

	cout << "Printing lowest first class price flight." << endl;

	for (int i = 0; i < MAX_FLIGHTS; i++) {
		Flight currentFlight = flights[i];
		if (currentFlight.destination.empty()) {
			continue;
		}

		if (currentFlight.firstClassTicketPrice == lowestFirstClassPrice) {
			cout << endl;
			printFlight(currentFlight);
			cout << endl;
		}
	}
}

void printFlightByPilot(Flight* flights) {
	cout << "Enter pilot: ";
	cin.ignore(256, '\n');
	string pilotName;
	getline(cin, pilotName);

	cout << "Printing current pilot's flights: " << pilotName << endl << endl;

	for (int i = 0; i < MAX_FLIGHTS; i++)
	{
		Flight currentFlight = flights[i];
		if (currentFlight.destination.empty()) {
			continue;
		}

		if (currentFlight.pilotName == pilotName) {
			cout << endl;
			printFlight(currentFlight);
			cout << endl;
		}
	}
}



void buyTicket(Flight* flights) {
	cout << "Enter destiantion you wish to travel to: ";
	string ticketDestiantion;
	cin.ignore(256, '\n');
	getline(cin, ticketDestiantion);
	cout << "Enter date you wish to travel on: ";
	int ticketDate;
	cin >> ticketDate;

	for (int i = 0; i < MAX_FLIGHTS; i++)
	{
		Flight currentFlight = flights[i];
		if (currentFlight.destination.empty()) {
			continue;
		}

		if (currentFlight.destination == ticketDestiantion && currentFlight.flightDay == ticketDate)
		{
			int currentDay;
			cout << "Please enter current day of the month." << endl;
			cin >> currentDay;
			int calculatedDays = currentDay - currentFlight.flightDay;
			if (calculatedDays < 1)
			{
				currentFlight.firstClassTicketPrice = currentFlight.firstClassTicketPrice * 1.2;
			}
			else if (calculatedDays < 5)
			{
				currentFlight.firstClassTicketPrice = currentFlight.firstClassTicketPrice;
			}
			else if (calculatedDays < 20)
			{
				currentFlight.firstClassTicketPrice = currentFlight.firstClassTicketPrice * 0.75;
			}
			else if (calculatedDays > 20)
			{
				currentFlight.firstClassTicketPrice = currentFlight.firstClassTicketPrice * 0.5;
			}
			cout << "Flight number: " << currentFlight.flightNumber << endl
				<< "First class ticket price:" << currentFlight.firstClassTicketPrice << endl
				<< "Second class ticket price: " << currentFlight.secondClassTicketPrice << endl << endl;


			cout << "Please confirm your purchase. Y/N" << endl;

			string answer;
			cin.ignore(256, '\n');
			getline(cin, answer);

			if (answer == "Y")
			{
				cout << "Please enter your Name." << endl;
				cin.ignore(256, '\n');
				string passangerName;
				getline(cin, passangerName);	
				currentFlight.passangerList.push_back(passangerName);
				
				cout << "Ticket receipt will be sent to you by email, thank you for using Flight Manager!" << endl;
				
				return;
			}
			else
			{
				cout << "Returning to previous menu." << endl;
				return;
			}
		}
		else
		{
			cout << "We do not have flight that meets your destiantion or date." << endl;
			return;
		}
	}
}
void cancelTicket(Flight* flights)
{
	int cancelFlightNumber;

	cout << "Please enter your flight number." << endl;
	cin >> cancelFlightNumber;
	cout << "Please enter your name." << endl;
	cin.ignore(256, '\n');
	string cancelName;
	getline(cin, cancelName);

	for (int i = 0; i < MAX_FLIGHTS; i++)
	{
		Flight currentFlight = flights[i];
		if (currentFlight.destination.empty()) {
			continue;
		}
		if (currentFlight.flightNumber == cancelFlightNumber)
		{
			bool found = (find(currentFlight.passangerList.begin(), currentFlight.passangerList.end(), cancelName) != currentFlight.passangerList.end());
			if (found == true)
			{
				cout << "works" << endl;
			}

			else
			{
				cout << "There is no such name on this flight." << endl;
				return;
			}
		}
	}
}



