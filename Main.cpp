#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#define getMid(start,end) (start + (end - start) / 2)

using namespace std;
typedef int STtype;

 
STtype getSumUtil(vector<STtype> segmentTree, int ss, int se, int qs, int qe, int si)
{
	if (qs <= ss && qe >= se)
		return segmentTree[si];
	if (se < qs || ss > qe)
		return 0;

	int mid = getMid(ss, se);
	return getSumUtil (segmentTree, ss, mid, qs, qe, 2 * si + 1) +
		getSumUtil (segmentTree, mid + 1, se, qs, qe, 2 * si + 2);
}

void updateValueUtil(vector<STtype> &segmentTree, int ss, int se, int i, STtype diff, int si)
{
	if (i < ss || i > se)
		return;

	segmentTree[si] = segmentTree[si] + diff;
	if (se != ss)
	{
		int mid = getMid(ss, se);
		updateValueUtil (segmentTree, ss, mid, i, diff, 2 * si + 1);
		updateValueUtil (segmentTree, mid + 1, se, i, diff, 2 * si + 2);
	}
}

void updateValue(vector<STtype> &originalArray, vector<STtype> &segmentTree, int n, int i, STtype new_val, bool *isvalid)
{
	if (i < 0 || i > n - 1)
	{
		*isvalid = false;
		return;
	}

	STtype diff = new_val - originalArray[i];
	originalArray[i] = new_val;
	*isvalid = true;
	updateValueUtil (segmentTree, 0, n - 1, i, diff, 0);
}
 
STtype getSum(vector<STtype> segmentTree, int n, int qs, int qe, bool *isvalid)
{
	if (qs < 0 || qe > n - 1 || qs > qe)
	{
		*isvalid = false;
		return -1;
	}

	*isvalid = true;
	return getSumUtil (segmentTree, 0, n - 1, qs, qe, 0);
}

STtype constructSTUtil(vector<STtype> arr, int ss, int se, vector<STtype> &segmentTree, int si)
{
	if (ss == se)
	{
		segmentTree[si] = arr[ss];
		return arr[ss];
	}

	int mid = getMid(ss, se);
	segmentTree[si] = constructSTUtil (arr, ss, mid, segmentTree, si * 2 + 1) +
		constructSTUtil (arr, mid + 1, se, segmentTree, si * 2 + 2);
	return segmentTree[si];
}

vector<STtype> constructST(vector<STtype> arr, int n)
{
	
	int x = (int)(ceil(log2(n)));

	
	int max_size = 2 * (int)pow(2, x) - 1;

	
	vector<STtype> segmentTree(max_size);

	
	constructSTUtil(arr, 0, n - 1, segmentTree, 0);

	
	return segmentTree;
}

vector<STtype> InitializeVector(int size){
	vector<STtype> a;
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		a.push_back((STtype)rand());
	}
	return a;
}


int main(){
	vector<STtype> numbers;
	numbers = InitializeVector(10000);
	int n = numbers.size();
	vector<STtype> segmentTree = constructST(numbers, n);
	int i = 4;
	int j = 99;
	bool isvalid;
	int sum;
	
	sum = getSum(segmentTree, n, i, j, &isvalid);
	if (isvalid){
		cout << "Sum before update = " << sum << endl;
	}
	else {
		cout << "invalid query" << endl;
	}
	updateValue(numbers, segmentTree, n, 10, 100, &isvalid);
	sum = getSum(segmentTree, n, i, j, &isvalid);
	if (isvalid){
		cout << "Sum after update one value = " << sum << endl;
	}
	else {
		cout << "invalid query" << endl;
	}
	

	getchar();
	return 0;
}