CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (request)

ADD_EXECUTABLE (request
	request.cpp)
TARGET_LINK_LIBRARIES (request
	gud)
ADD_TEST (request
	request)