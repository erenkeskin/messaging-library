#ifndef MESSAGING_LIBRARYSRC_MESSAGE_H
#define MESSAGING_LIBRARYSRC_MESSAGE_H

#include <string>
#include <chrono>
#include <variant>

/**
 * @struct Message
 * @brief Representation of a message.
 *
 * A message is composed of a topic, a timestamp and a payload.
 * The topic field is a string indicating the subject of the message.
 * The timestamp field is a time point indicating when the message was created.
 * The payload field can be any type of data that the client code wants to send.
 */
struct Message {
    std::string topic;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::variant<int, std::string> payload;
};

#endif    // MESSAGING_LIBRARYSRC_MESSAGE_H