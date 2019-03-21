# openCV_color_tracker
これは東京大学2019年五月祭工学展覧会の制御班が制作する、二次元倒立振子に必要となっているコンピュータビジョンのモジュールである。
This module is aiming to get location of certain color object in camera image.
U-Tokyo Department of Applid Physics hold own exhibition during 2019's U-Tokyo May-Fes, besides "object control group" manufacture 2 degree of freedom inverted pendulum. We use this computer vision module to obtain the position of inverted pendulum.

```
visual studioのパス設定
include C:\opencv\build\include
lib C:\opencv\build\x64\vc15\lib\opencv_world401.lib
全般->出力ディレクトリ $(SolutionDir)build\
デバック->作業ディレクトリ $(ProjectDir)build\
だけで良い
プレコンパイル済みヘッダーの不使用
```