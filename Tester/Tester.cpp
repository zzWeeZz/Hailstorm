#include "pch.h"
#include "CppUnitTest.h"
#include <windows.h>

#include "HailStorm/Hailstorm.h"
#include <debugapi.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static void CallBack(std::string str, HailStorm::Severity sev)
{
	OutputDebugStringA(str.c_str());
}

namespace Tester
{
	TEST_CLASS(Tester)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HailStorm::ThreadPool::Initialize(CallBack);
			while (true) {};
		}
	};
}
