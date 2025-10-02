#include <iostream>
#include "bank_customer.h"
#include "buyer.h"
#include <vector>
#include <string>
#include <algorithm> 
#include <limits>    // Untuk membersihkan buffer input (cin)

// --- SIMULASI KELAS (PENGGANTI BUYER/SELLER/BANKCUSTOMER) ---
struct Account {
    int id;
    std::string type; // "Buyer" atau "Seller"
    std::string name;
    std::string address;
    std::string phone;
    std::string email;
    // Saldo Bank disimulasikan sebagai string untuk kemudahan
    double balance; 
};

// Vektor global untuk menyimpan data akun (Simulasi Database)
std::vector<Account> accounts;

// Fungsi untuk membuat data dummy agar kita bisa menguji fungsi Admin
void initializeAccounts() {
    accounts.push_back({101, "Buyer", "Alice", "Jl. Mawar 1", "081234567890", "alice@mail.com", 1500.50});
    accounts.push_back({201, "Seller", "Bob's Store", "Jl. Kenanga 2", "089876543210", "bob@store.com", 5000.75});
    accounts.push_back({102, "Buyer", "Charlie", "Jl. Anggrek 3", "081122334455", "charlie@mail.com", 50.00});
}

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, ADMIN_LOGIN};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
using namespace std;

int main() {
    //create a loop prompt 
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;
    initializeAccounts(); // Inisialisasi data akun dummy

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                /* if Login is selected, based on authority then provide options:
                assume user is logged in as Buyer for now
                1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
                Will display Buyer, Seller and Banking Account details
                2. Upgrade Account to Seller
                Will prompt user to enter Seller details and create a Seller account linked to Buyer account
                Will reject if a user dont have a banking account linked
                3. Create Banking Account (if not already linked), will be replaced with banking functions
                Must provides: initial deposit amount, Address, Phone number, Email
                Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
                4. Browse Store Functionality
                Will display all stores initially
                Need to select a store to browse each store inventory
                Will display all items in the store inventory
                After selecting an item, will display item details and option to add to cart
                After adding to cart, will notify user item is added to cart
                5. Order Functionality
                Will display all items in cart
                Will provide option to remove item from cart
                Will provide option to checkout
                After checkout invoide will be generated (will go to payment functionality)
                6. Payment Functionality
                Will display all listed invoices
                Pick an invoice to pay
                Will display invoice details and total amount
                Will provide option to pay invoice
                Payment is done through confirmation dialogue
                In confirmation dialogue, will display account balance as precursor
                User will need to manually enter invoice id to pay
                After paying balance will be redacted from buyer and added to the responding seller account
                After payment, order status will be changed to paid
                7. Logout (return to main menu)
                Display confirmation dialogue
                If confirmed, return to main menu
                If not, return to Buyer menu
                8. Delete Account (remove both Buyer and Seller account and relevant banking account)
                Display confirmation dialogue
                If confirmed, delete account and return to main menu
                If not, return to Buyer menu

                assume user is logged in as Seller for now
                9. Check Inventory
                10. Add Item to Inventory
                11. Remove Item from Inventory
                12. View Orders (will display all orders placed to this seller
                Only orders with paid status will be listed
                Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
                extra functions
                9. Exit to main Menu
                10. Exit Program
                **/
                break;
            case REGISTER:
                regPrompt = CREATE_BUYER; // reset regPrompt to CREATE_BUYER when entering register menu
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER:
                            cout << "Create Buyer Account selected." << endl;
                            break;
                        case CREATE_SELLER:
                            cout << "Create Seller Account selected." << endl;
                            break;
                        case BACK:
                            cout << "Back selected." << endl;
                            break;
                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                /* if register is selected then went throuhh registration process:
                1. Create a new Buyer Account
                Must provides: Name, Home Address, Phone number, Email
                2. Option to create a Seller Account (will be linked to Buyer account)
                Must Provides 1: Home Address, Phone number, Email
                Must provides 2: Store Name, Store Address, Store Phone number, Store Email
                Must provides 3: initial deposit amount
                After finished immediately logged in as Buyer/Seller
                */
                break;
            case EXIT:
                cout << "Exiting." << endl;
                break;
            case ADMIN_LOGIN:
                /* 1. Prompt for username & password then check the entries with our hard coded features */
                cout << "--- ADMIN LOGIN ---" << endl;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                // Cek Login Admin
                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    cout << "Admin Login successful." << endl;
                    int adminChoice;
                    bool adminLoggedIn = true;

                    // Sub prompt for User related function
                    while (adminLoggedIn) {
                        cout << "\n--- ADMIN MENU ---" << endl;
                        cout << "1. View Accounts (All / Buyer / Seller)" << endl;
                        cout << "2. Seek (Search) Account" << endl;
                        cout << "3. Create New Account" << endl;
                        cout << "4. Remove Account" << endl;
                        cout << "5. Logout" << endl; // Logout adalah Case 5
                        cout << "Select option: ";
                        
                        // Error handling untuk input non-angka
                        if (!(cin >> adminChoice)) {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number." << endl;
                            continue;
                        }

                        switch (adminChoice) {
                            case 1: // View All Buyers & Sellers (DENGAN OPSI FILTER)
                                {
                                    int viewChoice;
                                    string filterType = "";
                                    
                                    cout << "\n--- VIEW ACCOUNTS ---" << endl;
                                    cout << "1. View ALL Accounts" << endl;
                                    cout << "2. View ONLY Buyers" << endl;
                                    cout << "3. View ONLY Sellers" << endl;
                                    cout << "Select view type: ";
                                    
                                    if (!(cin >> viewChoice)) {
                                        cin.clear();
                                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        cout << "Invalid input." << endl;
                                        break;
                                    }
                                    if (viewChoice == 2) filterType = "Buyer";
                                    else if (viewChoice == 3) filterType = "Seller";
                                    cout << "\n--- " << (filterType.empty() ? "ALL" : filterType) << " ACCOUNTS ---" << endl;
                                    if (accounts.empty()) {
                                        cout << "No accounts registered." << endl;
                                    } else {
                                        int count = 0;
                                        for (const auto& acc : accounts) {
                                            // Tampilkan jika tidak ada filter, atau jika tipe akun cocok dengan filter
                                            if (filterType.empty() || acc.type == filterType) {
                                                cout << "-----------------------------------" << endl;
                                                cout << "ID       : " << acc.id << endl;
                                                cout << "Type     : " << acc.type << endl;
                                                cout << "Name     : " << acc.name << endl;
                                                cout << "Address  : " << acc.address << endl;
                                                cout << "Phone    : " << acc.phone << endl;
                                                cout << "Email    : " << acc.email << endl;
                                                cout << "Balance  : $" << acc.balance << endl;
                                                count++;
                                            }
                                        }
                                        cout << "-----------------------------------" << endl;
                                        cout << "Total " << (filterType.empty() ? "" : filterType) << " Accounts: " << count << endl;
                                    }
                                }
                                break;
                            case 2: // Seek certain buyer of seller
                                {
                                    string searchKey;
                                    cout << "\n--- SEARCH ACCOUNT ---" << endl;
                                    cout << "Enter search key (Name/ID/Address/Phone): ";
                                    
                                    // Membersihkan buffer sebelum getline untuk input string dengan spasi
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                                    getline(cin, searchKey);
                                    
                                    cout << "\n--- SEARCH RESULTS ---" << endl;
                                    bool found = false;
                                    
                                    // Loop untuk mencari di semua akun
                                    for (const auto& acc : accounts) {
                                        // Konversi ID ke string agar bisa dibandingkan dengan searchKey
                                        string idStr = std::to_string(acc.id);
                                        
                                        // Logika pencarian: periksa apakah searchKey cocok dengan ID, Nama, Alamat, atau Phone
                                        if (idStr == searchKey || 
                                            acc.name.find(searchKey) != string::npos || // string::npos berarti tidak ditemukan
                                            acc.address.find(searchKey) != string::npos ||
                                            acc.phone.find(searchKey) != string::npos) 
                                        {
                                            // Jika cocok, tampilkan detail akun
                                            cout << "-----------------------------------" << endl;
                                            cout << "ID       : " << acc.id << endl;
                                            cout << "Type     : " << acc.type << endl;
                                            cout << "Name     : " << acc.name << endl;
                                            cout << "Address  : " << acc.address << endl;
                                            cout << "Phone    : " << acc.phone << endl;
                                            cout << "Email    : " << acc.email << endl;
                                            cout << "Balance  : $" << acc.balance << endl;
                                            found = true;
                                        }
                                    }
                                    
                                    if (!found) {
                                        cout << "No account found matching '" << searchKey << "'." << endl;
                                    }
                                }
                                break;
                           case 3: // Create new buyer/seller/Bank account
                                {
                                    int newId;
                                    string newType, newName, newAddr, newPhone, newEmail;
                                    double initialBalance;

                                    cout << "\n--- CREATE NEW ACCOUNT ---" << endl;
                                    
                                    // 1. Dapatkan ID
                                    cout << "Enter new ID (e.g., 301): ";
                                    if (!(cin >> newId)) {
                                        cout << "Invalid ID format. Returning to Admin Menu." << endl;
                                        cin.clear();
                                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        break;
                                    }
                                    
                                    // 2. Dapatkan Tipe Akun
                                    cout << "Enter Type (Buyer or Seller): ";
                                    cin >> newType;
                                    
                                    // 3. Dapatkan Detail Akun
                                    cout << "Enter Name: ";
                                    // Membersihkan buffer sebelum getline
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, newName);
                                    
                                    cout << "Enter Address: ";
                                    getline(cin, newAddr);
                                    
                                    cout << "Enter Phone: ";
                                    getline(cin, newPhone); // Gunakan getline untuk phone jika formatnya mungkin panjang
                                    
                                    cout << "Enter Email: ";
                                    getline(cin, newEmail);

                                    // 4. Dapatkan Saldo Awal (Bank Account feature)
                                    cout << "Enter Initial Deposit Amount (Balance): $";
                                    if (!(cin >> initialBalance)) {
                                        cout << "Invalid balance format. Setting balance to 0.00." << endl;
                                        initialBalance = 0.0;
                                        cin.clear();
                                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    }
                                    
                                    // 5. Tambahkan akun baru ke vektor
                                    accounts.push_back({newId, newType, newName, newAddr, newPhone, newEmail, initialBalance});
                                    cout << "\nSUCCESS: Account " << newName << " (" << newType << ") created with ID " << newId << "." << endl;
                                }
                                break;
                            case 4: // Remove buyer/seller based on ID (all related info will be deleted)
                                {
                                    int idToRemove;
                                    cout << "\n--- REMOVE ACCOUNT ---" << endl;
                                    cout << "Enter ID of the account to remove: ";
                                    
                                    if (!(cin >> idToRemove)) {
                                        cout << "Invalid ID format." << endl;
                                        cin.clear();
                                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        break;
                                    }

                                    // Gunakan erase-remove idiom untuk menghapus elemen dari vektor
                                    // 1. std::remove_if memindahkan semua elemen yang cocok (return true) ke akhir vektor.
                                    auto it = std::remove_if(accounts.begin(), accounts.end(), 
                                        [idToRemove](const Account& acc){
                                            return acc.id == idToRemove;
                                        });

                                    // 2. Jika iterator (it) tidak berada di akhir vektor (berarti ada yang dihapus)
                                    if (it != accounts.end()) {
                                        // std::vector::erase menghapus elemen dari posisi 'it' hingga akhir.
                                        accounts.erase(it, accounts.end());
                                        cout << "\nSUCCESS: Account with ID " << idToRemove << " and all related info removed." << endl;
                                    } else {
                                        cout << "ERROR: Account with ID " << idToRemove << " not found." << endl;
                                    }
                                }
                                break;
                            case 5: // Logout (Exit to main Menu)
                                cout << "Admin logged out." << endl;
                                adminLoggedIn = false;
                                break;
                            default:
                                cout << "Invalid admin option." << endl;
                                break;
                        }
                    }
                } else {
                    cout << "Login failed. Invalid username or password." << endl;
                }
                break;
        }
        cout << endl;
    }

    //BankCustomer customer1(1, "Alice", 1000.0);
    //Buyer buyer1(1, customer1.getName(), customer1);
    return 1;
}