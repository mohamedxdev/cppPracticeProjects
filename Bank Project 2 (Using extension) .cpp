#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientFileName = "Clients.txt";
void ShowMainMenu();
void ShowTransactionsMenuScreen();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector <string> Vstring;
	string sword = "";
	short pos = 0;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sword = S1.substr(0, pos);
		if (sword != "")
		{
			Vstring.push_back(sword);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		Vstring.push_back(S1);
	}
	return Vstring;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> stClientData = SplitString(Line, Seperator);

	Client.AccountNumber = stClientData[0];
	Client.PinCode = stClientData[1];
	Client.Name = stClientData[2];
	Client.Phone = stClientData[3];
	Client.AccountBalance = stod(stClientData[4]);

	return Client;
}

string ConvertRecordToLine(sClient Client, string Sperator = "#//#")
{
	string stClientToRecord = "";

	stClientToRecord += Client.AccountNumber + Sperator;
	stClientToRecord += Client.PinCode + Sperator;
	stClientToRecord += Client.Name + Sperator;
	stClientToRecord += Client.Phone + Sperator;
	stClientToRecord += to_string(Client.AccountBalance);

	return stClientToRecord;


}

vector<sClient> LoadClientDataFromFile(string FileName)
{
	vector<sClient> VClients;
	fstream Myfile;
	Myfile.open(FileName, ios::in);
	if (Myfile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(Myfile,Line))
		{
			Client = ConvertLineToRecord(Line);
			VClients.push_back(Client);
		}
		Myfile.close();
	}
	return VClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}





bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector<sClient> VClients;
	fstream Myfile;
	Myfile.open(FileName, ios::in);
	if (Myfile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(Myfile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				Myfile.close();
				return true;
			}
			VClients.push_back(Client);
		}
		Myfile.close();
	}
	return false;
}
sClient ReadNewCLient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);
	
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << stDataLine << endl;
		Myfile.close();
	}
}
void AddNewClient()
{
	sClient Client;
	Client = ReadNewCLient();
	AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}
void AddClients()
{
	char Answer = 'Y';

	do {
		cout << "Adding New Client:\n";
		AddNewClient();
		cout << "Client Added Successfully Do you want to add more Clients? Y/n? ";
		cin >> Answer;
	} while (toupper(Answer == 'Y'));
}




string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\nPLease enter AccountNumber? ";
	cin >> AccountNumber;

	return AccountNumber;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> VClients, sClient &Client)
{
	

	for (sClient C : VClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "--------------------------------------\n";
	cout << "\nAccountNumber  : " << Client.AccountNumber;
	cout << "\nPinCode        : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccountBalance : " << Client.AccountBalance;
	cout << "\n--------------------------------------\n";	
}






bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& VClients)
{
	for (sClient &C : VClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> VClients)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out);
	string DataLine;
	if (Myfile.is_open())
	{
		for (sClient C : VClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				Myfile << DataLine << endl;
			}
			
		}
		Myfile.close();
	}
	return VClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &VClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, VClients,Client))
	{
		PrintClientCard(Client);
		cout << "\nAre you sure you want to Delete this Client? ";
		cin >> Answer;
		
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, VClients);
			SaveCleintsDataToFile(ClientFileName, VClients);

			VClients = LoadClientDataFromFile(ClientFileName);

			cout << "\nClient Deleted Succssfully.";
			return true;
		}

	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!";
		return false;
	}

}



sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Name? ";
	getline(cin, Client.Name);

	cout << "Phone? ";
	getline(cin, Client.Phone);

	cout << "AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> VClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, VClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this Client y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : VClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientFileName, VClients);
			cout << "\nClient Updated Successfully.";
			return true;
		}


	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!";
		return false;
	}
}



bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &VClients)
{
	char Answer = 'n';

	cout << "\nAre you sure you want perform this Transaction? y/n? ";
	cin >> Answer;

	while (Answer == 'Y' || Answer == 'y')
	{
		for (sClient& C : VClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientFileName, VClients);
				cout << "\n\nAdded Successfully. New Balance is: " << C.AccountBalance;
				
				return true;
			}
		}
		return false;
	}

}


void ShowTotalBalances()
{
	double TotalBalance = 0;
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	cout << "\n\t\t\tClient List (" << VClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (VClients.size() == 0)
	{
		cout << "\t\t\tNo Clients Available In the system!";
	}
	else {
		for (sClient C : VClients)
		{
			PrintClientRecordLine(C);
			TotalBalance += C.AccountBalance;
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t\t\tTotal Balances = " << TotalBalance;
	}


}

void ShowWithdrawScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Deposit Screen\n";
	cout << "\n-------------------------------------\n";
	sClient Client;
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumber = ReadAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, VClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter Withdraw Amount? ";
	cin >> Amount;
	
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance;
		cout << "\nPlease enter Withdraw Amount? ";
		cin >> Amount;

	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount *-1, VClients);
}

void ShowTotalBalanceScreen()
{
	ShowTotalBalances();
}

void ShowDepositScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Deposit Screen\n";
	cout << "\n-------------------------------------\n";
	sClient Client;
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumber = ReadAccountNumber();
	
	while (!FindClientByAccountNumber(AccountNumber, VClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit Amount? ";
	cin >> Amount;
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, VClients);
}

void ShowUpdateClientInfoScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Update Client Info Screen\n";
	cout << "\n-------------------------------------\n";
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, VClients);

}

void ShowDeleteClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Delete Client Screen\n";
	cout << "\n-------------------------------------\n";
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, VClients);


}

void showFindClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Find Client Screen\n";
	cout << "\n-------------------------------------\n";
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	if (FindClientByAccountNumber(AccountNumber,VClients,Client))
	{
		PrintClientCard(Client);
	}
	else {
		cout << "\nClient with AccountNumber (" << AccountNumber << ") Not Found!";
	}
}

void ShowAddNewClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\t Add New Client Screen\n";
	cout << "\n-------------------------------------\n";
	AddClients();

}

void ShowAllClientList()
{
	vector<sClient> VClients = LoadClientDataFromFile(ClientFileName);
	cout << "\n\t\t\tClient List (" << VClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (VClients.size() == 0)
	{
		cout << "\t\t\tNo Clients Available In the system!";
	}
	else {
		for (sClient C : VClients)
		{
			PrintClientRecordLine(C);
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}


}

void ShowEndScreen()
{
	cout << "\n============================================\n";
	cout << "\t\tProgram Ends :-)\n";
	cout << "\n============================================\n";
	
}

void GoBackToMainMenu()
{
	cout << "\n\nPress Any Key To Go Back To Main Menue. . .";
	system("pause>0");
	ShowMainMenu();
}
void GoBackToTransactionsMainMenu()
{
	cout << "\n\nPress Any Key To Go Back To Transactions Main Menu . .";
	system("pause>0");
	ShowTransactionsMenuScreen();
}

enum enMainMenu {
	eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eExit = 7
};
enum enTransactionsMenueOptions {
	eDepositList = 1, eWithDrawList = 2, eTotalBalance = 3, eMainMenu = 4
};

short ReadMainMenuOption()
{
	short Choice;
	cout << "Choose what do want to do? [1 to 7] ";
	cin >> Choice;
	return Choice;
}

short ReadTrasactionOption()
{
	short Choice;
	cout << "Choose what do want to do? [1 to 4] ";
	cin >> Choice;
	return Choice;

}

void PerformMainMenuChoice(enMainMenu MainMenu)
{
	switch (MainMenu)
	{
	case enMainMenu::eShowClientList:
	{
		system("cls");
		ShowAllClientList();
		GoBackToMainMenu();
		system("pause");
		break;
	}
	case enMainMenu::eAddNewClient:
	{
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenu();
		system("pause");
		break;

	}
	case enMainMenu::eDeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		system("pause");
		break;

	}
	case enMainMenu::eUpdateClient:
	{
		system("cls");
		ShowUpdateClientInfoScreen();
		GoBackToMainMenu();
		system("pause");
		break;
	}
	case enMainMenu::eFindClient:
	{
		system("cls");
		showFindClientScreen();
		GoBackToMainMenu();
		system("pause");
		break;

	}
	case enMainMenu::eTransactions:
	{
		system("cls");
		ShowTransactionsMenuScreen();
		system("pause");
		break;
	}
	case enMainMenu::eExit:
	{
		system("cls");
		ShowEndScreen();
		break;
		
	}
	}
}
void PerformTransactionsChoice(enTransactionsMenueOptions TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionsMenueOptions::eDepositList:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMainMenu();
		break;
	}
	case enTransactionsMenueOptions::eWithDrawList:
	{
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMainMenu();
		break;
	}
	case enTransactionsMenueOptions::eTotalBalance:
	{
		system("cls");
		ShowTotalBalanceScreen();
		GoBackToTransactionsMainMenu();
		break;
	}
	case enTransactionsMenueOptions::eMainMenu:
	{
		ShowMainMenu();
	}
	}
}

void ShowTransactionsMenuScreen()
{
	system("cls");
	cout << "============================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "============================================\n";
	PerformTransactionsChoice((enTransactionsMenueOptions)ReadTrasactionOption());


}
void ShowMainMenu()
{
	system("cls");
	cout << "============================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "============================================\n";

	PerformMainMenuChoice((enMainMenu)ReadMainMenuOption());
}



int main()
{
	ShowMainMenu();
	system("pause>0");
	return 0;

}