target_sources(runTestBoxMuller PUBLIC ${CMAKE_CURRENT_LIST_DIR}/randomGenerator.cpp ${CMAKE_CURRENT_LIST_DIR}/NormalDistribution.cpp)
target_sources(cmdCalculateCorrelationSkew
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/NormalDistribution.cpp
	${CMAKE_CURRENT_LIST_DIR}/BiVariateJumpDistribution.cpp
	${CMAKE_CURRENT_LIST_DIR}/LognormalDistribution.cpp
	${CMAKE_CURRENT_LIST_DIR}/LognormalSumDistribution.cpp
	${CMAKE_CURRENT_LIST_DIR}/randomGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/PoissonDistribution.cpp)
