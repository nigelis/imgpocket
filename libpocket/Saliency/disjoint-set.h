#ifndef DISJOINT_SET
#define DISJOINT_SET

//不相交集合森林：利用按秩合并和路径压缩；

typedef struct {
	int rank; //秩-树高;
	int p; //父节点;
	int size; //节点个数;
} uni_elt;

class universe {
public:
	universe(int elements);
	~universe();
	int find(int x);  
	void join(int x, int y);
	int size(int x) const { return elts[x].size; }
	int num_sets() const { return num; }

private:
	uni_elt *elts;
	int num;
};

//建立集合;
__inline universe::universe(int elements) {
	elts = new uni_elt[elements];
	num = elements;
	for (int i = 0; i < elements; i++) {
		elts[i].rank = 0;
		elts[i].size = 1;
		elts[i].p = i;
	}
}

__inline universe::~universe() {
	delete [] elts;
}

//使用路径压缩进行查找;
__inline int universe::find(int x) {
	int y = x;
	while (y != elts[y].p)
		y = elts[y].p;
	elts[x].p = y;
	return y;
}

//按秩合并;
__inline void universe::join(int x, int y) {
	if (elts[x].rank > elts[y].rank) {
		elts[y].p = x;
		elts[x].size += elts[y].size;
	} else {
		elts[x].p = y;
		elts[y].size += elts[x].size;
		if (elts[x].rank == elts[y].rank)
			elts[y].rank++;
	}
	num--;
}

#endif //DISJOINT_SET
