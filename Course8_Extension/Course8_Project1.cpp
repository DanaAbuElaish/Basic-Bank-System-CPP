// ***************************************************************** Project1  ***************************************************************************
// ************************************************************ Bank Extension2 ******************************************************************

#include <iostream>
using namespace std;
#include <string>
#include <iomanip>
#include<vector>
#include <fstream>




struct stClientData {

	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance;

};


struct stUsersData {

	string userName;
	string password;
	short permissions = 0;
};


struct stFullAccessOrNot {


	bool full = false,
		showClientList = false,
		addNewClient = false,
		deleteClient = false,
		updateClient = false,
		findClient = false,
		transactions = false,
		manageUsers = false;
};


void funcPerfromMainMenueOption(short choice);
vector<stUsersData> funcLoadUsersDataFromFile(string fileName);
stFullAccessOrNot funcFullAccessOrNot(short binaryNumber);
short funcPermissionsCounter();
short funcShowManageUsersMenuScreen();
void funcPerformUserMenuOption(short choice);


const string fileName = "Clients5656.txt";
const string usersFileName = "Users.txt";
stUsersData currentUser;
stFullAccessOrNot currentAccess;


string funcReadUserName() {

	string userName;
	cout << "\nPlease Enter Username : ";
	cin >> userName;
	return userName;
}


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


void funcFindClient(string accountNumber, vector<stClientData>& vClientData, stClientData& clientData) {

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
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "========================================\n";
	cout << "Choose what do you want to do?? [1 to 8] : ";
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


string funcReadPassword() {

	string password;
	cout << "\nPlease Enter Password : ";
	cin >> password;
	return password;
}


bool funcFindUserByUsernameAndPassword(string username, string password, stUsersData& userData) {

	vector<stUsersData> vUsersData = funcLoadUsersDataFromFile(usersFileName);

	for (stUsersData& u : vUsersData) {
		if (u.userName == username && u.password == password) {
			userData = u;
			return true;
		}
	}

	return false;
}


void funcLoginScreen() {

	string userName;
	string password;


	while (true) {
		userName = funcReadUserName();
		password = funcReadPassword();

		if (funcFindUserByUsernameAndPassword(userName, password, currentUser)) {
			currentAccess = funcFullAccessOrNot(currentUser.permissions);
			cout << "\nLogin Successfully.\n";
			cout << "Press Any Key To Go To Main Menu...\n";
			system("pause>0");
			return;
		}
		else {
			cout << "\n";
			cout << "Invalid Username/Password !!\n";
		}
	}
}


void funcPerfromMainMenueOption(short choice) {

	while (true) {
		switch (choice) {

		case 1: {
			if (!currentAccess.full && !currentAccess.showClientList) {
				system("cls");
				cout << "\n\n";
				cout << "---------------------------------------" << endl;
				cout << "Access Denied\n";
				cout << "You Don't Have Permission To Do This!..\n";
				cout << "Please Contact Your Admin\n";
				cout << "---------------------------------------" << endl;
				cout << "\nPress Any Key To Go Back To Main Menu...";
				system("pause>0");
				break;

			}
			system("cls");
			vector<stClientData> vClientData = funcLoadDataFromFile(fileName);
			funcPrintAllClientsData(vClientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;


		case 2: {

			if (!currentAccess.full && !currentAccess.addNewClient) {
				system("cls");
				cout << "\n\n";
				cout << "---------------------------------------" << endl;
				cout << "Access Denied\n";
				cout << "You Don't Have Permission To Do This!..\n";
				cout << "Please Contact Your Admin\n";
				cout << "---------------------------------------" << endl;
				cout << "\nPress Any Key To Go Back To Main Menu...";
				system("pause>0");
				break;

			}
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

			if (!currentAccess.full && !currentAccess.deleteClient) {
				system("cls");
				cout << "\n\n";
				cout << "---------------------------------------" << endl;
				cout << "Access Denied\n";
				cout << "You Don't Have Permission To Do This!..\n";
				cout << "Please Contact Your Admin\n";
				cout << "---------------------------------------" << endl;
				cout << "\nPress Any Key To Go Back To Main Menu...";
				system("pause>0");
				break;
}

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

			if (!currentAccess.full && !currentAccess.updateClient) {
				system("cls");
				cout << "\n\n";
				cout << "---------------------------------------" << endl;
				cout << "Access Denied\n";
				cout << "You Don't Have Permission To Do This!..\n";
				cout << "Please Contact Your Admin\n";
				cout << "---------------------------------------" << endl;
				cout << "\nPress Any Key To Go Back To Main Menu...";
				system("pause>0");
				break;

			}
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

			if (!currentAccess.full && !currentAccess.findClient) {
				system("cls");
				cout << "\n\n";
				cout << "---------------------------------------" << endl;
				cout << "Access Denied\n";
				cout << "You Don't Have Permission To Do This!..\n";
				cout << "Please Contact Your Admin\n";
				cout << "---------------------------------------" << endl;
				cout << "\nPress Any Key To Go Back To Main Menu...";
				system("pause>0");
				break;

			}

			system("cls");
			vector <stClientData> vClientData = funcLoadDataFromFile(fileName);
			string accountNumber = funcReadAccountNumber();
			stClientData clientData;
			funcFindClient(accountNumber, vClientData,clientData);
			cout << "\nPress Any Key To Go Back To Menue ...";
			system("pause >0");
		} break;

		case 6: {
			if (!currentAccess.full && !currentAccess.transactions) {
				system("cls");
				cout << "\n\n";
				cout << "---------------------------------------" << endl;
				cout << "Access Denied\n";
				cout << "You Don't Have Permission To Do This!..\n";
				cout << "Please Contact Your Admin\n";
				cout << "---------------------------------------" << endl;
				cout << "\nPress Any Key To Go Back To Main Menu...";
				system("pause>0");
				break;

			}
			system("cls");
			funcPerformTransactionsMenueOption(funcShowTransactionsMenu());
		} break;

		  case 7: {
			  if (!currentAccess.full && !currentAccess.manageUsers) {
				  system("cls");
				  cout << "\n\n";
				  cout << "---------------------------------------" << endl;
				  cout << "Access Denied\n";
				  cout << "You Don't Have Permission To Do This!..\n";
				  cout << "Please Contact Your Admin\n";
				  cout << "---------------------------------------" << endl;
				  cout << "\nPress Any Key To Go Back To Main Menu...";
				  system("pause>0");
				  break;

			  }
			  system("cls");
			  funcPerformUserMenuOption(funcShowManageUsersMenuScreen());
		}break;

		case 8: {
			system("cls");
			cout << "\n----------------------------------\n";
			cout << "\tLogin Screen";
			cout << "\n----------------------------------\n";

			//funcLoginScreen();
			return;

		}break;

		}
		choice = funcShowMainMenu();
	}
}




// ******************************************* Users Side *************************************************

short funcShowManageUsersMenuScreen() {
	cout << "======================================================\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "======================================================\n";
	cout << "Choose What Do You Want To Do? [1 to 6 ] : ";
	short choice = 0;
	cin >> choice;
	return choice;
}


stUsersData funcConvertUsersLineToRecord(string s1, string separator) {

	stUsersData userData;
	vector<string>vUserData;

	vUserData = funcSplitString(s1, "#//#");
	userData.userName = vUserData[0];
	userData.password = vUserData[1];
	userData.permissions = stoi(vUserData[2]);

	return userData;

}


string funcConvertUsersRecordToLine(stUsersData userData, string separetor) {

	string stUserRecord = "";

	stUserRecord += userData.userName + separetor;
	stUserRecord += userData.password + separetor;
	stUserRecord += to_string(userData.permissions);

	return stUserRecord;
}


vector <stUsersData> funcLoadUsersDataFromFile(string fileName) {

	vector <stUsersData> vUsersData;
	fstream myFile;
	myFile.open(fileName, ios::in);


	if (myFile.is_open()) {

		string line;
		stUsersData user;

		while (getline(myFile, line)) {
			user = funcConvertUsersLineToRecord(line, "#//#");
			vUsersData.push_back(user);
		}
		myFile.close();
	}

	return vUsersData;
}


void funcSaveUsersDataToFile(string fileName, vector<stUsersData>& vUserData) {
	ofstream outFile(fileName);

	if (outFile.is_open()) {
		for (stUsersData& user : vUserData) {
			if (user.userName != "") {
				outFile << user.userName << "#//#"
					<< user.password << "#//#"
					<< user.permissions
					<< endl;
			}
		}
		outFile.close();
	}

}





short funcPermissionsCounter() {

	stFullAccessOrNot fullAccessOrNot;
	stUsersData usersData;
	char ans;

	cout << "\n\n";
	cout << "Do You want to give full access?? [Y:N] : ";
	cin >> ans;
	fullAccessOrNot.full = (ans == 'Y' || ans == 'y');
	if (fullAccessOrNot.full) {
		return -1;
	}

		cout << "\n\n";
		cout << "Do You Want To Give Access To : \n\n";
		cout << "Show Client List? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.showClientList = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.showClientList ) {
			usersData.permissions += 1;
		}

		cout << "\n\n";
		cout << "Add New Client? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.addNewClient = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.addNewClient ){
			usersData.permissions += 2;
		}

		cout << "\n\n";
		cout << "Delete Client? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.deleteClient = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.deleteClient) {
			usersData.permissions += 4;
		}

		cout << "\n\n";
		cout << "Update Client? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.updateClient = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.updateClient) {
			usersData.permissions += 8;
		}

		cout << "\n\n";
		cout << "Find Client? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.findClient = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.findClient ) {
			usersData.permissions += 16;
		}

		cout << "\n\n";
		cout << "Transactions? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.transactions = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.transactions) {
			usersData.permissions += 32;
		}

		cout << "\n\n";
		cout << "Manage Users? [Y:N] : ";
		cin >> ans;
		fullAccessOrNot.manageUsers = (ans == 'y' || ans == 'Y');
		if (fullAccessOrNot.manageUsers ) {
			usersData.permissions += 64;
		}

	return usersData.permissions;
}

void funcPrintUsersList(stUsersData userData) {

	cout << "| " << setw(15) << left << userData.userName;
	cout << "| " << setw(30) << left << userData.password;
	cout << "| " << setw(15) << left << userData.permissions << "| " << endl;

}

void funcPrintAllUsersList(vector<stUsersData>& vUserData) {

	cout << "\n\t\t\t  Users List (" << vUserData.size() << ") Client(s)\n";
	cout << "\n-------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(30) << "Password";
	cout << "| " << left << setw(15) << "Permissions    |";
	cout << "\n-------------------------------------------------------------------\n";

	for (const stUsersData& userData : vUserData) {

		funcPrintUsersList(userData);

	}

	cout << "-------------------------------------------------------------------\n";

	cout << "\nPress Any Key To Go Back To Transactions Menu ...";

}


stUsersData funcAddNewUser(vector<stUsersData>& vUserData) {

	stUsersData userData;
	bool exsists = false;

	do {
		cout << "\nEnter Username : ";
		exsists = false;
		getline(cin >> ws, userData.userName);

		for (stUsersData& u : vUserData) {
			if (u.userName == userData.userName) {
				cout << "\nUser with [" << userData.userName << "] already exsists , Please Enter another username\n";
				exsists = true;
				break;
			}
		}
	} while (exsists);

	cout << "\nEnter Password : ";
	getline(cin, userData.password);
	userData.permissions = funcPermissionsCounter();

	return userData;
}



stFullAccessOrNot funcFullAccessOrNot(short binaryNumber) {

	stFullAccessOrNot fullAccessOrNot;

	if (binaryNumber == -1) {
		fullAccessOrNot.full = true;
		return fullAccessOrNot;
	}

	fullAccessOrNot.showClientList = (binaryNumber & 1) != 0;
	fullAccessOrNot.addNewClient = (binaryNumber & 2) != 0;
	fullAccessOrNot.deleteClient = (binaryNumber & 4) != 0;
	fullAccessOrNot.updateClient = (binaryNumber & 8) != 0;
	fullAccessOrNot.findClient = (binaryNumber & 16) != 0;
	fullAccessOrNot.transactions = (binaryNumber & 32) != 0;
	fullAccessOrNot.manageUsers = (binaryNumber & 64) != 0;

	return fullAccessOrNot;
}



void funcDeleteUserByUserName(string userName, vector<stUsersData>& vUserData) {

	bool found = false;
	char deleteUser = 'y';


		if (userName == "Admin") {
			cout << "\n\n";
			cout << "You Can't Delete this User.\n";
			return;
		}


	for (stUsersData& userData : vUserData) {
		if (userName == userData.userName) {

			cout << "\n\n";
			cout << "The following are the client details:\n";
			cout << "-------------------------------------\n";
			cout << "User Name       : " << userData.userName << endl;
			cout << "Password        : " << userData.password << endl;
			cout << "Permissions     : " << userData.permissions << endl;
			cout << "-------------------------------------\n";
			found = true;

			cout << "Are You Sure to delete this user ?? [Y:N] : ";
			cin >> deleteUser;
			if (deleteUser == 'y' || deleteUser == 'Y') {
				userData.userName = "";
				userData.password = "";
				userData.permissions = 0;
				funcSaveUsersDataToFile(usersFileName, vUserData);
				cout << "\nUser Deleted Successfully.\n";

			}
			break;
		}

	}
	if (!found) {
		cout << "\nUser With [" << userName << "] is NOT Found\n";
	}


}


void funcUpdateUserByUserName(string userName, vector<stUsersData>& vUserData) {

	bool found = false;
	char UpdateUser = 'y';

	for (stUsersData& userData : vUserData) {
		if (userName == userData.userName) {

			cout << "\n\n";
			cout << "The following are the client details:\n";
			cout << "-------------------------------------\n";
			cout << "User Name       : " << userData.userName << endl;
			cout << "Password        : " << userData.password << endl;
			cout << "Permissions     : " << userData.permissions << endl;
			cout << "-------------------------------------\n";
			found = true;

			cout << "\n\nAre You Sure to Update this user?? [Y:N] : ";
			cin >> UpdateUser;
			if (UpdateUser == 'y' || UpdateUser == 'Y') {
				cout << "\nEnter Password        : ";
				getline(cin >> ws, userData.password);
				userData.permissions = funcPermissionsCounter();
				funcSaveUsersDataToFile(usersFileName, vUserData);
				cout << "\nUser Updated Successfully.\n";

			}
		}

	}
	if (!found) {
		cout << "\nUser With [" << userName << "] is NOT Found\n";
	}


}


void funcFindUser(string userName, vector<stUsersData>& vUserData, stUsersData& userData) {

	bool found = false;
	for (stUsersData& c : vUserData) {
		if (userName == c.userName) {

			cout << "\n\n";
			cout << "The Following are the user details\n";
			cout << "------------------------------------\n";
			cout << "Username     :  " << c.userName << endl;
			cout << "Password     : " << c.password << endl;
			cout << "Permissions  : " << c.permissions << endl;
			cout << "------------------------------------\n";
			userData = c;
			found = true;
			break;
		}

	}
	if (!found) {
		cout << "\nUser With [" << userName << "] is NOT Found\n";
	}
}


void funcPerformUserMenuOption(short choice) {

	while (true) {
		switch (choice) {

		case 1: {
			system("cls");
			vector<stUsersData> vUserData = funcLoadUsersDataFromFile(usersFileName);
			funcPrintAllUsersList(vUserData);
			cout << "\nPress Any Key To Go Back To Transactions ...";
			system("pause >0");
		} break;

		case 2: {
			char choice = 'y';
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tAdd New User Screen \n";
			cout << "-------------------------------------------------\n";
			string line = "";
			cout << "\n\nAdding New User :\n";
			cout << "-----------------\n";

			string username;

			do {
				vector<stUsersData> vUserData = funcLoadUsersDataFromFile(usersFileName);
				stUsersData userData = funcAddNewUser(vUserData);
				vUserData.push_back(userData);
				funcSaveUsersDataToFile(usersFileName, vUserData);

				cout << "\nUser Added Successfuly\n";
				cout << "Do You Want To Add More Users?? [Y:N] : ";
				cin >> choice;
			} while (choice == 'Y' || choice == 'y');

			cout << "\nPress Any Key To Go Back To Transactions ...";
			system("pause>0");
		} break;

		case 3: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tDelete Users Screen \n";
			cout << "-------------------------------------------------\n";
			vector<stUsersData> vUserData = funcLoadUsersDataFromFile(usersFileName);
			string userName = funcReadUserName();
			funcDeleteUserByUserName(userName, vUserData);
			cout << "\nPress Any Key To Go Back To Transactions ...";
			system("pause>0");
		} break;

		case 4: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tUpdate Clients Screen \n";
			cout << "-------------------------------------------------\n";
			vector <stUsersData> vUserData = funcLoadUsersDataFromFile(usersFileName);
			string userName = funcReadUserName();
			funcUpdateUserByUserName(userName, vUserData);
			cout << "\nPress Any Key To Go Back To Transactions ...";
			system("pause>0");

		} break;

		case 5: {
			system("cls");
			cout << "\n-------------------------------------------------\n";
			cout << "\t\tFind Users Screen \n";
			cout << "-------------------------------------------------\n";

			vector <stUsersData> vUserData = funcLoadUsersDataFromFile(usersFileName);
			string userName = funcReadUserName();
			stUsersData userData;
			funcFindUser(userName, vUserData, userData);
			cout << "\nPress Any Key To Go Back To Transactions ...";
			system("pause>0");
		} break;

		case 6: {

			return;
		} break;

		}
		system("cls");
		choice = funcShowManageUsersMenuScreen();
	}

}


void funcFirstScreen() {

	while (true) {
		funcLoginScreen();
		funcPerfromMainMenueOption(funcShowMainMenu());
	}
}



int main() {

	funcFirstScreen();
}
