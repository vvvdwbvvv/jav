//
// Created by Eddie Tsai on 2/21/25.
//

#ifndef KAFKA_CONSUMER_H
#define KAFKA_CONSUMER_H

#include <string>

class KafkaConsumer {
public:
    // 傳入 Kafka broker 與訂閱的 topic 名稱
    KafkaConsumer(const std::string &broker, const std::string &topic);

    // 關閉並釋放 Kafka 資源
    ~KafkaConsumer();

    // 返回取得的訊息字串（若無訊息則為空字串）
    std::string consume();

private:
    std::string brokers;
    std::string topic;
    void* consumer;
};

#endif // KAFKA_CONSUMER_H

