# ExamGame
Made By Thistle(@ciesle)

私はGithubの使い方に明るくないので、アプリケーションの使い方だけを適当に書いておきます。

## アプリケーションの説明
暗記をするためのアプリです。
使用ライブラリは、OpenSiv3D 0.4.2です。
単語帳電子版だと思っておけば正しいです。
問題セット機能を使うことで、繰り返し用いる組み合わせを保存することができます。

## 使い方
### 問題制作
1. 出題する問題を作ります。
2. .csvファイルに問題を書き込みます。。問題がA列、答えがB列です。
3. 問題集合を作ります。hoge.txtを作り、中にhuga.csvのファイル名「huga」を改行区切りで書き込むだけです。
4. 問題集合にはほかの問題集合を入れることもできます。
5. 問題ファイルのC列にはプログラムによって自動的に「learned」「notlearned」が追加されます。learnedになった問題は二度と出題されません。
6. 問題はフォルダの中に入れても検知されますが、同名ファイルが2つ以上あった場合の処理は未定義です。
### 問題を解く
1. ExamGame.exeを起動します。
2. Filenamesに出題する問題ファイル名/問題集合名を入れます。(拡張子はつけない)何もいれなかった場合、Probsという名前の問題集合が使用されます。
3. not reverse は問題と答えを反転しないか、randomizeは問題と答えのどちらを提示するかを選ぶもので、randomizeのほうがnot reverseよりも優先順が上です。
4. Start!で開始します
5. 問題が分かったらOKを押し、この問題をもう出さなくてよい場合はNeverをクリックします。Neverの設定はアプリを閉じても保持されます。
6. Never以外の青いボタンは全てEnterキーで代用でき、Neverはバックスペースキーで代用できます。

## その他
Probs/not_referencedファイルに入れた問題ファイルは参照されません。


Copyright (c) 2021 Thistle
Released under the MIT license