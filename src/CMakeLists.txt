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
# Build the graphics library
########################################################################

file(GLOB modules *) 

SET(SOURCES_ALL "")
FILE(GLOB tmp "*.cpp")
LIST(APPEND SOURCES_ALL ${tmp})
FOREACH (_module ${modules})
	IF(IS_DIRECTORY ${_module})
		FILE(GLOB tmp "${_module}/*.cpp")
		LIST(APPEND SOURCES_ALL ${tmp})		
	ENDIF(IS_DIRECTORY ${_module})
ENDFOREACH(_module ${modules})

IF(QWT_MAJOR_VERSION LESS 6)
	MESSAGE(STATUS "QWT6 is required.")
ENDIF(QWT_MAJOR_VERSION LESS 6)

IF(QT4_FOUND AND QWT_FOUND AND QWT_MAJOR_VERSION EQUAL 6)
  QT4_WRAP_CPP(lineplotwraps ../include/libsdrgui/common/Lineplot.h)
  QT4_WRAP_CPP(pointplotwraps ../include/libsdrgui/common/Pointplot.h)
  QT4_WRAP_CPP(spectrogramplotwraps ../include/libsdrgui/common/Spectrogramplot.h)
  QT4_WRAP_CPP(complex complexplot/ComplexWidget.h complexplot/ComplexplotWrapper.h)
  QT4_WRAP_CPP(real realplot/RealWidget.h realplot/RealplotWrapper.h)
  QT4_WRAP_CPP(scatter scatterplot/ScatterWidget.h scatterplot/ScatterplotWrapper.h)
  QT4_WRAP_CPP(waterfall waterfallplot/WaterfallWidget.h waterfallplot/WaterfallplotWrapper.h)

  INCLUDE_DIRECTORIES(common complexplot realplot scatterplot waterfallplot ${Boost_INCLUDE_DIRS}) 
  
  ADD_LIBRARY(sdrgui SHARED ${eventwraps} ${lineplotwraps} ${pointplotwraps} ${spectrogramplotwraps} ${complex} ${real} ${scatter} ${waterfall} ${SOURCES_ALL} )
  TARGET_LINK_LIBRARIES(sdrgui pthread ${QT_LIBRARIES} ${QWT_LIBRARIES})
  INSTALL(TARGETS sdrgui DESTINATION ${LIBRARY_DIR})
  SG_SET_PIC(sdrgui)

  MESSAGE(STATUS "   libSDRGUI library will be installed.")

ELSE(QT4_FOUND AND QWT_FOUND AND AND QWT_MAJOR_VERSION EQUAL 6) 

  MESSAGE(STATUS "   QT4 or Qwt6 not found. libSDRGUI library is not generated")
  
ENDIF(QT4_FOUND AND QWT_FOUND AND QWT_MAJOR_VERSION EQUAL 6)




