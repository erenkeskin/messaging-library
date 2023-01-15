#include <gtest/gtest.h>

#include <thread>
#include <variant>

#include "../src/common/message_queue.h"
#include "../src/publisher/publisher.h"
#include "../src/subscriber/subscriber.h"

class MessageQueueTest : public ::testing::Test {
protected:
    std::shared_ptr<MessageQueue> messageQueue;
    std::shared_ptr<Publisher> publisher;
    std::shared_ptr<Subscriber> subscriber;

    virtual void SetUp() {
        messageQueue = std::make_shared<MessageQueue>();
        publisher = std::make_shared<Publisher>(*messageQueue);
        subscriber = std::make_shared<Subscriber>(*messageQueue);
    }
};

TEST_F(MessageQueueTest, TestEnqueueDequeue) {
    // Enqueue a message
    Message message;
    message.topic = "example";
    message.payload = "Hello, world!";
    publisher->publish(message);
    // Dequeue the message
    Message dequeuedMessage = messageQueue->dequeue();
    EXPECT_EQ(message.topic, dequeuedMessage.topic);
    EXPECT_EQ(message.payload, dequeuedMessage.payload);
}

TEST_F(MessageQueueTest, TestSubscribe) {
    std::string receivedPayload;
    subscriber->subscribe("example", [&receivedPayload, this](const Message& message) {
        if (auto payload = std::get_if<std::string>(&message.payload)) {
            receivedPayload = *payload;
        }
        subscriber->stop();
    });

    // Publish a message
    Message message;
    message.topic = "example";
    message.payload = "Hello, world!";
    publisher->publish(message);

    std::thread t1(&Subscriber::run, subscriber);

    t1.join();
    EXPECT_EQ("Hello, world!", receivedPayload);
}
