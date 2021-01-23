#ifndef PROJECT_DELAY_ABSTRACT_HEADER
#define PROJECT_DELAY_ABSTRACT_HEADER

#include <atomic>
#include <thread>
#include <condition_variable>

class ADelay
{
	private:
        std::atomic<bool> _isRun;
        std::atomic<bool> _isPause;
        std::thread _thread;
        long _delay;
        std::condition_variable _cv;

    protected:

		virtual void invoke() const noexcept = 0;

		ADelay(long delay, bool stat);

		virtual ~ADelay();

		void worker(ADelay* delay) const noexcept;

public:

        bool is_run() const noexcept;

        void run() noexcept;

        void stop() noexcept;

        void update(unsigned int delta) noexcept;
};

#endif //PROJECT_DELAY_ABSTRACT_HEADER
