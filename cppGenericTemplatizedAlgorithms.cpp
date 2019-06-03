#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;

bool globalDebugFlag = false;

void InitializeSrand(bool debugFlag = false)
{
	if (globalDebugFlag || debugFlag)
		srand (1);
	else
		srand (time(NULL));
}

template <typename T>
bool operator==(vector<T> const &lhs, vector<T> const &rhs)
{
	if (lhs.size()!=rhs.size()) return false;

	for (int i=0; i<lhs.size(); i++)
	{
		if (lhs[i]!=rhs[i]) return false;
	}
	return true;
}

template <typename Key, typename Value>
bool operator==(map<Key, Value> const &lhs, map<Key, Value> const &rhs)
{
	typename map<Key, Value>::iterator it;

	for ( it = lhs.begin(); it != lhs.end(); it++ )
	{
		if (rhs.count(it->first)<=0) return false;
		if (rhs[it->first]!=it->second) return false;
	}
	return true;
}

template <typename T> 
ostream& operator<<(ostream& os, const vector<T> &v) 
{ 
    for (int i = 0; i < v.size(); ++i) 
    { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << " "; 
    } 
    return os; 
}

template <typename Key, typename Value>
map<int, Key> ValuesOfMap(map<Key, Value> &m, bool debugFlag = false)
{
	if (globalDebugFlag || debugFlag) { cout << "Inside UnzipMap function." << endl; }
	map<int, Key> keys;
	map<int, Value> values;
    tie(keys, values) = UnzipMap(m);
    return values;
}

template <typename Key, typename Value>
ostream& operator<<(ostream& os, map<Key, Value> &m) 
{ 
	map<int, Key> keys;
	map<int, Value> values;

    tie(keys, values) = UnzipMap(m);

    for (int i = 1; i <= m.size(); ++i) 
    { 
    	os << "Key: ";
    	os << keys[i];
    	os << " -> ";
    	os << "Value: ";
    	os << values[i];
    	os << endl; 
    } 
    return os; 
}

int ReverseFlag(bool ascending)
{
	return (ascending ? 1 : -1);
}

template <typename Type>
int OperatorCompare(Type one, Type two, int reverse = 1)
{
	if (one == two) return 0;
	return (one < two ? -reverse : reverse);
}

template <typename Type>
int OperatorCompareReverse(Type one, Type two, int reverse = -1)
{
	return OperatorCompare(one, two, reverse);
}

template <typename Type>
vector<Type> Subvector
	(
		vector<Type> const &v,
		int start, int end,
		bool debugFlag = false
	)
{
	if (globalDebugFlag || debugFlag)
		cout << "Inside Subvector Function." << endl;
	vector<Type> subvector(end-start+1);
	for (int i=start; i<=end; i++)
	{
		subvector[i-start]=v[i];
		if (globalDebugFlag || debugFlag)
			cout << "Subvector (i-start) is: " << subvector[i-start] << endl;
	}
	return subvector;
}

template <typename Type>
void SwapInPlace
	(
		Type &one, Type &two
	)
{
	Type temp = one;
	one = two;
	two = temp;
}

template <typename Type>
void Swap(Type &one, Type &two)
{
	SwapInPlace(one, two);
}

template <typename Type>
void VectorSwapInPlace
	(
		vector<Type> &v,
		int i, int j
	)
{
	SwapInPlace(v[i], v[j]);
}

template <typename Type>
vector<Type> VectorPrepend
	(
		vector<Type> const &v,
		Type element
	)
{
	vector<Type> result;
	result[0] = element;
	for (int i=0; i<v.size(); i++)
	{
		result[i+1] = v[i];
	}
	return result;
}

template <typename Type>
vector<Type> VectorAppend
	(
		vector<Type> const &v,
		Type element
	)
{
	vector<Type> result = v;
	result.push_back(element);
	return result;
}

template <typename Type>
vector<Type> VectorConcatenate
	(
		vector<Type> const &u,
		vector<Type> const &v
	)
{
	vector<Type> result = u;
	for (int i=0; i<v.size(); i++)
	{
		result.push_back(v[i]);
	}
	return result;
}

template <typename Type>
void VectorReverseInPlace
	(
		vector<Type> &v,
		int start = 0, int end = -10
	)
{
	if (end == -10)
		end = v.size()-1;
	if (v.size()<=1) return;
	else if (end - start <= 0) return;
	else
	{
		VectorSwapInPlace(v, start, end);
		VectorReverseInPlace(v, start+1, end-1);
	}
}

template <typename Type>
vector<Type> VectorReverse(vector<Type> const &v)
{
	vector<Type> u = v;
	VectorReverseInPlace(u);
	return u;
}

template <typename Type>
void SortSelectionInPlace
	(
		vector<Type> &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	int reverse = ReverseFlag(ascending);

	for (int i=0; i<v.size(); i++)
	{
		int minIndex = i;
		for (int j=i+1; j<v.size(); j++)
		{
			if (compare(v[j], v[minIndex], reverse) == -1) 
				minIndex = j;
		}
		SwapInPlace(v[i],v[minIndex]);
	}
}

template <typename Type>
vector<Type> SortSelection
	(
		vector<Type> const &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	vector<Type> u = v;
	SortSelectionInPlace(u, ascending, compare);
	return u;
}

template <typename Type>
void SortInsertionInPlace
	(
		vector<Type> &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	int reverse = ReverseFlag(ascending);

	for (int i=0; i<v.size(); i++)
	{
		Type current = v[i];
		int j;
		for (j=i-1; j>=0 && compare(v[j], current, reverse)==1; j--)
		{
			v[j+1] = v[j];
		}
		v[j+1] = current;
	}
}

template <typename Type>
vector<Type> SortInsertion
	(
		vector<Type> const &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	vector<Type> u = v; SortInsertionInPlace(u); return u;
}

template <typename Type>
int SortQuickPartition
	(
		vector<Type> &v,
		int start, int stop,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	int reverse = ReverseFlag(ascending);

	int lh = start + 1, rh = stop;
	Type pivotValue = v[start];

	while (true)
	{
		while ((lh < rh) && (compare(v[rh], pivotValue, reverse) >= 0 )) rh--;
		while ((lh < rh) && (compare(v[lh], pivotValue, reverse) == -1)) lh++;

		if (lh == rh) break;
		SwapInPlace(v[lh], v[rh]);
	}
	if (compare(v[lh], pivotValue, reverse)>=0) return start;
	SwapInPlace(v[start], v[lh]);
	return lh;
}

template <typename Type>
void SortQuickInPlace
	(
		vector<Type> &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare,
		int start = 0, int stop = -10,
		bool debugFlag = false
	)
{
	// cout << "Inside SortQuickInPlace" << endl;
	if (stop == -10) stop = v.size() - 1;
	if (globalDebugFlag || debugFlag)
		cout << "Value of stop index is: " << stop << endl;
	if (stop > start)
	{
		int pivotIndex = SortQuickPartition(v, start, stop, ascending, compare);
		SortQuickInPlace(v, ascending, compare, start, pivotIndex -1);
		SortQuickInPlace(v, ascending, compare, pivotIndex + 1, stop);
	}
}

template <typename Type>
vector<Type> SortQuick
	(
		vector<Type> const &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare,
		int start = 0, int stop = -10
	)
{
	if (stop == -10) stop = v.size()-1;
	vector<Type> sorted = v;
	SortQuickInPlace(sorted, ascending, compare);
	return sorted;
}

template <typename Type>
void Merge
	(
		vector<Type> &v,
		vector<Type> &left, vector<Type> &right,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	int reverse = ReverseFlag(ascending);

	int p, l, r;
	p = l = r = 0;

	while (l < left.size() && r < right.size())
	{
		if (compare(left[l], right[r], reverse)==-1)
			v[p++] = left[l++];
		else
			v[p++] = right[r++];
	}
	while (l < left.size()) v[p++] = left[l++];
	while (r < right.size()) v[p++] = right[r++];
}

template <typename Type>
void SortMergeInPlace
	(
		vector<Type> &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare,
		bool debugFlag = false
	)
{
	if (v.size()>1)
	{
		int n = v.size()/2;
		vector<Type> left = Subvector(v, 0, n-1);
		vector<Type> right = Subvector(v, n, v.size()-1);

		if (globalDebugFlag || debugFlag)
		{
			cout << "Left: " << endl;
			cout << left << endl;

			cout << "Right: " << endl;
			cout << right << endl;
		}

		SortMergeInPlace(left, ascending, compare);
		SortMergeInPlace(right, ascending, compare);
		Merge(v, left, right, ascending, compare);
	}
}

template <typename Type>
vector<Type> SortMerge
	(
		vector<Type> const &v,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare
	)
{
	vector<Type> u = v; SortMergeInPlace(u, ascending, compare); return u;
}

enum SortType 
{ 
	QuickSort = 0, 
	MergeSort, 
	SelectionSort,
	InsertionSort,
	EfficientSort 
};

template <typename Type>
void SortGenericInPlace
	(
		vector<Type> &v,
		bool ascending = true,
		SortType algorithm = QuickSort
	)
{
	switch (algorithm)
	{
		case QuickSort: 	SortQuickInPlace(v, ascending); break;
		case MergeSort: 	SortMergeInPlace(v, ascending); break;
		case SelectionSort:	SortSelectionInPlace(v, ascending); break;
		case InsertionSort: SortInsertionInPlace(v, ascending); break;
		// case Efficient: return SortEfficientInPlace(v, ascending); break;
	}
}


template <typename Type>
vector<Type> SortGeneric
	(
		vector<Type> const &v,
		bool ascending = true,
		SortType algorithm = QuickSort
	)
{
	vector<Type> u = v;
	SortGenericInPlace(u, ascending, algorithm);
	return u;
}

const int NotFound = -1;

template <typename Type>
int BinarySearchSorted 
	(
		vector<Type> const &v,
		Type key,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare,
		int start = 0, int stop = -10
	)
{
	if (stop == -10)
		stop = v.size()-1;
	if (start > stop) return NotFound;
	int mid = (start + stop)/2;

	int reverse = ReverseFlag(ascending);
	
	if (compare(key, v[mid], reverse) == 0)
		return mid;
	else if (compare(key, v[mid], reverse) == -1)
	{
		return 	BinarySearchSorted 
				(
					v,
					key,
					ascending,
					compare,
					start, mid-1
				);
	}
	else if (compare(key, v[mid], reverse) == 1)
	{
		return 	BinarySearchSorted
				(
					v,
					key,
					ascending,
					compare,
					mid+1, stop
				);
	}
}

template <typename Type>
int BinarySearchGeneric
	(
		vector<Type> const &v,
		Type key,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare,
		int start = 0, int stop = -10,
		int sorted = 0
	)
{
	bool ascending = true;
	if (sorted == -1)
		ascending = false;

	vector<Type> u;
	if (sorted == 0)
		u = SortGeneric(v);
	else
		u = v;
	
	return 	BinarySearchSorted
				(
					u,
					key,
					ascending,
					compare,
					start, stop
				);
}


vector<string> UserInputVector()
{
	int index = 0;
	string value;
	vector<string> v;
	int n;

	cout << "Enter the number of elements: " << endl;
	cin >> n;

	while (index<n)
	{
		cout << "Enter element number " << index << ":" << endl;
		cin >> value;
		v.push_back(value);
		index++;
	}

	cout << "The vector entered by you is:" << endl;
	cout << v << endl;
	return v;
}

vector<int> RandomVectorInt()
{
	int sizeMin = 10;
	int sizeMax = 15;

	int elemMin = 1;
	int elemMax = 100;

	/* initialize random seed: */
  	// srand (time(NULL));
  	InitializeSrand();

  	vector<int> randVector;
  	
  	/* generate a random position to cut the deck of cards */
  	int randSize = rand() % (sizeMax - sizeMin + 1) + sizeMin;
  	cout << "The size of the vector is: " << randSize << endl;

  	for (int i=0; i<randSize; i++)
  	{
  		randVector.push_back(rand() % (elemMax - elemMin + 1) + elemMin);
  	}

  	cout << "The random vector is: " << endl;
  	cout << randVector << endl;

  	return randVector;
}


template <typename Type>
bool IsValidSort
	(
		vector<Type> const &original, 
		vector<Type> sorted,
		bool ascending = true,
		int (compare)(Type one, Type two, int reverse) = OperatorCompare,
		bool debugFlag = true
	)
{
	if (original.size() != sorted.size()) return false;


	int reverse = ReverseFlag(ascending);
	for (int i=0; i<sorted.size()-1; i++)
	{
		if (globalDebugFlag || debugFlag)
		{
			cout << "sorted[i] is: " << sorted[i] << endl;
			cout << "sorted[i+1] is: " << sorted[i+1] << endl;
			cout << "compare value is: " << compare(sorted[i], sorted[i+1], reverse) << endl;
		}
		if (compare(sorted[i], sorted[i+1], reverse)>0) return false;
	}

	for (int i=0; i<original.size(); i++)
	{
		int index = BinarySearchSorted(sorted, original[i],	ascending, compare);
		if (index == -1) return false;
		sorted.erase(sorted.begin() + index);
		if (globalDebugFlag || debugFlag)
		{
			cout << "IsValidSort Test: Popping elements in sorted vector that are in the original vector" << endl;
			cout << sorted << endl;
		}
	}

	if (sorted.size() != 0) return false;

	return true;
}

template <typename Type>
void SortTester(vector<Type> &v)
{
	bool ascending = false;
	vector<Type> u = SortGeneric(v, ascending, MergeSort);

	if (!IsValidSort(v, u, ascending)) 
	{
		cout << "ERROR: Sort operation failed. Sort invalid." << endl;
		return;
	}
	string order = ascending ? "ascending" : "descending";
	cout << "The vector entered by you in " << order << " order is:" << endl;
	cout << u << endl;
}

int main()
{
	vector<string> v = UserInputVector();
	// vector<int> v = RandomVectorInt();
	SortTester(v);
	return 0;
}
