template<typename Ret>
class Operation {
	// callee side
	void complete(const Ret& a_result);
	void fail(std::exception_ptr p);
};

template<typename Ret>
class NonblockingOperation: public Operation {
	NonblockingOperation(std::function<void(Ret)> a_cb);
}; 

template<typename Ret>
class BlockingOperation: public Operation {
	Ret wait();
}; 
