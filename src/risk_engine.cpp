//
// Created by Eddie Tsai on 2/21/25.
//
#include "risk_engine.h"
#include <iostream>

double RiskEngine::calculateLPI(const OrderBook &orderBook) {
    double sumBids = 0.0;
    double sumAsks = 0.0;
    int count = 0;

    for (auto it = orderBook.bids.rbegin(); it != orderBook.bids.rend() && count < 3; ++it, ++count) {
        sumBids += it->second;
    }
    if (count < 3) {
        std::cerr << "[RiskEngine::calculateLPI] Warning: 少於 3 檔買單可用。\n";
    }

    count = 0;
    for (auto it = orderBook.asks.begin(); it != orderBook.asks.end() && count < 3; ++it, ++count) {
        sumAsks += it->second;
    }
    if (count < 3) {
        std::cerr << "[RiskEngine::calculateLPI] Warning: 少於 3 檔賣單可用。\n";
    }

    if (sumAsks == 0.0) {
        std::cerr << "[RiskEngine::calculateLPI] Error: 賣單總量為 0。\n";
        return -1.0;
    }
    return sumBids / sumAsks;
}

void RiskEngine::evaluate(const OrderBook &orderBook) {
    double lpi = calculateLPI(orderBook);
    if (lpi < 0) {
        std::cout << "LPI 計算失敗。" << std::endl;
    } else {
        std::cout << "計算出的 LPI: " << lpi << std::endl;
    }

}
