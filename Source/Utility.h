#ifndef EDMONDS_ALGORITHM_UTILITY_H
#define EDMONDS_ALGORITHM_UTILITY_H

#ifdef _DEBUG
#define ENABLE_DEBUG
#endif

#define VERTEX_PER_EDGE_COUNT 2

#define FOREVER for(;;)

#define STD_VECTOR_FOREACH_(t,v,it,endIt) \
	for (std::vector<t>::iterator it(v.begin()), endIt(v.end()); it != endIt; ++it)
#define STD_VECTOR_CONST_FOREACH_(t,v,it,endIt) \
	for (std::vector<t>::const_iterator it(v.cbegin()), endIt(v.cend()); it != endIt; ++it)

#endif // EDMONDS_ALGORITHM_UTILITY_H