#ifndef MESSAGING_LIBRARYSRC_SUBSCRIBER_H
#define MESSAGING_LIBRARYSRC_SUBSCRIBER_H

#ifdef BUILD_TESTS
#include <gtest/gtest_prod.h>
#endif

#include <unordered_map>
#include <string>
#include <functional>

// Forward Declarations
class MessageQueue;
class Message;

/**
 * @class Subscriber
 * @brief Represents a subscriber in the messaging system
 *
 * A subscriber can subscribe to messages with a specific topic and
 * register a callback function that will be called when a message with
 * that topic is received. The subscriber also has a `run` method that
 * retrieves messages from the queue and calls the registered callbacks
 * for each message that has a matching topic.
 *
 * @see Publisher, MessageQueue
 */
class Subscriber {
public:
    /**
     * @brief Constructor
     * @param messageQueue The message queue from which the subscriber will receive messages.
     */
    explicit Subscriber(MessageQueue& messageQueue);

    ~Subscriber() = default;
    Subscriber(const Subscriber&) = delete;               // copy constructor deleted
    Subscriber& operator=(const Subscriber&) = delete;    // copy assigment deleted
    Subscriber(Subscriber&&) = delete;                    // move constructor deleted
    Subscriber& operator=(Subscriber&&) = delete;         // move assigment deleted

    /**
     * @brief Subscribe to messages with a specific topic
     * @param topic The topic for which the subscriber wants to receive messages.
     * @param callback The function that will be called when a message with the specified topic is received.
     */
    void subscribe(const std::string& topic, std::function<void(const Message&)> callback);

    void stop() noexcept;

    /**
     * @brief Continuously retrieves messages from the queue and calls the registered callbacks
     */
    void run();

private:
    bool running_ = true;
    MessageQueue& messageQueue_;
    std::unordered_map<std::string, std::function<void(const Message&)>> callbacks_;
#ifdef BUILD_TESTS
    FRIEND_TEST(MessageQueueTest);
#endif
};

#endif    // MESSAGING_LIBRARYSRC_SUBSCRIBER_H