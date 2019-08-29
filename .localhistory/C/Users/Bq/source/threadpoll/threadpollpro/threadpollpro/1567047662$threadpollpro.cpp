// threadpollpro.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "threadpool.h"
#include <iostream>

void fun1(int slp)
{
	printf("  hello, fun1 !  %d\n", std::this_thread::get_id());
	if (slp > 0) {
		printf(" ======= fun1 sleep %d  =========start  %d\n", slp, std::this_thread::get_id());
		std::this_thread::sleep_for(std::chrono::seconds(slp));
		printf(" ======= fun1 sleep %d  =========end %d\n", slp, std::this_thread::get_id());
		//Sleep(slp );
	}
}

void fun2(int slp)
{
	printf("  hello, fun2 !  %d\n", std::this_thread::get_id());
	printf(" ======= fun2 sleep %d  =========start  %d\n", slp, std::this_thread::get_id());
	std::this_thread::sleep_for(std::chrono::seconds(slp));
	printf(" ======= fun2 sleep %d  =========end %d\n", slp, std::this_thread::get_id());
}

int main()
{
	try {
		std::threadpool executor{ 2 };
		executor.commit(fun1, 1);
		executor.commit(fun2, 2);
		executor.commit(fun2, 3);
		executor.commit(fun1, 4);
		executor.commit(fun1, 5);
		executor.commit(fun1, 6);
		executor.commit(fun1, 7);
		executor.commit(fun1, 8);
		executor.commit(fun1, 9);

		std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(900));

		while (1)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(900));
		}
	}
	catch (std::exception& e) {
		std::cout << "some unhappy happened...  " << std::this_thread::get_id() << e.what() << std::endl;
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件