#ifndef _GBN_PROTOCOL_HPP_
#define _GBN_PROTOCOL_HPP_

#include "./BasicRole.hpp"
#include "./SR_Protocol.hpp"
#include "./Timer.hpp"
#include "./UDPFileReader.h"

namespace my
{
    template <int senderWindowSize, int seqNumBound>
        requires(senderWindowSize <= seqNumBound - 1 && senderWindowSize > 0)
    class GBN_Sender : public BasicSender<senderWindowSize, seqNumBound>
    {
    public:
        GBN_Sender() = default;
        GBN_Sender(SOCKET host_socket) : BasicSender<senderWindowSize, seqNumBound>(host_socket) {};
        virtual ~GBN_Sender() = default;

        GBN_Sender(const GBN_Sender &) = delete;
        GBN_Sender &operator=(const GBN_Sender &) = delete;

        virtual void sendtoPeer(::std::string_view filename) override;
    };

    template <int seqNumBound>
    using GBN_Receiver = SR_Receiver<1, seqNumBound>;

    template <int senderWindowSize, int seqNumBound>
        requires(senderWindowSize <= seqNumBound - 1 && senderWindowSize > 0)
    class GBN_Transceiver : public GBN_Sender<senderWindowSize, seqNumBound>,
                            public GBN_Receiver<seqNumBound>
    {
    public:
        GBN_Transceiver() = default;
        GBN_Transceiver(SOCKET host_socket) : BasicRole<senderWindowSize, seqNumBound>(host_socket) {};
        virtual ~GBN_Transceiver() = default;
    };

    template <int senderWindowSize, int seqNumBound>
        requires(senderWindowSize <= seqNumBound - 1 && senderWindowSize > 0)
    void my::GBN_Sender<senderWindowSize, seqNumBound>::sendtoPeer(::std::string_view filename)
    {
        UDPFileReader reader(filename);

        int base = 0;
        int nextSeqNum = 0;
        int ack_num = -1;
        const int line_count = reader.getLineCount();
        constexpr int N = senderWindowSize;
        constexpr int M = seqNumBound;

        Timer timer;

        while (base <= line_count) {
            if (timer.isTimeout()) {
                timer.setTimeout(5000);
                for (int i = base; i < nextSeqNum; i++) {
                    UDPDataframe dataframe = reader.getDataframe(i);
                    dataframe.setDataNum(i % M);
                    sendUDPDataframeTo(dataframe, this->m_host, this->m_peer);
                }
            }

            ack_num = this->recvAckFromPeer();
            if (ack_num != -1) {
                int actual_ack_line = this->getActualLine(base, ack_num);
                base = actual_ack_line + 1;
                if (base == nextSeqNum) {
                    timer.stop();
                } else {
                    timer.setTimeout(5000);
                }
            }

            if (nextSeqNum < base + N && nextSeqNum <= line_count) {
                UDPDataframe dataframe = reader.getDataframe(nextSeqNum);
                dataframe.setDataNum(nextSeqNum % M);
                sendUDPDataframeTo(dataframe, this->m_host, this->m_peer);
                if (base == nextSeqNum) {
                    timer.setTimeout(5000);
                }
                nextSeqNum++;
            }
        }
    }

} // namespace my

#endif // _GBN_PROTOCOL_HPP_