//
// Created by Eddie Tsai on 2/21/25.
//

#include "kafka_consumer.h"
#include <iostream>
#include <librdkafka/rdkafka.h>
#include <cstring>

KafkaConsumer::KafkaConsumer(const std::string &broker, const std::string &topic)
    : brokers(broker), topic(topic), consumer(nullptr) {

    // config
    rd_kafka_conf_t *conf = rd_kafka_conf_new();
    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers.c_str(), nullptr, 0) != RD_KAFKA_CONF_OK) {
        std::cerr << "設定 Kafka broker 失敗" << std::endl;
    }
    char errstr[512];
    if (rd_kafka_conf_set(conf, "group.id", "my_consumer_group", errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        std::cerr << "設定 group.id 失敗: " << errstr << std::endl;
    }

    // create instance
    consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, nullptr, 0);
    if (!consumer) {
        std::cerr << "無法建立 Kafka consumer" << std::endl;
    }

    // build subscribe
    rd_kafka_topic_partition_list_t *topics = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(topics, topic.c_str(), -1);
    rd_kafka_subscribe(static_cast<rd_kafka_t*>(consumer), topics);
    rd_kafka_topic_partition_list_destroy(topics);
}

KafkaConsumer::~KafkaConsumer() {
    if (consumer) {
        rd_kafka_consumer_close(static_cast<rd_kafka_t*>(consumer));
        rd_kafka_destroy(static_cast<rd_kafka_t*>(consumer));
    }
}

std::string KafkaConsumer::consume() {
    std::string payload = "";
    rd_kafka_message_t *msg = rd_kafka_consumer_poll(static_cast<rd_kafka_t*>(consumer), 100);
    if (msg) {
        if (msg->err == RD_KAFKA_RESP_ERR_NO_ERROR) {
            payload = std::string(static_cast<char *>(msg->payload), msg->len);
        } else {
            std::cerr << "Kafka 消費錯誤: " << rd_kafka_message_errstr(msg) << std::endl;
        }
        rd_kafka_message_destroy(msg);
    }
    return payload;
}

