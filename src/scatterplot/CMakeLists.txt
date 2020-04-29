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
  QT5_WRAP_CPP(MOCSrcs ScatterWidget.h ScatterplotWrapper.h)
  ADD_LIBRARY(scatterplot ScatterWidget.cpp ScatterplotWrapper.cpp Scatterplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(scatterplot Qt5::Widgets ${QWT_LIBRARIES} pointplot)
  SG_SET_PIC(scatterplot)
  SET(SG_HAVE_SCATTERPLOT ON CACHE INTERNAL "Has Scatterplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(Qt5_FOUND AND QWT_FOUND)
  SET(SG_HAVE_SCATTERPLOT OFF CACHE INTERNAL "Has Scatterplot been built?")
ENDIF(Qt5_FOUND AND QWT_FOUND)
