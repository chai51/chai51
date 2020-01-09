// utf8中文
#include <chai51/utility/task.h>

namespace chai51
{
void CTask::init()
{
	createWork(0);
}

void CTask::release()
{

}

void CTask::put(uint32_t workID, const func_type& func)
{
	if (workID == 0 || workID == 1)
	{
		return;
	}

	auto it = m_mapTask.find(workID);
	if (it == m_mapTask.end())
	{
		return;
	}

	it->second.mutex.lock();
	it->second.funcs.push_back(func);
	it->second.mutex.unlock();
	it->second.cond.notify_one();
}

void CTask::createWork(uint32_t workID)
{
	auto it = m_mapTask.find(workID);
	if (it != m_mapTask.end())
	{
		return;
	}
	auto& task = m_mapTask[workID];
	std::shared_ptr<std::thread> t(new std::thread(CTask::work, workID));
	task.thread = t;
	return;
}

void CTask::run(std::list<func_type>& funcs, std::condition_variable& cond, std::mutex& mutex)
{
	std::unique_lock<std::mutex> lk(mutex);
	if (funcs.empty())
	{
		cond.wait(lk);
	}

	func_type func = *funcs.begin();
	funcs.pop_front();
	lk.unlock();
	func();
}

void CTask::runTimer(std::list<timer_func_type>& funcs, std::condition_variable& cond, std::mutex& mutex)
{
	std::unique_lock<std::mutex> lk(mutex);
	if (funcs.empty())
	{
		cond.wait(lk);
	}
	
	std::chrono::steady_clock::time_point clock = std::chrono::steady_clock::now();
	for (auto it = funcs.begin(); it != funcs.end(); )
	{
		if (std::get<0>(*it) <= clock)
		{
			put(std::get<1>(*it), std::get<2>(*it));
			funcs.erase(it++);
		}
		else
		{
			++it;
		}
	}
	lk.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void CTask::work(uint32_t workID)
{
	auto it = m_mapTask.find(workID);
	if (workID == 0)
	{
		while (true)
		{
			runTimer(it->second.func2s, it->second.cond, it->second.mutex);
		}
		
	}
	else
	{
		while (true)
		{
			run(it->second.funcs, it->second.cond, it->second.mutex);
		}
	}
}

std::map<int, CTask::task_type> CTask::m_mapTask;
}