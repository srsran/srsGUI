########################################################################
# Setup Qt and Qwt
########################################################################
FIND_PACKAGE(Qt4)
IF(QT4_FOUND)
    INCLUDE(${QT_USE_FILE})
ENDIF(QT4_FOUND)

FIND_PACKAGE(Qwt)
IF(QT4_FOUND AND QWT_FOUND)
    INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIRS})
ENDIF(QT4_FOUND AND QWT_FOUND)

########################################################################
# Build our library
########################################################################
IF(QT4_FOUND AND QWT_FOUND)
  QT4_WRAP_CPP(MOCSrcs KeyValueWidget.h KeyValueWrapper.h)
  ADD_LIBRARY(keyvalue KeyValueWidget.cpp KeyValueWrapper.cpp KeyValue.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(keyvalue ${QT_LIBRARIES} ${QWT_LIBRARIES})
  SG_SET_PIC(keyvalue)
  SET(SG_HAVE_KEYVALUE ON CACHE INTERNAL "Has KeyValue been built?")
  #ADD_SUBDIRECTORY(test)
ELSE(QT4_FOUND AND QWT_FOUND)
  SET(SG_HAVE_KEYVALUE OFF CACHE INTERNAL "Has KeyValue been built?")
ENDIF(QT4_FOUND AND QWT_FOUND)
