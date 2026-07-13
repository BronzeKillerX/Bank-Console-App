#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>

struct BankAccount {
	std::string userName;
	std::string ID;
	std::string pin;
	std::string DoB;
	double balance = 0.0;
};

int login(BankAccount& accountDB);

int main() {
	// Variable initialization
	std::vector <BankAccount> accountDB;
	int option; //Variable for selecting an option.
	// Variable initialization End


	// Login Menu
	std::cout << "=====================================\n";
	std::cout << "               Bank App              \n";
	std::cout << "=====================================\n\n";

	std::cout << "-------------------------\n";
	std::cout << "1. Login\n";
	std::cout << "2. Create Account\n";
	std::cout << "3. Exit\n";
	std::cout << "------------------------\n";
	std::cout << "Enter an option (1-3): "; //Prompt to ask for user input
	
	while ((!std::cin >> option) || (option < 1 || option > 3)) { // Validating user input
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "\nEnter a valid option (1-3): ";
		}
		else {
			std::cout << "\nEnter a valid option (1-3): ";
		}
	}

	switch (option) {
		case 1: 
			break;
		case 2:
			break;
		default:
			break;
	}


}

int login(std::vector <BankAccount>& accountDB) {
	if (accountDB.empty()) {
		std::cout << "No Account Available !!!!!....\n";
		std::cout << "Returning to Main Menu......\n";
		std::system("pause");
		return -1;
	}
	//Variable initialization
	BankAccount tempAccount;
	int matchedIndex = -1;
	//Variable initaialization End
	for (int attempt = 0; attempt < 3; attempt++) {
		std::system("cls");
		std::cout << "--------------------LOGIN--------------------\n\n";
		std::cout << "=============================\n";
		std::cout << "Enter User Name: ";
		while (true) {
			bool IsValidString = true;
			std::getline(std::cin >> std::ws, tempAccount.userName);
			for (int i = 0; i < tempAccount.userName.length(); i++) {
				if ((!isalpha(tempAccount.userName[i])) && (!isspace(tempAccount.userName[i]))) {
					IsValidString = false;
					break;
				}
			}

			if (IsValidString) {
				break;
			}
			else {
				std::cout << "Enter a valid user name!!!: ";
			}
		}

		std::cout << "Enter 4 digit Pin Code: ";
		while (true) {
			bool isValidDigit = true;
			std::getline(std::cin >> std::ws, tempAccount.pin);
			for (int i = 0; i < tempAccount.pin.length(); i++) {
				if ((!isdigit(tempAccount.pin[i]))) {
					isValidDigit = false;
					break;
				}
			}

			if (isValidDigit && tempAccount.pin.length() == 4) {
				break;
			}
			else {
				std::cout << "Enter a valid Pin: ";
			}
		}

		bool loginSuccessful = false;
		BankAccount loggedInAccount;
		for (int i = 0; i < accountDB.size(); i++) {
			if (tempAccount.userName == accountDB[i].userName && tempAccount.pin == accountDB[i].pin) {
				loginSuccessful = true;
				loggedInAccount = accountDB[i];
				matchedIndex = i;
				break;
			}
		}

		if (loginSuccessful) {
			std::cout << "---------------Login Successful!!!!--------------------\n";
			std::cout << "Welcome, " << loggedInAccount.userName;
			return matchedIndex;
		}
		else {
			std::cout << "Incorrect Username / Password!!!... Try again!!!";
			if (attempt < 2) {
				std::system("pause");
			}
		}
		std::cout << "=============================\n";
	}
	std::system("cls");
	std::cout << "===================================\n";
	std::cout << "Too many attempts.... Login Failed!!!\n";
	std::cout << "Returning to Main Menu....\n";
	std::cout << "===================================\n";
	std::system("pause");
	return -1;
}