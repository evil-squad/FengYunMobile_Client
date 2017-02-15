/**
 * @file  Timer.ipp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

namespace
{
    class Timer : public net::Timer
    {
    public:
        Timer(asio::io_service& io)
        : _timer(io)
        {}

        virtual void setExpiresTime(int timeInMs) override
        {
            _timer.expires_from_now(std::chrono::milliseconds(timeInMs));
        }

        virtual bool isExpires() const override
        {
            return _timer.expires_from_now().count() < 0;
        }

        virtual void startWait(const std::function<void(net::ErrorCode)>& handler) override
        {
            _timer.async_wait([this, handler] (const asio::error_code& ec){
                if (ec == asio::error::operation_aborted)
                    return ;

                handler(net::ErrorCode::NONE);
            });
        }

        virtual void destroy() override
        {
            _timer.cancel();
            _timer.get_io_service().post([this] {
                delete this;
            });
        }

    private:
        asio::steady_timer _timer;

        virtual ~Timer() {}
    };
}
