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
  QT5_WRAP_CPP(MOCSrcs RealWidget.h RealplotWrapper.h)
  ADD_LIBRARY(realplot RealWidget.cpp RealplotWrapper.cpp Realplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(realplot Qt5::Widgets ${QWT_LIBRARIES} lineplot)
  SG_SET_PIC(realplot)
  SET(SG_HAVE_REALPLOT ON CACHE INTERNAL "Has Realplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(Qt5_FOUND AND QWT_FOUND)
  SET(SG_HAVE_REALPLOT OFF CACHE INTERNAL "Has Realplot been built?")
ENDIF(Qt5_FOUND AND QWT_FOUND)
