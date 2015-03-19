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
  QT4_WRAP_CPP(MOCSrcs WaterfallWidget.h WaterfallplotWrapper.h)
  ADD_LIBRARY(waterfallplot WaterfallWidget.cpp WaterfallplotWrapper.cpp Waterfallplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(waterfallplot ${QT_LIBRARIES} ${QWT_LIBRARIES} lineplot spectrogramplot)
  SG_SET_PIC(waterfallplot)
  SET(SG_HAVE_WATERFALLPLOT ON CACHE INTERNAL "Has Waterfallplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(QT4_FOUND AND QWT_FOUND)
  SET(SG_HAVE_WATERFALLPLOT OFF CACHE INTERNAL "Has Waterfallplot been built?")
ENDIF(QT4_FOUND AND QWT_FOUND)
