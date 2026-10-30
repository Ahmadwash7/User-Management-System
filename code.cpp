#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

const string ClientsFile = "Clients.txt";
const string UsersFile = "Users.txt";

enum enMenuList
{
    ShowClient = 1, 
    AddClient = 2, 
    DeleteClient = 3, 
    UpdateClient = 4, 
    FindClient = 5,
    Transactions = 6,
    ManageUser = 7,
    Logout = 8
};

enum enTransactions
{
    Deposit = 1, 
    Withdraw = 2, 
    TotalBalances = 3, 
    MainMenue = 4, 
};

enum enMangeUsers
{
    eListUsers = 1,
    eAddNewUsers = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenueManage = 6
};

enum enMainMenuePermissions
{

    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

struct stUsers
{
    string userName;
    string password;
    short Permissions = 0;
    bool MarkForDelete = false;
};

int ReadNumber();

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std ::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

stClient ConvertLinetoRecord(string Line, string Separator = "#//#")
{
    stClient Client;

    vector<string> vClient;

    vClient = SplitString(Line, Separator);


    if (vClient.size() != 5)
    {
        return Client;
    }

    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.PhoneNumber = vClient[3];
    Client.AccountBalance = stod(vClient[4]);

    return Client;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
    vector<stClient> vClient;

    fstream MyFile;

    MyFile.open(FileName, ios ::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClient.push_back(Client);
        }

        MyFile.close();
    }

    return vClient;
}

void PrintClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(13) << left << Client.PhoneNumber;
    cout << "| " << setw(13) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector<stClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(13) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (stClient Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

stClient ReadClientData(string AccountNumber)
{
    stClient ReadData;

    ReadData.AccountNumber = AccountNumber;

    cout << "Enter PinCode: ";
    getline(cin >> ws,ReadData.PinCode);

    cout << "Enter Name: ";
    getline(cin, ReadData.Name);

    cout << "Enter Phone: ";
    getline(cin, ReadData.PhoneNumber);

    cout << "Enter Account Balance: ";
    cin >> ReadData.AccountBalance;

    return ReadData;
}

string ConvertRecordToLine(stClient Client, string Separator = "#//#")
{
    string S1 = "";

    S1 += Client.AccountNumber + Separator;
    S1 += Client.PinCode + Separator;
    S1 += Client.Name + Separator;
    S1 += Client.PhoneNumber + Separator;
    S1 += to_string(Client.AccountBalance) + Separator;

    return S1;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile2;

    MyFile2.open(FileName, ios::out | ios::app);

    if (MyFile2.is_open())
    {
        MyFile2 << stDataLine << endl;

        MyFile2.close();
    }
}

bool IsClientExist(string AccountNumber, vector<stClient>& vClient)
{
    vClient = LoadClientsDataFromFile(ClientsFile);

    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            return true;
        }
    }
    return false;
}

void AddNewClient()
{
    vector<stClient> vClient;
    stClient Client;

    char AddMore = 'n';

    do
    {
        cout << "------------------------------------" << endl;
        cout <<"\t   Add New Client " << endl;
        cout << "------------------------------------" << endl;
    
        while (true)
        {
            cout << "\nEnter Account Number: ";

            cin >> Client.AccountNumber;
    
            if (IsClientExist(Client.AccountNumber, vClient))
            {
                cout << "\nClient with [" << Client.AccountNumber << "] Already Exists, Enter Another Account Number" << endl;
            }
            else
            {
                break;
            }
        }

        Client = ReadClientData(Client.AccountNumber);
    
        AddDataLineToFile(ClientsFile, ConvertRecordToLine(Client));
    
        cout << "\nClient Added Successfully, Do You Want To Add More Clients? (Y/N:):- ";
        cin >> AddMore;

        if(toupper(AddMore) == 'Y')
        {
            system("clear");
        }
    
    }while (toupper(AddMore) == 'Y');
    
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "Please Enter Account Number: ";
    cin >> AccountNumber;
    return AccountNumber;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:" << endl;

    cout << "--------------------------------------" << endl;
    cout << "Accout Number: "<< Client.AccountNumber << endl;
    cout << "Name         : "<< Client.Name << endl;
    cout << "Pin Code     : "<< Client.PinCode << endl;
    cout << "Phone        : "<<Client.PhoneNumber << endl;
    cout << "Balance      : "<< Client.AccountBalance << endl;
    cout << "--------------------------------------" << endl;
}

bool FindClientByAccountNumber(string& AccountNumber, stClient &Client, vector<stClient> &vClient)
{
    vClient = LoadClientsDataFromFile(ClientsFile);

    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void FindClientPrint(string &AccountNumber, stClient &Client)
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFile);
    
    cout << "------------------------------------" << endl;
    cout <<"\t   Find Client " << endl;
    cout << "------------------------------------\n" << endl;
    
    AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);
    }    
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber <<") is Not Found!" << endl;
    }    
} 

bool MarkClientForDelete(string& AccountNumber, vector <stClient>& vClient)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <stClient> SaveClientDataToFile(string FileName, vector<stClient> vClient)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out); //overwrite
    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient C : vClient)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClient;
}

bool DeleteClientByAccountNumber(string& AccountNumber, vector<stClient> &vClient)
{
    stClient Client;
    char Answer = 'n';

    cout << "------------------------------------" << endl;
    cout <<"\t   Delete Client" << endl;
    cout << "------------------------------------\n" << endl;

    AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to delete this client? (Y/N:):- ";
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            MarkClientForDelete(AccountNumber, vClient);
            SaveClientDataToFile(ClientsFile, vClient);
            vClient = LoadClientsDataFromFile(ClientsFile);

            cout << "\nClient Deleted Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!" << endl;
    }
    return false;
}

bool UpdateClientByAccountNumber(string& AccountNumber, vector<stClient> &vClient)
{
    stClient Client;
    char Answer = 'n';

    cout << "------------------------------------" << endl;
    cout <<"\t   Update Cilent" << endl;
    cout << "------------------------------------\n" << endl;

    AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to update this client? (Y/N:):- ";
        cin >> Answer;
        
        cout << endl;

        if (toupper(Answer) == 'Y')
        {
            for (stClient & C : vClient)
            {
                if(C.AccountNumber == AccountNumber)
                {
                    C = ReadClientData(AccountNumber);
                    break;
                }
            }

            SaveClientDataToFile(ClientsFile, vClient);
            cout << "\nClient update Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!" << endl;
    }
    return false;
}

bool CheckAmountDeposit(int Amount)
{
    if (Amount <= 0)
    {
        cout << "\nInvalid Deposit Amount!" << endl;
        return false;
    }
    return true;
}

bool DepositFunction(string& AccountNumber, vector<stClient>& vClient)
{
    stClient Client;
    char Answer = 'n';

    double depositAmount = 0;

    cout << "------------------------------------" << endl;
    cout << "\t   Deposit" << endl;
    cout << "------------------------------------\n" << endl;

    AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);

        while (true)
        {
            cout << "\nPlease Enter deposit amount: ";
            depositAmount = ReadNumber();

            if (CheckAmountDeposit(depositAmount))
            {
                cout << "\nAre you sure you want perform this transaction? (Y/N):- ";
                cin >> Answer;
                cout << endl;

                if (toupper(Answer) == 'Y')
                {
                    for (stClient& C : vClient)
                    {
                        if (C.AccountNumber == AccountNumber)
                        {
                            C.AccountBalance += depositAmount;

                            cout << "Done Successfully. New Balance [" << C.AccountBalance << "]" << endl;
                            SaveClientDataToFile(ClientsFile, vClient);
                            return true;
                        }
                    }
                }
                else
                {
                    cout << "Transaction Cancelled." << endl;
                    return false;
                }
            }
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;

    }
    return false;
}

bool CheckAmountWithdraw(int Amount, stClient Client)
{
    if (Amount <= 0)
    {
        cout << "\nInvalid Withdraw Amount!" << endl;
        return false;
    }
    else if(Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can Withdraw up to : " << Client.AccountBalance << endl;
        return false;
    }

    return true;
}

bool WithdrawFunction(string& AccountNumber, vector<stClient> &vClient)
{   
    stClient Client;
    char Answer = 'n';

    int WithdrawAmount = 0;

    cout << "------------------------------------" << endl;
    cout <<"\t   Withdraw" << endl;
    cout << "------------------------------------\n" << endl; 
    
    AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);
    
        while (true)
        {
            cout << "\nPlease Enter Withdraw amount: ";
            WithdrawAmount = ReadNumber();
          
            if (CheckAmountWithdraw(WithdrawAmount, Client))
            {
                cout << "\nAre you sure you want to perform this transaction? (Y/N):- ";
                cin >> Answer;
                cout << endl;
        
                if (toupper(Answer) == 'Y')
                {
                    for (stClient & C : vClient)
                    {
                        if(C.AccountNumber == AccountNumber)
                        {
                            C.AccountBalance -= WithdrawAmount;
                            
                            SaveClientDataToFile(ClientsFile, vClient);
                            cout << "Done Successfully. New Balance [" << C.AccountBalance << "]" << endl;
                            return true;
                        }
                    }
                }
                else
                {
                    cout << "Transaction Cancelled." << endl; 
                    return false; 
                }
            }
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!" << endl;
    }
    return false;
}

void PrintClientsBalce(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(13) << left << Client.AccountBalance;
}

void PrintAllBalances(vector<stClient> vClients)
{
    double Balances = 0;

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (stClient Client : vClients)
        {
            PrintClientsBalce(Client);

            Balances += Client.AccountBalance;
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout <<"\t\t\t\t   Total Balances: " << Balances << endl;
}

void TotallBalances()
{
    vector<stClient> vClients;
    vClients =  LoadClientsDataFromFile(ClientsFile);

    PrintAllBalances(vClients);
}

int ReadNumber()
{
    int Number;

    while (!(cin >> Number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid input, please enter a number: ";
    }
    return Number;
}

void ShowMenu()
{
    cout << "===========================================" << endl;
    cout <<"\t     Main Menu Screen" << endl;
    cout << "===========================================" << endl;
    
    cout << "\t [1] Show Client List." << endl;
    cout << "\t [2] Add New Client." << endl;
    cout << "\t [3] Delete Client." << endl;
    cout << "\t [4] Update Client Info." << endl;
    cout << "\t [5] Find Client." << endl;
    cout << "\t [6] Transactions." << endl;
    cout << "\t [7] Manage User." << endl;
    cout << "\t [8] Logout." << endl;
    
    cout << "===========================================" << endl;
}

void ShowTransactionsMenu()
{
    cout << "===========================================" << endl;
    cout <<"\t      Transactions Menu Screen" << endl;
    cout << "===========================================" << endl;

    cout << "\t [1] Deposit." << endl;
    cout << "\t [2] Withdraw." << endl;
    cout << "\t [3] Total Balances." << endl;
    cout << "\t [4] Main Menu." << endl;
    
    cout << "===========================================" << endl;
}

void ShowManageUserMenu()
{
    cout << "===========================================" << endl;
    cout <<"\t Manage Users Menu Screen" << endl;
    cout << "===========================================" << endl;

    cout << "\t [1] List Users." << endl;
    cout << "\t [2] Add New User." << endl;
    cout << "\t [3] Delete User." << endl;
    cout << "\t [4] Update User." << endl;
    cout << "\t [5] Find User." << endl;
    cout << "\t [6] Main Menu." << endl;
    
    cout << "===========================================" << endl;
}

stUsers ConvertLinetoRecordUsers(string Line, string Separator = "#//#")
{
    stUsers Users;

    vector<string> vUsers;

    vUsers = SplitString(Line, Separator);


    if (vUsers.size() != 3)
    {
        return Users;
    }

    Users.userName = vUsers[0];
    Users.password = vUsers[1];
    Users.Permissions = stod(vUsers[2]);


    return Users;
}

vector<stUsers> LoadUsersDataFromFile(string FileName)
{
    vector<stUsers> vUsers;

    fstream MyFile;

    MyFile.open(FileName, ios ::in);

    if (MyFile.is_open())
    {
        string Line;
        stUsers Users;

        while (getline(MyFile, Line))
        {
            Users = ConvertLinetoRecordUsers(Line);
            vUsers.push_back(Users);
        }
        
        MyFile.close();
    }
    
    return vUsers;
}

string ConvertRecordToLineUsers(stUsers User, string Separator = "#//#")
{
    string S1 = "";

    S1 += User.userName + Separator;
    S1 += User.password + Separator;
    S1 += to_string(User.Permissions) + Separator;

    return S1;
}

vector <stUsers> SaveUsersDataToFile(string FileName, vector<stUsers> vUsers)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out); //overwrite
    string DataLine;

    if (MyFile.is_open())
    {
        for (stUsers U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLineUsers(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

void LoginScreen()
{
    cout << "===========================================" << endl;
    cout <<"\t      Login" << endl;
    cout << "===========================================" << endl; 
}

bool LoginUsersCheck(stUsers& User, vector<stUsers>& vUsers)
{
    for (stUsers& C : vUsers)
    {
        if (C.userName == User.userName && C.password == User.password)
        {
            User = C;
            return true;
        }
    }
    return false;
}

bool LoginUser(stUsers& User, vector<stUsers>& vUsers)
{
    while (true)
    {
        cout << "Enter UserName: ";
        cin >> User.userName;

        cout << "Enter Password: ";
        cin >> User.password;

        if (LoginUsersCheck(User, vUsers))
        {
            return true;
        }
        else
        {
            system("clear");
            LoginScreen();
            cout << "Invalid UserName/Password!" << endl;
        }
    }
    return false;
}

void PrintUsersRecord(stUsers User)
{
    cout << "| " << setw(15) << left << User.userName;
    cout << "| " << setw(10) << left << User.password;

    string Permissions = to_string(User.Permissions);
    cout << "| " << left << setw(10) << (Permissions.length() == 1 ? " " + Permissions : Permissions);
}

void PrintAllUsersData(vector<stUsers> vUsers)
{
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ")User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(10) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
    {
        cout << "\t\t\t\tNo Users Available In the System!";
    }
    else
    {
        for (stUsers Users : vUsers)
        {
            PrintUsersRecord(Users);
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void AddNewUserScreen()
{
    cout << "===========================================" << endl;
    cout <<"\t      Add New User" << endl;
    cout << "===========================================" << endl;
    cout << "Adding New User: \n" << endl;
}

bool CheckUserFind(string &UserName, vector<stUsers> &vUsers, stUsers& User)
{
    for (stUsers& C : vUsers)
    {           
        if (C.userName == UserName)
        {
            User = C;
            return true;
        }
    }

    return false;
}

short ReadPermissionsToSet()
{
    short Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to:\n";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') 
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }

    return Permissions;
}

bool AddNewUser(stUsers Users, vector<stUsers> vUsers)
{
    vUsers = LoadUsersDataFromFile(UsersFile);
    char AddMore = 'n';

    do
    {
        while(true)
        {
            cout << "\nEnter UserName: ";
            cin >> Users.userName;

            if (CheckUserFind(Users.userName, vUsers, Users))
            {
                cout << "\nUser With [" << Users.userName << "] Already exists, Enter Another UserName: " << endl;
            }
            else
            {
                break;
            }
        }
        
        cout << "Enter Password: ";
        cin >> Users.password;
        Users.Permissions = ReadPermissionsToSet(); 

        AddDataLineToFile(UsersFile, ConvertRecordToLineUsers(Users));

        cout << "\nUser Added Successfully, Do You Want To Add More Users? (Y/N:):- ";
        cin >> AddMore;
        
        if(toupper(AddMore) == 'Y')
        {
            system("clear");
            AddNewUserScreen();
        }
            
    } while (toupper(AddMore) == 'Y');

    return true;
} 

bool CheckPermissions(stUsers User, short RequiredPermission)
{
    if (User.Permissions == -1)
        return true;

    return (User.Permissions & RequiredPermission) == RequiredPermission;
}

void AccessDeniedScreen()
{
    cout << "--------------------------------------" << endl;
    cout << "Access Denied!" << endl;
    cout << "You Do Not Have Permission To Do This." << endl;
    cout << "Please Contact Your Admin." << endl;
    cout << "--------------------------------------" << endl;
}

void DeleteUsersScreen()
{
    cout << "===========================================" << endl;
    cout <<"\t      Delete User" << endl;
    cout << "===========================================" << endl;
}
 
void PrintUserCard(stUsers Users)
{

    cout << "\nThe following are the User details:" << endl;

    cout << "--------------------------------------" << endl;
    cout << "Username: "<< Users.userName << endl;
    cout << "Password: "<< Users.password << endl;
    cout << "Permissions: "<< Users.Permissions << endl;
    cout << "--------------------------------------" << endl;
}

bool MarkUserForDelete(string &Username, vector <stUsers> &vUsers)
{
    for (stUsers& C : vUsers)
    {
        if (C.userName == Username)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool DeleteUser(string &Username, vector <stUsers> &vUsers)
{
    stUsers User;
    vUsers = LoadUsersDataFromFile(UsersFile);

    char Answer = 'n';

    cout << "Enter Username: ";
    cin >> User.userName;

    if (CheckUserFind(User.userName, vUsers, User))
    {
        PrintUserCard(User);

        cout << "\nAre you sure you want to delete this Users? (Y/N:):- ";
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            MarkUserForDelete(User.userName, vUsers);
            SaveUsersDataToFile(UsersFile, vUsers);
            vUsers = LoadUsersDataFromFile(UsersFile);

            cout << "\nUser Deleted Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << User.userName << ") is Not Found!" << endl;
    }
    return false;
}

void UpdateUserScreen()
{
    cout << "===========================================" << endl;
    cout <<"\t      Update User" << endl;
    cout << "===========================================" << endl;
}

stUsers ReadUsersInfo(string Username)
{
    stUsers User;

    User.userName = Username;

    cout << "\nEnter Password: ";
    getline(cin >> ws, User.password);

    User.Permissions = ReadPermissionsToSet();

    return User;
}

bool UpdateUser(string &Username, vector <stUsers> &vUsers)
{
    stUsers User;
    vUsers = LoadUsersDataFromFile(UsersFile);

    char Answer = 'n';

    cout << "Enter Username: ";
    cin >> User.userName;

    if (CheckUserFind(User.userName, vUsers, User))
    {
        PrintUserCard(User);

        cout << "\nAre you sure you want to Update this Users? (Y/N:):- ";
        cin >> Answer;

        if(toupper(Answer) == 'Y')
        {
            for (stUsers &C : vUsers)
            {
                if (C.userName == User.userName)
                {
                    C = ReadUsersInfo(User.userName); 
                    break;
                } 
            }
            
            SaveUsersDataToFile(UsersFile, vUsers);
            cout << "\nUser Updated Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << User.userName << ") is Not Found!" << endl;
    }
    return false;
}

void FindUserScreen()
{
    cout << "===========================================" << endl;
    cout <<"\t      Find User" << endl;
    cout << "===========================================" << endl;
}

bool FindUser(stUsers &User, vector <stUsers> &vUsers)
{
    vUsers = LoadUsersDataFromFile(UsersFile);

    cout << "Enter Username: ";
    cin >> User.userName;

    if (CheckUserFind(User.userName, vUsers, User))
    {
        PrintUserCard(User);
        return true;
    }
    else
    {
        cout << "\nUser with Username (" << User.userName << ") is Not Found!" << endl;
    }
    return false;

}

void AddNewUsers(stUsers Users, vector<stUsers> vUsers)
{
    AddNewUserScreen();
    AddNewUser(Users, vUsers);
}

void DeleteUsers(string Username, vector<stUsers> vUsers)
{
    DeleteUsersScreen();
    DeleteUser(Username, vUsers);
}

void UpdateUsers(string Username, vector<stUsers> vUsers)
{
    UpdateUserScreen();
    UpdateUser(Username, vUsers);
}

void FindUsers(stUsers Users, vector<stUsers> vUsers)
{
    FindUserScreen();
    FindUser(Users, vUsers);
}

enMenuList ReadMenuList(short& MenuList)
{
    do
    {
        cout << "Choose What do You want To Do [1 To 8]: ";
        MenuList = ReadNumber();

    } while(MenuList < 1 || MenuList > 8);

    return (enMenuList)MenuList;
}

enTransactions TransactionsList(short& TransactionsMenu)
{
    do 
    {
        cout << "Choose What do You want To Do [1 To 4]: ";
        TransactionsMenu = ReadNumber();

    } while(TransactionsMenu < 1 || TransactionsMenu > 4);

    return (enTransactions)TransactionsMenu;
}

enMangeUsers ManageUserList(short& ManageUserMenu)
{
    do 
    {
        cout << "Choose What do You want To Do [1 To 6]: ";
        ManageUserMenu = ReadNumber();

    } while(ManageUserMenu < 1 || ManageUserMenu > 6);

    return (enMangeUsers)ManageUserMenu;
}

void GoBackToManageUserMenu()
{
    cout << "\nPress any key to go back to Manage Users Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    system("clear");
}

void GoBackToTransactionsMenu()
{
    cout << "\nPress any key to go back to Transactions Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    system("clear");
}

void GoBackToMenu()
{
    cout << "\nPress any key to go back to Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    system("clear");
}

void ManageUserMenuList(short& ManageUserMenu)
{
    string Username;
    stUsers Users;
    vector<stUsers> vUsers;

    do
    {
        system("clear");
        ShowManageUserMenu();

        ManageUserList(ManageUserMenu);

        switch(ManageUserMenu)
        {
            case eListUsers:

                system("clear");

                vUsers = LoadUsersDataFromFile(UsersFile);
                PrintAllUsersData(vUsers);
                GoBackToManageUserMenu();

                break;

            case eAddNewUsers:

                system("clear");
                AddNewUsers(Users, vUsers);
                GoBackToManageUserMenu();

                break;

            case eDeleteUser:

                system("clear");
                DeleteUsers(Username, vUsers);
                GoBackToManageUserMenu();

                break;

            case eUpdateUser:

                system("clear");
                UpdateUsers(Username, vUsers);
                GoBackToManageUserMenu();
                
                break;

            case eFindUser:

                system("clear");
                FindUsers(Users, vUsers);
                GoBackToManageUserMenu();

                break;

            case eMainMenueManage:

                system("clear");
                break;        
        }

    } while (ManageUserMenu != eMainMenueManage);
}

void TransactionsMenuList(short& TransactionsMenu)
{
    string AccountNumber;
    vector<stClient> vClient;
    stClient Client;

    do
    {
        system("clear");

        ShowTransactionsMenu();
        TransactionsList(TransactionsMenu);

        switch(TransactionsMenu)
        {
            case Deposit:

                system("clear");
                DepositFunction(AccountNumber, vClient);
                GoBackToTransactionsMenu();

                break;


            case Withdraw:

                system("clear");

                WithdrawFunction(AccountNumber, vClient);
                GoBackToTransactionsMenu();

                break;

            case TotalBalances:

                system("clear");

                TotallBalances();
                GoBackToTransactionsMenu();

                break;

            case MainMenue:

                system("clear");
                break;
        }

    } while (TransactionsMenu != MainMenue);
}

void Login();

void ChoosMenuList(short MenuList, stUsers User)
{
    string AccountNumber;
    vector<stClient> vClient;
    stClient Client;

    do
    {
        system("clear");

        ShowMenu();
        ReadMenuList(MenuList);

        switch (MenuList)
        {
            case ShowClient:

                system("clear");

                if(CheckPermissions(User, 1))
                {
                    vClient = LoadClientsDataFromFile(ClientsFile);
                    PrintAllClientsData(vClient);
                }
                else
                {
                    AccessDeniedScreen();
                }

                GoBackToMenu();
                break;

            case AddClient:

                system("clear");

                if(CheckPermissions(User, 2))
                {
                    AddNewClient();
                }
                else
                {
                    AccessDeniedScreen();
                }

                GoBackToMenu();
                break;

            case DeleteClient:

                system("clear");

                if(CheckPermissions(User, 4))
                {
                    DeleteClientByAccountNumber(AccountNumber, vClient);
                }
                else
                {
                    AccessDeniedScreen();
                }

                GoBackToMenu();
                break;

            case UpdateClient:

                system("clear");

                if(CheckPermissions(User, 8))
                {
                    UpdateClientByAccountNumber(AccountNumber, vClient);
                }
                else
                {
                    AccessDeniedScreen();
                }

                GoBackToMenu();
                break;

            case FindClient:

                system("clear");

                if(CheckPermissions(User, 16))
                {
                    FindClientPrint(AccountNumber, Client);
                }
                else
                {
                    AccessDeniedScreen();
                }

                GoBackToMenu();
                break;

            case Transactions:
            {
                system("clear");
    
                if(CheckPermissions(User, 32))
                {
                    short TransactionsMenu = 0;
                    TransactionsMenuList(TransactionsMenu);
                }
                else
                {
                    AccessDeniedScreen();
                    GoBackToMenu();
                }

                break;
            }

            case ManageUser:
            {
                system("clear");

                if(CheckPermissions(User, 64))
                {
                    short ManageUsers = 0;
                    ManageUserMenuList(ManageUsers);
                }
                else
                {
                    AccessDeniedScreen();
                    GoBackToMenu();
                }

                break;
            }

            case Logout:

                Login();
                return;
        }

    } while (MenuList != Logout);

}

void Login()
{
    short MenuList = 0;
    stUsers User;
    vector<stUsers> vUsers;

    vUsers = LoadUsersDataFromFile(UsersFile);

    system("clear");
    LoginScreen();

    if(LoginUser(User, vUsers))
    {
        ChoosMenuList(MenuList, User);
    }
}

int main()
{
    Login();

    return 0;
}