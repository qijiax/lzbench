#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Qpl::qpl" for configuration "Release"
set_property(TARGET Qpl::qpl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qpl::qpl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "ASM_NASM;C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libqpl.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qpl::qpl )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qpl::qpl "${_IMPORT_PREFIX}/lib64/libqpl.a" )

# Import target "Qpl::qplhl" for configuration "Release"
set_property(TARGET Qpl::qplhl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Qpl::qplhl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libqplhl.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Qpl::qplhl )
list(APPEND _IMPORT_CHECK_FILES_FOR_Qpl::qplhl "${_IMPORT_PREFIX}/lib64/libqplhl.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
