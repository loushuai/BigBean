/*
 * TimedEventQueue.h
 *
 *  Created on: 2016��5��8��
 *      Author: loushuai
 */

#ifndef JNI_MEDIAPLAYER_TIMEDEVENTQUEUE_H_
#define JNI_MEDIAPLAYER_TIMEDEVENTQUEUE_H_

#include <stdint.h>
#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>

namespace whitebean
{

class TimedEventQueue {
public:
	typedef int32_t event_id;
	struct Event {
		Event()
			: mEventID(0) {
		}

		virtual ~Event() {}

        event_id eventID() {
            return mEventID;
        }

    protected:
        virtual void fire(TimedEventQueue *queue, int64_t now_us) = 0;
	private:
		friend class TimedEventQueue;
		event_id mEventID;

        void setEventID(event_id id) {
            mEventID = id;
        }
	};

    TimedEventQueue();
    ~TimedEventQueue();

    // Start executing the event loop.
    void start();

    // Stop executing the event loop, if flush is false, any pending
    // events are discarded, otherwise the queue will stop (and this call
    // return) once all pending events have been handled.
    void stop(bool flush = false);

    // Posts an event to the front of the queue (after all events that
    // have previously been posted to the front but before timed events).
    event_id postEvent(const std::shared_ptr<Event> &event);

    event_id postEventToBack(const std::shared_ptr<Event> &event);

    // It is an error to post an event with a negative delay.
    event_id postEventWithDelay(const std::shared_ptr<Event> &event, int64_t delay_us);

    // If the event is to be posted at a time that has already passed,
    // it will fire as soon as possible.
    event_id postTimedEvent(const std::shared_ptr<Event> &event, int64_t realtime_us);

    // Returns true if event is currently in the queue and has been
    // successfully cancelled. In this case the event will have been
    // removed from the queue and won't fire.
    bool cancelEvent(event_id id);

    // Cancel any pending event that satisfies the predicate.
    // If stopAfterFirstMatch is true, only cancels the first event
    // satisfying the predicate (if any).
    void cancelEvents(
            bool (*predicate)(void *cookie, const std::shared_ptr<Event> &event),
            void *cookie,
            bool stopAfterFirstMatch = false);

private:
    struct QueueItem {
    	std::shared_ptr<Event> event;
        int64_t realtime_us;
    };

    struct StopEvent : public TimedEventQueue::Event {
        virtual void fire(TimedEventQueue *queue, int64_t now_us) {
            queue->mStopped = true;
        }
    };

    std::thread mThread;
    std::list<QueueItem> mQueue;

    std::mutex mLock;
    std::condition_variable mQueueNotEmptyCondition;
    std::condition_variable mQueueHeadChangedCondition;
    event_id mNextEventID;

    bool mRunning;
    bool mStopped;

    inline int64_t GetNowUs();
    static void *ThreadWrapper(void *me);
    void threadEntry();
    std::shared_ptr<Event> removeEventFromQueue_l(event_id id);
};


}

#endif /* JNI_MEDIAPLAYER_TIMEDEVENTQUEUE_H_ */
