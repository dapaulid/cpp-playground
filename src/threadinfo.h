#include <string>

class ThreadInfo {

public:
	static ThreadInfo& current();

	const std::string& get_name() const;
	void set_name(const std::string& a_name);

private:
	ThreadInfo();
	~ThreadInfo();

private:
	std::string m_name;
	unsigned int m_number;
};