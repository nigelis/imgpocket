/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#ifndef SEGMENT_GRAPH
#define SEGMENT_GRAPH

#include <algorithm>
#include <cmath>
#include "disjoint-set.h"

// ��ֵ������;cԽ��綨��������������Ľ��޾�Խ����;
#define THRESHOLD(size, c) (c/size)

typedef struct {
	float w;//Ȩֵ;
	int a, b;//�ڵ�;
} edge;

// ������С�ںŵ�����;
__inline bool operator<(const edge &a, const edge &b) {
	return a.w < b.w;
}

/*
* �������ܣ��ָ�ͼ��;
*
* �� �� ֵ������һ�����ཻ�ı߼���ʾ�ָ�;
*
* num_vertices: ͼ���еĽڵ�;
* num_edges: ͼ���еı�;
* edges: ������;
* c: ��ֵ����������cԽ�󣬽綨��������������Ľ��޾�Խ����;
*/
__inline universe *segment_graph(int num_vertices, int num_edges, edge *edges, float c) { 
	// ��Ȩֵ�����;
	std::sort(edges, edges + num_edges);

	// ����һ�������ཻ����ɭ��;
	universe *u = new universe(num_vertices);

	// ��ʼ����ֵ;
	float *threshold = new float[num_vertices];
	for (int i = 0; i < num_vertices; i++)
		threshold[i] = THRESHOLD(1,c);

	// ��Ȩֵ�������б�...;
	for (int i = 0; i < num_edges; i++) {
		edge *pedge = &edges[i];

		// �����ӵ�����;
		int a = u->find(pedge->a);
		int b = u->find(pedge->b);
		if (a != b) {
			if ((pedge->w <= threshold[a]) &&
				(pedge->w <= threshold[b])) {
					u->join(a, b);
					a = u->find(a);
					threshold[a] = pedge->w + THRESHOLD(u->size(a), c);
			}
		}
	}

	delete threshold;
	return u;
}

#endif
