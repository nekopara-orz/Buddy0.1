#include <stdio.h>
#define MAX  16
int treenode[MAX * 2];
#define LEFT_NODE(n) (n + 1) * 2 - 1
#define RIGHT_NODE(n) (n + 1) * 2 
#define FATHER_NODE(n) (n - 1) / 2
int pow(int n,int w)
{
	int ans = 1;
	for (int i = 0; i < w; ++i)
	{
		ans *= n;
	}
	return ans;
}
void printTree()
{
	printf("--------------printTree------------\n");
	int f = 0;
	for (int i = 0; i < MAX * 2 - 1; ++i)
	{
		
		printf("%d ", treenode[i]);
		if( i == f )
		{
			f = RIGHT_NODE(f);
			printf("\n");
		}
			
	}
	printf("\n");
}
void init_buddy()
{
	// int bgn = 0,end = 0;

	treenode[0] = MAX;
	
}
int fix(int n)
{
	for (int i = 1; i <= MAX; i *= 2)
	{
		if (n <= i)
		{
			return i;
		}
	}
	return MAX;
}

static int find_dude(int n)
{
	if(n % 2 == 1) 
			return n + 1;
		else
			return n - 1;
}
int update_child_alloc(int n,int need)
{
	int node_size = treenode[n];
	int ln,rn;
	treenode[n] = 0;
	
	while(node_size != need)
	{
		ln = LEFT_NODE(n);
		rn = RIGHT_NODE(n);
		treenode[n] = 0;
		node_size /= 2;
		treenode[ln] = node_size;
		treenode[rn] = node_size;
		n = ln;
	}
	return n;

}
void update_father_free(int n)
{
	int dude ; 
	int node_size = treenode[n];
	while(n != 0)
	{
		dude = find_dude(n);
		int fn = FATHER_NODE(n);
		//printf("dude = %d %d %d\n", treenode[dude],node_size,treenode[fn]);
		if ( treenode[dude] == node_size && treenode[n] == node_size) //如果有兄弟则合并
		{
			treenode[fn] = 2 * node_size;
			treenode[dude] = 0;
			treenode[n] = 0;
		}
		node_size *= 2;
		n = fn;
	}
}
int my_alloc_page(int n)
{
	int index = -1,node_size;
	n = fix(n);

	node_size = n;
	
	int bgn,end;
	bgn = MAX / n - 1; //最左侧和最右侧结点
	end = 2 * bgn;

	while(node_size <= MAX)
	{
		//printf("%d\n", bgn);
		for (int i = bgn; i <= end; ++i)
		{
			//可优化
			if (treenode[i] >= n )
			{
				index = update_child_alloc(i,n);
				treenode[index] = -1; //已分配则标为-1
				break;
			}
		}
		if (index != -1)
		{
			break;
		}
		bgn = FATHER_NODE(bgn);
		end = FATHER_NODE(end);
		node_size *= 2;
	}
	int offset = (index + 1) * n - MAX;
	//printf("index = %d\n", index);
	//printf("offset = %d\n", offset);
	return offset;
}
void my_free_page(int offset)
{
	int index = offset + MAX - 1;
	int node_size = 1;
	//printf("index1 = %d offset = %d\n", index,offset);
	for (; index != 0; index = FATHER_NODE(index))
	{
		if (treenode[index] == -1)
		{
			break;
		}
		node_size *= 2;
	}
	//printf("index = %d  %d\n", index,node_size);
	//printf("%d\n", treenode[20]);
	treenode[index] = node_size;
	update_father_free(index);
}
int main(int argc, char const *argv[])
{
	
	init_buddy();
	printTree();
	int of1 = my_alloc_page(4);
	printTree();
	int of2 = my_alloc_page(1);
	printTree();
	int of3 = my_alloc_page(3);
	printTree();
	int of4 = my_alloc_page(4);
	printTree();
	int of5 = my_alloc_page(2);
	printTree();
	int of6 = my_alloc_page(1);
	printTree();
	my_free_page(of5);
	printTree();
	my_free_page(of1);
	printTree();
	my_free_page(of2);
	printTree();
	my_free_page(of3);
	printTree();
	my_free_page(of4);
	printTree();
	
	my_free_page(of6);
	printTree();
	return 0;
}
