#pragma once

#include <atomic>

#include "socket_worker.hpp"

namespace chat {
    class Chat : public SocketWorker {
    public:
        Chat() = default;
        explicit Chat(in_addr_t, in_port_t);
        ~Chat();

        static void *StartWritingMessages(void *);
        static void *StartListeningMessages(void *);

        void SetNickname();
        void WriteMessages();
        void ListenMessages();

    private:
        void ReceiveMessage();
        void SendMessage(const std::string &);

        [[nodiscard]] static std::string GetIpAddressStr(in_addr_t);
        [[nodiscard]] std::string ConstructTextToBuffer(const std::string &) const;

        [[nodiscard]] bool isValidNickname() const;
        [[nodiscard]] static bool isValidMessageText(const std::string &);
        [[nodiscard]] static std::string GetValidSizeMessageText(const std::string &);
        bool IsStopWordPrinted(const std::string &);

        std::string nickname_{};
        std::string ip_address_view_{};

        std::atomic<bool> must_stop_ = false;

        static const size_t kMaxTextSize = 1007;
        static const size_t kMaxNicknameSize = 20;

        const size_t kAdditionalCharsSize = 5;

        const char *kStopSign = "/STOP_CHAT";
    };
} // namespace chat
