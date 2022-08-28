# OmuctCanUtil
大阪公立大学工業高等専門学校ろぼっと倶楽部のCANライブラリ.

### Summary
CanManagerクラスを通して部内規格に従ったCAN通信を行う.
使用する基板に応じたヘッダをincludeし, APIを操作する.

### 対応フレームワーク
- Arduino
- Mbed

### License
Copyright (c) 2022 Yoshikawa Teru
This code is released under the MIT License, see LICENSE.

# Table of Contents
- CanBus
- CanMessage
- CanManager
- CanId
- CanUtil
- PlugBase FirmBase

## CanBus
mbedのCANクラス.
Arduinoの場合、標準ライブラリのCANをラップしたクラス.

## CanMessage
CanBusで送信するメッセージの構造体.

## CanManager
CanBusを操作するクラス.
examples内にArduino, Mbedの利用例があるので参照のこと.

### How to use CanManager
1. CanBusのinstanceの参照を受け取ってCanManagerのinstanceを作成する.
1. set_callbackでcallback関数を設定すると, CanMessageを受信したとき, callback関数が呼び出される.
1. main-loop内でtask関数を呼び出し続ける.

## CanId
標準フォーマット, 拡張フォーマットのCAN ID.
get_idでidを取得.
standard-layout型かつtrivial-copyable型である.

## CanUtil
便利関数とenum,構造体の定義.

## PlugBase FirmBase
プラグインをファームウェアのインターフェイスクラス.

## Px[0-9]{3}
各種APIを操作するプラグイン
- Px002 ソレノイド基板.
- Px400 サーボ基板.

## Fx[0-9]{3}
ファームウェア.

## dir
```
├── LICENSE
├── README.md
├── examples
│   ├── Arduino
│   ├── Firm
│   └── Mbed
├── include
│   └── OmuctCanUtil
│       ├── CanBus.h
│       ├── CanId.h
│       ├── CanManager.h
│       ├── CanMessage.h
│       ├── CanUtil.h
│       └── 各種プラグイン
└── library.json
```
