# Thread-Safe Publish/Subscribe Messaging Library

This is a thread-safe C++ library for publish/subscribe messaging. It allows clients to send and receive messages by topic. The library provides a well-defined API for client code to send and receive messages. The message definition includes a 'topic' designator and a timestamp, making it easy for subscribers to filter messages they are interested in. The payload of the message can be anything the user wants, it can be a string, struct, or a class object.

The library is designed to handle concurrent access of multiple threads to the publisher and subscriber objects. This ensures that the library can be used in high-performance, multithreaded applications without any issues. The library also provides a way to register callbacks for subscribers so that they can be notified as soon as a message arrives for the topic they are subscribed to. This feature makes the library suitable for real-time applications where low latency is a requirement.

By using this library, developers can easily implement the publish/subscribe pattern in their applications, making it easy to decouple different parts of the system and improving the overall scalability and maintainability of the codebase. The library is built using modern C++ features, making it easy to integrate with other C++ libraries and frameworks.

# Build
## Requirements

    C++20 compliant compiler
    Conan Package Manager
    CMake version 3.20 or higher
    GoogleTest/Gtest (for unit tests)

## Building the library
Clone the repository to your local machine.

```
git clone https://github.com/erenkeskin/messaging-library.git
```
Create a build directory and navigate to it.
```
mkdir build && cd build
```
Install conan dependencies
```
conan install . --build=missing
```
Run CMake to generate the build files.
```
cmake ..
```
Build the library using the generated build files.
```
make
```
Run the library example
```
./bin/messaging_library
```

## Building the unit tests
Run CMake with the -DBUILD_TESTS=ON option to enable building the unit tests.
```
cmake -DBUILD_TESTS=ON ..
```
Build the unit tests using the generated build files.
```
make
```
Run the unit tests
```
./bin/messaging_library_test
./bin/messaging_library_test --gtest_repeat=10 --gtest_shuffle --gtest_break_on_failure
```

# Build using Docker
## Requirements
Docker version 18.09 or higher

## Building the image
Clone the repository to your local machine.
```
git clone https://github.com/erenkeskin/messaging-library.git
```
Navigate to the root of the repository.
```
cd messaging-library
```
Build the Docker image. Replace <image_tag> with a desired tag for the image.
```
docker build -t <image_tag> .
```
## Building the library
Run a container using the image built in the previous step. Replace <image_tag> with the tag used in the build step.
```
docker run -it <image_tag>
```
You are already inside the container app/build_docker folder, You may pass this instruction.
```
cd /app/build_docker
```
Run the library example
```
./bin/messaging_library
```
## Building the unit tests
You should navigate app/build_docker folder.
```
cd /app/build_docker
```
Run CMake with the -DBUILD_TESTS=ON option to enable building the unit tests.
```
cmake -DBUILD_TESTS=ON ..
```
Build the unit tests using the generated build files.
```
make
```
Run the unit tests
```
./bin/messaging_library_tests
```

# Running using Docker Compose
## Requirements
    Docker version 18.09 or higher
    Docker Compose version 1.23 or higher

# Starting the service
Clone the repository to your local machine.
```
git clone https://github.com/erenkeskin/messaging-library.git
```
Navigate to the root of the repository.
```
cd messaging-library
```
Start the service using Docker Compose.
```
docker-compose up
```
Accessing the service \
You can check the logs of the service by running
```
docker-compose logs -f
```
You can stop the service by running
```
docker-compose down --remove-orphans
```

# Usage
To use this library, you will need to include the following header files:
```
#include "publisher/publisher.h"
#include "subscriber/subscriber.h"
#include "common/message_queue.h"
```

## Create Objects
To use this library, you should create these following smart pointers:
```
// Create a message queue
auto messageQueue = std::make_shared<MessageQueue>();

// Create a publisher and a subscriber
auto publisher = std::make_shared<Publisher>(*messageQueue);
auto subscriber = std::make_shared<Subscriber>(*messageQueue);
```

## Defining a message
```
// Create Message object
Message message;

// Define the topic of the message
message.topic = "not_subscribed_topic";

// Define the message time
message.timestamp = std::chrono::system_clock::now();

// Define the message payload
message.payload = "Hello, world from subscribed topic";
```

## Publishing a message
```
// Publish the message
publisher->publish(message);
```

## Subscribing to a topic
```
// Subscribe to the topic
subscriber->subscribe(subscriber->subscribe("example", [](const Message& message) {
    // Make something in callback
}););

// Start subscriber (preferred a thread)
std::thread subscriberThread([subscriber]() {
    subscriber->run();
});
```

Note: The library is thread-safe, it can handle concurrent access of multiple threads to the publisher and subscriber objects.


# Project Structure
The project is composed of four main classes:

    + Publisher: This class is used to publish messages to the message queue.
    + Subscriber: This class is used to subscribe to topics and receive messages from the message queue. It also runs a loop to check for new messages in the queue.
    + Message: This struct represents a message, which has a topic, a timestamp, and a payload.
    + MessageQueue: This class is used to store messages and provide thread-safety through the use of mutexes and condition variables.

It's important to notice that Subscriber class has a run method that check the MessageQueue at regular intervals, and if there are messages it can pass it to callback functions with the topic that it subscribed before. also Subscriber class provide a way to stop this process by using stop() method.

# Conclusion
This messaging library is designed to be thread-safe and easy to use. It provides a simple API for publishing and subscribing to messages, allowing clients to send and receive data by topic. The implementation of the library is based on the use of queue and the use of thread-safe mechanisms such as mutexes and condition variables to ensure the safe and efficient handling of messages. \
The Message struct provides a simple way to define messages with a topic, a timestamp, and a payload, while the MessageQueue class handles the storage and distribution of messages. The Publisher and Subscriber classes provide a convenient way for clients to publish and subscribe to messages, respectively. Overall, this library can be used as a starting point for creating more complex messaging systems, and can be easily integrated into any existing project that requires messaging functionality.