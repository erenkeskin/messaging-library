#include "message_queue.h"

void MessageQueue::enqueue(const Message& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    messages_.push(message);
}

Message MessageQueue::dequeue() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (messages_.empty()) {
        condition_variable.wait(lock);
    }
    auto message = messages_.front();
    messages_.pop();
    return message;
}
