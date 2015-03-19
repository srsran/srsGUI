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
  QT4_WRAP_CPP(MOCSrcs ComplexWidget.h ComplexplotWrapper.h)
  ADD_LIBRARY(complexplot ComplexWidget.cpp ComplexplotWrapper.cpp Complexplot.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(complexplot ${QT_LIBRARIES} ${QWT_LIBRARIES} lineplot)
  SG_SET_PIC(complexplot)
  SET(SG_HAVE_COMPLEXPLOT ON CACHE INTERNAL "Has Complexplot been built?")
  ADD_SUBDIRECTORY(test)
ELSE(QT4_FOUND AND QWT_FOUND)
  SET(SG_HAVE_COMPLEXPLOT OFF CACHE INTERNAL "Has Complexplot been built?")
ENDIF(QT4_FOUND AND QWT_FOUND)
