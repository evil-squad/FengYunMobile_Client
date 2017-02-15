/**
 * @file  TcpConnection.ipp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

namespace
{
    class TcpConnection : public net::Connection
    {
    public:
        typedef asio::ip::tcp::socket socket_type;
        typedef asio::ip::tcp::endpoint endpoint_type;

        TcpConnection(asio::io_service& io)
        : _socket(io)
        , _recving(false)
        , _sending(false)
        {}

        virtual bool isOpen() { return _socket.is_open(); }

        virtual void recv(net::mutable_buffer buf, const Handler& handler)
        {
            _socket.get_io_service().post([this, buf, handler] {
                if (!_socket.is_open()) return;
                if (_recving) return handler(net::ErrorCode::BUSY, 0);

                _recving = true;
                asio::async_read(_socket, asio::buffer(buf.ptr(), buf.size()),
                                 [this, handler] (const asio::error_code& ec, std::size_t bytes_transferred) {
                                     _recving = false;

                                     if (ec == asio::error::operation_aborted)
                                         return;

                                     if (ec)
                                         handler(net::ErrorCode::UNKNOWN, bytes_transferred);
                                     else
                                         handler(net::ErrorCode::NONE, bytes_transferred);
                                 });
            });
        }

        virtual void send(net::const_buffer buf, const Handler& handler)
        {
            _socket.get_io_service().post([this, buf, handler] {
                if (!_socket.is_open()) return;
                if (_sending) return handler(net::ErrorCode::BUSY, 0);

                _sending = true;
                asio::async_write(_socket, asio::buffer(buf.ptr(), buf.size()),
                                  [this, handler] (const asio::error_code& ec, std::size_t bytes_transferred) {
                                      _sending = false;

                                      if (ec == asio::error::operation_aborted)
                                          return;

                                      if (ec)
                                          handler(net::ErrorCode::UNKNOWN, bytes_transferred);
                                      else
                                          handler(net::ErrorCode::NONE, bytes_transferred);
                                  });
            });
        }

        virtual void destroy()
        {
            _socket.close();
            _socket.get_io_service().post([this] {
                delete this;
            });
        }
        
        socket_type& getSocket() { return _socket; }
        
    private:
        socket_type _socket;
        
        bool _recving;
        bool _sending;
        
        virtual ~TcpConnection() {}
    };
}
