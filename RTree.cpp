// RTree.cpp: 定义控制台应用程序的入口点。
//

// Test.cpp
//
// This is a direct port of the C version of the RTree test program.
//
#include"stdafx.h"
#include <stdio.h>
#include<string>
#include "RTree.h"
#include"readFile.h"
using namespace std;

vector<string> imageList;  //查询到的imagename

bool MySearchCallback(string* id,void* arg)
{
	cout<<"Hit data "<<*id<<endl;
	imageList.push_back(*id);
	return true; // keep going
}


void main()
{
	string feature_Filename = "color_feature.txt";
	string image_Filename = "imagelist.txt";
	vector<vector<int>> featureArray;
	vector<string> imageArray;  //所有的imagename
	readFeature(feature_Filename, featureArray);
	readImage(image_Filename, imageArray);
	int n = featureArray.size();
	int **array_feature = new int*[n];
	for (int i = 0; i < n; i++)
		array_feature[i] = new int[9];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 9; j++)
			array_feature[i][j] = featureArray[i][j];

	int a[9] = { 5180,4835,5186,2767,3165,3531,3090,3398,3781 };
	int b[9] = { 1000,1009,1068,1011,1050,1000,1000,1000,1000 };

	RTree<string*, int, 9, double> tree;

	printf("For number = %d\n", n);

	for (int i = 0; i< n; i++)
	{
		tree.Insert(array_feature[i],array_feature[i],&imageArray[i]); // Note, all values including zero are fine in this version
	}

	int nhits = tree.	Search(b,a, MySearchCallback, NULL);

	printf("Search resulted in %d hits\n", nhits);

	for (int i = 0; i < n; i++)
		delete[] array_feature[i];
	delete[] array_feature;

	// Iterator test 
	//int itIndex = 0;
	//RTree<int, int, 2, float>::Iterator it;
	//for (tree.GetFirst(it);
	//	!tree.IsNull(it);
	//	tree.GetNext(it))
	//{
	//	int value = tree.GetAt(it);

	//	int boundsMin[2] = { 0,0 };
	//	int boundsMax[2] = { 0,0 };
	//	it.GetBounds(boundsMin, boundsMax);
	//	printf("it[%d] %d = (%d,%d,%d,%d)\n", itIndex++, value, boundsMin[0], boundsMin[1], boundsMax[0], boundsMax[1]);
	//}

	// Iterator test, alternate syntax
	//itIndex = 0;
	//tree.GetFirst(it);
	//while (!it.IsNull())
	//{
	//	int value = *it;
	//	++it;
	//	printf("it[%d] %d\n", itIndex++, value);
	//}

	getchar(); 

}