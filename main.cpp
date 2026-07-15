#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

struct BankAccount {
	std::string userName;
	std::string ID;
	std::string pin;
	std::string DoB;
	double balance = 0.0;
};
void deposit(BankAccount& activeAccount, std::vector <BankAccount>& accountDB);
void checkBalance(BankAccount& activeAccount, std::vector <BankAccount>& accountDB);
void withdrawal(BankAccount& activeAccount, std::vector <BankAccount>& accountDB);
void saveDatabase(const std::vector <BankAccount>& accountDB);
void loadDatabase(std::vector <BankAccount>& accountDB);
int login(std::vector <BankAccount>& accountDB);
void createAccount(std::vector <BankAccount>& accountDB);

int main() {
	// Variable initialization
	std::vector <BankAccount> accountDB;
	loadDatabase(accountDB);
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
	case 1: {
		break;
		}
	case 2: {
		break;
	}
	default: {
		break;
		}
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

void createAccount(std::vector <BankAccount>& accountDB) {
	//Variable initialization
	BankAccount tempAccount;
	//Variable initialization end

	std::cout << "--------------Create An Account----------------\n\n";
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

	std::cout << "Enter Date of Birth (DD/MM/YYYY): ";

	while (true) {
		bool isValidFormat = true;
		std::getline(std::cin >> std::ws, tempAccount.DoB);

		if (tempAccount.DoB.length() != 10) {
			isValidFormat = false;
		}
		else {
			for (int i = 0; i < 10; i++) {
				if (i == 2 || i == 5) {
					if (tempAccount.DoB[i] != '/') {
						isValidFormat = false;
						break;
					}
				}
				else {
					if (!isdigit(tempAccount.DoB[i])) {
						isValidFormat = false;
						break;
					}
				}
			}
		}

		if (isValidFormat) {
			break;
		}
		else {
			std::cout << "Invalid format... Enter Date of Birth as (DD/MM/YYYY): ";
		}

	}

	while (true) {
		std::cout << "Enter Pin: ";

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

		std::cout << "Re-Enter Pin: ";
		std::string temporalPin;
		while (true) {
			bool isValidDigit = true;
			std::getline(std::cin >> std::ws, temporalPin);
			for (int i = 0; i < temporalPin.length(); i++) {
				if ((!isdigit(temporalPin[i]))) {
					isValidDigit = false;
					break;
				}
			}

			if (isValidDigit && temporalPin.length() == 4) {
				break;
			}
			else {
				std::cout << "Enter a valid Pin: ";
			}
		}

		if (temporalPin == tempAccount.pin) {
			break;
		}
		else {
			std::cout << "The Pin you entered does not match... Try Again\n\n";
		}
	}

	std::cout << "Enter ID (GHA-****-****-*): ";

	while (true) {
		bool isValidFormat = true;
		std::getline(std::cin >> std::ws, tempAccount.ID);

		if (tempAccount.ID.length() != 15) {
			isValidFormat = false;
		}
		else {
			for (int i = 0; i < 15; i++) {
				if (i == 0 && tempAccount.ID[i] != 'G') {
					isValidFormat = false;
					break;
				}
				else if (i == 1 && tempAccount.ID[i] != 'H'	) {
					isValidFormat = false;
					break;
				}
				else if (i == 2 && tempAccount.ID[i] != 'A') {
					isValidFormat = false;
					break;
				}
				else if (i == 3 || i == 8 || i == 13) {
					if (tempAccount.ID[i] != '-') {
						isValidFormat = false;
						break;
					}
				}
				else if (!isdigit(tempAccount.ID[i])) {
					isValidFormat = false;
					break;
				}
			}
		}
		if (isValidFormat) {
			break;
		}
		else {
			std::cout << "Invalid Format.... Try Again!! (GHA-****-****-*)\n\n";
		}
	}

	tempAccount.balance = 0.0;
	accountDB.push_back(tempAccount);
	saveDatabase(accountDB);

	std::cout << "\n==================================================\n";
	std::cout << "  Account Created Successfully!\n";
	std::cout << "  Welcome to the family, " << tempAccount.userName << "!\n";
	std::cout << "==================================================\n";
	std::system("pause");

}

void saveDatabase(const std::vector <BankAccount>& accountDB) {
	std::ofstream outfile("database.txt");

	if (!outfile) {
		std::cout << "Error: Could not open database.txt for writing!\n";
		return;
	}

	for (int i = 0; i < accountDB.size(); i++) {
		outfile << accountDB[i].userName << " | "
			<< accountDB[i].ID << " | "
			<< accountDB[i].DoB << " | "
			<< accountDB[i].pin << " | "
			<< accountDB[i].balance << "\n";
	}
	outfile.close();
}

void loadDatabase(std::vector <BankAccount>& accountDB) {
	std::ifstream inFile("database.txt");

	if (!inFile) {
		return;
	}

	accountDB.clear();
	std::string line;

	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		BankAccount tempAccount;
		std::string balanceStr;

		std::getline(ss, tempAccount.userName, '|');
		std::getline(ss, tempAccount.ID, '|');
		std::getline(ss, tempAccount.DoB, '|');
		std::getline(ss, tempAccount.pin, '|');
		std::getline(ss, balanceStr, '|');

		tempAccount.balance = std::stod(balanceStr);
		accountDB.push_back(tempAccount);
	}
	inFile.close();
}