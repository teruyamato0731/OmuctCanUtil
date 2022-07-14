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
