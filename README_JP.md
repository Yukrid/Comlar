COMLAR

---

C++のコマンドライン引数の処理を簡単に実装するためのヘッダーオンリーライブラリです．

## Description

COMLARはコマンドライン引数の処理をサポートするライブラリです．ユーザーはオプション名，入力型，オプション処理の３つを定義するだけで簡単にコマンドオプションを実装できます．文字列から型への変換を自動で行う他，自動でのヘルプ作成や，単純なオプション処理の省略などが実装されています．楽にコマンド処理を実装できる設計を目指しています．

## Requirement

C++17

## Install

cmakeを使ったインストールに対応しています．

```shell
git clone https://github.com/Yukrid/Comlar
cd Comlar
mkdir build
cd build
cmake ..
make
sudo make install
```

COMLARはヘッダーオンリーライブラリのため，リポジトリを直接ダウンロードし，`include` 内のファイル，ディレクトリを全てコピーして `#include "comlar.hpp"` を行うだけでも使用できます．

## Usage

[User Manual](/MANUAL_JP.md) を参照して下さい．

## LICENSE

GNU General Public License v3.0
