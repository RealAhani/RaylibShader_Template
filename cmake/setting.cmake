# ## Settings
include_guard()

# ################### Naming Conventions of project
# project name
set(P_NAME "NAME" CACHE STRING "project name" FORCE)

# output name
set(P_OUT_NAME "main" CACHE STRING "exe or lib name" FORCE)


# ################### Versioning
set(PRVERSION_MAJOR "0" CACHE STRING "" FORCE)
set(PRVERSION_MINOR "0" CACHE STRING "" FORCE)
set(PRVERSION_PATCH "1" CACHE STRING "" FORCE)

# projcet version
set(P_VERSION "${PRVERSION_MAJOR}.${PRVERSION_MINOR}.${PRVERSION_PATCH}" CACHE STRING "project version" FORCE)

# c++ version
set(P_CXX_VERSION 23 CACHE STRING "c++ version")

# c version
set(P_C_VERSION 11 CACHE STRING "c version")

# ################### Compiler detail
# compiler name
set(P_CXX_COMPILER "clang++" CACHE STRING "c++ compiler name" FORCE)

# c++ Extention option
option(P_CXX_EXTENTION ON "c++ extentions")

# c++ Standard option
option(P_CXX_STANDARD ON "c++ standard")

# ################### Flags
# debug flags
option(WERROR_FLAG OFF "Warning as error on/off")

# -Wall
# -Wextra # reasonable and standard
# -Wshadow # warn the user if a variable declaration shadows one from a parent context
# -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
# -Wcast-align # warn for potential performance problem casts
# -Wunused # warn on anything being unused
# -Woverloaded-virtual # warn if you overload (not override) a virtual function
# -Wconversion # warn on type conversions that may lose data
# -Wsign-conversion # warn on sign conversions
# -Wdouble-promotion # warn if float is implicit promoted to double
# -Wformat=2 # warn on security issues around functions that format output (ie printf)
# -Wimplicit-fallthrough # warn when a missing break causes control flow to continue at the next case in a switch statement
# -Wsuggest-override # warn when 'override' could be used on a member function overriding a virtual function
# -Wnull-dereference # warn if a null dereference is detected
# -Wold-style-cast # warn for c-style casts
# -Wpedantic # warn if non-standard C++ is used
# ${OS_ANDROID}:-Wno-main
set(DBG_FLAGS "-DDEBUG;-g;-O0"
  CACHE STRING "debug flags")

# ################### Project config
# the output type of the project can be exe or lib
option(HAS_EXE ON "project is an exe type")
option(HAS_CONSOLE ON "exe run with window and console at the same time")

# ################### Build Config
option(HAS_UNITY_BUILD OFF "unity build should just enabled in release mode")

# External fetched libs type
set(P_EXTERNAL_LIBS_TYPE "STATIC" CACHE STRING "Fetched librareis type (STATIC/SHARED)")

# ################### ThirdParty Dependencies or Fetch Libraries from github (External Libraries)
# URLS          = [raylib git url;box2d git url]
# TAGS          = [raylib git tag;box2d git tag] e.g (version or master/main or comit hash)
# LINKING_VARS  = [raylib;box2d]
set(URLS "https://github.com/raysan5/raylib.git" CACHE STRING "repositories usrls")
set(TAGS "5.5" CACHE STRING "Tag that you want to fetch or branch name")
set(LINK_VARS "raylib" CACHE STRING "the library linking variables")

if(${PLATFORM} STREQUAL "Android")
  list(APPEND LINK_VARS "native_app_glue;log;android;EGL;GLESV2;OpenSLES")
endif(${PLATFORM} STREQUAL "Android")

# ################### Packaging for release
option(HAS_PACKAGE OFF "packaging for release")
set(DISCRIPTION "MyProject - A brief description" CACHE STRING "")
set(VENDOR "YOUR COMPANY" CACHE STRING "")
set(SUPPORTMAIL "support@mycompany.com" CACHE STRING "")

# ################### Android config
set(LIBNAME "${P_OUT_NAME}")
set(ANDROID_OUTPUT "${CMAKE_BINARY_DIR}/../App")
set(APP_LABEL "Raylib" CACHE STRING "")
set(APP_COMPANY_NAME "Nullref" CACHE STRING "")
set(APP_PRODUCT_NAME "game" CACHE STRING "")
set(APP_PACKAGE "com.${APP_COMPANY_NAME}.${APP_PRODUCT_NAME}" CACHE STRING "")
set(APP_VERSION_CODE "1")
set(APP_VERSION_NAME "${P_VERSION}")
set(APP_ORIENTATION "landscape" CACHE STRING "")
set(APP_KEYSTORE_PASS "password" CACHE STRING "")
set(JAVA_HOME "$ENV{JAVA_HOME}")
set(ANDROID_PLATFORM "34")
set(ANDROID_ABI "arm64-v8a")
set(ANDROID_NDK "$ENV{ANDROID_NDK_HOME}")
set(ANDROID_PLATFORM_PATH "$ENV{ANDROID_SDK_HOME}")
set(CMAKE_ANDROID_STL_TYPE c++_static)
option(BUILD_APK OFF "first build all android targets then set this to ON for build .apk")