cmake_minimum_required(VERSION 3.14)

project(TensorRTSP VERSION 0.1 LANGUAGES C CXX CUDA)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/msvc2019_64/lib/cmake/")
set(THIRD_PARTY_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")

add_definitions(
    -DBOOST_DATE_TIME_NO_LIB
    -DBOOST_REGEX_NO_LIB
    -DASIO_STANDALONE

    -D_WEBSOCKETPP_CPP11_STL_
    -D_WEBSOCKETPP_CPP11_FUNCTIONAL_
    -D_WEBSOCKETPP_CPP11_TYPE_TRAITS_
    -D_WEBSOCKETPP_CPP11_CHRONO_

    #-DQT_NO_KEYWORDS
)

# Define Preprocessor
add_compile_definitions(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
add_compile_definitions(_HAS_AUTO_PTR_ETC)
add_compile_definitions(NO_OPENSSL)
add_compile_definitions(NO_GETIFADDRS)
add_compile_definitions(_USAGEENVIRONMENT_VERSION_HH)
add_compile_definitions(NO_STD_LIB)
add_compile_definitions(SOLARIS)
add_compile_definitions(OMIT_REGISTER_HANDLING)


##############################QT#################################

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Multimedia)

###########################OpenCV#################################

find_package( OpenCV REQUIRED )

#######################################################################

###########################TensorRT#################################

#Tensor RT
file(GLOB CPPMODULES "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cpp")
file(GLOB CUMODULESS "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cu")

set(TENSORRT_INCLUDE_DIR "C:/TensorRT-8.6.1.6/include")

if(TENSORRT_INCLUDE_DIR)
  message("TENSORRT_INCLUDE_DIR Available!")
  message("TENSORRT_INCLUDE_DIR : ${TENSORRT_INCLUDE_DIR}")
else()
  message("TENSORRT_INCLUDE_DIR NOT Available")
endif()

set(TENSORRT_LIBRARY "C:/TensorRT-8.6.1.6/lib")

if(TENSORRT_LIBRARY)
  message("TENSORRT_LIBRARY Available!")
  message("TENSORRT_LIBRARY : ${TENSORRT_LIBRARY}")
else()
  message("TENSORRT_LIBRARY NOT Available")
endif()

set(CMAKE_PREFIX_PATH "C:/TensorRT-8.6.1.6/lib")
find_library(NVINFER NAMES nvinfer PATHS ${CMAKE_PREFIX_PATH})

if(NVINFER)
    message("Found nvinfer library: ${NVINFER}")
else()
    message("nvinfer library not found.")
endif()

###########################CUDA##################################

find_package(CUDAToolkit 11.1 REQUIRED)
find_package(CUDA REQUIRED)
message("CUDA_INCLUDE_DIRS : ${CUDA_LIBRARIES}")
message("CUDA_LIBRARIES : ${CUDA_INCLUDE_DIRS}")

if(CUDA_INCLUDE_DIRS)
    message("CUDA_INCLUDE_DIRS Available!!!")
else()
    message("CUDA_INCLUDE_DIRS Not Available!!!")
endif()

if(CUDA_LIBRARIES)
    message("CUDA_LIBRARIES Available!!!")
else()
    message("CUDA_LIBRARIES Not Available!!!")
endif()

enable_language(CUDA)

#######################################################################


##############################FFMPEG###################################

file(GLOB FFMPEG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/FFMPEG/*.cpp")

set(FFMPEG_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/FFMPEG/include")
set(FFMPEG_LIB "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/FFMPEG/lib")

#######################################################################

##############################Live555###################################

file(GLOB LIVE555_BASIC_USAGE_ENVIRONMENT_CPP "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/BasicUsageEnvironment/*.cpp")
file(GLOB LIVE555_BASIC_USAGE_ENVIRONMENT_C "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/BasicUsageEnvironment/*.c")
set(LIVE555_BASIC_USAGE_ENVIRONMENT_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/BasicUsageEnvironment/include")

file(GLOB LIVE555_GROUP_SOCK_CPP "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/groupsock/*.cpp")
file(GLOB LIVE555_GROUP_SOCK_C "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/groupsock/*.c")
set(LIVE555_GROUP_SOCK_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/groupsock/include")

file(GLOB LIVE555_LIVE_MEDIA_CPP "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/liveMedia/*.cpp")
file(GLOB LIVE555_LIVE_MEDIA_C "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/liveMedia/*.c")
set(LIVE555_LIVE_MEDIA_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/liveMedia/include")

file(GLOB LIVE555_USAGE_ENVIRONMENT_CPP "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/UsageEnvironment/*.cpp")
file(GLOB LIVE555_USAGE_ENVIRONMENT_C "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/UsageEnvironment/*.c")
set(LIVE555_USAGE_ENVIRONMENT_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/UsageEnvironment/include")

# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/WindowsAudioInputDevice")
# file(GLOB LIVE555WINDOWSAUDIOINPUTDEVICE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/live555/WindowsAudioInputDevice/*.cpp")

#######################################################################

##############################Socket.IO###################################

file(GLOB SOCKETIO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/sioclient/src/*.cpp")
file(GLOB SOCKETIO_INTERNAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/sioclient/src/internal/*.cpp")

set(SOCKETIO_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/sioclient/src")
set(SOCKETIO_INTERNAL_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/sioclient/src/internal")

set(SUB_MODULE_INCLUDE
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/sioclient/lib/websocketpp
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/sioclient/lib/rapidjson/include
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/sioclient/lib/asio/asio/include
)

#######################################################################

set(PROJECT_SOURCES
        src/main.cpp
        qml.qrc
        ${CPPMODULES}
        ${CUMODULES}
        modules/chunk.cu
        modules/detect.cu
        modules/kernel.cu
        modules/hardswish.cu
        modules/decodeTensorCUDA.cu
        modules/mish.cu
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TensorRTSP
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/VideoStreamer/videostreamer.h src/VideoStreamer/videostreamer.cpp
        src/VideoStreamer/detectionmanager.h
        src/Common/Singleton.h
        src/Network/socketeventhandler.h src/Network/socketeventhandler.cpp
        src/Model/streamingmodel.h src/Model/streamingmodel.cpp
        src/Model/streamingprovider.h src/Model/streamingprovider.cpp
    )
else()
    if(ANDROID)
        add_library(TensorRTSP SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TensorRTSP
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(TensorRTSP PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CUDA_INCLUDE_DIRS}
    ${TENSORRT_INCLUDE_DIR}
    ${FFMPEG_INCLUDE}
    ${LIVE555_BASIC_USAGE_ENVIRONMENT_INCLUDE}
    ${LIVE555_GROUP_SOCK_INCLUDE}
    ${LIVE555_LIVE_MEDIA_INCLUDE}
    ${LIVE555_USAGE_ENVIRONMENT_INCLUDE}
    ${THIRD_PARTY_INCLUDE}
    ${SOCKETIO_INCLUDE}
    ${SOCKETIO_INTERNAL_INCLUDE}
    ${SUB_MODULE_INCLUDE}
)

target_link_directories(TensorRTSP PRIVATE ${FFMPEG_LIB})

target_link_libraries(TensorRTSP
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick  Qt${QT_VERSION_MAJOR}::Multimedia ${OpenCV_LIBS} ${CUDA_LIBRARIES} ${NVINFER} avcodec avformat avutil)

target_sources(TensorRTSP PRIVATE
    ${FFMPEG_SOURCES}
    ${LIVE555_BASIC_USAGE_ENVIRONMENT_CPP}
    ${LIVE555_BASIC_USAGE_ENVIRONMENT_C}
    ${LIVE555_GROUP_SOCK_CPP}
    ${LIVE555_GROUP_SOCK_C}
    ${LIVE555_LIVE_MEDIA_CPP}
    ${LIVE555_LIVE_MEDIA_C}
    ${LIVE555_USAGE_ENVIRONMENT_CPP}
    ${LIVE555_USAGE_ENVIRONMENT_C}
    ${SOCKETIO_SOURCES}
    ${SOCKETIO_INTERNAL_SOURCES}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TensorRTSP)
endif()
set_target_properties(TensorRTSP PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    # CXX_STANDARD 17
    # CXX_EXTENSIONS OFF
    CUDA_ARCHITECTURES "35;50;72"
)

include(GNUInstallDirs)
install(TARGETS TensorRTSP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(TensorRTSP)
    qt_finalize_executable(TensorRTSP)
endif()
