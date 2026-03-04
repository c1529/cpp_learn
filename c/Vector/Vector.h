//对外的接口：结构体的定义，API(函数声明)
typedef struct {
	int* elements;    //指向堆空间的数组
	int size;         //元素个数
	int capacity;    //数组容量
} Vector;

Vector* creaet_vector();

void destroy_vector(Vector* v);

void push_back(Vector* v, int val);
