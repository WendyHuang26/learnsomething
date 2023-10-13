//
// Created by Ethan on 9/13/2023.
//

#include "hackathonbot.h"
#include "action.h"
#include <vector>
#include <algorithm>

HackathonBot::HackathonBot() : balance(0.0), holding(true) {}

double HackathonBot::getBalance() {
    return this->balance;
}

bool HackathonBot::isHolding() {
    return this->holding;
}

void HackathonBot::takeAction(float price) {
    static std::vector<float> priceHistory; // history of past stock prices
    static float purchasePrice = 100.0;  // keep track of the price when the stock was bought

    priceHistory.push_back(price);

    if (!holding) {
        // buy if the stock price is less than 52
        if (price < 52) {
            holding = true;
            purchasePrice = price;
        }
        // buy if the stock drops in price for 5 windows
        else if (priceHistory.size() >= 5 && 
                 std::all_of(priceHistory.end() - 5, priceHistory.end(), [&](float p){ return p < priceHistory[priceHistory.size() - 6]; })) {
            holding = true;
            purchasePrice = price;
        }
    } else {
        // conditions to sell
        float percentChange = ((price - purchasePrice) / purchasePrice) * 100;

        // sell if the stock goes up in price for 52 windows
        if (priceHistory.size() >= 52 && 
            std::all_of(priceHistory.end() - 52, priceHistory.end(), [&](float p){ return p > priceHistory[priceHistory.size() - 53]; })) {
            holding = false;
        }
        // sell if the stock goes down in price for 47 windows
        else if (priceHistory.size() >= 47 && 
                 std::all_of(priceHistory.end() - 47, priceHistory.end(), [&](float p){ return p < priceHistory[priceHistory.size() - 48]; })) {
            holding = false;
        }
        // sell if the stock drops by over 62% from the purchase price bought
        else if (percentChange <= -62) {
            holding = false;
        }
        // sell if the stock raises by over 89% from the purchase price bought
        else if (percentChange >= 89) {
            holding = false;
        }

        // sell if stock stays +-5% for 10 cycles (after buying)
        else if (priceHistory.size() >= 10 && 
                 std::all_of(priceHistory.end() - 10, priceHistory.end(), [&](float p){ return abs(((p - purchasePrice) / purchasePrice) * 100) <= 5; })) {
            holding = false; // not so sure this part
        }
        // 3-window checks:
        else if (priceHistory.size() >= 3) {
            float change1 = ((priceHistory[priceHistory.size()-3] - purchasePrice) / purchasePrice) * 100;
            float change2 = ((priceHistory[priceHistory.size()-2] - purchasePrice) / purchasePrice) * 100;
            float change3 = ((priceHistory[priceHistory.size()-1] - purchasePrice) / purchasePrice) * 100;
            float overallChange = change3;
            
            if (change1 >= 20 && change2 <= -15 && change3 >= 30 && (change1 + change2 + change3) >= 50) {
                holding = false;
            } else if (change1 <= -15 && change2 >= 15 && change3 <= -25 && overallChange <= -45) {
                holding = false;
            }
        }
    }

    // test ensuring that our price history doesn't grow indefinitely. This is a simple mechanism to keep last 150 prices.
    if (priceHistory.size() > 150) {
        priceHistory.erase(priceHistory.begin());
    }
}

