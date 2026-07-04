#include <iostream>
#include <string>

using namespace std;

// *** Global Player Stats ***
int playerLevel = 1, playerXP = 0, playerGold = 0;
int strength = 5, intellect = 5;

// *** Arrays for Quests & Inventory (Mandatory Concepts) ***
const int MAX_QUESTS = 5;
string quests[MAX_QUESTS];
int questDifficulty[MAX_QUESTS]; // 1=Easy, 2=Medium, 3=Boss
bool questActive[MAX_QUESTS] = {false};
int currentQuestCount = 0;

const int MAX_ITEMS =  5;
string inventory[MAX_ITEMS];
int currentItemCount = 0;

// === USER DEFINED FUNCTIONS ===

void showStats() {
    cout << "\n=== PLAYER STATS ===\n";
    cout<<"\n=======================\n";
    cout << "LEVEL: " << playerLevel << "\nXP: " << playerXP << "/100\n";
    cout << "GOLD: " << playerGold << "g\n";
    cout << "STRENGTH: " << strength << " | INTELLECT: " << intellect << "\n";
    cout << "====================\n";
}

void addQuest() {
    if (currentQuestCount >= MAX_QUESTS) {
        cout << "Quest log full! Complete some quests first.\n";
        return;
    }

    cout << "\nEnter real life task: ";
    // 'ws' consumes any leftover whitespace/newlines from previous menus
    getline(cin >> ws, quests[currentQuestCount]);

    cout << "Select Difficulty (1=Easy, 2=Medium, 3=Hard): ";
    cin >> questDifficulty[currentQuestCount];

    if (questDifficulty[currentQuestCount] < 1 || questDifficulty[currentQuestCount] > 3) {
        cout << "Invalid difficulty. Defaulting to Easy (1).\n";
        questDifficulty[currentQuestCount] = 1;
    }

    questActive[currentQuestCount] = true;
    currentQuestCount++;
    cout << "=> Quest Added to your Log!\n";
    cout <<"RETURNING TO THE MENU... ";
}

void battleBoss() {
    cout << "\n*** ACTIVE QUESTS ***\n";
    bool hasQuests = false;

    for (int i = 0; i < currentQuestCount; i++) {
        if (questActive[i]) {
            cout << i + 1 << ". " << quests[i] << " (Difficulty: " << questDifficulty[i] << ")\n";
            hasQuests = true;
        }
    }

    if (!hasQuests) {
        cout << "No active quests. Go add some tasks!\n";
        return;
    }

    int choice;
    cout << "\nEnter the number of the Quest you just completed: ";
    cin >> choice;

    if (choice < 1 || choice > currentQuestCount || !questActive[choice - 1]) {
        cout << "Invalid Quest selection.\n";
        return;
    }

    int index = choice - 1;
    questActive[index] = false; // Mark completed

    // Base Rewards
    int diff = questDifficulty[index];
    int earnedXP = diff * 25;
    int earnedGold = diff * 15;

    // Item Bonuses (Only applies to Hard Quests)
    if (diff == 3) {
        for (int i = 0; i < currentItemCount; i++) {
            if (inventory[i] == "Cyber Sword  ") {
                earnedXP += 50; earnedGold += 30;
                cout << "\n[!] Cyber Sword slices the Hard quest! Huge bonus granted!\n";
            } else if (inventory[i] == "Cyber Bomb") {
                earnedXP += 30; earnedGold += 15;
                cout << "\n[!] Cyber Bomb blows up the Hard quest! Moderate bonus granted!\n";
            }
        }
    }

    playerXP += earnedXP;
    playerGold += earnedGold;

    cout << "\n>>> COMBAT SUCCESS! <<<\n";
    cout << "You slayed the task! Earned " << earnedXP << " XP and " << earnedGold << " Gold.\n";

    // Level up logic (While loop handles multi-level ups perfectly)
    while (playerXP >= 100) {
        playerLevel++;
        playerXP -= 100;
        strength += 2;
        intellect += 2;
        cout << "\n*** LEVEL UP! You are now Level " << playerLevel << " ***\n";
        cout << "Your stats have increased!\n";
    }
}

void visitShop() {
    cout << "\n*** THE BLACK MARKET ***\n";
    cout << "1. CYBER BOMB (O) (50g)\n";
    cout << "2. CYBER SWORD (--|======>)(50g)\n";
    cout << "3. Exit Shop\n";
    cout << "YOU HAVE " << playerGold << " Gold.\n";

    int choice;
    cout << "SELECT AN ITEM TO BUY: ";
    cin >> choice;

    if (choice == 3) {
        cout << "LEAVING THE BLACK Market.\n";
        return;
    }

    // Consolidated validation logic reduces redundant code
    if (choice == 1 || choice == 2) {
        if (playerGold < 50 || currentItemCount >= MAX_ITEMS) {
            cout << "Not enough gold or inventory is full!\n";
            return;
        }

        playerGold -= 50; // Deduct gold once for any valid purchase

        if (choice == 1) {
            inventory[currentItemCount++] = "Cyber Bomb";
            cout << "Purchased! Cyber Bomb equipped!\n";
        } else if (choice == 2) {
            strength += 5;
            inventory[currentItemCount++] = "Cyber Sword";
            cout << "Purchased! Cyber Sword equipped! (+5 Strength)\n";
        }
    } else {
        cout << "Invalid selection.\n";
    }
}

// === MAIN LOOP ===

int main() {
    int menuChoice = 0;

    do {
        cout << "\n====================================\n";
        cout << ">>>> WELCOME TO CYBER GRIND <<< \n";
        cout << "====================================\n";
        cout << "1. View Player Stats \n";
        cout << "2. Add a New Quest (Task) \n";
        cout << "3. Attack / Complete Quest \n";
        cout << "4. Visit Black Market (Shop) \n";
        cout << "5. Exit Game \n";
        cout << "====================================\n";
        cout << "Enter command: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1: showStats(); break;
            case 2: addQuest(); break;
            case 3: battleBoss(); break;
            case 4: visitShop(); break;
            case 5: cout << "Logging out... Keep grinding in real life!\n"; break;
            default: cout << "Error: Invalid command. Try again.\n";
        }
    } while (menuChoice != 5);

    return 0;
}
