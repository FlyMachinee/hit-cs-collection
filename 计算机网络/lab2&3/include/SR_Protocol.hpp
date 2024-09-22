#ifndef _SR_PROTOCOL_HPP_
#define _SR_PROTOCOL_HPP_

#include "./BasicRole.hpp"

namespace my
{
    template <int senderWindowSize, int seqNumBound>
    class SR_Sender : public BasicSender<senderWindowSize, seqNumBound>
    {
        // TODO
    };

    template <int receiverWindowSize, int seqNumBound>
    class SR_Receiver : public BasicReceiver<receiverWindowSize, seqNumBound>
    {
    public:
        SR_Receiver() = default;
        SR_Receiver(SOCKET host_socket) : BasicReceiver<receiverWindowSize, seqNumBound>(host_socket) {};
        virtual ~SR_Receiver() = default;

        SR_Receiver(const SR_Receiver &) = delete;
        SR_Receiver &operator=(const SR_Receiver &) = delete;

        virtual void recvfromPeer(::std::string_view file_path) override;
    };

    template <int senderWindowSize, int receiverWindowSize, int seqNumBound>
        requires(senderWindowSize + receiverWindowSize <= seqNumBound)
    class SR_Transceiver : public SR_Sender<senderWindowSize, seqNumBound>,
                           public SR_Receiver<receiverWindowSize, seqNumBound>
    {
    };

    template <int receiverWindowSize, int seqNumBound>
    void SR_Receiver<receiverWindowSize, seqNumBound>::recvfromPeer(::std::string_view file_path)
    {
        UDPFileWriter writer(file_path);

        int base = 0;
        int nextSeqNum = 0;
        int ack_num = -1;
        const int line_count = writer.getLineCount();
        constexpr int N = receiverWindowSize;
        constexpr int M = seqNumBound;

        while (base <= line_count) {
            ack_num = recvAckFromPeer();
            if (ack_num == -1) continue;

            if (ack_num == base) {
                base = getActualLine(base, ack_num);
                nextSeqNum = base + N;
            }
        }
    }
} // namespace my

#endif // _SR_PROTOCOL_HPP_