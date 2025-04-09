# ## Project
include(${CMAKE_SOURCE_DIR}/cmake/Setting.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/LibsConfig.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Android.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/BuildAPK.cmake)

# -------------------- source that compile
file(GLOB p_src_files "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/src/*.cc")
set(mysrc_exe ${p_src_files})

# -------------------- source that compile
if(HAS_EXE)
  # target is desktop app with console debuger
  if(HAS_CONSOLE)
    add_executable(${P_OUT_NAME} ${mysrc_exe})

  # its Desktop without console
  else()
    add_executable(${P_OUT_NAME} WIN32 ${mysrc_exe})
  endif(HAS_CONSOLE)

# other target: target is Android
else()
  add_library(${P_OUT_NAME} SHARED ${mysrc_exe})
  AndroidSetup(${P_OUT_NAME})
endif(HAS_EXE)
configure_file("${CMAKE_SOURCE_DIR}/source/setup/config/config.hh.in" "${CMAKE_CURRENT_BINARY_DIR}/generate/config.hh")
target_include_directories(
  ${P_OUT_NAME}
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/generate"
  PUBLIC "./include"
)
fetch_repositories(${P_OUT_NAME})
target_link_libraries(${P_OUT_NAME} PRIVATE ${LINK_VARS})

# Unity build
if(HAS_UNITY_BUILD)
  set_target_properties(${P_OUT_NAME} PROPERTIES UNITY_BUILD ON)
endif(HAS_UNITY_BUILD)

target_include_directories(${P_OUT_NAME} PUBLIC "./include")
target_compile_options(${P_OUT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CUSTOME_FLAGS}>)

if(HAS_PACKAGE)
  install(TARGETS ${P_OUT_NAME} RUNTIME DESTINATION bin)
endif(HAS_PACKAGE)
