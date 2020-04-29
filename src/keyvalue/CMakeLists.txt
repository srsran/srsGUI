########################################################################
# Setup Qt and Qwt
########################################################################
FIND_PACKAGE(Qwt)
IF(Qt5_FOUND AND QWT_FOUND)
    INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIRS})
ENDIF(Qt5_FOUND AND QWT_FOUND)

########################################################################
# Build our library
########################################################################
IF(Qt5_FOUND AND QWT_FOUND)
  QT5_WRAP_CPP(MOCSrcs KeyValueWidget.h KeyValueWrapper.h)
  ADD_LIBRARY(keyvalue KeyValueWidget.cpp KeyValueWrapper.cpp KeyValue.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(keyvalue Qt5::Widgets ${QWT_LIBRARIES})
  SG_SET_PIC(keyvalue)
  SET(SG_HAVE_KEYVALUE ON CACHE INTERNAL "Has KeyValue been built?")
  #ADD_SUBDIRECTORY(test)
ELSE(Qt5_FOUND AND QWT_FOUND)
  SET(SG_HAVE_KEYVALUE OFF CACHE INTERNAL "Has KeyValue been built?")
ENDIF(Qt5_FOUND AND QWT_FOUND)
