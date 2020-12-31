#ifndef __MACRO_H__
#define __MACRO_H__

typedef int DataType; 

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type)	typedef struct __struct##type type;\
						struct __struct##type

#endif