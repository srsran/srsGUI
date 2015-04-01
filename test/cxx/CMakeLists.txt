########################################################################
# Build tests
########################################################################
#turn the test cpp files into executables with int main() functions
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

ADD_EXECUTABLE(waterfallplot_test waterfallplot_test.cpp)
TARGET_LINK_LIBRARIES(waterfallplot_test ${Boost_LIBRARIES} srsgui)
ADD_TEST(waterfallplot_test waterfallplot_test)

ADD_EXECUTABLE(complexplot_test complexplot_test.cpp)
TARGET_LINK_LIBRARIES(complexplot_test ${Boost_LIBRARIES} srsgui)
ADD_TEST(complexplot_test complexplot_test)

ADD_EXECUTABLE(realplot_test realplot_test.cpp)
TARGET_LINK_LIBRARIES(realplot_test ${Boost_LIBRARIES} srsgui)
ADD_TEST(realplot_test realplot_test)

ADD_EXECUTABLE(scatterplot_test scatterplot_test.cpp)
TARGET_LINK_LIBRARIES(scatterplot_test ${Boost_LIBRARIES} srsgui)
ADD_TEST(scatterplot_test scatterplot_test)
