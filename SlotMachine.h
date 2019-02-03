#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class SlotMachine {
    private:
        string name;
        int numReels;
        int bet;
        vector<int> reels;
        static int biggestJackpot;

    void setReelsToZero() {
        cout << "Setting reels to zero" << endl;
        for (int x = 0; x < numReels; x++) {
            reels.push_back(0);
        }
    }

    void playReels() {
        srand (time(NULL));
        for (int x = 0; x < reels.size(); x++) {
            int randNum = rand() % UPPER_BOUND + LOWER_BOUND;
            reels.at(x) = randNum;
        };
    }

    string getStringReels() {
        string ans;
        for (int x = 0; x < reels.size(); ++x) {
            ans += to_string(reels[x]);
        }
        return ans;
    }

    int inputInt(string prompt) {
        int num;
        cout << prompt;
        cin >> num;

        cout << "You entered: " + num << endl;
        return num;
    }

    void resetBet() {
        bet = 0;
    }

    void betOneCoin() {
        if (bet + 1 > MAX_BET) {
            cout << "Maximum bet reached. Bet will not change." << endl;
        } else {
            bet++;
            cout << "Bet is now: " + to_string(bet) << endl;
        }
    }

    void pullHandle() {
        cout << "Pulling handle..." << endl;
        playReels();
        int winAmt = 0;
        bool winCondition = true;
        string report;
        if (bet == 0) {
            cout << "Cannot pull handle due to no bets. Please bet a coin." << endl;
        } else {
            if (reels[0] == TEN_TIMES_MULTIPLIER_NUM) {
                winAmt = 10 * bet;
                for (int x = 0; x < reels.size(); x++) {
                    if (reels[x] != TEN_TIMES_MULTIPLIER_NUM) {
                        int possibleWinNum = reels[x];
                        for (int inner = x; inner < reels.size(); inner++) {
                            if (reels[inner] != possibleWinNum) {
                                winCondition = false;
                                winAmt = 0;
                            }
                        }
                    }
                }
                if (winCondition) {
                    report ="All numbers were zeroes!";
                }
            } else { // Other win conditions
                int temp = reels[0];
                int diffNumCount = 0;
                for (int x = 0; x < reels.size(); x++) {
                    if (reels[x] != temp) {
                        diffNumCount++;
                        if (diffNumCount >= 2) {
                            winCondition = false;
                        }
                    }
                }

                if (diffNumCount == 0) {
                    cout << "All three non-zero numbers matched!" << endl;
                    winAmt = 5 * bet;
                } else if (diffNumCount == 1) {
                    cout << "Two numbers matched." << endl;
                    winAmt = 2 * bet;
                }
            }
            cout << to_string(winAmt) << endl;
            if (winAmt > biggestJackpot) {
                biggestJackpot = winAmt;
            }
            cout << report << endl;
        }
        

    }

    public:
        static const int MAX_BET = 3;
        static const int LOWER_BOUND = 0; // For reel num generator. Avoids magic numbers!
        static const int UPPER_BOUND = 5;
        static const int TEN_TIMES_MULTIPLIER_NUM = 0; // When all reels equal this, give 10 * the bet for reward.

        SlotMachine() {
            name = "Slot Machine";
            numReels = 3;
            bet = 0;
            setReelsToZero();
        }

        SlotMachine(std::string name, int numReels) {
            this -> name = name;
            this -> numReels = numReels;
            setReelsToZero();
        }

        static int getBigJackpot() { return biggestJackpot; }

        string getMachineName() { return name; }

        void play() {
            string menu = "1. Reset.";
            menu += "\n2. Bet one coin.";
            menu += "\n3. Pull the handle.";
            menu +="\n4. Walk away.";

            bool again = true;
            while(again) {
                cout << getState() << endl;
                cout << "Biggest jackpot won: " + to_string(getBigJackpot()) << endl;
                cout << menu << endl;
                int choice = inputInt("Enter a choice: ");

                switch(choice) {
                    case 1:
                        resetBet();
                        cout << "Bet is now set to 0." << endl;
                        break;
                    case 2:
                        betOneCoin();
                        break;
                    case 3:
                        pullHandle();
                        break;
                    case 4:
                        again = false;
                }
            }
        }

        string getState() {
            cout << "numReels is: " + to_string(numReels) << endl;
            string ans = "\nMachine Name: " + name;
            ans += "\nReel Values: ";   
            ans += getStringReels();         
            return ans;
        }

};

int SlotMachine::biggestJackpot = 0;
