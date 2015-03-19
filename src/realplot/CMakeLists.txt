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
  QT4_WRAP_CPP(MOCSrcs RealWidget.h RealplotWrapper.h)
  ADD_LIBRARY(realplot RealWidget.cpp RealplotWrapper.cpp Realplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(realplot ${QT_LIBRARIES} ${QWT_LIBRARIES} lineplot)
  SG_SET_PIC(realplot)
  SET(SG_HAVE_REALPLOT ON CACHE INTERNAL "Has Realplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(QT4_FOUND AND QWT_FOUND)
  SET(SG_HAVE_REALPLOT OFF CACHE INTERNAL "Has Realplot been built?")
ENDIF(QT4_FOUND AND QWT_FOUND)
