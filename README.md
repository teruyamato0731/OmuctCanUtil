# OmuctCanUtil
大阪公立大学工業高等専門学校ろぼっと倶楽部のCANライブラリ

# 対応フレームワーク
- Arduino(予定)
- Mbed

# overview
CanManagerクラスに全部投げるといい感じに通信される！
(コールバック関数は必要)
使うAPIに応じてプラグイン(ヘッダ)をinclude

# dir
```bash
├── LICENSE
├── README.md
├── examples
│   ├── Arduino
│   │   └── main.cpp
│   └── Mbed
│       ├── platformio.ini
│       └── src
│           └── main.cpp
├── include
│   └── OmuctCanUtil
│       ├── CanBus.h
│       ├── CanId.h
│       ├── CanManager.h
│       ├── CanMessage.h
│       ├── CanUtil.h
│       ├── FarmBase.h
│       ├── PlugBase.h
│       ├── Px001.h
│       ├── Px002.h
│       ├── Px400.h
│       └── PxC00.h
├── library.json
└── src
    └── test.cpp
```

# License
The source code is licensed MIT.

Copyright (c) 2022 Yoshikawa Teru
This software is released under the MIT License, see LICENSE.

# 開発の進捗
- [x] CanManager
    - [x] 各種共通コマンドが送信できる。
    - [x] callbackを設定し呼び出せる。
- [x] PlugBase
- [x] FirmBase
- [ ] Px002
    - [x] 各種共通コマンドが送信できる。
    - [x] send_dataに移行
    - [ ] テスト
- [ ] Fx002
    - [ ] テスト
- [ ] Px400
    - [ ] テスト
- [ ] Fx400
    - [ ] テスト

TODO get_state的なの欲しくない？
receive id や state, config などの値を返信
