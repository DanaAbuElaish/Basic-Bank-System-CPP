// ***************************************************************** Project 1 ***************************************************************************
// ************************************************************ Bank 1 ******************************************************************

#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include<vector>
#include <fstream>


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
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance  |";
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


void funcFindClient(string accountNumber, vector<stClientData>& vClientData) {

	bool found = false;
	for (stClientData& clientData : vClientData) {
		if (accountNumber == clientData.accountNumber) {

			cout << "\n\n";
			cout << "Account Number  : " << clientData.accountNumber << endl;
			cout << "PIN Code        : " << clientData.pinCode << endl;
			cout << "Name            : " << clientData.name << endl;
			cout << "Phone           : " << clientData.phone << endl;
			cout << "Account Balance : " << clientData.accountBalance << endl;
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
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client Info\n";
	cout << "\t[5] Find Client\n";
	cout << "\t[6] Exit\n";
	cout << "========================================\n";
	cout << "Choose what do you want to do?? [1 to 6] : ";
	cin >> choice;

	return choice;
}


string funcReadAccountNumber() {

	string accountNumber = "";
	cout << "\nPlease Enter Account Number : ";
	cin >> accountNumber;
	return accountNumber;
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
			funcFindClient(accountNumber, vClientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;


		case 6: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\tProgram Ends :)\n";
			cout << "-------------------------------------------------\n";
			return;
		}

		}
		choice = funcShowMainMenu();
	}
}

int main() {

	funcPerfromMainMenueOption(funcShowMainMenu());
}
