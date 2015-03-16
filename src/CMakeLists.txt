CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (web)

FIND_PACKAGE (Boost REQUIRED)

SET (SOURCES
	request.cpp
	response.cpp
	application.cpp
	exceptions.cpp
    log.cpp
    view.cpp
    plustache/context.cpp
    plustache/template.cpp
    config.cpp
)

ADD_LIBRARY (web
	${SOURCES}
)
