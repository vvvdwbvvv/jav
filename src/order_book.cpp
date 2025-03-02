//
// Created by Eddie Tsai on 2/21/25.
//

#include "order_book.h"
#include <nlohmann/json.hpp>
#include <exception>
#include <cstdlib>

void OrderBook::update(bool is_bid, double price, double size) {
    if (is_bid) bids[price] = size;
    else asks[price] = size;
}

OrderBook parse_order_book(const std::string &message) {
    OrderBook ob;
    try {
        auto jsonData = nlohmann::json::parse(message);
        // 若外層訊息為字串，再解析一次
        if (jsonData.is_string()) {
            jsonData = nlohmann::json::parse(jsonData.get<std::string>());
        }
        auto data = jsonData["data"];

        // 填入買檔資料：同時更新 bids map 與最佳買價 bidPrice
        if (data.contains("b") && !data["b"].empty()) {
            // 更新 bids map
            for (const auto &level : data["b"]) {
                double price = std::stod(level[0].get<std::string>());
                double size = std::stod(level[1].get<std::string>());
                ob.bids[price] = size;
            }
            // 取第一檔作為最佳買價（注意：bids 可能需排序逆序取最大價）
            // 由於 std::map 依 key 升序排序，最佳買價為最後一筆
            ob.bidPrice = ob.bids.rbegin()->first;
        }

        // 填入賣檔資料：同時更新 asks map 與最佳賣價 askPrice
        if (data.contains("a") && !data["a"].empty()) {
            for (const auto &level : data["a"]) {
                double price = std::stod(level[0].get<std::string>());
                double size = std::stod(level[1].get<std::string>());
                ob.asks[price] = size;
            }
            // 由於 asks map 升序排序，最佳賣價為第一筆
            ob.askPrice = ob.asks.begin()->first;
        }
    } catch (const std::exception &e) {
        std::cerr << "解析訂單簿 JSON 失敗: " << e.what() << std::endl;
    }
    return ob;
}
