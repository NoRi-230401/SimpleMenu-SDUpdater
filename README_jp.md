# SimpleMenu-SDUpdater
**[`　English　`](README.md)**

## 1. はじめに

このプログラムは、M5Stackデバイス（Cardputer, Core2, CoreS3）上で、microSDカードに保存されたアプリケーション（`.bin`ファイル）をリスト表示し、選択して実行するためのシンプルなランチャーです。
M5StackUpdaterライブラリを利用して、選択したアプリケーションを起動します。

**元プログラム作成者:** @shikarunochi

**改修者:** NoRi


## 2. 対応デバイス

*   M5Stack Cardputer/Cardputer v1.1
*   M5Stack Core2/Core2 for AWS/Core2 v1.1
*   M5Stack CoreS3/CoreS3-SE

## 3. 準備するもの

*   上記のいずれかのM5Stackデバイス
*   microSDカード
*   実行したいM5Stack用のアプリケーションファイル（`.bin`形式）

## 4. 使い方

### 4.1. プログラムの準備

1.  実行したいアプリケーションの`.bin`ファイルをmicroSDカードの**ルートディレクトリ**（一番上の階層）にコピーします。
    *   例: `myapp.bin`, `game.bin` など

### 4.2. ランチャーの起動

1.  この`SimpleMenu-SDUpdater`プログラム (`SimpleMenu-SDUpdater\src\main.cpp` をコンパイルしたもの) をM5Stackデバイスに書き込みます。
2.  デバイスを起動すると、ランチャーが自動的に開始されます。

### 4.3. アプリケーションの選択と実行

画面に、microSDカードのルートディレクトリにある`.bin`ファイルの一覧がアルファベット順で表示されます。

*   **M5Stack Cardputer の場合:**
    *   **カーソル上移動:** `;` キー (セミコロンキー、上矢印の印字があるキー)
    *   **カーソル下移動:** `.` キー (ピリオドキー、下矢印の印字があるキー)
    *   **実行:** `Enter` キー

*   **M5Stack Core2 / CoreS3 の場合:**
    *   **カーソル上移動:** `BtnA` (一番左のボタン)
    *   **カーソル下移動:** `BtnC` (一番右のボタン)
    *   **実行:** `BtnB` (中央のボタン) を**長押し**

選択したアプリケーションが緑色でハイライト表示されます。実行したいアプリケーションを選択し、上記の操作で実行してください。

### 4.4. アプリケーションの実行後

選択したアプリケーションが読み込まれ、実行が開始されます。
アプリケーションの実行が終了するか、リセットされると、通常はデバイスが再起動し、再度このランチャーが起動します（選択したアプリケーションの仕様によります）。

## 5. 画面表示について

*   **ファイルリスト:** microSDカード内の`.bin`ファイル名が表示されます。
*   **選択中のファイル:** 現在カーソルが合っているファイル名が**緑色**で表示されます。その他のファイル名は白色で表示されます。
*   **ファイル名の長さ:** ファイル名が画面幅を超える場合、途中で省略されて表示されます。
    *   Cardputer: 約20文字まで
    *   Core2/CoreS3: 約26文字まで
*   **ヘルプメッセージ (Core2/CoreS3のみ):** 画面下部に簡単な操作方法（`up`, `select`, `down`）が黄色で表示されます。

## 6. 注意事項

*   `.bin`ファイルは必ずmicroSDカードの**ルートディレクトリ**に置いてください。サブフォルダ内のファイルは認識されません。
*   ファイル拡張子は`.bin`である必要があります（大文字・小文字は問いません）。
*   一度に画面に表示できるファイル数には限りがあります。ファイルリストが長い場合は、カーソルを移動させることでスクロールして選択できます。
*   microSDカードが正しく挿入されていない、または認識できない場合、ファイルリストは表示されません（または空のリストが表示されます）。
*   ファイル名に日本語などのマルチバイト文字を使用すると、文字化けする可能性があります。英数字のファイル名をおすすめします。

## 7. 開発者向け情報 (コード内の主要な設定値)

ソースコード `SimpleMenu-SDUpdater\src\main.cpp` 内の以下の定義値を変更することで、一部の動作をカスタマイズできます。

*   `dispfileCount`: 1画面に表示する最大のファイル数（実際には `dispfileCount + 1` 個のファイルが表示されます）。
    *   Cardputer: `7` (実際には8ファイル表示)
    *   Core2/CoreS3: `12` (実際には13ファイル表示)
*   `N_COLS`: ファイル名を表示する際の最大列数（おおよその文字数）。これを超えるファイル名は途中でカットされます。
    *   Cardputer: `20`
    *   Core2/CoreS3: `26`


## 8. Link

[SimpleMenu-SDUpdater](https://github.com/NoRi-230401/SimpleMenu-SDUpdater)

[SDUpdater-AppTemplate-v2](https://github.com/NoRi-230401/SDUpdater-AppTemplate-v2)

[CardputerSimpleLauncher@shikarunochi](https://github.com/shikarunochi/CardputerSimpleLaucher)

[M5Stack-SD-Updater@tobozo](https://github.com/tobozo/M5Stack-SD-Updater)

