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

// 阈值函数τ;c越大界定可以区分两区域的界限就越明显;
#define THRESHOLD(size, c) (c/size)

typedef struct {
	float w;//权值;
	int a, b;//节点;
} edge;

// 操作符小于号的重载;
__inline bool operator<(const edge &a, const edge &b) {
	return a.w < b.w;
}

/*
* 函数功能：分割图像;
*
* 返 回 值：返回一个不相交的边集表示分割;
*
* num_vertices: 图像中的节点;
* num_edges: 图像中的边;
* edges: 边数组;
* c: 阈值函数常量，c越大，界定可以区分两区域的界限就越明显;
*/
__inline universe *segment_graph(int num_vertices, int num_edges, edge *edges, float c) { 
	// 以权值排序边;
	std::sort(edges, edges + num_edges);

	// 建立一个互不相交集合森林;
	universe *u = new universe(num_vertices);

	// 初始化阈值;
	float *threshold = new float[num_vertices];
	for (int i = 0; i < num_vertices; i++)
		threshold[i] = THRESHOLD(1,c);

	// 按权值升序排列边...;
	for (int i = 0; i < num_edges; i++) {
		edge *pedge = &edges[i];

		// 边连接的区域;
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
