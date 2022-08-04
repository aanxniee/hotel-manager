/* Annie Cai
	 ICS4U1-4A Dr. Noukhovitch
   Monday, May 9, 2022 
	 
	C++ Final Project
		The Hotel Manager
*/ 

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// classes ------------------------------------------------------------------
// super class
class Hotel {
	protected:
		// class attributes
		// each hotel booking will require a floor, unit number, name and phone number
		int floor;
		int unit_number;
		string name;
		string phone_number;

	public:
		// class constructors for initialization
		Hotel();
		Hotel(int floor, int unit_number, string name, string phone_number);

		// class methods, virtual --> overriden by its subclasses
		virtual void print();
		virtual int getUnitNumber() { return unit_number; };
		virtual void modifyName(string name) { this->name = name; };
		virtual void modifyPhoneNumber(string phone_number) { this->phone_number = phone_number; };

		// class destructor to free up memory
		~Hotel() {};
};

// constructor which initializes all atrributes as blank --> creates object template
Hotel::Hotel() {
	this->floor = 0;
	this->unit_number = 0; 
	this->name = ""; 
	this->phone_number = "";
}

// constructor which sets the values of the attributes
Hotel::Hotel(int floor, int unit_number, string name, string phone_number) {
	this->floor = floor;
	this->unit_number = unit_number;
	this->name = name;
	this->phone_number = phone_number;
}

// method which prints the status of the booking
void Hotel::print() {
	cout << "Floor: " << floor << endl;
	cout << "Unit Number: " << unit_number << endl;
	cout << "Occupant Name: " << name << endl;
	cout << "Phone Number: " << phone_number << endl;
}

// subclass of the super class Hotel
class Chelsea: public Hotel {
	public:
		// inherit constructors from the super class, used for initialization upon object creation
		Chelsea() : Hotel() { }
 		Chelsea(int floor, int unit_number, string name, string phone_number) : Hotel(floor, unit_number, name, phone_number) { }

		// class methods, override original method from the superclass --> polymorphism
		void print() {
			cout << "CHELSEA HOTEL" << endl;
			cout << "Floor: " << floor << endl;
			cout << "Unit Number: " << unit_number << endl;
			cout << "   Occupant Name: " << name << endl;
			cout << "   Phone Number: " << phone_number << endl;
		}
		int getUnitNumber() { return unit_number; };
		void modifyName(string name) { this->name = name; };
		void modifyPhoneNumber(string phone_number) { this->phone_number = phone_number; };

		// class destructor to free up memory
		~Chelsea() {}
};

// subclass of the super class Hotel
class Fairmont: public Hotel {
	public:
		// inherit constructors from the super class, used for initialization upon object creation
		Fairmont() : Hotel() { }
 		Fairmont(int floor, int unit_number, string name, string phone_number) : Hotel(floor, unit_number, name, phone_number) { }
		
		// class methods, override original method from the superclass --> polymorphism
		void print() {
			cout << "FAIRMONT HOTEL" << endl;
			cout << "Floor: " << floor << endl;
			cout << "Unit Number: " << unit_number << endl;
			cout << "   Occupant Name: " << name << endl;
			cout << "   Phone Number: " << phone_number << endl;
		}
		int getUnitNumber() { return unit_number; };
		void modifyName(string name) { this->name = name; };
		void modifyPhoneNumber(string phone_number) { this->phone_number = phone_number; };

		// class destructor to free up memory
		~Fairmont() {}	
};


// function declarations ---------------------------------------------------
void printLogo();
void printMenu();
void printEnd();
void printCommand(int command);
void printHotels();
void printModificationMenu();
bool checkHotel(int hotel);
bool checkFloor(int floor);
bool checkUnitNumber(int unit_number);
bool checkPhoneNumber(string phone_number);
bool isDigit(string s);
int search(int unit_number, Hotel occupants[], int count);
void list(Hotel bookings[], int count);


// main code --------------------------------------------------------------
int main() {

	// display a welcome message and the menu
  printLogo();
	printMenu();

	// initialize program variables
	int count_one, count_two = 0; // used to track objects in the array
	int hotel, floor, unit_number, index; 
	string command, modify, name, first_name, last_name, phone_number;

	// create two array of objects to store bookings
	Chelsea chelsea_hotel[10000];
	Fairmont fairmont_hotel[10000];

	// ask the user to enter a command
	cout << "Please select a command (1-5): ";
	cin >> command;

	// while loop that will continually run the program until the user chooses to exist
	while (command != "5") {

		// display error message if the user enters an invalid command
		if (command != "1" && command != "2" && command != "3" && command != "4") {
			cout << endl;
			cout << ">>> ERROR 1: Invalid command." << endl << endl;
		}

		// try block, ensures that user inputs are valid
		try {
			/* -------------------------------------------------------------
                                 ADD A BOOKING
				  if the user selects 1, perform the "add a booking" function
				-------------------------------------------------------------- */
			if (command == "1") {
				printCommand(1);

				// ask the user which hotel they would like to book at (chelsea or fairmont)
				printHotels();
				cin >> hotel;

				// invalid hotel = throw an exception --> error detected
				if (checkHotel(hotel) == false) {
					throw ">>> ERROR 2: Invalid hotel.";
				}

				// ask the user which floor they would like to book
				cout << "Floor: ";
				cin >> floor;
				
				// invalid floor = throw an exception --> error detected
				if (checkFloor(floor) == false) {
					throw ">>> ERROR 3: Invalid floor.";
				}

				// ask the user which room they would like to book
				cout << "Unit Number: ";
				cin >> unit_number;

				// invalid room number = throw an exception --> error detected
				if (checkUnitNumber(unit_number) == false) {
					throw ">>> ERROR 4: Invalid unit number.";
				}

				// ask the user for their full name, convert to uppercase for readability
				cout << "Occupant Name: ";
				cin >> first_name >> last_name;
				name = first_name + " " + last_name;
				transform(name.begin(), name.end(),name.begin(), ::toupper);

				// ask the user for their contact information
				cout << "Phone Number: ";
				cin >> phone_number;

				// invalid phone number = throw an exception --> error detected
				if (checkPhoneNumber(phone_number) == false) {
					throw ">>> ERROR 5: Invalid phone number.";
				}
				phone_number.insert(3, "-");
				phone_number.insert(7, "-");

				// create an object of class chelsea
				if (hotel == 1) {
					// pass the user's inputs into the constructor to create the object
					Chelsea occupant(floor, unit_number, name, phone_number); 
					Chelsea *ptr = &occupant; // pointer to the object

					// add the object to its corresponding array and increment the count
					chelsea_hotel[count_one] = occupant;
					count_one++;
				}

				// create an object of class fairmont
				else if (hotel == 2) {
					// pass the user's inputs into the constructor to create the object
					Fairmont occupant(floor, unit_number, name, phone_number);
					Fairmont *ptr = &occupant; // pointer to the object

					// add the object to its corresponding array and increment the count
					fairmont_hotel[count_two] = occupant;
					count_two++;
				}

				// display success message
				cout << endl;
				cout << " > Booking has successfully been added." << endl << endl;
			}

			/* -------------------------------------------------------------
                               LIST ALL BOOKINGS
			  if the user selects 2, perform the "list all bookings" function
				-------------------------------------------------------------- */
			else if (command == "2") {
				printCommand(2);

				// if there are no objects in the arrays (no bookings to be listed), display message
				if (count_one == 0 && count_two == 0) {
					cout << " > There are no bookings at the time." << endl << endl;
				}
					
				else {
					// call the list function for both hotels
					list(chelsea_hotel, count_one);
					list(fairmont_hotel, count_two);
				}
			}

			/* -------------------------------------------------------------
                               MODIFY A BOOKING
			 if the user selects 3, perform the "modify a booking" function
				-------------------------------------------------------------- */
			else if (command == "3") {
				printCommand(3);

				// if there are no objects in the arrays (no bookings to be modified), display message
				if (count_one == 0 && count_two == 0) {
					cout << " > There are no bookings at the time." << endl << endl;
				}
				
				else {
					// ask the user which hotel booking they would like to modify (chelsea or fairmont)
					printHotels();
					cin >> hotel;

					// invalid hotel = throw an exception --> error detected
					if (checkHotel(hotel) == false) {
						throw ">>> ERROR 2: Invalid hotel.";
					}
					
					if (hotel == 1) {
						// if there are no bookings at the hotel specified, display error message
						if (count_one == 0) {
							cout << " > There are no bookings at the time." << endl << endl;
						}
						
						else {
							// ask the user which room at their specified hotel they would like to modify
							cout << "Enter the unit number at Chelsea Hotel to be modified: ";
							cin >> unit_number;
	
							// invalid room number = throw an exception --> error detected
							if (checkUnitNumber(unit_number) == false) {
									throw ">>> ERROR 4: Invalid unit number.";
							}
						
	
							// find the index of bject (booking) the user is trying to modify (used to access the object)
							index = search(unit_number, chelsea_hotel, count_one);
	
							// if the object exists (can be found in booking), display the booking information to the user
							if (index != -1) {
								cout << endl;
								chelsea_hotel[index].print();
								cout << endl; 
							}
	
							// cannot be found = throw an exception --> error detected
							else {
								throw ">>> ERROR 6: Booking not found.";		
							}
	
							// ask the user what they would like to modify
							printModificationMenu();
							cout << "Select a modification: ";
							cin >> modify;
	
							// display error message if the user enters an invalid command
							if (modify != "1" && modify != "2") {
								cout << endl;
								cout << ">>> ERROR 1: Invalid command." << endl << endl;
							}
							
							if (modify == "1") {
								// allow the user to modify their name --> ask them to enter a new name
								cout << "Enter a new name: ";
								cin >> first_name >> last_name;
								name = first_name + " " + last_name;
								transform(name.begin(), name.end(),name.begin(), ::toupper);
	
								// call the modifyName method on the specific object (booking) --> updates the name attribute
								chelsea_hotel[index].modifyName(name);
								cout << endl;
	
								// display success message
								cout << " > Name has successfully been modified." << endl << endl;
							}
								
	
							else if (modify == "2") {
								// allow the user to modify their contact method --> ask them to enter a new phone number
								cout << "Enter a new phone number: ";
								cin >> phone_number;
	
								// invalid phone number = throw an exception --> error detected
								if (checkPhoneNumber(phone_number) == false) {
									throw ">>> ERROR 5: Invalid phone number.";
								}
								phone_number.insert(3, "-");
								phone_number.insert(7, "-");
	
								// call the modifyPhoneNumber method on the specific object (booking) --> updates the phone number attribute
								chelsea_hotel[index].modifyPhoneNumber(phone_number);
								cout << endl;
	
								// display success message
								cout << " > Phone number has successfully been modified." << endl << endl;
							}
						}
					}
	
					else if (hotel == 2) {
						// if there are no bookings at the hotel specified, display error message
						if (count_two == 0) {
							cout << " > There are no bookings at the time." << endl << endl;
						}
						
						else {
							// ask the user which room at their specified hotel they would like to modify
							cout << "Enter the unit number at Fairmont Hotel to be modified: ";
							cin >> unit_number;
	
							// invalid hotel = throw an exception --> error detected
							if (checkUnitNumber(unit_number) == false) {
								throw ">>> ERROR 4: Invalid unit number.";
							}
							
							// find the index of bject (booking) the user is trying to modify (used to access the object)
							index = search(unit_number, fairmont_hotel, count_two);
	
							// if the object exists (can be found in booking), display the booking information to the user
							if (index != -1) {
								cout << endl;
								fairmont_hotel[index].print();
								cout << endl; 
							}
	
							// cannot be found = throw an exception --> error detected
							else {
								throw ">>> ERROR 6: Booking not found.";		
							}
	
							// ask the user what they would like to modify
							printModificationMenu();
							cout << "Select a modification: ";
							cin >> modify;
	
							// display error message if the user enters an invalid command
							if (modify != "1" && modify != "2") {
								cout << endl;
								cout << ">>> ERROR 1: Invalid command." << endl << endl;
							}
							
							if (modify == "1") {
								// allow the user to modify their name --> ask them to enter a new name
								cout << "Enter a new name: ";
								cin >> first_name >> last_name;
								name = first_name + " " + last_name;
								transform(name.begin(), name.end(),name.begin(), ::toupper);
	
								// call the modifyName method on the specific object (booking) --> updates the name attribute
								fairmont_hotel[index].modifyName(name);
								cout << endl;
	
								// display success message
								cout << " > Name has successfully been modified." << endl << endl;
							}
		
							else if (modify == "2") {
								// allow the user to modify their contact method --> ask them to enter a new phone number
								cout << "Enter a new phone number: ";
								cin >> phone_number;
	
								// invalid phone number = throw an exception --> error detected
								if (checkPhoneNumber(phone_number) == false) {
									throw ">>> ERROR 5: Invalid phone number.";
								}
								phone_number.insert(3, "-");
								phone_number.insert(7, "-");
	
								// call the modifyPhoneNumber method on the specific object (booking) --> updates the phone number attribute
								fairmont_hotel[index].modifyPhoneNumber(phone_number);
								cout << endl;
	
								// display success message
								cout << " > Phone number has successfully been modified." << endl << endl;
							}
						}
					}		
				}
			}

			/* -------------------------------------------------------------
                               DELETE A BOOKING
			  if the user selects 4, perform the "delete a booking" function
				-------------------------------------------------------------- */
			else if (command == "4") {
				printCommand(4);
				// if there are no objects in the arrays (no bookings to be modified), display message
				if (count_one == 0 && count_two == 0) {
					cout << " > There are no bookings at the time." << endl << endl;
				}
					
				else {
					// ask the user which hotel booking they would like to delete (chelsea or fairmont)
					printHotels();
					cin >> hotel;

					// invalid hotel = throw an exception --> error detected
					if (checkHotel(hotel) == false) {
						throw ">>> ERROR 2: Invalid hotel.";
					}
						
					if (hotel == 1) {
						// if there are no bookings at the hotel specified, display error message
						if (count_one == 0) {
							cout << " > There are no bookings at the time." << endl << endl;
						}
						
						else {
							// ask the user which room at their specified hotel they would like to modify
							cout << "Enter the unit number at Chelsea Hotel to be deleted: ";
							cin >> unit_number;

							// invalid room number = throw an exception --> error detected
							if (checkUnitNumber(unit_number) == false) {
								throw ">>> ERROR 4: Invalid unit number.";
							}

							// find the index of bject (booking) the user is trying to modify (used to access the object)
							index = search(unit_number, chelsea_hotel, count_one);

							// if the object exists (can be found), delete it by shifting everything after the object to the left
							// ie. [obj1, obj2, obj3, obj4] and you want to delete obj2 --> [obj1, obj3, obj4]
							if (index != -1) {
								for (int i = index; i < count_one - 1; i++) {
									chelsea_hotel[i] = chelsea_hotel[i+1];
								}	
								count_one--; // decrement the count
								cout << endl;

								// display success message
								cout << " > Booking has successfully been deleted." << endl << endl;
							}
								
							else {
								throw ">>> ERROR 6: Booking not found.";
							}
						}
					}
		
					else if (hotel == 2) {
						// if there are no bookings at the hotel specified, display error message
						if (count_two == 0) {
							cout << " > There are no bookings at the time." << endl << endl;
						}
						
						else {
							// ask the user which room at their specified hotel they would like to modify
							cout << "Enter the unit number at Fairmont Hotel to be deleted: ";
							cin >> unit_number;

							// invalid room number = throw an exception --> error detected
							if (checkUnitNumber(unit_number) == false) {
								throw ">>> ERROR 4: Invalid unit number.";
							}

							// find the index of bject (booking) the user is trying to modify (used to access the object)
							index = search(unit_number, fairmont_hotel, count_two);

							// if the object exists (can be found), delete it by shifting everything after the object to the left
							// ie. [obj1, obj2, obj3, obj4] and you want to delete obj2 --> [obj1, obj3, obj4]
							if (index != -1) {
								for (int i = index; i < count_two - 1; i++) {
									fairmont_hotel[i] = fairmont_hotel[i+1];
								}
								count_two--; // decrement the count
								cout << endl;

								// display success message
								cout << " > Booking has successfully been deleted." << endl << endl;
							}

							// cannot be found = throw an exception --> error detected
							else {
								throw ">>> ERROR 6: Booking not found.";
							}
						}
					}
				}
			}

			// display the menu after performing the specifed function and ask the user to select a new command
			// reset the while loop
			printMenu();
			cout << "Please select a command (1-5): ";
			cin >> command;
		}
		// catch block, handles the exceptions throw --> display the error message
		catch (const char* msg) {
			cout << endl;
			cout << msg << endl;
		}
	}

	// display thank you message
	printEnd();
	return 0;
}


// functions ------------------------------------------------------------------
// function that prints the logo
void printLogo() {
	cout << "---------------------------------------------------------" << endl;
	cout << "              WELCOME TO THE HOTEL MANAGER               " << endl;
	cout << "---------------------------------------------------------" << endl;
}

// function that prints the menu
void printMenu() {
	cout << "---------------------------------------------------------" << endl;
	cout << "                          MENU                           " << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "                   1. Add a booking" << endl;
	cout << "                   2. List all bookings" << endl;
	cout << "                   3. Modify a booking" << endl;
	cout << "                   4. Delete a booking" << endl;
	cout << "                   5. Exit" << endl << endl;
}

// function that prints the command that is selected
void printCommand(int command) {
	// switch block to display the correpsonding command
	switch(command) {
		case 1:
			cout << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "                     ADD A BOOKING                       " << endl;
			cout << "---------------------------------------------------------" << endl;
			break;

		case 2:
			cout << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "                    LIST ALL BOOKINGS                    " << endl;
			cout << "---------------------------------------------------------" << endl;
			break;

		case 3:
			cout << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "                     MODIFY A BOOKING                    " << endl;
			cout << "---------------------------------------------------------" << endl;
			break;

		case 4:
			cout << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "                     DELETE A BOOKING                    " << endl;
			cout << "---------------------------------------------------------" << endl;
			break;
	}
}

// function that displays the two hotel options
void printHotels() {
	cout << "1. Chelsea Hotel " << endl;
	cout << "2. Fairmont Hotel " << endl << endl;
	cout << "Select a hotel (1 or 2): ";
}

// function that displays a thank you message
void printEnd() {
	cout << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "          THANK YOU FOR USING THE HOTEL MANAGER          " << endl;
	cout << "---------------------------------------------------------" << endl;
}

// function that prints the modification menu
void printModificationMenu() {
	cout << "Modification Options" << endl;
	cout << "   1. Name" << endl;
	cout << "   2. Phone Number" << endl << endl;
}

// function that checks if the user entered a valid hotel (either 1 or 2)
bool checkHotel(int hotel) {
	if (hotel != 1 && hotel != 2) {
		return false; 
	}
	return true; 
}

// function that checks if the user entered a valid floor (positive number)
bool checkFloor(int floor) {
	if (floor < 0) {
		return false; 
	}
	return true; 
}

// function that checks if the user entered a valid room number (positive number)
bool checkUnitNumber(int unit_number) {
	if (unit_number < 0) {
		return false; 
	}
	return true; 
}

// function that checks if the user entered a valid phone number (10 numbers)
bool checkPhoneNumber(string phone_number) {
	if (phone_number.length() != 10 || isDigit(phone_number) == false) {
		return false; 
	}
	return true; 
}

// function that checks if a string contains all digits (used to check phone number)
bool isDigit(string s) {
	// split the string into chars and check if each char is a digit
	if (! s.empty() && all_of(s.begin(), s.end(), [](char c){return isdigit(c);})) {
    return true;
  }
	return false;
}

// function that finds the index of a specific object (booking) in the array of objects
int search(int unit_number, Hotel occupants[], int count) {
	// iterate through the array and check if the unit number matches
	for (int i = 0; i < count; i++) {
		if (occupants[i].getUnitNumber() == unit_number) {
			return i; // return index if it exists
		}
	}
	return -1; // otherwise return -1 to indicate it cannot be found
};

// function that prints the attributes of each of the objects in the array of objects
void list(Hotel occupants[], int count) {
	
	// iterate through the array call the print() method on each object
	for (int i = 0; i < count; i++) {
		occupants[i].print();
		cout << endl;
	}
};