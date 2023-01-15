#include "publisher.h"

#include "../common/message_queue.h"

Publisher::Publisher(MessageQueue& messageQueue) :
        messageQueue_(messageQueue) {
}

void Publisher::publish(const Message& message) noexcept {
    messageQueue_.enqueue(message);
}