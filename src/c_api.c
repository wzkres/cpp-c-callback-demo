#include "c_api.h"

#include <stdio.h>

void c_api_start_counting_no_context(c_api_callback_no_context callback, int max)
{
    if (max <= 0)
    {
        fprintf(stderr, "Invalid max %d!\n", max);
        return;
    }

    if (NULL == callback)
    {
        fprintf(stderr, "Must provide a callback to call this API!\n");
        return;
    }

    for (int a = 0; a < max; a++)
        callback(a);
}

void c_api_start_counting_context(c_api_callback_context callback, int max, void* user_context)
{
    if (max <= 0)
    {
        fprintf(stderr, "Invalid max %d!\n", max);
        return;
    }

    if (NULL == callback)
    {
        fprintf(stderr, "Must provide a callback to call this API!\n");
        return;
    }

    for (int a = 0; a < max; a++)
        callback(a, user_context);
}
