############################################################
# Basic
############################################################
# min wersja cmake
cmake_minimum_required(VERSION 3.16.3)

# nazwa projektu i wersja
project(Template VERSION 1.0)

set(SOURCES
    Src/Main.cpp
)

set(HEADERS
    Include/Config.h.in
)

# wskazanie maina
add_executable(${PROJECT_NAME} ${SOURCES})

# dodanie pliku konfiguracyjnego projektu
configure_file(Include/Config.h.in Include/Config.h)


############################################################
# External Libraries
############################################################
option(ADD_BOOST   "Include boost lib in a project"   ON)
option(ADD_OPENCV  "Include opencv lib in a project"  ON)
option(ADD_CURL    "Include curl lib in a project"    ON)

if(ADD_BOOST)
    set(Boost_FIND_REQUIRED TRUE)
    set(Boost_FIND_QUIETLY TRUE)
    set(Boost_DEBUG FALSE)
    set(Boost_USE_MULTITHREADED TRUE)
    set(Boost_USE_STATIC_LIBS TRUE)
    #set(Boost_ADDITIONAL_VERSIONS "1.67" "1.67.0")

    find_package(Boost COMPONENTS regex)

    list(APPEND EXTRA_INCLUDES ${Boost_INCLUDE_DIRS})
    list(APPEND EXTRA_LINKS    ${Boost_LIBRARIES})    
endif()

if(ADD_OPENCV)
    find_package(OpenCV REQUIRED)

    list(APPEND EXTRA_INCLUDES ${OpenCV_INCLUDE_DIRS})
    list(APPEND EXTRA_LINKS    ${OpenCV_LIBS})
endif()

if(ADD_CURL)
    find_package(CURL REQUIRED) 
    
    list(APPEND EXTRA_INCLUDES ${CURL_INCLUDE_DIR})
    list(APPEND EXTRA_LINKS    ${CURL_LIBRARIES})
endif()
############################################################
# Target 
############################################################
# dodanie podfolderów do projektu
add_subdirectory(Lib)
add_subdirectory(Tests)

# wskazanie folderów "include"(plików nagłówkowych bibliotek)
target_include_directories(${PROJECT_NAME} 
    PRIVATE ${PROJECT_BINARY_DIR}
    PRIVATE ${EXTRA_INCLUDES}
    PRIVATE ${PROJECT_SOURCE_DIR}/Include
)

# wskazanie folderów "src"(plików źródłowych bibliotek)
target_link_directories(${PROJECT_NAME}
    PRIVATE ${EXTRA_LIBS}
)

# linkowanie blibliotek
target_link_libraries(${PROJECT_NAME} 
    ${EXTRA_LINKS}
)

############################################################
# Install
############################################################
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES   ${HEADERS}      DESTINATION include)