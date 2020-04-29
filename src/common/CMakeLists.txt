########################################################################
# Setup Qt and Qwt
########################################################################
FIND_PACKAGE(Qwt)
IF(Qt5_FOUND AND QWT_FOUND)
    INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIRS})
ENDIF(Qt5_FOUND AND QWT_FOUND)
 
########################################################################
# Build our libraries
########################################################################
IF(Qt5_FOUND AND QWT_FOUND)
  QT5_WRAP_CPP(eventwraps Events.h)
  ADD_LIBRARY(events Events.cpp ${eventwraps})
  TARGET_LINK_LIBRARIES(events Qt5::Widgets ${QWT_LIBRARIES})
  SG_SET_PIC(events)
  QT5_WRAP_CPP(lineplotwraps Lineplot.h)
  ADD_LIBRARY(lineplot Lineplot.cpp ${lineplotwraps})
  TARGET_LINK_LIBRARIES(lineplot Qt5::Widgets ${QWT_LIBRARIES} events)
  SG_SET_PIC(lineplot)
  QT5_WRAP_CPP(pointplotwraps Pointplot.h)
  ADD_LIBRARY(pointplot Pointplot.cpp ${pointplotwraps})
  TARGET_LINK_LIBRARIES(pointplot Qt5::Widgets ${QWT_LIBRARIES} events)
  SG_SET_PIC(pointplot)
  QT5_WRAP_CPP(spectrogramplotwraps Spectrogramplot.h)
  ADD_LIBRARY(spectrogramplot Spectrogramplot.cpp ${spectrogramplotwraps})
  TARGET_LINK_LIBRARIES(spectrogramplot Qt5::Widgets ${QWT_LIBRARIES} events)
  SG_SET_PIC(spectrogramplot)
ENDIF(Qt5_FOUND AND QWT_FOUND)
