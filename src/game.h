#ifndef GAME_H
#define GAME_H
#include<SFML/Graphics.hpp>
#include"res.h"
#include<array>
#include<map>
#include<iostream>
#include<SFML/Audio.hpp>
#define maxSoundNum 249 //同时播放的最大音效数
//动画信息类，对应按下按键后的波纹效果
class AnimationInfo{
    public:
        AnimationInfo(sf::Int32 startTime,sf::Int32 timePerFrame,int x,int y);
        sf::Int32 startTime;//动画开始的事件
        int currentFrame;//当前的帧
        sf::Int32 timePerFrame;//一帧所用的时间
        bool isOver;//是否播放完毕
        void update(sf::Int32 time);//根据现在的时间更新
        void restart(sf::Int32 ime);//动画重新开始
        int x;//动画绘制时的位置x
        int y;//动画绘制时的位置y
};
class Game {
    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game();
        void run(int frame_per_seconds);
    private:
        MResources res;
        void processEvents();//拉取时间
        void update(sf::Time deltaTime);//更新，没用到
        void render();//渲染窗口
        sf::RenderWindow* window;//程序的主窗口
        sf::Sprite* bgSprite;//背景图
        sf::Sprite *gSprite;//三个音符(高、中、低)
        sf::Vector2f* gPosition=new sf::Vector2f(80.f,150.f);//三个音符的位置
        sf::Sprite* cs;//按键背景图
        sf::Sprite* cs_down;//按下时的按键背景图
        sf::Sprite* huan;//按键上的圆环
        sf::Sprite* do_note;//按键上的音符
        int windowWidth=1536;//窗口大小
        int windowHeight=700;
        sf::Font* font;//按键上文本的字体
        int buttonSize=100;//按键的尺寸
        //21个键值
        std::array<std::string,21>keys={"Q","W","E","R","T","Y","U","A","S","D","F","G","H","J","Z","X","C","V","B","N","M"};
        //7中音符
        std::array<std::string,7>notes={"do","re","mi","fa","so","la","ti"};
        //键值与音符的对应关系
        std::map<std::string,std::string>keyNoteMap;
        //程序的音效管理集合
        std::array<sf::Sound*,maxSoundNum> soundArray{};
        int cSoundP=0;//音效管理用变量
        //键值与音效的映射
        std::map<std::string, sf::SoundBuffer*>keySoundMap;
        //键值与位置的对应关系，就是21个按钮的位置
        std::map<std::string,sf::Vector2f>positionMap;
        //键值与对应图片的映射
        std::map<std::string,sf::Sprite*>spriteMap;
        //键值与按键状态的映射
        std::map<std::string,int>stateMap;
        //播放音效
        void play(std::string key);
        void onKeyPressed(std::string key);
        void onKeyReleased(std::string key);
        //游戏主时钟
        sf::Clock clock;
        //环形动画效果
        sf::Sprite* donghua;
        int frameTime=60;//动画每一帧的时间
        //键值与对应的动画信息的映射
        std::map<std::string,AnimationInfo*>animationMap;
        //如果要计算帧率
        #ifdef SHUCHU_ZHENLV
        int count=0;
        sf::Int32 gTime=clock.getElapsedTime().asMilliseconds();
        #endif
};

#endif // GAME_H
