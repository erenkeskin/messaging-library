#ifndef MESSAGING_LIBRARYSRC_MESSAGE_QUEUE_H
#define MESSAGING_LIBRARYSRC_MESSAGE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "message.h"

/**
 * @class MessageQueue
 * @brief Representation of a message queue
 *
 * A message queue is a thread-safe data structure for storing and retrieving messages.
 * It can be used by publishers to send messages and by subscribers to receive messages.
 *
 * A message queue has two basic operations: enqueue and dequeue.
 * Enqueue adds a message to the queue and dequeue retrieves a message from the queue.
 * When the queue is empty, the dequeue operation blocks until a message is added to the queue.
 */
class MessageQueue {
public:
    MessageQueue() = default;
    ~MessageQueue() = default;
    MessageQueue(const MessageQueue&) = delete;               // copy constructor deleted
    MessageQueue& operator=(const MessageQueue&) = delete;    // copy assigment deleted
    MessageQueue(MessageQueue&&) = delete;                    // move constructor deleted
    MessageQueue& operator=(MessageQueue&&) = delete;         // move assigment deleted

    /**
     * @brief Enqueue a message
     * @param message The message to be enqueued
     */
    void enqueue(const Message& message);

    /**
     * @brief Dequeue a message
     * @return The message that was dequeued
     */
    Message dequeue();

private:
    std::queue<Message> messages_;
    std::mutex mutex_;
    std::condition_variable condition_variable;
};

#endif    // MESSAGING_LIBRARYSRC_MESSAGE_QUEUE_H