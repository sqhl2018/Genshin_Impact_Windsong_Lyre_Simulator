#include"game.h"
#include"res.h"
#include<stdint.h>
#include <thread>
//以下是防止按键变成输入法打字,接收不到按键信息
#ifdef IMM_COMPILE
#include<windows.h>
#include<imm.h>
#endif
Game::Game() {
/******************************加载资源文件,load resource files********************************************/
    //背景图,load background image
    sf::Texture* texture=new sf::Texture;
    //texture->loadFromFile("./res/png/bg.png");
    if(texture->loadFromMemory(res_bg_png,res_bg_png_size)){
       bgSprite=new sf::Sprite(*texture);
       bgSprite->setTextureRect(sf::IntRect(0, 30, windowWidth,windowHeight));
    }
    //三个音符
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_clef_png,res_clef_png_size)){
        clefSprite=new sf::Sprite(*texture);
        clefSprite->setPosition(*clefPosition);
    }
     texture=new sf::Texture;
    if(texture->loadFromMemory(res_clef_tensor_png,res_clef_tensor_png_size)){
        clefTensorSprite=new sf::Sprite(*texture);
        clefTensorSprite->setPosition(*clefTensorPosition);
    }
     texture=new sf::Texture;
    if(texture->loadFromMemory(res_clef_base_png,res_clef_base_png_size)){
        clefBaseSprite=new sf::Sprite(*texture);
        clefBaseSprite->setPosition(*clefBasePosition);
    }
    
    //一些对应关系
    int hGap=160;int sGap=130;int startX=240;int startY=180;
    for(int i=0;i<21;i++){
        uint8_t *ptr;
        uint32_t siz;
        keyNoteMap[keys.at(i)]=notes.at((i%7));//map:Q->do,W->re,E->mi...
        texture=new sf::Texture;
    
        //每个按键的动画信息
        animationMap[keys.at(i)]=new AnimationInfo(0,frameTime,hGap*(i%7)+startX-50,sGap*(i/7)+startY-50);
        //每个按键的位置
        positionMap[keys[i]]=sf::Vector2f(hGap*(i%7)+startX,sGap*(i/7)+startY);
        //按键背景图
        texture=new sf::Texture;
        std::string s1;
        s1.append(keyNoteMap[keys.at(i)]).append("_png");
        ptr=res.resMap[s1]->p;
        siz=res.resMap[s1]->size;
        if(texture->loadFromMemory(ptr,siz)){
            upMap[keys.at(i)]=new sf::Sprite(*texture);
            upMap[keys.at(i)]->setPosition(positionMap[keys.at(i)]);
        }
        texture=new sf::Texture;
        std::string s2;
        s2.append(keyNoteMap[keys.at(i)]).append("_down_png");
        ptr=res.resMap[s2]->p;
        siz=res.resMap[s2]->size;
        if(texture->loadFromMemory(ptr,siz)){
            downMap[keys.at(i)]=new sf::Sprite(*texture);
            downMap[keys.at(i)]->setPosition(positionMap[keys.at(i)]);
        }
        //每个按键的状态,0x00未按下,0xaa按下
        stateMap[keys[i]]=0x00;
        //每个按键对应的音效
        sf::SoundBuffer *sound_buffer=new sf::SoundBuffer;
        std::string sv;
        sv.append(keys.at(i)).append("_wav");
        ptr=res.resMap[sv]->p;
        siz=res.resMap[sv]->size;
        sound_buffer->loadFromMemory(ptr,siz);
        keySoundMap[keys.at(i)]=sound_buffer;
    }
    //初始化环形动画,donghua is animation
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_donghua_png,res_donghua_png_size)){
        donghua=new sf::Sprite(*texture);
    }
    //创建主窗口,show the main window
    window=new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight),"Genshin Impact.WindSong Lyre",sf::Style::Close);
    window->setKeyRepeatEnabled(false);//禁止重复按键
    //防止卡输入法
    #ifdef IMM_COMPILE
    sf::WindowHandle handle=window->getSystemHandle();
    HIMC g_hIMC = NULL;//g_hIMC 用于恢复时使用
    g_hIMC = ImmAssociateContext(handle, NULL);//handle 为要禁用的窗口句柄
    #endif
    //加载图标
    auto image = sf::Image{};
    if (image.loadFromMemory(res_icon_png,res_icon_png_size)){
        window->setIcon(50, 50, image.getPixelsPtr());
    }
}
void Game::run(int frame_per_seconds) {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f/frame_per_seconds);
    //程序主循环{processEvents();判断是否需要重新绘制;render()?;}
    while (window->isOpen()) {
        //降低运行速度，不然cpu占用高
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //拉取并处理事件
        processEvents();
        //计算是否需要重新绘制
        bool repaint = false;
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            repaint = true;
            update(TimePerFrame);
        }
        if(repaint){
            render();//重新渲染
        }
    }
}

void Game::onKeyPressed(std::string key){
    stateMap[key]=0x11;
    animationMap[key]->restart(clock.getElapsedTime().asMilliseconds());
    play(key);
}
void Game::onKeyReleased(std::string key){
    stateMap[key]=0x00;
}
void Game::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed ) {
            window->close();
        }else if(event.type==sf::Event::KeyPressed){
            switch(event.key.code){
                case sf::Keyboard::Escape:window->close();break;
                case sf::Keyboard::Q:onKeyPressed("Q");break;
                case sf::Keyboard::W:onKeyPressed("W");break;
                case sf::Keyboard::E:onKeyPressed("E");break;
                case sf::Keyboard::R:onKeyPressed("R");break;
                case sf::Keyboard::T:onKeyPressed("T");break;
                case sf::Keyboard::Y:onKeyPressed("Y");break;
                case sf::Keyboard::U:onKeyPressed("U");break;
                case sf::Keyboard::A:onKeyPressed("A");break;
                case sf::Keyboard::S:onKeyPressed("S");break;
                case sf::Keyboard::D:onKeyPressed("D");break;
                case sf::Keyboard::F:onKeyPressed("F");break;
                case sf::Keyboard::G:onKeyPressed("G");break;
                case sf::Keyboard::H:onKeyPressed("H");break;
                case sf::Keyboard::J:onKeyPressed("J");break;
                case sf::Keyboard::Z:onKeyPressed("Z");break;
                case sf::Keyboard::X:onKeyPressed("X");break;
                case sf::Keyboard::C:onKeyPressed("C");break;
                case sf::Keyboard::V:onKeyPressed("V");break;
                case sf::Keyboard::B:onKeyPressed("B");break;
                case sf::Keyboard::N:onKeyPressed("N");break;
                case sf::Keyboard::M:onKeyPressed("M");break;
            }
        }else if(event.type==sf::Event::KeyReleased){
            switch(event.key.code){
                case sf::Keyboard::Q:onKeyReleased("Q");break;
                case sf::Keyboard::W:onKeyReleased("W");break;
                case sf::Keyboard::E:onKeyReleased("E");break;
                case sf::Keyboard::R:onKeyReleased("R");break;
                case sf::Keyboard::T:onKeyReleased("T");break;
                case sf::Keyboard::Y:onKeyReleased("Y");break;
                case sf::Keyboard::U:onKeyReleased("U");break;
                case sf::Keyboard::A:onKeyReleased("A");break;
                case sf::Keyboard::S:onKeyReleased("S");break;
                case sf::Keyboard::D:onKeyReleased("D");break;
                case sf::Keyboard::F:onKeyReleased("F");break;
                case sf::Keyboard::G:onKeyReleased("G");break;
                case sf::Keyboard::H:onKeyReleased("H");break;
                case sf::Keyboard::J:onKeyReleased("J");break;
                case sf::Keyboard::Z:onKeyReleased("Z");break;
                case sf::Keyboard::X:onKeyReleased("X");break;
                case sf::Keyboard::C:onKeyReleased("C");break;
                case sf::Keyboard::V:onKeyReleased("V");break;
                case sf::Keyboard::B:onKeyReleased("B");break;
                case sf::Keyboard::N:onKeyReleased("N");break;
                case sf::Keyboard::M:onKeyReleased("M");break;
            }
    }else if(event.type==sf::Event::MouseButtonPressed){
            int x=event.mouseButton.x;
            int y=event.mouseButton.y;
            for(int i=0;i<21;i++){
                if((x-(positionMap[keys.at(i)].x+buttonSize/2))*(x-(positionMap[keys.at(i)].x+buttonSize/2))+(y-(positionMap[keys.at(i)].y+buttonSize/2))*(y-(positionMap[keys.at(i)].y+buttonSize/2))<(buttonSize/2)*(buttonSize/2)){
                    onKeyPressed(keys.at(i));
                    break;
                }
            }
        }
        if(event.type==sf::Event::MouseButtonReleased){
            for(int i=0;i<21;i++){
                onKeyReleased(keys.at(i));
            }
        }
    }
}
void Game::update(sf::Time deltaTime){

}

void Game::play(std::string key){
    if(soundArray.at(cSoundP)!=nullptr){delete soundArray.at(cSoundP);}
    sf::Sound *sound=new sf::Sound;
    sound->setVolume(80);
    sound->setBuffer(*keySoundMap[key]);
    sound->play();
    soundArray[cSoundP]=sound;
    cSoundP++;
    if(cSoundP>=maxSoundNum){
        cSoundP=0;
    }
}
void Game::render() {
    #ifdef SHUCHU_ZHENLV
    count++;
    int frameNum=100;
    if(count==frameNum){
        int cTime=clock.getElapsedTime().asMilliseconds();
        int delatTime=(cTime-gTime);
        if(delatTime==0){
            delatTime=1;
        }
        std::cout<<"frame:"<<frameNum*1000.0f/delatTime<<std::endl;
        gTime=cTime;
        count=0;
    }
    #endif
    window->clear(sf::Color::White);
    window->draw(*bgSprite);
    window->draw(*clefSprite);
    window->draw(*clefTensorSprite);
    window->draw(*clefBaseSprite);
    sf::Int32 msec = clock.getElapsedTime().asMilliseconds();
    //把21个按键画出来
    for(int i=0;i<21;i++){
        if(stateMap[keys.at(i)]==0x00){
            
            window->draw(*upMap[keys.at(i)]);
        }else{
            window->draw(*downMap[keys.at(i)]);
        }
        AnimationInfo* ani=animationMap[keys.at(i)];
        if(!ani->isOver){
           ani->update(msec);
           donghua->setPosition(sf::Vector2f(1.0f*ani->x,1.0f*ani->y));
           donghua->setTextureRect(sf::IntRect(ani->currentFrame*200, 0, 200, 200));
           window->draw(*donghua);
        }
    }
    window->display();
}

AnimationInfo::AnimationInfo(sf::Int32 startTime,sf::Int32 timePerFrame,int x,int y):startTime(startTime),currentFrame(0),timePerFrame(timePerFrame),isOver(true),x(x),y(y){

}
void AnimationInfo::update(sf::Int32 time){
    if(currentFrame==10){
        isOver=true;
        return;
    }
    if(time<startTime){
        isOver=true;
    }else{
        currentFrame=(time-startTime)/timePerFrame;
        if(currentFrame>10){
            currentFrame=10;
        }
    }
}
void AnimationInfo::restart(sf::Int32 time){
    startTime=time;
    currentFrame=0;
    isOver=false;
}