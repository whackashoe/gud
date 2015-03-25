CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (gud)

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
    db.cpp
    util.cpp
)

ADD_LIBRARY (gud ${SOURCES} )
TARGET_LINK_LIBRARIES ( gud mysqlclient )
TARGET_LINK_LIBRARIES ( gud mysqlcppconn )
