// RTree.cpp: 定义控制台应用程序的入口点。
//

// Test.cpp
//
// This is a direct port of the C version of the RTree test program.
//
#include"stdafx.h"
#include <stdio.h>
#include<string>
#include<fstream>
#include "RTree.h"
#include"readFile.h"
#include<time.h>
using namespace std;

vector<string> imageList;  //查询到的imagename

bool MySearchCallback(string* id,void* arg)
{
	//cout<<"Hit data "<<*id<<endl;
	//imageList.push_back(*id);
	return true; // keep going
}


void main()
{	
	srand(time(NULL));
	string feature_Filename = "color_feature.txt";
	string image_Filename = "imagelist.txt";
	vector<vector<int>> featureArray;
	vector<string> imageArray;  //所有的imagename
	//readFeature(feature_Filename, featureArray);
	readImage(image_Filename, imageArray);
	vector<int> lineArray;
	const int feature = 20;
	const int insertSize = 5000;
	for (int i = 0; i < 5000; i++)
	{
		for (int i = 0; i < feature; i++)
		{
			int a = rand() % 10000;
			lineArray.push_back(a);
		}
		featureArray.push_back(lineArray);
		lineArray.clear();
		
	}

	int n = featureArray.size();
	int **array_feature = new int*[n];
	for (int i = 0; i < n; i++)
		array_feature[i] = new int[feature];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < feature; j++)
			array_feature[i][j] = featureArray[i][j];

	/*for (int i = 0; i < n; i++)
		featureArray[i].clear();
	featureArray.~vector();*/

	RTree<string*, int, feature, double> tree;

	printf("For number = %d\n", n);

	for (int i = 0; i< insertSize; i++)
	{
		tree.Insert(array_feature[i], array_feature[i], &imageArray[i]); // Note, all values including zero are fine in this version
	}


	int min[feature], max[feature];
	int hits = 0;
	for (int i = 0; i < 10000; i++)
	{
		vector<int> a = featureArray[rand() % insertSize];
		for (int i = 0; i < feature; i++)
		{
			min[i] = (a[i]  - rand() %  4000) >= 0? a[i] - rand() % 10000:0;
			max[i] = (a[i] + rand() % 4000) <= 10000 ? a[i] + rand() % 10000 :10000;
		}
		int nhits = tree.Search(min, max, MySearchCallback, NULL);
		hits += nhits;
		cout<<"Search results in hits "<< nhits;
		cout << " ,disk access number is " << num - last << endl;
		last = num;
	}
	cout << "average hit = " << hits /10000 << endl;
	cout << "average disk access = " << num /10000 << endl;

	for (int i = 0; i < n; i++)
	{
		delete[] array_feature[i];
		array_feature[i] = NULL;
	}
	delete[] array_feature;
	array_feature = NULL;

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