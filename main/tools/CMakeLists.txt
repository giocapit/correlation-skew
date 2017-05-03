target_sources(cmdCalculateCorrelationSkew
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/Equity.cpp
	${CMAKE_CURRENT_LIST_DIR}/Asset.cpp
	${CMAKE_CURRENT_LIST_DIR}/BasketOption.cpp
	${CMAKE_CURRENT_LIST_DIR}/Option.cpp
	${CMAKE_CURRENT_LIST_DIR}/Basket.cpp
	${CMAKE_CURRENT_LIST_DIR}/CorrelationExtractors.cpp)
