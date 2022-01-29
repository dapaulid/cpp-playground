#include "threadinfo.h"

#include <sstream>
#include <iomanip>


typedef std::unordered_map<std::thread::id, ThreadInfo> TThreadMap;

// private static data
struct SStaticData {
	TThreadMap map;
	unsigned int threadnum;
};
	
SStaticData& ThreadInfo::sdata()
{
static SStaticData s_instance;
	return s_instance;
}

ThreadInfo& ThreadInfo::current()
{
	std::thread::id tid = std::this_thread::get_id();

	auto it = sdata().map.find(tid);
	if (it == sdata().map.end()) {
		// unknown thread -> create new entry
		ThreadInfo info;

		std::stringstream ss;
		//ss << tid;
		ss << "T" << std::setw(3) << std::setfill('0') << sdata().threadnum++;
		info.m_name = ss.str();
		//thread_num = (int)map.size();
		it = sdata().map.insert(TThreadMap::value_type(tid, info)).first;
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