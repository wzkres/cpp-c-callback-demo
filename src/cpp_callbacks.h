#ifndef CPP_C_CALLBACK_DEMO_CPP_CALLBACKS_H
#define CPP_C_CALLBACK_DEMO_CPP_CALLBACKS_H

#pragma once

#include <map>
#include <algorithm>

#include "c_api.h"

static std::mutex g_mutex;

static std::map<int, c_api_callback_no_context> mapped_cbs;

template<int x>
void cb_template(int count)
{
    std::unique_lock<std::mutex> lock(g_mutex);
    std::condition_variable cv;
    cv.wait_for(lock, std::chrono::milliseconds(100));

    c_api_callback_no_context my_p = cb_template<x>;

    auto found = std::find_if(mapped_cbs.cbegin(), mapped_cbs.cend(),
    [my_p](const std::pair<int, c_api_callback_no_context> & p)
    {
        return p.second == my_p;
    });

    if (mapped_cbs.cend() != found)
    {
        printf("Counting to %d, from caller %d!\n", count, (*found).first);
    }
}

template <size_t N>
struct ForEachCpp17
{
    template <size_t I>
    static void RegCallback()
    {
        printf("ForEachCpp17 reg functions %d %d %p\n", N, I, cb_template<I>);
        mapped_cbs.emplace(I, cb_template<I>);

        if constexpr (I + 1 < N) ForEachCpp17<N>::RegCallback<I+1>();
    }
};

template <size_t N>
struct ForEachCpp14
{
    template <size_t I>
    static void RegCallback()
    {
        printf("ForEachCpp14 reg functions %d %d %p\n", N, I, cb_template<I>);
        mapped_cbs.emplace(I, cb_template<I>);

        ForEachCpp14<N>::RecursiveReg<I>();
    }

    template <size_t I>
    static typename std::enable_if<I + 1 < N, void>::type
    RecursiveReg()
    {
        ForEachCpp14<N>::RegCallback<I+1>();
    }

    template <size_t I>
    static typename std::enable_if<I + 1 >= N, void>::type
    RecursiveReg()
    {
    }
};

#endif //CPP_C_CALLBACK_DEMO_CPP_CALLBACKS_H
