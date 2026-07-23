#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>

struct BankAccount {
	std::string userName;
	std::string ID;
	std::string pin;
	std::string DoB;
	double balance = 0.0;
	bool isAdmin = false;
};
void adminDashboard(int adminIndex, std::vector <BankAccount>& accountDB);
void viewAccount(const std::vector <BankAccount>& accountDB);
void deleteAccount(std::vector <BankAccount>& accountDB);
void dashboard(int userIndex, std::vector <BankAccount>& accountDB);
void deposit(int userIndex, std::vector <BankAccount>& accountDB);
void checkBalance(const BankAccount& activeAccount);
void withdrawal(int userIndex, std::vector <BankAccount>& accountDB);
void transferMoney(int userIndex, std::vector <BankAccount>& accountDB);
void saveDatabase(const std::vector <BankAccount>& accountDB);
void loadDatabase(std::vector <BankAccount>& accountDB);
int login(std::vector <BankAccount>& accountDB);
void createAccount(std::vector <BankAccount>& accountDB);

int main() {
	// Variable initialization
	std::vector <BankAccount> accountDB;
	loadDatabase(accountDB);
	int option = 0;
	// Variable initialization End


	// Login Menu
	while (true) {
		std::system("cls");
		std::cout << "=====================================\n";
		std::cout << "               Bank App              \n";
		std::cout << "=====================================\n\n";

		std::cout << "-------------------------\n";
		std::cout << "1. Login\n";
		std::cout << "2. Create Account\n";
		std::cout << "3. Exit\n";
		std::cout << "------------------------\n";
		std::cout << "Enter an option (1-3): "; //Prompt to ask for user input

		while (!(std::cin >> option) || (option < 1 || option > 3)) { // Validating user input
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "\nEnter a valid option (1-3): ";
		}

		switch (option) {
		case 1: {
			int userIndex = login(accountDB);
			if (userIndex != -1) {
				if (accountDB[userIndex].isAdmin) {
					adminDashboard(userIndex, accountDB);
				}
				else {
					dashboard(userIndex, accountDB);
				}
			}
		}
			break;
		case 2:
			createAccount(accountDB);
			break;
		case 3:
			return 0;
		}
	}
}

int login(std::vector <BankAccount>& accountDB) {
	std::system("cls");
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
				matchedIndex = static_cast<int>(i);
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
		else if (tempAccount.DoB[2] != '/' || tempAccount.DoB[5] != '/') {
			isValidFormat = false;
		}
		else {
			for (int i = 0; i < 10; i++) {
				if (i == 2 || i == 5) {
					continue;
				}
				if (!isdigit(tempAccount.DoB[i])) {
					isValidFormat = false;
					break;
				}
			}
		}
		if (isValidFormat) {
			int day = std::stoi(tempAccount.DoB.substr(0, 2));
			int month = std::stoi(tempAccount.DoB.substr(3, 2));
			int year = std::stoi(tempAccount.DoB.substr(6, 4));
			if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2026) {
				isValidFormat = false;
			}
		}
		if (isValidFormat) {
			break;
		}
		else {
			std::cout << "Invalid Date!! Enter date as (DD/MM/YYYY): ";
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
			if (tempAccount.ID[0] != 'G' || tempAccount.ID[1] != 'H' || tempAccount.ID[2] != 'A') {
				isValidFormat = false;
			}
			else if (tempAccount.ID[3] != '-' || tempAccount.ID[8] != '-' || tempAccount.ID[13] != '-') {
				isValidFormat = false;
			}
			else {
				for (int i = 0; i < 15; i++) {
					if (i == 0 || i == 1 || i == 2 || i == 3 || i == 8 || i == 13) {
						continue;
					}

					if (!isdigit(tempAccount.ID[i])) {
						isValidFormat = false;
						break;
					}
				}
			}
		}
		if (!isValidFormat) {
			std::cout << "Invalid Format.... Try Again!! (GHA-****-****-*)\n\n";
			std::system("pause");
			continue;
		}
		bool isDuplicate = false;
		for (const auto& acc : accountDB) {
			if (acc.ID == tempAccount.ID) {
				isDuplicate = true;
				break;
			}
		}
		if (isDuplicate) {
			std::cout << "Enter a unique ID!!";
			continue;
		}
		else {
			break;
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
		outfile << accountDB[i].userName << "|"
			<< accountDB[i].ID << "|"
			<< accountDB[i].DoB << "|"
			<< accountDB[i].pin << "|"
			<< accountDB[i].balance << "|"
			<< (accountDB[i].isAdmin ? "1" : "0") << "\n";
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
		std::string balanceStr, adminStr;

		std::getline(ss, tempAccount.userName, '|');
		std::getline(ss, tempAccount.ID, '|');
		std::getline(ss, tempAccount.DoB, '|');
		std::getline(ss, tempAccount.pin, '|');
		std::getline(ss, balanceStr, '|');
		std::getline(ss, adminStr);

		tempAccount.balance = std::stod(balanceStr);
		tempAccount.isAdmin = (adminStr == "1");
		accountDB.push_back(tempAccount);
	}
	inFile.close();
}

void dashboard(int userIndex, std::vector <BankAccount>& accountDB) {
	int option = 0;
	while (true) {
		std::system("cls");
		std::cout << "===========================================\n";
		std::cout << "              Customer DashBoard           \n";
		std::cout << "===========================================\n\n";
		std::cout << "Welcome " << accountDB[userIndex].userName << "\n";
		std::cout << "Account ID: " << accountDB[userIndex].ID << "\n";
		std::cout << "-----------------------------\n";
		std::cout << "1. Check Balance\n";
		std::cout << "2. Deposit\n";
		std::cout << "3. Withdrawal\n";
		std::cout << "4. Transfer / Send Money\n";
		std::cout << "5. Logout\n";
		std::cout << "-----------------------------\n";
		std::cout << "Enter your option: ";

		while (!(std::cin >> option) || (option < 1 || option > 5)) { // Validating user input
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "\nEnter a valid option (1-5): ";
		}

		switch (option) {
		case 1:
			checkBalance(accountDB[userIndex]);
			break;
		case 2:
			deposit(userIndex, accountDB);
			break;
		case 3:
			withdrawal(userIndex, accountDB);
			break;
		case 4:
			transferMoney(userIndex, accountDB);
			break;
		case 5:
			return;
		}
	}
}

void adminDashboard(int adminIndex, std::vector <BankAccount>& accountDB) {
	int option = 0;
	while (true) {
		std::system("cls");
		std::cout << "==========================================\n";
		std::cout << "               ADMIN DASHBOARD            \n";
		std::cout << "==========================================\n";
		std::cout << "Welcome " << accountDB[adminIndex].userName << "\n";
		std::cout << "Account ID: " << accountDB[adminIndex].ID << "\n";
		std::cout << "------------------------------------------\n";
		std::cout << "1. View all Accounts\n";
		std::cout << "2. Delete Account\n";
		std::cout << "3. Logout\n";
		std::cout << "------------------------------------------\n";
		std::cout << "Enter your option: ";
		
		while (!(std::cin >> option) || (option < 1 || option > 3)) { // Validating user input
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "\nEnter a valid option (1-3): ";
		}
		switch (option) {
			case 1:
				viewAccount(accountDB);
				break;
			case 2: 
				deleteAccount(accountDB);
				break;
			case 3:
				return;
		}
	}
}

void viewAccount(const std::vector <BankAccount>& accountDB) {
	std::system("cls");
	std::cout << "==================Registered Accounts===================\n";
	std::cout << std::left << std::setw(20) << "User Name"
		<< std::setw(20) << "ID"
		<< std::setw(20) << "Date of Birth"
		<< std::setw(15) << "Balance"
		<< std::setw(15) << "Status" << "\n";
	std::cout << "=========================================================\n";
	for (const auto& acc : accountDB) {
		std::cout << std::left << std::setw(20) << acc.userName
			<< std::setw(20) << acc.ID
			<< std::setw(20) << acc.DoB
			<< std::setw(15) << acc.balance
			<< std::setw(15) << (acc.isAdmin ? "Admin" : "User") << "\n";
	}
	std::cout << "----------------------------------------------------------\n";
	std::system("pause");
	return;
}

void deleteAccount(std::vector <BankAccount>& accountDB) {
	std::string targetID;
	while (true) {
		std::system("cls");
		std::cout << "-----------------Delete Account!!-----------------\n";
		std::cout << "Enter User Account ID: ";
		bool isValidFormat = true;
		std::getline(std::cin >> std::ws, targetID);
		if (targetID.length() != 15) {
			isValidFormat = false;
		}
		else {
			if (targetID[0] != 'G' || targetID[1] != 'H' || targetID[2] != 'A') {
				isValidFormat = false;
			}
			else if (targetID[3] != '-' || targetID[8] != '-' || targetID[13] != '-') {
				isValidFormat = false;
			}
			else {
				for (int i = 0; i < 15; i++) {
					if (i == 0 || i == 1 || i == 2 || i == 3 || i == 8 || i == 13) {
						continue;
					}

					if (!isdigit(targetID[i])) {
						isValidFormat = false;
						break;
					}
				}
			}
		}
		if (!isValidFormat) {
			std::cout << "Invalid Format.... Try Again!! (GHA-****-****-*)\n\n";
			std::system("pause");
			continue;
		}
		bool isFound = false;
		for (int i = 0; i < accountDB.size(); i++) {
			if (targetID == accountDB[i].ID) {
				if (accountDB[i].isAdmin) {
					std::cout << "Admin Account Cannot Be Deleted!!\n";
				}
				else {
					char confirm;
					std::cout << "\nAre you sure you want to delete account for "
						<< accountDB[i].userName << "? (Y/N): ";
					std::cin >> confirm;
					std::cin.ignore(1000, '\n');
					if (tolower(confirm) == 'y') {
						std::cout << "\nAccount for " << accountDB[i].userName << " successfully deleted!\n";
						accountDB.erase(accountDB.begin() + i);
						saveDatabase(accountDB);
					}
					else {
						std::cout << "\nDeletion canceled.\n";
					}
				}
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "Account with ID not found!!\n";
		}
		std::cout << "--------------------------------------------------\n";
		std::system("pause");
		break;
	}
}

void deposit(int userIndex, std::vector <BankAccount>& accountDB) {
	double amount = 0.0;
		std::cout << "-------------------Deposit-------------------\n\n";
		std::cout << "Enter amount to Deposit ($1.00 to $50,000.00): ";

		while (!(std::cin >> amount) || amount < 1.00 || amount > 50000.00) {
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Enter a valid amount!!! ($1.00 to $50000): ";
			}
			else {
				std::cout << "Enter a valid amount!!! ($1.00 to $50000): ";
			}
		}
		std::cin.ignore(1000, '\n');
		accountDB[userIndex].balance += amount;
		saveDatabase(accountDB);
		std::cout << "-------------------------------------\n";
		std::cout << "Deposit Successful!!\n";
		std::cout << "$" << amount << " has been deposited into your account.\n ";
		std::cout << "Your New Balance: $" << accountDB[userIndex].balance << "\n";
		std::cout << "--------------------------------------\n";
		std::cout << "Press the Enter button to continue...\n";
		std::system("pause");
}

void checkBalance(const BankAccount& activeAccount) {
	std::system("cls");
	std::cout << "---------------Check Balance---------------\n\n";
	std::cout << "Your current Balance is: $" << activeAccount.balance << "\n";
	std::cout << "--------------------------------------------\n";
	std::cout << "Press the Enter button to continue...";
	std::system("pause");
}

void withdrawal(int userIndex, std::vector <BankAccount>& accountDB) {
	std::system("cls");
	double amount = 0.0;
	std::cout << "-------------------Withdrawal----------------------------\n\n";
	std::cout << "Your Current Balance: $" << accountDB[userIndex].balance << "\n";
	std::cout << "Enter amount to withdraw ($1.00 to $10,000.00): ";
	while (!(std::cin >> amount) || amount < 1.00 || amount > 10000.00 || amount > accountDB[userIndex].balance) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Enter a valid amount!!! ($1.00 to $10,000.00): ";
		}
		else if (amount > accountDB[userIndex].balance) {
			std::cout << "You do not have enough funds to complete this process!!!...\n";
			std::cout << "Enter a valid amount $: ";
		}
		else {
			std::cout << "Enter a valid amount ($1.00 to $10,000.00): ";
		}
	}
	std::cin.ignore(1000, '\n');
	accountDB[userIndex].balance -= amount;
	saveDatabase(accountDB);
	std::cout << "-----------------------------------------------------\n";
	std::cout << "Withdrawal Complete!!!... Thanks for Banking with Us\n";
	std::cout << "Current Balance is: $" << accountDB[userIndex].balance << "\n";
	std::cout << "-----------------------------------------------------\n";
	std::cout << "Press the Enter key to continue....";
	std::system("pause");
}

void transferMoney(int userIndex, std::vector <BankAccount>& accountDB) {
	std::system("cls");
	double amount = 0.0;
	std::string recipientID;
	int recipientIndex = -1;
	std::cout << "--------------------Transfer Money--------------------\n\n";
	std::cout << "Your Current Balance: $" << accountDB[userIndex].balance << "\n";
	while (true) {
		std::cout << "Enter recipient ID (GHA-****-****-*):	";
		while (true) {
			bool isValidFormat = true;
			std::getline(std::cin >> std::ws, recipientID);
			if (recipientID.length() != 15) {
				isValidFormat = false;
			}
			else {
				if (recipientID[0] != 'G' || recipientID[1] != 'H' || recipientID[2] != 'A') {
					isValidFormat = false;
				}
				else if (recipientID[3] != '-' || recipientID[8] != '-' || recipientID[13] != '-') {
					isValidFormat = false;
				}
				else {
					for (int i = 0; i < 15; i++) {
						if (i == 0 || i == 1 || i == 2 || i == 3 || i == 8 || i == 13) {
							continue;
						}

						if (!isdigit(recipientID[i])) {
							isValidFormat = false;
							break;
						}
					}
				}
			}
			if (!isValidFormat) {
				std::cout << "Invalid Format.... Try Again!! (GHA-****-****-*)\n\n";
				continue;
			}
			else {
				break;
			}
		}

		if (recipientID == accountDB[userIndex].ID) {
			std::cout << "You cannot send money to yourself";
			continue;
		}
		else {
			recipientIndex = -1;
			for (int i = 0; i < accountDB.size(); i++) {
				if (accountDB[i].ID == recipientID) {
					recipientIndex = static_cast <int>(i);
					break;
				}
			}
			if (recipientIndex != -1) {
				break;
			}
			else {
				std::cout << "The Account ID you entered does not exist!!.... Try again\n\n";
			}
		}
	}
	std::cout << "Recipient Found! ( " << accountDB[recipientIndex].userName << " )\n";
	std::cout << "Enter amount to transfer ($1.00 to $10,000.00): ";
	while (!(std::cin >> amount) || amount < 1.00 || amount > 10000.00 || amount > accountDB[userIndex].balance) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Enter a valid amount!!! ($1.00 to $10,000.00): ";
		}
		else if (amount > accountDB[userIndex].balance) {
			std::cout << "You do not have enough funds to complete this process!!!...\n";
			std::cout << "Enter a valid amount $: ";
		}
		else {
			std::cout << "Enter a valid amount ($1.00 to $10,000.00): ";
		}
	}
	std::cin.ignore(1000, '\n');
	accountDB[userIndex].balance -= amount;
	accountDB[recipientIndex].balance += amount;
	saveDatabase(accountDB);
	std::cout << "------------------------------------------------------\n";
	std::cout << "Transaction Successful!!!";
	std::cout << "You sent $" << amount << " to " << accountDB[recipientIndex].userName <<"\n";
	std::cout << "Your current balance: $" << accountDB[userIndex].balance << "\n";
	std::cout << "------------------------------------------------------\n";
	std::cout << "Press Enter to continue....";
	std::system("pause");
}