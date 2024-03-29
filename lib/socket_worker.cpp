#include "socket_worker.hpp"

namespace chat {
    SocketWorker::SocketWorker(in_port_t port) : sockfd_(Socket()) {
        Setsockopt();
        FillAddressInfo(broadcast_addr_, INADDR_BROADCAST, port);
        FillAddressInfo(addr_out_, INADDR_ANY, port);
        Bind();
    }

    int SocketWorker::Socket() {
        return CheckError("Socket failed",
                          socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
    }

    void SocketWorker::Bind() {
        CheckError("Bind failed",
                   bind(sockfd_, reinterpret_cast<const sockaddr *>(&addr_out_), sizeof(addr_out_)));
    }

    void SocketWorker::Setsockopt() {
        CheckError("Setsockopt failed",
                   setsockopt(sockfd_, SOL_SOCKET, SO_BROADCAST, &kBroadcast, sizeof(kBroadcast)));
    }

    void SocketWorker::Sendto() {
        socklen_t sockaddr_len = sizeof(broadcast_addr_);
        CheckError("Sendto failed",
                   static_cast<int>(sendto(
                           sockfd_, text_buffer_out_.GetText().c_str(), text_buffer_out_.GetText().size(),
                           0, reinterpret_cast<const sockaddr *>(&broadcast_addr_), sockaddr_len)));
    }

    void SocketWorker::Recvfrom() {
        socklen_t sockaddr_len = sizeof(addr_in_);
        CheckError("Recvfrom failed",
                   static_cast<int>(recvfrom(
                           sockfd_, text_buffer_in_.GetText().data(), text_buffer_in_.GetMaxSize(),
                           MSG_WAITALL, reinterpret_cast<sockaddr *>(&addr_in_), &sockaddr_len)));
    }

    void SocketWorker::CloseSocket() const {
        close(sockfd_);
    }

    int SocketWorker::CheckError(const std::string &str, Descriptor descriptor) {
        if (descriptor == -1) {
            perror(str.c_str());
            exit(EXIT_FAILURE);
        }

        return descriptor;
    }

    void SocketWorker::FillAddressInfo(sockaddr_in &addr, in_addr_t host, in_port_t port) {
        memset(static_cast<void *>(&addr), 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(host);
        addr.sin_port = htons(port);
    }

    void SocketWorker::TextBuffer::SetMaxSize(size_t new_size) {
        max_size_ = new_size;
    }

    std::string &SocketWorker::TextBuffer::GetText() {
        return text_;
    }

    size_t SocketWorker::TextBuffer::GetMaxSize() const {
        return max_size_;
    }

    void SocketWorker::TextBuffer::SetText(const std::string &new_text) {
        text_.clear();
        text_ = new_text;
    }

    void SocketWorker::TextBuffer::Refresh() {
        text_.clear();
        text_.resize(max_size_);
    }
} // namespace chat
