#pragma once

#include <atomic>

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

        [[nodiscard]] bool isValidNickname() const;
        [[nodiscard]] static bool isValidMessageText(const std::string &);
        [[nodiscard]] static std::string GetValidSizeMessageText(const std::string &);
        bool IsStopWordPrinted(const std::string &);

        std::string nickname_{};

        std::atomic<bool> must_stop_ = false;

        static const size_t c_MaxTextSize = 1007;
        static const size_t c_MaxNicknameSize = 20;

        const std::string c_AdditionalChars = ": ";

        const char *c_StopSign = "/STOP_CHAT";
    };
} // namespace chat
