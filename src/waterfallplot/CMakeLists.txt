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
  QT5_WRAP_CPP(MOCSrcs WaterfallWidget.h WaterfallplotWrapper.h)
  ADD_LIBRARY(waterfallplot WaterfallWidget.cpp WaterfallplotWrapper.cpp Waterfallplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(waterfallplot Qt5::Widgets ${QWT_LIBRARIES} lineplot spectrogramplot)
  SG_SET_PIC(waterfallplot)
  SET(SG_HAVE_WATERFALLPLOT ON CACHE INTERNAL "Has Waterfallplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(Qt5_FOUND AND QWT_FOUND)
  SET(SG_HAVE_WATERFALLPLOT OFF CACHE INTERNAL "Has Waterfallplot been built?")
ENDIF(Qt5_FOUND AND QWT_FOUND)
