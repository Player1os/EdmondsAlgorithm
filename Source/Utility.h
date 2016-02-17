#ifndef UTILITY_H
#define UTILITY_H

#define ENABLE_ASSERTION

#define VERTEX_PER_EDGE_COUNT 2

#define STD_VECTOR_FOREACH_(t,v,it,endIt) \
	for (std::vector<t>::iterator it(v.begin()), endIt(v.end()); it != endIt; ++it)
#define STD_VECTOR_CONST_FOREACH_(t,v,it,endIt) \
	for (std::vector<t>::const_iterator it(v.begin()), endIt(v.end()); it != endIt; ++it)

#endif // UTILITY_H