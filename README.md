# Genshin_Impact_Windsong_Lyre_Imitation


仿制的原神风物之诗琴.An imitation of the genshin impact's windsong lyre.

源码亦可见于Gitee.Source code also avaliable on gitee.[Gitee repository]([仿制_风物之诗琴: 仿制的原神的风物之诗琴 (gitee.com)](https://gitee.com/aal_izz_well/fangzhi_fengwuzhishiqin))

Forgive me for my poor english.

#### 程序截图

![img](jietu.png)

#### 编译(How to Compile)

- 安装MingW.You should have MingW installed.
- 确保能使用`make`、`g++`、`windres`.Make sure that you can run following commands: `make`、`g++`、`windres`.
- 再本readme的目录执行`make`。Run `make` in the same folder of this readme.
- 拷贝`openal32.dll`、`qin_static.exe`到你想要的地方.Copy `openal32.dll` and `qin_static.exe` to the folder you want.

#### 其他(Others)

我想把openal编译成静态库，静态库是编译成功了，但是和SFML的静态库一起用的时候老是有链接错误，最后还是用动态库了。SFML库倒是链接到exe里去了。

资源文件我也编译到exe里去了。程序也有用QT写的版本，可见Gitee仓库.

音源是录的游戏里的声音。

I'd like to make openal a static library, but failed. Resource files are all linked into the exe.

