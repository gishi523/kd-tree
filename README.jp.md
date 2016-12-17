# kd-tree
k-d treeのc++実装です

====

<img src=https://dl.dropboxusercontent.com/u/36775496/kdtree_I0.png width=256>
<img src=https://dl.dropboxusercontent.com/u/36775496/kdtree_I1.png width=256>
<img src=https://dl.dropboxusercontent.com/u/36775496/kdtree_I2.png width=256>

## 概要
- k-d treeのc++実装です
- ヘッダをインクルードするだけで使えます
- 以下の近傍探索機能を提供します
  - 最近傍探索(Nearest neighbor search)
  - k-最近傍探索(K-nearest neighbor search)
  - 半径内に含まれる近傍の探索(Radius search)

## KDTreeクラスの使い方
- KDTreeクラスはユーザー定義のPoint型をテンプレートパラメータにとります
- ユーザー定義のPoint型は最低限以下の仕様を満たす必要があります
  - 添え字演算子(operator[])の実装 <= Point型の各座標へのアクセス手段
  - 静的メンバ変数 DIM             <= Point型の次元
- 点群をKDTreeのコンストラクタに渡すとk-d treeが構築されます
- 構築後のk-d treeに対して近傍探索機能を使用します

```
#include "kdtree.h"

// ユーザ定義のPoint型 (operator[]を使うためstd::arrayを継承)
class MyPoint : public std::array<double, 2>
{
public:

	// Point型の次元
	static const int DIM = 2;

	// 以下ご自由に
	// ...
};

int main()
{
	// 点群を生成
	std::vector<MyPoint> points = ...;

	// k-d treeを構築
	kdt::KDTree<MyPoint> kdtree(points);

	// k-近傍探索 (近傍へのインデックスを取得)
	int k = 10;
	MyPoint query = ...;
	std::vector<int> indices = kdtree.knnSearch(query, k);

	return 0;
}

```

## Requirement
- OpenCV(サンプルコードのみ)

## サンプルコード
### ビルド方法
```
$ git clone https://github.com/gishi523/kd-tree.git
$ cd kd-tree
$ mkdir build
$ cd build
$ cmake ../
$ make
```

### 実行方法
```
./kdtree [seed]
```
- seed
    - 点群をランダムに生成する際のシード

## Author
gishi523
