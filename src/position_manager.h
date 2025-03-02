//
// Created by Eddie Tsai on 2/21/25.
//

#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include "order_book.h"

class PositionManager {
public:
    void update(const OrderBook &orderBook);
};

#endif //POSITION_MANAGER_H
