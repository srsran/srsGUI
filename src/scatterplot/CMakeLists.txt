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
  QT4_WRAP_CPP(MOCSrcs ScatterWidget.h ScatterplotWrapper.h)
  ADD_LIBRARY(scatterplot ScatterWidget.cpp ScatterplotWrapper.cpp Scatterplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(scatterplot ${QT_LIBRARIES} ${QWT_LIBRARIES} pointplot)
  SG_SET_PIC(scatterplot)
  SET(SG_HAVE_SCATTERPLOT ON CACHE INTERNAL "Has Scatterplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(QT4_FOUND AND QWT_FOUND)
  SET(SG_HAVE_SCATTERPLOT OFF CACHE INTERNAL "Has Scatterplot been built?")
ENDIF(QT4_FOUND AND QWT_FOUND)
