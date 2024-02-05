#pragma once

#include "socket_worker.hpp"

namespace chat {
    class Chat : public SocketWorker {
    public:
        Chat() = default;
        explicit Chat(in_addr_t, in_port_t);

        static void *StartWritingMessages(void *);
        static void *StartListeningMessages(void *);

        void SetNickname();
        void WriteMessages();
        void ListenMessages();

        ~Chat();

    private:
        void ReceiveMessage();
        void SendMessage(const std::string &);

        static void RefreshTextBuffer(std::string &);

        [[nodiscard]] bool isValidNickname();
        [[nodiscard]] static bool isValidMessageText(const std::string &);
        [[nodiscard]] static std::string GetValidSizeMessageText(const std::string &);
        bool IsStopWordPrinted(const std::string &);

        std::string nickname_{};

        bool must_stop_ = false;

        const char *c_StopSign = "STOP";
    };
} // namespace chat
