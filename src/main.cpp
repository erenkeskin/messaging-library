#include <iostream>
#include <thread>
#include <ctime>

#include "publisher/publisher.h"
#include "subscriber/subscriber.h"
#include "common/message_queue.h"

int main() {
    std::cout << "Hello User" << std::endl;

    // Create a message queue
    auto messageQueue = std::make_shared<MessageQueue>();

    // Create a publisher and a subscriber
    auto publisher = std::make_shared<Publisher>(*messageQueue);
    auto subscriber = std::make_shared<Subscriber>(*messageQueue);

    // Subscribe to messages with topic "example"
    subscriber->subscribe("example", [](const Message& message) {
        std::cout << "Topic: " << message.topic << std::endl;

        auto messageTime = std::chrono::system_clock::to_time_t(message.timestamp);
        std::cout << std::ctime(&messageTime);

        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "Received message: " << arg << std::endl;
            } else if constexpr (std::is_same_v<T, int>) {
                std::cout << "Received message: " << arg << std::endl;
            } else {
                std::cout << "Wrong argument type" << std::endl;
            }
        },
                message.payload);

        std::cout << "------------------------------------------" << std::endl;
    });

    // Publish messages
    for (int i = 0; i <= 5; i++) {
        Message message;
        message.topic = "example";
        message.timestamp = std::chrono::system_clock::now();
        message.payload = std::to_string(i) + ". Message: Hello, world";
        publisher->publish(message);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    Message message;
    message.topic = "not_subscribed_topic";
    message.timestamp = std::chrono::system_clock::now();
    message.payload = "Hello, world from not subscribed topic";
    publisher->publish(message);

    // Start the subscriber in a separate thread
    std::thread subscriberThread([subscriber]() {
        subscriber->run();
    });

    // Wait for the subscriber thread to finish
    subscriber->stop();
    subscriberThread.join();

    return 0;
}