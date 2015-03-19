CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (application)

ADD_EXECUTABLE (application application.cpp)
TARGET_LINK_LIBRARIES (application gud)
ADD_TEST (application application)