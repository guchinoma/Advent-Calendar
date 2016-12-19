　本稿は,情報セキュリティ系論文紹介 Advent Calendar 2016の17日目である.

###はじめに
　今回は, “Explaining and Harnessing Adversarial Examples” を解説するつもりだった. しかし, いざこれをネタに書こうという段になってGoogleで検索してみると, 2, 3つぐらい, (筆者の理解が進むくらい)よく解説されている記事(http://sotetsuk.hatenablog.com/entry/2015/12/16/185102, http://fireflower.hatenablog.com/entry/2016/12/13/111016) を見つけてしまい, 完全にネタ切れ状態になった. ということで, 話の枕として最近発表された, ディープニューラルネットワーク向けにAdversarial Examplesを作るOSS, Deep-Pwningのソースコードをざっくり解説して, そしてその元になった考え方を当論文を援用して解説を試みる. 本稿にはどこか間違っているところがあるかもしれない. その際は是非”優しい”まさかりを乞いたい次第である.

###Adversarial Examplesとは
　Adversarial Examplesとは, 元の画像にノイズを加えることで, 機械学習に誤認識を起こさせる画像である. 機械学習のうち, 教師あり学習であるディープニューラルネットワーク(DNN)では,大量のデータを用いて学習させる.  例えば, 三種類の動物, パンダ, シマウマ, ブタの画像をDNNにたくさん学習させる例を考える. その後. 訓練データとは違うパンダの画像をを突っ込むと, 正しく判定をする. ここで特定の方法で生成されたノイズを, その正しく判定されたパンダの画像突っ込む. そしてそれを同じDNNに学習させると, シマウマだったり, ブタだったりと, 全く違う判別する. しかも, そのノイズ入り画像は, 人間にとっては全くパンダにしか見えないのに, である. 以下の図は, 別のDNNで, パンダと識別されていたものが, ノイズを加えることで, Gibbon(テナガザル)と出てしまうことを説明している. ノイズの下によく分からない数式が書いてあるが, これは後で解説する. 以下の図は, 別のDNNで, パンダと識別されていたものが, ノイズを加えることで, Gibbon(テナガザル)と出てしまうことを説明している. ノイズの下によく分からない数式が書いてあるが, これは後で解説する.
　

###Deep-Pwningとは
　Deep-Pwning(https://github.com/cchio/deep-pwning) とは, Clarence Chio氏がDEF CON 24の時に発表した, Adversarial Examplesを生成するツールである. このソフトウェアは, 訓練データのダウンロードから, 訓練, Adversarial Examples生成までを自動化する. 例えば, MNISTのデータセットを使用してAdversarial Examplesを作りたいなら,  mnist_driver.pyを実行する. すると自動でMNISTのデータをダウンロードし, 畳み込みニューラルネット(CNN)を訓練させる. そして, そのテストデータと, 訓練されたCNNとは別のCNNを使用して, テストデータの数だけAdversarial Examplesを生成し, pickleの形式で保存する. MNISTのときは一時間くらいで生成されるが, CIFAR-10の場合は, 訓練にかなり時間を要してしまう. GPUで使うのが効率的か. 現在では, MNISTの他, CIFAR-10のデータセットに対応している. このコードの何がAdversarial Examplesを生成しているかというと, adversarialファイルのfastgradientsign_advgen.py中の次のコードである.
 ```python:fastgradientsign_advgen.py
　adv_image = perturbation * grad_sign + image
 ```
　imageは, ノイズを挿入する前の画像, perturbationとは, confファイルで個別に設定された係数である. grad_signとは, 損失関数を微分した式に, Adversarial Example用のCNNにimageを突っ込んで計算した値を代入した値である. 端的にいうと, このperturbation * grad_signがノイズの正体である. 一体なぜこれで誤認識してしまうのか.


###Fast Gradient Sign Methodとは
　この式は, “Explaining and Harnessing Adversarial Examples”において提案されているFast Gradient Sign Methodである. まず, あらかじめDNNのバイアスの値と重みの値を適当に決めて, 訓練データをDNNに突っ込んで計算する. その計算結果で, データがどのラベルを示すのか確定する. 計算結果でのラベルと, 本当のラベルを, 損失関数を用いて比較する. 損失関数とは, そのデータがどのくらい確からしいのか示す関数である. 分類では, 主に交差エントロピー関数をつかう. もし計算結果が間違っていたら, 損失関数を微分した値を用いて,重みとバイアスを更新する. 一般的に損失関数の計算結果が大きければ, 予測ラベルが本当のラベルと乖離していることを示し, 逆に0に近ければ, 予測が正しいことを示す. とすれば, わざと損失関数を大きくすれば, それだけDNNが間違う可能性が高まる. これがAdversarial Examplesの基本的な考え方だ. 

　以下の図を見ていただきたい. J(x)は損失関数を示す. まずこの式を一次テイラー展開を用いて近似式を作る. 先ほどのこの微分した方の式をなるべく最大化したい. しかし, そのまま使用すると, どうしてもノイズが大きくなってしまう. そこで, 符合関数を導入し, 更に係数εをせってすることで, 調整をしている. それがこの, Fast Gradient Sign Methodの要諦である. この論文では, なぜadversarial examplesは誤認識を起こすのか, ということを, 結合層の線形性に着目して解説しているが, もっと詳しい説明は, 前掲のブログに譲りたいと思う.

###おわりに
　以上, 急遽内容を変えて書いてみたが, なんか全体的に薄く間延びしてしまった. 自分ごときの解像度ではこれが限界だった. 

###参考文献
　“Explaining and Harnessing Adversarial Examples” Goodfellow et al.
