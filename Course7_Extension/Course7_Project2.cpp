// ***************************************************************** Project 2 ***************************************************************************
// ************************************************************ Bank Extension ******************************************************************

#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include<vector>
#include <fstream>

void funcPerfromMainMenueOption(short choice);
const string fileName = "Clients5656.txt";

struct stClientData {

	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance;

};


vector <string> funcSplitString(string s1, string separator) {

	string word = "";
	vector<string> vWord;

	for (short i = 0; i < s1.length(); i++) {
		if (s1.substr(i, separator.length()) == separator) {
			vWord.push_back(word);
			word = "";
			i += separator.length() - 1;
		}
		else {
			word += s1[i];
		}

	}

	if (word != "") {
		vWord.push_back(word);
	}
	return vWord;

}


stClientData funcConvertLineToRecord(string s1, string separator) {

	stClientData clientData;
	vector<string>vClientData;

	vClientData = funcSplitString(s1, "#//#");
	clientData.accountNumber = vClientData[0];
	clientData.pinCode = vClientData[1];
	clientData.name = vClientData[2];
	clientData.phone = vClientData[3];
	clientData.accountBalance = stod(vClientData[4]);

	return clientData;

}


string funcConvertRecordToLine(stClientData clientData, string separetor) {

	string stClientRecord = "";

	stClientRecord += clientData.accountNumber + separetor;
	stClientRecord += clientData.pinCode + separetor;
	stClientRecord += clientData.name + separetor;
	stClientRecord += clientData.phone + separetor;
	stClientRecord += to_string(clientData.accountBalance);

	return stClientRecord;
}


vector <stClientData> funcLoadDataFromFile(string fileName) {

	vector <stClientData> vClientData;
	fstream myFile;
	myFile.open(fileName, ios::in);


	if (myFile.is_open()) {

		string line;
		stClientData client;

		while (getline(myFile, line)) {
			client = funcConvertLineToRecord(line,"#//#");
			vClientData.push_back(client);
		}
		myFile.close();
	}

	return vClientData;
}




void funcSaveDataToFile(string fileName, vector<stClientData>& vClientData) {
	ofstream outFile(fileName);

	if (outFile.is_open()) {
		for (stClientData& client : vClientData) {
			if (client.accountNumber != "") {
				outFile << client.accountNumber << "#//#"
					<< client.pinCode << "#//#"
					<< client.name << "#//#"
					<< client.phone << "#//#"
					<< client.accountBalance << endl;
			}
		}
		outFile.close();
	}

}


void funcPrintClientRecord(stClientData clientData) {

	cout << "| " << setw(15) << left << clientData.accountNumber;
	cout << "| " << setw(10) << left << clientData.pinCode;
	cout << "| " << setw(20) << left << clientData.name;
	cout << "| " << setw(12) << left << clientData.phone;
	cout << "| " << setw(15) << left << clientData.accountBalance << "| " << endl;

}


void funcPrintAllClientsData(vector<stClientData>& vClientData) {

	cout << "\n\t\t\t  Client List (" << vClientData.size() << ") Client(s)\n";
	cout << "\n------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PIN Code";
	cout << "| " << left << setw(20) << "Name";
	cout << "  | " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance|";
	cout << "\n------------------------------------------------------------------------------------\n";
	for (const stClientData& clientData : vClientData) {

		funcPrintClientRecord(clientData);

	}

	cout << "\n------------------------------------------------------------------------------------\n";
}


stClientData funcAddNewClient() {

	stClientData clientData;
	vector <string> vClient;

	cout << "Enter Account Number  : ";
	getline(cin >> ws, clientData.accountNumber);
	cout << "Enter PIN Code        : ";
	getline(cin, clientData.pinCode);
	cout << "Enter Name            : ";
	getline(cin, clientData.name);
	cout << "Enter Phone           : ";
	getline(cin, clientData.phone);
	cout << "Enter Account Balance : ";
	cin >> clientData.accountBalance;

	return clientData;
}


void funcDeleteClientByAccountNumber(string accountNumber, vector<stClientData>& vClientData) {

	bool found = false;
	char deleteClient = 'y';

	for (stClientData& clientData : vClientData) {
		if (accountNumber == clientData.accountNumber) {

			cout << "\n\n";
			cout << "Account Number  : " << clientData.accountNumber << endl;
			cout << "PIN Code        : " << clientData.pinCode << endl;
			cout << "Name            : " << clientData.name << endl;
			cout << "Phone           : " << clientData.phone << endl;
			cout << "Account Balance : " << clientData.accountBalance << endl;
			found = true;

			cout << "Are You Sure to delete this client ?? [Y:N] : ";
			cin >> deleteClient;
			if (deleteClient == 'y' || deleteClient == 'Y') {
				clientData.accountNumber = "";
				clientData.pinCode = "";
				clientData.name = "";
				clientData.phone = "";
				clientData.accountBalance = 0.0;
				funcSaveDataToFile(fileName, vClientData);
				cout << "\nClient Deleted Successfully.\n";

			}
		}

	}
	if (!found) {
		cout << "\nClient With Account Number (" << accountNumber << ") is NOT Found\n";
	}


}


void funcUpdateClientByAccountNumber(string accountNumber, vector<stClientData>& vClientData) {

	bool found = false;
	char UpdateClient = 'y';

	for (stClientData& clientData : vClientData) {
		if (accountNumber == clientData.accountNumber) {

			cout << "\n\n";
			cout << "Account Number  : " << clientData.accountNumber << endl;
			cout << "PIN Code        : " << clientData.pinCode << endl;
			cout << "Name            : " << clientData.name << endl;
			cout << "Phone           : " << clientData.phone << endl;
			cout << "Account Balance : " << clientData.accountBalance << endl;
			found = true;

			cout << "\n\nAre You Sure to Update this client ?? [Y:N] : ";
			cin >> UpdateClient;
			if (UpdateClient == 'y' || UpdateClient == 'Y') {
				cout << "\nEnter PIN Code        : ";
				getline(cin >> ws, clientData.pinCode);
				cout << "\nEnter Name            : ";
				getline(cin, clientData.name);
				cout << "\nEnter Phone           : ";
				getline(cin, clientData.phone);
				cout << "\nEnter Account Balance : ";
				cin >> clientData.accountBalance;
				funcSaveDataToFile(fileName, vClientData);
				cout << "\nClient Updated Successfully.\n";

			}
		}

	}
	if (!found) {
		cout << "\nClient With Account Number (" << accountNumber << ") is NOT Found\n";
	}


}


void funcFindClient(string accountNumber, vector<stClientData>& vClientData ,stClientData &clientData) {

	bool found = false;
	for (stClientData& c : vClientData) {
		if (accountNumber == c.accountNumber) {

			cout << "\n\n";
			cout << "Account Number  : " << c.accountNumber << endl;
			cout << "PIN Code        : " << c.pinCode << endl;
			cout << "Name            : " << c.name << endl;
			cout << "Phone           : " << c.phone << endl;
			cout << "Account Balance : " << c.accountBalance << endl;

			clientData = c;
			found = true;
			break;
		}

	}
	if (!found) {
		cout << "\nClient With Account Number (" << accountNumber << ") is NOT Found\n";
	}
}


short funcShowMainMenu() {

	short choice = 0;
	system("cls");

	cout << "========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "========================================\n";
	cout << "Choose what do you want to do?? [1 to 7] : ";
	cin >> choice;

	return choice;
}


string funcReadAccountNumber() {

	string accountNumber = "";
	cout << "\nPlease Enter Account Number : ";
	cin >> accountNumber;
	return accountNumber;
}


short funcShowTransactionsMenu() {
	cout << "======================================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "======================================================\n";
	cout << "Choose What Do You Want To Do? [1 to 4] : ";
	short choice = 0;
	cin >> choice;
	return choice;
}


void funcDepositeScreen() {

	stClientData clientData;
	cout << "-------------------------------------\n";
	cout << "\t\tDeposite Screen\n";
	cout << "-------------------------------------\n";

	vector <stClientData> vClientData = funcLoadDataFromFile(fileName);


	string accountNumber = "";
	bool found = false;
	while (!found) {
		accountNumber = funcReadAccountNumber();

		for (stClientData& c : vClientData) {
			if (c.accountNumber == accountNumber) {
				clientData = c;
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "\nAccount Number (" << accountNumber
				<< ") NOT FOUND. Please enter a valid account number.\n";
		}
	}

	cout << "\n\nThe following are the client details :\n";
	cout << "-------------------------------------------------";
	funcFindClient(accountNumber, vClientData,clientData);
	cout << "\n-------------------------------------------------\n";

	int depositeAmount = 0;
	char choice = 'n';

	cout << "\nPlease Enter Deposite Amount : ";
	cin >> depositeAmount;

	cout << "\nAre You sure you want to perform this transaction?? [Y:N] : ";
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		clientData.accountBalance += depositeAmount;

		for (stClientData& c : vClientData) {
			if (c.accountNumber == clientData.accountNumber) {
				c.accountBalance = clientData.accountBalance;
				break;
			}
		}
		funcSaveDataToFile(fileName, vClientData);
		cout << "\nDone Successflly ,New Balance is : " << clientData.accountBalance << endl;
	}
}



void funcWithDrawScreen() {


	cout << "-------------------------------------\n";
	cout << "\t\tWithdraw Screen\n";
	cout << "-------------------------------------\n";
	stClientData clientData;
	vector <stClientData> vClientData = funcLoadDataFromFile(fileName);
	string accountNumber = "";
	bool found = false;

	while (!found) {
		cout << "\nPlease Enter Account Number : ";
		cin >> accountNumber;

		for (stClientData& c : vClientData) {
			if (c.accountNumber == accountNumber) {
				clientData = c;
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "\nAccount Number (" << accountNumber
				<< ") NOT FOUND. Please enter a valid account number.\n";
		}
	}

	cout << "\nThe following are the client details :\n";
	cout << "-------------------------------------------------";

	funcFindClient(accountNumber, vClientData,clientData);
	cout << "\n-------------------------------------------------\n";


	int withDrawAmount= 0;
	char choice = 'n';

	cout << "\nPlease Enter Withdraw Amount : ";
	cin >> withDrawAmount;

	while (withDrawAmount > clientData.accountBalance) {
		cout << "Amount Exceeds the balance , you can withdraw up to : " << clientData.accountBalance << endl;
		cout << "Please Enter Another Amount : ";
		cin >> withDrawAmount;
	}
	cout << "\nAre You sure you want to perform this transaction?? [Y:N] : ";
	cin >> choice;


	if (choice == 'y' || choice == 'Y') {
		clientData.accountBalance -= withDrawAmount;

		for (stClientData& c : vClientData) {
			if (c.accountNumber == clientData.accountNumber) {
				c.accountBalance = clientData.accountBalance;
				break;
			}
		}
				funcSaveDataToFile(fileName, vClientData);
				cout << "\nDone Successflly ,New Balance is : " << clientData.accountBalance << endl;
		}
}


void funcPrintBalancesList(stClientData clientData) {

	cout << "| " << setw(15) << left << clientData.accountNumber;
	cout << "| " << setw(30) << left << clientData.name;
	cout << "| " << setw(15) << left << clientData.accountBalance << "  | " << endl;

}


void funcPrintAllBalancesList(vector<stClientData>& vClientData) {

	cout << "\n\t\t\t  Client List (" << vClientData.size() << ") Client(s)\n";
	cout << "\n---------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(30) << "Name";
	cout << "| " << left << setw(15) << "Account Balance  |";
	cout << "\n---------------------------------------------------------------------\n";

	for (const stClientData& clientData : vClientData) {

		funcPrintBalancesList(clientData);

	}

	cout << "\n---------------------------------------------------------------------\n";

	double sum = 0;
	for (short i = 0; i < vClientData.size(); i++) {
		sum += vClientData[i].accountBalance;
	}
	cout << "\n\t\t\tTotal Balances = " << sum << endl;
}


void funcPerformTransactionsMenueOption(short choice) {

	while (true) {
		switch (choice) {
		case 1: {
			system("cls");
			funcDepositeScreen();
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;

		case 2: {
			system("cls");
			funcWithDrawScreen();
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;

		case 3: {
			system("cls");
			vector<stClientData> vClientData = funcLoadDataFromFile(fileName);
			funcPrintAllBalancesList(vClientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;

		case 4: {
			//funcPerfromMainMenueOption(funcShowMainMenu());
			return;
		} break;
		}
		system("cls");
		choice = funcShowTransactionsMenu();
	}

}


void funcPerfromMainMenueOption(short choice) {

	while (true) {
		switch (choice) {

		case 1: {
			system("cls");
			vector<stClientData> vClientData = funcLoadDataFromFile(fileName);
			funcPrintAllClientsData(vClientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;


		case 2: {
			char choice = 'y';
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tAdd New Clients Screen \n";
			cout << "-------------------------------------------------\n";
			string line = "";
			cout << "\n\n***** Adding new Clients *****\n\n";
			do {
				vector<stClientData> vClientData = funcLoadDataFromFile(fileName);
				stClientData clientData = funcAddNewClient();
				vClientData.push_back(clientData);
				funcSaveDataToFile(fileName, vClientData);
				cout << "\nClient Added Successfuly\n";
				cout << "\nDo you want to add more clients?? [Y:N] : ";
				cin >> choice;
			} while (choice == 'y' || choice == 'Y');
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		}break;


		case 3: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tDelete Clients Screen \n";
			cout << "-------------------------------------------------\n";
			vector <stClientData> vClientData = funcLoadDataFromFile(fileName);
			string accountNumber = funcReadAccountNumber();
			funcDeleteClientByAccountNumber(accountNumber, vClientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;


		case 4: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tUpdate Clients Screen \n";
			cout << "-------------------------------------------------\n";
			vector <stClientData> vClientData = funcLoadDataFromFile(fileName);
			string accountNumber = funcReadAccountNumber();
			funcUpdateClientByAccountNumber(accountNumber, vClientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;


		case 5: {
			system("cls");
			vector <stClientData> vClientData = funcLoadDataFromFile(fileName);
			string accountNumber = funcReadAccountNumber();
			stClientData clientData;
			funcFindClient(accountNumber, vClientData,clientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;

		case 6: {

			system("cls");
			funcPerformTransactionsMenueOption(funcShowTransactionsMenu());
		} break;

		case 7: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\tProgram Ends :)\n";
			cout << "-------------------------------------------------\n";
			return;
		}break;

		}
		choice = funcShowMainMenu();
	}
}


int main() {

	funcPerfromMainMenueOption(funcShowMainMenu());
}

