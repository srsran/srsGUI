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
# Build our libraries
########################################################################
IF(QT4_FOUND AND QWT_FOUND)
  QT4_WRAP_CPP(eventwraps Events.h)
  ADD_LIBRARY(events Events.cpp ${eventwraps})
  TARGET_LINK_LIBRARIES(events ${QT_LIBRARIES} ${QWT_LIBRARIES})
  SG_SET_PIC(events)
  QT4_WRAP_CPP(lineplotwraps Lineplot.h)
  ADD_LIBRARY(lineplot Lineplot.cpp ${lineplotwraps})
  TARGET_LINK_LIBRARIES(lineplot ${QT_LIBRARIES} ${QWT_LIBRARIES} events)
  SG_SET_PIC(lineplot)
  QT4_WRAP_CPP(pointplotwraps Pointplot.h)
  ADD_LIBRARY(pointplot Pointplot.cpp ${pointplotwraps})
  TARGET_LINK_LIBRARIES(pointplot ${QT_LIBRARIES} ${QWT_LIBRARIES} events)
  SG_SET_PIC(pointplot)
  QT4_WRAP_CPP(spectrogramplotwraps Spectrogramplot.h)
  ADD_LIBRARY(spectrogramplot Spectrogramplot.cpp ${spectrogramplotwraps})
  TARGET_LINK_LIBRARIES(spectrogramplot ${QT_LIBRARIES} ${QWT_LIBRARIES} events)
  SG_SET_PIC(spectrogramplot)
ENDIF(QT4_FOUND AND QWT_FOUND)
