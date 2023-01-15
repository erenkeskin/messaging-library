#ifndef MESSAGING_LIBRARYSRC_PUBLISHER_H
#define MESSAGING_LIBRARYSRC_PUBLISHER_H

// Forward Declarations
class MessageQueue;
class Message;
/**
 * @class Publisher
 * @brief Represents a publisher in the messaging system
 *
 * A publisher can publish messages with a specific topic and payload
 * to the message queue.
 *
 * @see Subscriber, MessageQueue
 */
class Publisher {
public:
    /**
     * @brief Constructor
     * @param messageQueue The message queue to which the publisher will send messages.
     */
    explicit Publisher(MessageQueue& messageQueue);
    ~Publisher() = default;
    Publisher(const Publisher&) = delete;               // copy constructor deleted
    Publisher& operator=(const Publisher&) = delete;    // copy assigment deleted
    Publisher(Publisher&&) = delete;                    // move constructor deleted
    Publisher& operator=(Publisher&&) = delete;         // move assigment deleted

    /**
     * @brief Publish a message to the message queue
     * @param message The message to be published
     */
    void publish(const Message& message) noexcept;

private:
    MessageQueue& messageQueue_;
};

#endif    // MESSAGING_LIBRARYSRC_PUBLISHER_H
