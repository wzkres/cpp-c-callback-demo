#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "cpp_callbacks.h"

void test1()
{
    c_api_callback_no_context shared_callback = [](int count)
    {
        std::unique_lock<std::mutex> lock(g_mutex);
        std::condition_variable cv;
        cv.wait_for(lock, std::chrono::milliseconds(100));

        std::cout << "Counting to " << count << ", but don't know which caller!" << std::endl;
    };

    std::thread c_api_caller1([cb = shared_callback]()
    {
        c_api_start_counting_no_context(cb, 10);
    });

    std::thread c_api_caller2([cb = shared_callback]()
    {
        c_api_start_counting_no_context(cb, 10);
    });

    if (c_api_caller1.joinable())
        c_api_caller1.join();

    if (c_api_caller2.joinable())
        c_api_caller2.join();
}

void test2()
{
    c_api_callback_context shared_callback = [](int count, void * user_context)
    {
        std::unique_lock<std::mutex> lock(g_mutex);
        std::condition_variable cv;
        cv.wait_for(lock, std::chrono::milliseconds(100));

        int * caller_id = static_cast<int *>(user_context);
        std::cout << "Counting to " << count << ", from caller " << *caller_id << " (context)!" << std::endl;
    };

    std::thread c_api_caller1([cb = shared_callback]()
    {
        int user_context = 1;
        c_api_start_counting_context(cb, 10, static_cast<void *>(&user_context));
    });

    std::thread c_api_caller2([cb = shared_callback]()
    {
        int user_context = 2;
        c_api_start_counting_context(cb, 10, static_cast<void *>(&user_context));
    });

    if (c_api_caller1.joinable())
        c_api_caller1.join();

    if (c_api_caller2.joinable())
        c_api_caller2.join();
}

void test3()
{
    ForEachCpp11<2>::RegCallback<0>();

    std::thread c_api_caller1([cb = mapped_cbs[0]]()
    {
      c_api_start_counting_no_context(cb, 10);
    });

    std::thread c_api_caller2([cb = mapped_cbs[1]]()
    {
      c_api_start_counting_no_context(cb, 10);
    });

    if (c_api_caller1.joinable())
        c_api_caller1.join();

    if (c_api_caller2.joinable())
        c_api_caller2.join();

    mapped_cbs.clear();
}

void test4()
{
    ForEachCpp14<2>::RegCallback<0>();

    std::thread c_api_caller1([cb = mapped_cbs[0]]()
                              {
                                  c_api_start_counting_no_context(cb, 10);
                              });

    std::thread c_api_caller2([cb = mapped_cbs[1]]()
                              {
                                  c_api_start_counting_no_context(cb, 10);
                              });

    if (c_api_caller1.joinable())
        c_api_caller1.join();

    if (c_api_caller2.joinable())
        c_api_caller2.join();

    mapped_cbs.clear();
}

void test5()
{
    ForEachCpp17<4>::RegCallback<0>();

    std::thread c_api_caller1([cb = mapped_cbs[2]]()
    {
      c_api_start_counting_no_context(cb, 10);
    });

    std::thread c_api_caller2([cb = mapped_cbs[3]]()
    {
      c_api_start_counting_no_context(cb, 10);
    });

    if (c_api_caller1.joinable())
        c_api_caller1.join();

    if (c_api_caller2.joinable())
        c_api_caller2.join();

    mapped_cbs.clear();
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return EXIT_SUCCESS;
}
