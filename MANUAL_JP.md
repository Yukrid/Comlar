# User Manual

ユーザーマニュアルでは以下の内容を取り扱います．

- [基本的な使い方](#anc1)
  
  1. [実行器クラスのインスタンス化](#anc1-1)
  
  2. [オプション処理で使う変数の準備](#anc1-2)
  
  3. [オプションの定義](#anc1-3)
  
  4. [実行器クラスの実行関数を呼び出し](#anc1-4)
  - [コード例と出力結果](#anc1-5) ([example/basic.cpp](/example/basic.cpp))

- [追加機能](#anc2)
  
  1. [チェック処理の定義](#anc2-1)
  
  2. [自動ヘルプの追加](#anc2-2)
  - [コード例と出力結果](#anc2-3) ([example/additional.cpp](/example/additioal.cpp))

---

<a name="anc1"></a>

## 基本的な使い方

COMLARのコマンドライン処理を実装するには以下の流れで行います．

1. 実行器クラスのインスタンス化

2. オプション処理で使う変数の準備

3. オプションの定義

4. 実行器クラスの実行関数を呼び出し

<a name="anc1-1"></a>

### 1. 実行器クラスのインスタンス化

COMLARを利用するには，まずヘッダーをインクルードし，実行器(Executor)クラスのインスタンス化する必要があります．

```cpp
#include <comlar.hpp>

using namespace comlar;

int main(int argc, char** argv){

    Executor exec(argc, argv);
}
```

Executorクラスのコンストラクタの引数には，main関数の引数である `argc` 及び `argv` を指定して下さい．Executorクラスは，引数なしのデフォルトコンストラクタを使用することはできません．

<a name="anc1-2"></a>

### 2. オプション処理で使う変数の準備

COMLARは，コマンドライン引数であるオプションが選択されている時，そのオプションの入力値を文字列から取得し，そのオプションに応じたオプション処理を行います．オプション処理はただ入力値を代入するだけの非常に単純なものから，ユーザー定義の複雑な処理まで様々なものが考えられます．COMLARのシステムでは，このオプション処理の結果を，事前に定義された変数（外部変数）を書き換えることで受け取るため，予め外部変数を用意しておく必要があります．外部変数には任意の型を使用することができます．

オプション処理で書き換えられる外部変数の寿命は，Executorクラスのexecute関数が実行されるまで維持されている必要があります．

<a name="anc1-3"></a>

## 3. オプションの定義

次にオプションを定義します．オプションはOptionクラスをインスタンス化し，Executorクラスのadd_option 関数を用いて実行器に追加します．

#### Optionクラスのインスタンス化

Optionクラスはテンプレートで，２つのクラスをテンプレートパラメータに追加する必要があります．１つ目のクラスは Arg クラスで，２つ目のクラスは Ope クラスである必要があります．Arg および Ope クラスはどちらも可変引数テンプレートクラスです．

Arg クラスのテンプレートパラメータには，コマンドライン引数を読む時に受けたい値の型（入力値の型）を指定します．Arg クラスのテンプレートパラメータには基本的な整数型とfloat, double, char*, std::stringが使用できます．char型は文字として，unsigned charは数値と処理されます．Opeクラスのテンプレートパラメータにはコマンド処理で変更したい外部変数の型を指定します．入力値の型のパラメータパックを `As...` ，外部変数の型のパラメータパックを`Bs...` とした時，Optionクラスは `Option<Arg<As...>,Ope<Bs...>`となります．

Optionクラスのインスタンス化には，オプションの省略名(`name1`)，正式名(`name2`)，必須フラグ(`flag`)，およびオプション処理で使用する外部変数の参照(`bs...`)を必要とします．必須フラグには `REQUIRED`と`OPTIONAL`を指定することができます．`REQUIRED`指定されたオプションがコマンドライン引数を全て読み終わっても指定されていなかった場合，実行器はエラーを返します．実際に次の様にインスタンス化します．

```cpp
Option<Arg<As...>,Ope<Bs...> opt{name1, name2, flag, bs...}
```

#### オプション処理の指定

Optionクラスのインスタンス化後，Optionクラスのメンバー関数であるset_operate 関数を用いてオプション処理を定義します．set_operate 関数の引数は，戻り値がint型の関数ポインタである必要があり，引数はOpetionクラス宣言時に指定したArgおよびOpeクラスのテンプレートパラメータと整合していなければいけません（引数の型が不整合でもコンパイルエラーにはなりません）．

`Option<Arg<As...>, Ope<Bs...>>`クラスを宣言した場合，期待されるオプション処理関数の関数ポインタの型は `int(*)(const As&..., Bs&...)`です．

オプション処理関数の戻り値に0以外を指定した場合，異常処理として扱われ，実行器は処理中のオプション名と戻り値を出力した上でプログラムを終了させます．

１変数を代入する処理の場合はdefault_assign関数，bool型の変数を変えるだけの処理の場合はdafault_flag関数が使用することで，オプション処理関数の定義を省略できます．

#### オプション定義の例

具体的に幾つかのOptionクラスのインスタンス化・オプション処理関数の指定例を示します． 

##### 例１ ( -s  --scalar )

| 省略名  | 正式名        | 入力型   | 処理で使用する外部変数     | 必須  | 使用例       |
| ---- | ---------- | ----- | --------------- | --- | --------- |
| `-s` | `--scalar` | float | float: `scalar` | YES | `-s 3.13` |

- オプション処理
  
  float型の入力値をfloat型の外部変数`scalar`に代入する．

- ユーザー定義の場合
  
  ```cpp
  float scalar;
  Option<Arg<float>,Ope<float>> opt{"s", "scalar", REQUIRED, scalar}; 
  opt.set_operate(+[](const float& in_, float& scalar_){
      scalar_=in_;
      return 0;
  });
  exec.add_option(opt);
  ```

- default_assign関数を使用する場合
  
  ```cpp
  float scalar;
  Option<Arg<float>,Ope<float>> opt{"s", "scalar", REQUIRED, scalar}; 
  opt.set_operate(default_assign<float>());
  exec.add_option(opt);
  ```

##### 例２ ( -f  --flag )

| 省略名  | 正式名      | 入力型  | 処理で使用する外部変数  | 必須  | 使用例  |
| ---- | -------- | ---- | ------------ | --- | ---- |
| `-f` | `--flag` | （なし） | bool: `flag` | NO  | `-f` |

- オプション処理
  
  入力値はなしでbool型の外部変数`flag`を`true`にする．

- ユーザー定義の場合
  
  ```cpp
  bool flag;
  Option<Arg<>,Ope<bool>> opt{"f", "flag", OPTIONAL, flag}; 
  opt.set_operate(+[](bool& flag_){
      flag_=true;
      return 0;
  });
  exec.add_option(opt);
  ```

- default_flag関数を使用する場合
  
  ```cpp
  bool flag;
  Option<Arg<>,Ope<bool>> opt{"f", "flag", OPTIONAL, flag}; 
  opt.set_operate(default_flag<true>());
  exec.add_option(opt);
  ```

##### 例３ ( -pm   --pmave )

| 省略名   | 正式名       | 入力型      | 処理で使用する外部変数            | 必須  | 使用例        |
| ----- | --------- | -------- | ---------------------- | --- | ---------- |
| `-pm` | `--pmave` | int, int | float: `plus`, `minus` | NO  | `-pm -1 3` |

- オプション処理
  
  int型の２つの入力値を平均し，平均値を`plus` に加算し，`minus`から減算する．

- ユーザー定義の場合
  
  ```cpp
  float plus=1.0, minus=1.0;
  Option<Arg<int, int>,Ope<float, float>> opt{"pm", "pmave", OPTIONAL, plus, minus};
  opt.set_operate(+[](const int& in1_, const int& in2_, float& plus_, float& minus_){
  
      float ave=static_cast<float>(in1_+in2_)*0.5;
      plus +=ave;
      minus-=ave;
  
      return 0;
  });
  exec.add_option(opt);
  ```

<a name="anc1-4"></a>

### 4. 実行器クラスの実行関数を呼び出し

コマンドを全て追加し終わったら，実行器のexcute関数を呼び出します．

```cpp
int result =exec.execute();
```

execute関数は，コマンドライン引数の処理中にエラーが発生した場合，メッセージを出力した上で，0 以外の値を返します．execute関数が戻り値には次のようなものがあります．

| 戻り値 | メッセージ                                                                      | 補足                                         |
| --- | -------------------------------------------------------------------------- | ------------------------------------------ |
| 0   | (なし)                                                                       | 成功した．                                      |
| -1  | Terminal function called due to invalid number of arguments.               | コマンドライン引数の文字列を変換・保存する際に到達しないはずの関数に到達した．    |
| -2  | * is not expected.                                                         | オプションとして認識されない文字列が，オプションが来るべき所で検出された．      |
| -3  | *  is unknown option.                                                      | オプションとして登録されていない文字列が，オプションが来るべき所で検出された．    |
| -4  | * is required but not inputed.                                             | 必須オプション（`REQUIRED`）指定されたオプションが選択されていない．    |
| -5  | * should have more * arguments.                                            | オプションで予期している数の入力値を読んでいないのにコマンドライン引数を読み切った． |
| -6  | Input value does not satisfy the constraint. Error detected in checking *. | デフォルトチェック関数で指定した制約条件を満たさない数値が入力された．        |

COMLAR内のシステムは，今後新たな値が追加される場合であっても，負の値を戻り値として使用します．そのため自身で作成したユーザー定義関数の戻り値には正の値を用いることを推奨しています．



 <a name="anc1-5"></a>

### コード例と出力結果

```cpp
#include <comlar.hpp>
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    // 1. Instantiation of Executor class
    Executor exec(argc, argv);


    // 2. Prepare variables for use in option operation
    float scalar;
    bool  flag;
    float plus=1.0, minus=1.0;


    // 3. Definition of options
    // Example1 (-s --scalar)
    {
        Option<Arg<float>, Ope<float>> opt{"s", "scalar", REQUIRED, scalar};
        opt.set_operate(default_assign<float>());
        exec.add_option(opt);
    }

    // Example2 (-f --flag)
    {
        Option<Arg<>, Ope<bool>> opt{"f", "flag", OPTIONAL, flag};
        opt.set_operate(default_flag<true>());
        exec.add_option(opt);
    }

    // Example3 (-pm --pmave)
    {
        Option<Arg<int, int>, Ope<float, float>> opt{"pm", "pmave", OPTIONAL, plus, minus};
        opt.set_operate(+[](const int& in1_, const int& in2_, float& plus_, float& minus_){

            float ave=static_cast<float>(in1_+in2_)*0.5;
            plus_ +=ave;
            minus_-=ave;

            return 0;
        });
        exec.add_option(opt);
    }


    // 4. Call the execute function of Exectutor class
    int result=exec.execute();
    if(result){
        std::cout<<"result: "<<result<<std::endl;
        std::exit(EXIT_FAILURE);
    }


    // Result
    std::cout<<"scalar: "<<scalar<<std::endl;
    std::cout<<"flag  : "<<flag<<std::endl;
    std::cout<<"plus  : "<<plus<<std::endl;
    std::cout<<"minus : "<<minus<<std::endl;
    std::cout<<"result: "<<result<<std::endl;
};
```

#### 出力結果（成功）

- `./a.out -s 2.3`
  
  ```
  scalar: 2.3
  flag : 0
  plus : 1
  minus : 1
  result: 0
  ```

- `./a.out -s 2.3 -f -pm 0 3`
  
  ```
  scalar: 2.3
  flag  : 1
  plus  : 2.5
  minus : -0.5
  result: 0
  ```

#### 出力結果（失敗）

- `./a.out`
  
  必須オプション`-s`がない．
  
  ```
  comlar::Executor::execute] -s --scalar is required but not inputed.
  result: -4
  ```

- `./a.out -t`
  
  追加していないオプション`-t`が使用されている
  
  ```
  [comlar::Executor::execute] -t is unknwon option.
  result: -3
  ```

- `./a.out -pm 0`
  
  `-pm`の引数が不足している
  
  ```
  [comlar::Executor::execute] -pm --pmave should have more 1 argments.
  result: -5
  ```

---

<a name="anc2"></a>

# 追加機能

<a name="anc2-1"></a>

## 1. チェック処理の定義

オプションを定義する際，オプション処理関数と同じ要領で，入力値のチェックを行うための関数を指定することができます．チェック関数は，オプション処理を実行する前に実行されます．チェック関数は必須ではなく，定義しなかった場合はチェック処理の呼び出し自体が行われません．

チェック関数の引数は入力値のみで，外部変数を受け取ることはできません．チェック関数の指定はOptionクラスのset_check関数で行います．`Option<Arg<As...>, Ope<Bs...>>`クラスを宣言した場合，期待されるチェック関数の関数ポインタの型は `int(*)(const As&...)`です．

#### デフォルトチェック関数

数値が単純な比較条件を満たしているか確認するチェック関数を実装したい場合，default_cstr関数，default_and_cstrs関数，default_or_cstrs関数を利用できます．default_cstr関すは１つの式評価を，default_and_cstrs関数，dafault_or_cstrs関数は複数の式をそれぞれ`and`，`or`で連結して評価します．

デフォルトチェック関数には，評価の仕方を評価クラスを用いてテンプレートパラメータとして与え，数値を引数で与えます．テンプレートパラメータに与えられる評価クラスには以下のようなものがあります．

| 評価クラス | 式    |
| ----- | ---- |
| `Les` | `<`  |
| `Leq` | `<=` |
| `Grt` | `>`  |
| `Geq` | `>=` |
| `Eq`  | `=`  |
| `Neq` | `!=` |

これらのクラスを用いて入力値と指定された値を式で評価し，`true`であった場合，チェックに成功します．デフォルトチェック関数内でチェックに失敗した場合，Executorのexecute関数は戻り値 `-6` を返します．

#### チェック処理の定義例

以下に例を示します．

##### 例１

- チェック処理
  
  int型の入力値`in_`について`in_!=0`であることをチェックする．

- ユーザー定義の場合
  
  ```cpp
  opt.set_check(+[](const int& in_){
      if(in_) return 0;
      else    return 1; 
  });
  ```

- defalut_cstr関数を使用する場合
  
  ```cpp
  opt.set_check(default_cstr<int, Neq>(0))
  ```

##### 例２

- チェック処理
  
  float型の入力値`in_`について`-1.<=in_<1.`を満たしていることをチェックする．

- ユーザー定義の場合
  
  ```cpp
  opt.set_check(+[](const float& in_){
      if(-1.<=in_ and in_<1.) return 0;
      else                    return 1; 
  });
  ```

- defalut_and_cstrs関数を使用する場合
  
  ```cpp
  opt.set_check(default_and_cstrs<float, Geq, Les>({-1., 1.}))
  
  ```



<a name="anc2-2"></a>

## 2. 自動ヘルプの追加

### ヘルプの追加

COMLARは自動でヘルプを追加する機能を備えています．ヘルプの追加は全てのコマンドを追加し終わった後に，Executorクラスのadd_help関数を用いて追加できます．

```cpp
exec.add_help("Header String")
```

add_help関数の第1引数にstd::string型の文字列を挿入することで，ヘルプ表示時に出力されるヘッダーを追加できます．ヘルプに表示されるオプションの順番は，Executorに追加された順になります．

### ヘルプ表示時のオプションの説明・追加情報

各オプション毎にヘルプ表示時の説明と追加情報を設定できます．オプションの説明と追加情報を設定するにはOptionクラスのset_info関数を使用します．

```cpp
opt.set_info("Explanation", "Additional Information")
```

### フィールドによるオプションの分類分け

自動ヘルプを使用する際にフィールドを使用することができます．フィールドを利用することでヘルプを表示する際に各オプションを分類分けして表示させることができます．フィールドを利用するにはまずExecutorのadd_field関数でフィールドを追加します．

```cpp
Field f1=exec.add_field("Field1");
```

Field型の変数`f1`はそれぞれのオプションをフィールドに追加する際に使用します．add_field関数を使用した場合，`f1`の値は0より大きいものになります．

次にそれぞれのOptionのset_field関数を用いて，オプションをフィールド分けさせます．

```cpp
opt.set_field(f1);
```

各OptionクラスはField型の値を保持しており，デフォルトでは0です．

ヘルプ表示時，フィールドはadd_field関数で追加した順に表示され，更にそのフィールドに属しているコマンドが，追加した順に表示されます．



<a name="anc2-3"></a>

## コード例と出力結果

```cpp
#include <comlar.hpp>
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    // 1. Instantiation of Executor class
    Executor exec(argc, argv);

    //*** Add field1
    Field f1=exec.add_field("Field1");


    // 2. Prepare variables for use in option operation
    float scalar;
    bool  flag;
    float plus=1.0, minus=1.0;


    // 3. Definition of options
    // Example1 (-s --scalar)
    {
        Option<Arg<float>, Ope<float>> opt{"s", "scalar", REQUIRED, scalar};
        //*** Set check function
        opt.set_check(default_and_cstrs<float, Geq, Les>({-1., 1.}));
        opt.set_operate(default_assign<float>());
        //*** Set information for help
        opt.set_info("set scalar value", "<=-1 and <1");
        exec.add_option(opt);
    }

    // Example2 (-f --flag)
    {
        Option<Arg<>, Ope<bool>> opt{"f", "flag", OPTIONAL, flag};
        opt.set_operate(default_flag<true>());
        //*** Set information for help
        opt.set_info("turn on flag");
        exec.add_option(opt);
    }

    // Example3 (-pm --pmave)
    {
        Option<Arg<int, int>, Ope<float, float>> opt{"pm", "pmave", OPTIONAL, plus, minus};
        opt.set_operate(+[](const int& in1_, const int& in2_, float& plus_, float& minus_){

            float ave=static_cast<float>(in1_+in2_)*0.5;
            plus_ +=ave;
            minus_-=ave;

            return 0;
        });
        //*** Set field
        opt.set_field(f1);
        //*** Set information for help
        opt.set_info("add and subtract average");
        exec.add_option(opt);
    }

    //*** Add help
    exec.add_help("Header String");


    // 4. Call the execute function of Exectutor class
    int result=exec.execute();
    if(result){
        std::cout<<"result: "<<result<<std::endl;
        std::exit(EXIT_FAILURE);
    }



    // Result
    std::cout<<"scalar: "<<scalar<<std::endl;
    std::cout<<"flag  : "<<flag<<std::endl;
    std::cout<<"plus  : "<<plus<<std::endl;
    std::cout<<"minus : "<<minus<<std::endl;
    std::cout<<"result: "<<result<<std::endl;
}
```

#### 出力結果（成功）

- `./a.out -h`
  
  ```
  Header String
   -s  --scalar  set scalar value          <f>  <=-1 and <1
   -f  --flag    turn on flag      (Opt.)                  
   -h  --help    show help         (Opt.)                  
  
  [Field1]
   -pm  --pmave  add and subtract average  (Opt.)  <i, i>  
  ```

#### 出力結果（失敗）

- `./a.out -s -1.1`
  
  `-s` オプションの数値が，-1以上1未満の値の制約を満たさなかったため
  
  ```
  [comlar::(default_cstr::func)] Input value does not satisfy the constraint.
  [comlar::Executor::execute] Error detected in checking -s --scalar (-6).
  result: -6
  ```


