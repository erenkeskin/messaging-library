#include "subscriber.h"

#include <thread>
#include "../common/message_queue.h"

Subscriber::Subscriber(MessageQueue& messageQueue) :
        messageQueue_(messageQueue) {
}

void Subscriber::subscribe(const std::string& topic, std::function<void(const Message&)> callback) {
    callbacks_[topic] = callback;
}

void Subscriber::stop() noexcept {
    running_ = false;
}

void Subscriber::run() {
    running_ = true;
    while (running_) {
        auto message = messageQueue_.dequeue();
        if (callbacks_.count(message.topic)) {
            callbacks_[message.topic](message);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}