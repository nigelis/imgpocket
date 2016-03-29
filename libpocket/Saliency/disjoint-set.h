#ifndef DISJOINT_SET
#define DISJOINT_SET

//���ཻ����ɭ�֣����ð��Ⱥϲ���·��ѹ����

typedef struct {
	int rank; //��-����;
	int p; //���ڵ�;
	int size; //�ڵ����;
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

//��������;
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

//ʹ��·��ѹ�����в���;
__inline int universe::find(int x) {
	int y = x;
	while (y != elts[y].p)
		y = elts[y].p;
	elts[x].p = y;
	return y;
}

//���Ⱥϲ�;
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
