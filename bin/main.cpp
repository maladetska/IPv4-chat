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

    pthread_t listening_thread;
    pthread_t writing_thread;

    pthread_create(&writing_thread, nullptr, chat::Chat::StartWritingMessages, &chat);
    pthread_create(&listening_thread, nullptr, chat::Chat::StartListeningMessages, &chat);

    pthread_join(listening_thread, nullptr);
    pthread_join(writing_thread, nullptr);

    return EXIT_SUCCESS;
}
