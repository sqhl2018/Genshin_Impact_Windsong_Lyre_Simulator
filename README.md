# Genshin_Impact_Windsong_Lyre_Simulator

仿制的原神风物之诗琴.An imitation(or call it a simulator) of the genshin impact's windsong lyre.

Forgive me for my poor english.

源码可以同时在Gitee和Github上看到。[Gitee](https://gitee.com/aal_izz_well/fangzhi_fengwuzhishiqin) - [Github](https://github.com/sqhl2018/Genshin_Impact_Windsong_Lyre_Simulator)。这两仓库并不是同步的，会有滞后。

The source code can be seen on both Gitee and Github. The two repositories are not synchronized and will lag.

#### 下载(Download)

见Release.Download is available,see release.

#### 程序截图(Screenshot)

![img](jietu_screenshot.png)

#### 编译(How to Compile)

- 执行resProcessor.exe.Run resProcessor.exe.(这是个啥程序？下面有解释.What is resProcessor.exe?See below.)
- 安装MingW_w64(C/C++编译器).You should have MingW_w64(C/C++ Compiler) installed.
- 确保能使用`make`、`g++`、`windres`.Make sure that you can run following commands: `make`、`g++`、`windres`.(PS:make.exe or mingw32-make.exe)
- 再本readme的目录执行`make`。Run `make` in the same folder of this readme.
- 拷贝`WindsongLyre.exe`到你想要的地方.Copy`WindsongLyre.exe` to the folder you want.

#### 关于resProcessor.exe(About resProcessor.exe)

是我自己写的一个小程序.功能如下：
输入:资源文件res/xxx.xxx
输出:src/res.cpp、src/res.h、tmp/res_arr.cpp
结果，我可以通过这三个文件在内存中访问资源文件(原理的话你去看一下这三个输出就明白了)。

It is a tool built by myself.Function:
Input:resource files:res/xxx.xxx
OutPut:src/res.cpp、src/res.h、tmp/res_arr.cpp
So finally,i can access resource files in memory(Want to  know how? See the three outputs).

#### 声音(About the voice)

我只是把录的游戏的声音播放出来。不是很懂声学原理。

如果需要修正, 请提交ISSUE。我看到ISSUE就会解决。

I just played the sound recorded from the game. I don't know much about acoustics.

If corrections are required, please submit an ISSUE.If I see ISSUE , i will solve it.

#### 其他(Others)

库、资源文件都编译到exe里去了。程序也有用QT写的版本，可见Gitee仓库.

All libraries and resource files are linked into the executable file;
