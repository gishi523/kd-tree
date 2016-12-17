# kd-tree
A c++ implementation of k-d tree

====

<img src=https://dl.dropboxusercontent.com/u/36775496/kdtree_I0.png width=256>
<img src=https://dl.dropboxusercontent.com/u/36775496/kdtree_I1.png width=256>
<img src=https://dl.dropboxusercontent.com/u/36775496/kdtree_I2.png width=256>

## Description
- A c++ implementation of k-d tree
- Header-only library
- Provides following Nearest neighbor search functions
  - Nearest neighbor search
  - K-nearest neighbor search
  - Radius search

## How to use KDTree class
- KDTree class takes a user-defined Point type as its template parameter
- A user-defined Point type needs to satisfy following specifications
  - Implementation of operator[] <= accessor to its coordinates
  - Static member variable DIM <= dimension of the Point
- Passing point cloud to KDTree constructor starts to build k-d tree
- After building k-d tree, you can use Nearest neighbor search functions

```
#include "kdtree.h"

// user-defined Point type (inherits std::array in order to use operator[])
class MyPoint : public std::array<double, 2>
{
public:

	// dimension of the Point
	static const int DIM = 2;

	// As you want
	// ...
};

int main()
{
	// generate point cloud
	std::vector<MyPoint> points = ...;

	// build k-d tree
	kdt::KDTree<MyPoint> kdtree(points);

	// K-nearest neighbor search (gets indices to neighbors)
	int k = 10;
	MyPoint query = ...;
	std::vector<int> indices = kdtree.knnSearch(query, k);

	return 0;
}

```

## Requirement
- OpenCV (only for running sample code)

## Sample code
### How to build
```
$ git clone https://github.com/gishi523/kd-tree.git
$ cd kd-tree
$ mkdir build
$ cd build
$ cmake ../
$ make
```

### How to run
```
./kdtree [seed]
```
- seed
    - Seed of rand() in generating random point cloud

## Author
gishi523