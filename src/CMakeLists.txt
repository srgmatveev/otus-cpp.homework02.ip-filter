

set(IP_FILTER_LIB_HEADER_FILES ip_filter.h)
set(IP_FILTER_LIB_FILES  ip_filter.cpp addon_functions.h addon_function.cpp)


    add_library(${IP_FILTER_LIB} STATIC
        ${IP_FILTER_LIB_FILES} ${IP_FILTER_LIB_HEADER_FILES}
         )
