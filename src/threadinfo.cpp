#include "threadinfo.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <sstream>
#include <iomanip>

ThreadInfo::ThreadInfo()
{
	// use monotonic counter for thread number
	static std::atomic_uint s_thread_num;
	m_number = s_thread_num++;

	// use thread number for default name
	std::stringstream ss;
	ss << "T" << std::setfill('0') << std::setw(3) << m_number;
	m_name = ss.str();
}

ThreadInfo::~ThreadInfo()
{
	// here be dragons - at least with emscripten, my Linux VM needed to reboot
	//std::cout << "bye from " << m_name << std::endl;
}

const std::string& ThreadInfo::get_name() const
{
	return m_name;
}

void ThreadInfo::set_name(const std::string& a_name)
{
	m_name = a_name;
}

// return info about the current thread using thread-local storage
ThreadInfo& ThreadInfo::current()
{
	thread_local ThreadInfo t_info;
	return t_info;
}

// give the initial thread (the one calling the static ctors)
// a special name
struct SMainNamer {
	SMainNamer() {
		ThreadInfo::current().set_name("Main");
	}
};
static SMainNamer s_main_namer;