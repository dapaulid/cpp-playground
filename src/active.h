#include "command.h"

#include <queue>

class ActiveObject {

 public:
 	template<class F, class C, class... Args >
	void dispatch(F&& func, C&& cb, Args&&... args) {
	#if 1
		// more efficient, move instead of copy
		m_queue.emplace([
			func = std::forward<F>(func), 
			cb   = std::forward<C>(cb), 
			args = std::make_tuple(std::forward<Args>(args)...)
		](){
			cb(std::apply(func, args));
		});
	#else
		// simpler, copy instead of move
		m_queue.emplace([=](){
			cb(func(args...));
		});
	#endif
	}

	void process() {
		if (m_queue.empty()) {
			return;
		}
		m_queue.front().execute();
		m_queue.pop();
	}

 private:
	// TODO use some threadsafe, lockfree queue
	using Queue = std::queue<Command<>>;
	Queue m_queue;
};