SET(SRC_LIST tsqueue.c thread_pool.c tp_test.c)
ADD_EXECUTABLE(tp_test ${SRC_LIST})
TARGET_LINK_LIBRARIES(tp_test pthread)
