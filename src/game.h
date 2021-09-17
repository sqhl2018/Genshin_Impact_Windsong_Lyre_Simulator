#ifndef GAME_H
#define GAME_H
#include<SFML/Graphics.hpp>
#include"res.h"
#include<array>
#include<map>
#include<iostream>
#include<SFML/Audio.hpp>
#include<windows.h>
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
class Button{
    public:
        Button(int typeId,sf::RenderWindow* parentWindow,int x,int y);
        static const int TYPE_CLOSE=0x00;
        static const int TYPE_MIN=0x11;
        ~Button();
        bool onEvent(sf::Event *event);
        void draw();
    private:
        int cx;
        int cy;
        int type;
        sf::Sprite* spriteToDraw;
        sf::Sprite* hover;
        sf::Sprite* pressed;
        sf::Sprite* released;
        sf::RenderWindow*parentWindow;
        void onAction();
};
class Game {
    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game();
        ~Game();
        void run(int frame_per_seconds);
    private:
    
#ifdef SHUCCHU_ZIFU
        int index=0;
#endif
        MResources res;
        void processEvents();//拉取时间
        void update(sf::Time deltaTime);//更新，没用到
        void render();//渲染窗口
        sf::RenderWindow* window;//程序的主窗口
        sf::Sprite* bgSprite;//背景图
        sf::Sprite* clefSprite;
        sf::Sprite* clefTensorSprite;
        sf::Sprite* clefBaseSprite;
        int btnHGap=160;//按键横向间隔
        int btnVGap=130;//按键纵向间隔
        int btnStartX=158;//第一个按键的x
        int btnStartY=160;//第一个按键的y
        int btnSize=100;//按键的直径
        //三个音符的位置
        double clefStartX=60.f;
        double clefStartY=140.f;
        sf::Vector2f* clefPosition=new sf::Vector2f(clefStartX, clefStartY+8);
        sf::Vector2f* clefTensorPosition=new sf::Vector2f(clefStartX, clefStartY+150);
        sf::Vector2f* clefBasePosition=new sf::Vector2f(clefStartX, clefStartY+285);
        std::map<std::string,sf::Sprite*>btnUpSpirteMap;//每个按键对应的未按下的图像
        std::map<std::string,sf::Sprite*>btnDownSpirteMap;//每个按键对应的按下的图像
        int windowWidth=1272;//窗口的宽
        int windowHeight=600;//窗口的高
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
        //键值与按键状态的映射
        std::map<std::string,int>stateMap;
        //播放音效
        void play(std::string key);
        void onKeyPressed(std::string key);
        void onKeyReleased(std::string key);
        // void setWindowMiniMize();
        //游戏主时钟
        sf::Clock clock;
        //环形动画效果
        sf::Sprite* donghua;
        int frameTime=60;//动画每一帧的时间
        //键值与对应的动画信息的映射
        std::map<std::string,AnimationInfo*>animationMap;
        bool pressed=false;
        sf::Vector2i globalPosition = sf::Mouse::getPosition();
        sf::Vector2i windowpos=sf::Vector2i();
        int moveY=159;
        Button* closeBtn;
        Button* minBtn;
        sf::Sprite* titleSprite;
        //如果要计算帧率
        #ifdef SHUCHU_ZHENLV
        int count=0;
        sf::Int32 gTime=clock.getElapsedTime().asMilliseconds();
        #endif
};


#endif // GAME_H
