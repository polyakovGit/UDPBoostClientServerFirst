//Client
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;

        udp::resolver resolver(io_service);
        udp::resolver::query query(udp::v4(), argv[1], "13");
        udp::endpoint receiver_endpoint = *resolver.resolve(query);

        udp::socket socket(io_service);
        socket.open(udp::v4());

        boost::array<char, 12> send_buf = { "Test123" };
        boost::array<char, 128> recv_buf;

        for (;;) {
            socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

            udp::endpoint sender_endpoint;

            size_t len = socket.receive_from(
                boost::asio::buffer(recv_buf), sender_endpoint);
            std::cout<<std::string(recv_buf.data(), len);
            Sleep(1000);
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}