########################################################################
# Install headers
########################################################################
INSTALL(DIRECTORY srsgui
        DESTINATION "${INCLUDE_DIR}"
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)

########################################################################
# Add headers to cmake project (useful for IDEs)
########################################################################
SET(HEADERS_ALL "")
FILE(GLOB headers *)
FOREACH (_header ${headers})
        IF(IS_DIRECTORY ${_header})
                FILE(GLOB_RECURSE tmp "${_header}/*.h")
                LIST(APPEND HEADERS_ALL ${tmp})
        ENDIF(IS_DIRECTORY ${_header})
ENDFOREACH()
ADD_CUSTOM_TARGET (add_srsgui_headers SOURCES ${HEADERS_ALL})
