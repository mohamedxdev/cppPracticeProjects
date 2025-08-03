#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

const string ClientFileName = "Clients.txt";

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
enum enTransactionsMenueOptions {
	eQuickDraw = 1, eNormalDraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5
};

sClient CurrentClient;

void ShowATMenuScreen();
void ShowDepositScreen();
void ShowNormalWithDrawScreen();
void ShowQuickWithDrawScreen();
void Login();


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
vector<sClient> LoadClientDataFromFile(string FileName)
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
			VClients.push_back(Client);
		}
		Myfile.close();
	}
	return VClients;
}
bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient &CurrentClient)
{
	vector<sClient> VClient = LoadClientDataFromFile(ClientFileName);

	for (sClient C : VClient)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			CurrentClient = C;
			return true;
		}
	}
	return false;
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
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& VClients)
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
				cout << "\n\Done Succussfly. New Balance is: " << C.AccountBalance;

				return true;
			}
		}
		return false;
	}

}



double ReadDepositAmount()
{
	double Amount;
	cout << "\nEnter a positve Deposit Amount? ";
	cin >> Amount;

	while (Amount < 0)
	{
		cout << "Please enter a positive Amount ";
		cin >> Amount;
	}

	return Amount;
		
}
void PerfromDepositOption()
{
	double DepositAmount = ReadDepositAmount();

	vector<sClient> vClient;
	vClient = LoadClientDataFromFile(ClientFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClient);
	CurrentClient.AccountBalance += DepositAmount;

	
}


int ReadWithDrawAmount()
{
	int Amount = 0;
	cout << "Enter an Amount multiple of 5's ? ";
	cin >> Amount;
	
	while (Amount % 5 != 0)
	{
		cout << "Enter an Amount multiple of 5's ? ";
		cin >> Amount;
	}
	return Amount;
}
void PerformWithDrawOptinon()
{
	int WithDrawAmount = ReadWithDrawAmount();
	
	if (WithDrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe Amount exceeds your balance, make another choice.\n";
		cout << "\nPress ay key to Continue ";
		system("pause>0");
		ShowNormalWithDrawScreen();
		return;
	}

	vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawAmount * -1, vClient);
	CurrentClient.AccountBalance -= WithDrawAmount;
	

}



short ReadQuickWithDraw()
{
	short Choice = 0;
	while (Choice < 1 || Choice>9)
	{
		cout << "\nChoose what to do from [1] to [9] ? ";
		cin >> Choice;
	}

	return Choice;
}
short GetQuickWithDrawOption(short QuickWithDrawOption)
{

	switch (QuickWithDrawOption)
	{
	case 1:
		return  20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;

	}

}
void PerfromQuickWithDrawOption(short QuickWithDrawOption)
{
	if (QuickWithDrawOption == 9)
		return;
	short WithDrawBalance = GetQuickWithDrawOption(QuickWithDrawOption);

	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe Amount exceeds your balance, make another choice.\n";
		cout << "\nPress ay key to Continue ";
		system("pause>0");
		ShowQuickWithDrawScreen();
		return;
	}
	vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
	CurrentClient.AccountBalance -= WithDrawBalance;


}

void ShowQuickWithDrawScreen()
{
	system("cls");
	cout << "============================================\n";
	cout << "\t\tQucik Withdraw\n";
	cout << "============================================\n";
	cout << "\t[1] 20  \t[2] 50\n";
	cout << "\t[3] 100 \t[4] 200\n";
	cout << "\t[5] 400 \t[6] 600\n";
	cout << "\t[7] 800 \t[8] 1000\n";
	cout << "\t[9] Exit";
	cout << "\n============================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << "\n";
	PerfromQuickWithDrawOption(ReadQuickWithDraw());

}
void ShowNormalWithDrawScreen()
{
	
	system("cls");
	cout << "============================================\n";
	cout << "\t\tNormal Draw Screen\n";
	cout << "============================================\n";
	PerformWithDrawOptinon();

}
void ShowDepositScreen()
{
	system("cls");
	cout << "============================================\n";
	cout << "\t\tDeposit Screen\n";
	cout << "============================================\n";
	PerfromDepositOption();
}
void ShowCheckBalanceScreen()
{

	
	system("cls");
	cout << "============================================\n";
	cout << "\t\Check Balance Screen\n";
	cout << "============================================\n";
	cout << "\nYour Balance is " << CurrentClient.AccountBalance;


}



void GoBackToMainMenu()
{
	cout << "\nPress ay key to go back to Main Menu... ";
	system("pause>0");
	ShowATMenuScreen();
}

short ReadTrasactionOption()
{
	short Choice;
	cout << "Choose what do you want to do? [1] to [5]?";
	cin >> Choice;

	return Choice;
}
void PerformTransactionsChoice(enTransactionsMenueOptions TransactionMenueOption) 
{

	switch (TransactionMenueOption)
	{
	case enTransactionsMenueOptions::eQuickDraw:
	{
		system("cls");
		ShowQuickWithDrawScreen();
		GoBackToMainMenu();
		break;
	}
	case enTransactionsMenueOptions::eNormalDraw:
	{
		system("cls");
		ShowNormalWithDrawScreen();
		GoBackToMainMenu();
		break;
	}
	case enTransactionsMenueOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenu();

		break;
	}
	case enTransactionsMenueOptions::eCheckBalance:
	{
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToMainMenu();
		break;
	}
	case enTransactionsMenueOptions::eLogout:
	{
		Login();
	}
	}
}

void ShowATMenuScreen()
{
	system("cls");
	cout << "============================================\n";
	cout << "\t\tATM Main Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] Quick Draw.\n";
	cout << "\t[2] Normal Draw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "============================================\n";

	PerformTransactionsChoice((enTransactionsMenueOptions)ReadTrasactionOption());

}



bool LoadClienInfo(string AccountNumber ,string PinCode)
{
	if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
		return true;
	else
		return false;
}
void Login()
{
	bool LoginFaild = false;
	string AccountNumber, PinCode;

	do {
		system("cls");

		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFaild)
		{
			cout << "Invlaid AccountNumber/PinCode!\n";

		}
		cout << "Enter AccountNumber? ";
		cin >> AccountNumber;
		cout << "Enter PinCode? ";
		cin >> PinCode;

		LoginFaild = !LoadClienInfo(AccountNumber, PinCode);
	} while (LoginFaild);

	ShowATMenuScreen();

}

int main()
{
	Login();

	system("pause>0");
}