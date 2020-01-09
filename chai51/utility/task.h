#pragma once
#include <functional>
#include <map>
#include <list>
#include <condition_variable>
#include <chrono>
#include <tuple>
#include <thread>

// 任务队列，0为定时器队列，1为主线程队列
namespace chai51
{
typedef std::function<void(void)> func_type;

class CTask
{
	typedef std::tuple<std::chrono::time_point<std::chrono::steady_clock>, int, func_type> timer_func_type;
	typedef struct task_type
	{
		std::shared_ptr<std::thread> thread;
		std::list<func_type> funcs;
		std::list<timer_func_type> func2s;
		std::mutex mutex;
		std::condition_variable cond;
	}task_type;
	
public:
	static void init();
	static void release();

	static void put(uint32_t workID, const func_type& func);
	template <class Rep, class Period>
	static void put(uint32_t workID, const func_type& func, const std::chrono::duration<Rep, Period>& d);

	static void createWork(uint32_t workID);

protected:
	static void run(std::list<func_type>& funcs, std::condition_variable& cond, std::mutex& mutex);
	static void runTimer(std::list<timer_func_type>& funcs, std::condition_variable& cond, std::mutex& mutex);
private:
	static void work(uint32_t workID);

private:
	static std::map<int, task_type> m_mapTask;
};

template <class Rep, class Period>
void CTask::put(uint32_t workID, const func_type& func, const std::chrono::duration<Rep, Period>& d)
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

	auto& task = m_mapTask[0];
	task.mutex.lock();
	task.func2s.push_back(timer_func_type(std::chrono::steady_clock::now() + d, workID, func));
	task.mutex.unlock();
	task.cond.notify_one();
}

}
