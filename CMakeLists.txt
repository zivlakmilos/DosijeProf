cmake_minimum_required(VERSION 2.8)
project(DosijeProf)

find_package(Qt4 COMPONENTS QtCore QtGui QtSql QtNetwork REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_AUTORCC on)

include_directories(
    ${QT_INCLUDE}
    ${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(include/)

include(${QT_USE_FILE})

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/centralwidget.cpp
    src/dpodaci.cpp
)

set(HEADERS
    include/mainwindow.h
    include/centralwidget.h
    include/dpodaci.h
)

set(UI
    res/ui/podaci.ui
)

set(RESOURCES
    res/ikonice.qrc
)

foreach(MOCheader ${HEADERS})
    QT4_WRAP_CPP(MOCsrc ${MOCheader})
endforeach(MOCheader)

foreach(UIheader ${UI})
    QT4_WRAP_UI(UIsrc ${UIheader})
endforeach(UIheader)

add_executable(${PROJECT_NAME} ${SOURCES} ${MOCsrc} ${RESOURCES} ${UIsrc})
target_link_libraries(${PROJECT_NAME}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTSQL_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
