#include "ThreadPool.h"

namespace HailStorm
{
	
	void ThreadPool::Initialize(std::function<void(std::string message, Severity severity)>&& messageCallback)
	{
		s_Logger = messageCallback;
		Log("Logger linked!", Severity::Log);
		auto threadCount = std::thread::hardware_concurrency();
		for (size_t i = 0; i < threadCount; ++i)
		{
			ThreadInfo info;
			info.thread = new std::thread(ThreadLoop);
			info.status = ThreadStatus::Idle;
			s_Threads[info.thread->get_id()] = info;
		}

	}
	void ThreadPool::Log(const std::string& messsage, Severity severity)
	{
		std::lock_guard<std::mutex> lock(s_LogMutex);
		s_Logger(messsage, severity);
	}
	void ThreadPool::ThreadLoop()
	{
		auto& localInfo = s_Threads[std::this_thread::get_id()];
		while (true)
		{
			
		}
	}
}
