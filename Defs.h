#ifndef DEFS_H_
#define DEFS_H_
typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure } status;
typedef void* element;
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);
typedef element (*copyFunction)(element);
typedef status(*printFunction) (element);
typedef status(*freeFunction) (element);
typedef int (*equalFunction)(element e1,element e2);

#endif /* DEFS_H_ */
