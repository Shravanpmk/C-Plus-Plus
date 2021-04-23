#include <bits/stdc++.h>
using namespace std;


// A function to get the middle index from corner indexes.
int getMid(int s, int e) { return s + (e -s)/2; }


int getSumUtil(int *st, int ss, int se, int qs, int qe, int si)
{
	if (qs <= ss && qe >= se)
		return st[si];

	// If segment of this node is outside the given range
	if (se < qs || ss > qe)
		return 0;

	// If a part of this segment overlaps with the given range
	int mid = getMid(ss, se);
	return getSumUtil(st, ss, mid, qs, qe, 2*si+1) +
		getSumUtil(st, mid+1, se, qs, qe, 2*si+2);
}

void updateValueUtil(int *st, int ss, int se, int i, int diff, int si)
{
	if (i < ss || i > se)
		return;

	st[si] = st[si] + diff;
	if (se != ss)
	{
		int mid = getMid(ss, se);
		updateValueUtil(st, ss, mid, i, diff, 2*si + 1);
		updateValueUtil(st, mid+1, se, i, diff, 2*si + 2);
	}
}

void updateValue(int arr[], int *st, int n, int i, int new_val)
{
	if (i < 0 || i > n-1)
	{
		cout<<"Invalid Input";
		return;
	}

	int diff = new_val - arr[i];
	arr[i] = new_val;
	updateValueUtil(st, 0, n-1, i, diff, 0);
}

int getSum(int *st, int n, int qs, int qe)
{
	// Check for erroneous input values
	if (qs < 0 || qe > n-1 || qs > qe)
	{
		cout<<"Invalid Input";
		return -1;
	}
	return getSumUtil(st, 0, n-1, qs, qe, 0);
}

// A recursive function that constructs Segment Tree for array[ss..se].
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
	if (ss == se)
	{
		st[si] = arr[ss];
		return arr[ss];
	}

	int mid = getMid(ss, se);
	st[si] = constructSTUtil(arr, ss, mid, st, si*2+1) +
			constructSTUtil(arr, mid+1, se, st, si*2+2);
	return st[si];
}



int *constructSegmentTree(int arr[], int n)
{
	// Allocate memory for the segment tree
	//Height of segment tree
	int x = (int)(ceil(log2(n)));
	//Maximum number of nodes of segment tree
	int max_size = 2*(int)pow(2, x) - 1;
	// Allocate memory
	int *st = new int[max_size];
	// Fill the allocated memory st
	constructSTUtil(arr, 0, n-1, st, 0);
	// Return the constructed segment tree
	return st;
}


int main()
{
	int arr[] = {1, 3, 5, 7, 9, 11};
	int n=6;
	//Create a segment tree with the nodes.
	int *st = constructSegmentTree(arr, n);
	// Print sum of values
	cout<<"Sum of values in given range = "<<getSum(st, n, 1, 3)<<endl;
	// Update: arr[1] = 10
	updateValue(arr, st, n, 1, 10);	
	// Find sum after the value is updated
	cout<<"Updated sum of values in given range = "<<getSum(st, n, 1, 3)<<endl;
	return 0;
}