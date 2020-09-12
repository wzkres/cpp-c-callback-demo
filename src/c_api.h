#ifndef CPP_C_CALLBACK_DEMO_C_API_H
#define CPP_C_CALLBACK_DEMO_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

// C-Style callback function without user context
typedef void (*c_api_callback_no_context)(int count);
// C-Style callback function with user context
typedef void (*c_api_callback_context)(int count, void * user_context);

// C API function that will trigger the callback function
void c_api_start_counting_no_context(c_api_callback_no_context callback, int max);
void c_api_start_counting_context(c_api_callback_context callback, int max, void * user_context);

#ifdef __cplusplus
}
#endif

#endif //CPP_C_CALLBACK_DEMO_C_API_H
