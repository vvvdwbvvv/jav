//
// Created by Eddie Tsai on 2/21/25.
//
#ifndef RISK_ENGINE_H
#define RISK_ENGINE_H

#include "order_book.h"

class RiskEngine {
public:
    RiskEngine() = default;

    // 根據 OrderBook 進行風控評估
    void evaluate(const OrderBook &orderBook);

private:
    // 計算流動性壓力指數 (LPI)
    // LPI = (前三檔買單數量總和) / (前三檔賣單數量總和)
    double calculateLPI(const OrderBook &orderBook);
};

#endif // RISK_ENGINE_H
