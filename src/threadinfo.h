#include <string>


class ThreadInfo {

public:
	static ThreadInfo& current();

	const std::string& get_name() const;
	void set_name(const std::string a_name);

private:
	std::string m_name;

private:
	// static members as implementation detail
	struct SStaticData;
	static SStaticData& sdata();
};