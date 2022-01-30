#include "threadinfo.h"

#include <thread>
#include <mutex>
#include <unordered_map>
#include <sstream>
#include <iomanip>


// private static data
struct ThreadInfo::SStaticData {
	std::unordered_map<std::thread::id, ThreadInfo> map;
	unsigned int threadnum;
	std::mutex mutex;
};
	
ThreadInfo::SStaticData& ThreadInfo::sdata()
{
	static ThreadInfo::SStaticData s_instance;
	return s_instance;
}

ThreadInfo& ThreadInfo::current()
{
	std::thread::id tid = std::this_thread::get_id();

	// critical section
	std::lock_guard<std::mutex> lock(sdata().mutex);

	auto it = sdata().map.find(tid);
	if (it == sdata().map.end()) {
		// unknown thread -> create new entry
		ThreadInfo info;

		std::stringstream ss;
		//ss << tid;
		ss << "T" << std::setw(3) << std::setfill('0') << sdata().threadnum++;
		info.m_name = ss.str();
		it = sdata().map.insert({tid, info}).first;
	}

	return it->second;
}

const std::string& ThreadInfo::get_name() const
{
	return m_name;
}

void ThreadInfo::set_name(const std::string a_name)
{
	m_name = a_name;
}

struct SMainNamer {
	SMainNamer() {
		ThreadInfo::current().set_name("Main");
	}
};
static SMainNamer s_main_namer;