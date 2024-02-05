#include <pthread.h>

#include "lib/chat.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Please provide host and a port number!" << std::endl;
        return EXIT_FAILURE;
    }

    chat::Chat chat(
            inet_addr(argv[1]),
            std::strtol(argv[2], nullptr, 10));
    chat.SetNickname();

    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread2, nullptr, chat::Chat::StartWritingMessages, &chat);
    pthread_create(&thread1, nullptr, chat::Chat::StartListeningMessages, &chat);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    return EXIT_SUCCESS;
}
