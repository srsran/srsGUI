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
  QT5_WRAP_CPP(MOCSrcs ComplexWidget.h ComplexplotWrapper.h)
  ADD_LIBRARY(complexplot ComplexWidget.cpp ComplexplotWrapper.cpp Complexplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(complexplot Qt5::Widgets ${QWT_LIBRARIES} lineplot)
  SG_SET_PIC(complexplot)
  SET(SG_HAVE_COMPLEXPLOT ON CACHE INTERNAL "Has Complexplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(Qt5_FOUND AND QWT_FOUND)
  SET(SG_HAVE_COMPLEXPLOT OFF CACHE INTERNAL "Has Complexplot been built?")
ENDIF(Qt5_FOUND AND QWT_FOUND)
