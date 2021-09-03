#include"game.h"
#include"res.h"
#include<stdint.h>
#include <thread>
#define GPP_COMPILE
//以下是防止按键变成输入法打字,接收不到按键信息
#ifdef GPP_COMPILE
#include<windows.h>
#include<imm.h>
#pragma comment (lib ,"imm32.lib")
#endif
Game::Game() {
/******************************加载资源文件********************************************/
    //字体
    font=new sf::Font;
    if (!font->loadFromMemory(res_ft_ttf,res_ft_ttf_size)){std::cout<<"an exception occured when load font"<<std::endl;}
    //背景图
    sf::Texture* texture=new sf::Texture;
    if(texture->loadFromMemory(res_bg_png,res_bg_png_size)){
       bgSprite=new sf::Sprite(*texture);
       bgSprite->setTextureRect(sf::IntRect(0, 30, windowWidth,windowHeight));
    }
    //三个音符
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_g_png,res_g_png_size)){
        gSprite=new sf::Sprite(*texture);
        gSprite->setPosition(*gPosition);
    }
    //按键背景图
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_cs_png,res_cs_png_size)){
        cs=new sf::Sprite(*texture);
        cs->setPosition(sf::Vector2f(0.0f,0.0f));
    }
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_cs_down_png,res_cs_down_png_size)){
        cs_down=new sf::Sprite(*texture);
        cs_down->setPosition(sf::Vector2f(0.0f,10.0f));
    }
    //按键上的圆环
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_h_png,res_h_png_size)){
        huan=new sf::Sprite(*texture);
        huan->setPosition(sf::Vector2f(0.0f,20.0f));
    }
    //一些对应关系
    int hGap=160;int sGap=130;int startX=240;int startY=180;
    for(int i=0;i<21;i++){
        keyNoteMap[keys.at(i)]=notes.at((i%7));//map:Q->do,W->re,E->mi...
        texture=new sf::Texture;
        //每个按键上画的音符
        std::string sn;
        sn.append(keyNoteMap[keys.at(i)]).append("_png");
        uint8_t* ptr=res.resMap[sn]->p;
        std::size_t siz=res.resMap[sn]->size;
        if(texture->loadFromMemory(ptr,siz)){
            sf::Sprite* note=new sf::Sprite(*texture);
            spriteMap[keys.at(i)]=note;
        }
        //每个按键的动画信息
        animationMap[keys.at(i)]=new AnimationInfo(0,frameTime,hGap*(i%7)+startX-50,sGap*(i/7)+startY-50);
        //每个按键的位置
        positionMap[keys[i]]=sf::Vector2f(hGap*(i%7)+startX,sGap*(i/7)+startY);
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
    //初始化环形动画
    texture=new sf::Texture;
    if(texture->loadFromMemory(res_donghua_png,res_donghua_png_size)){
        donghua=new sf::Sprite(*texture);
    }
    //创建主窗口
    window=new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight),"Genshin Impact.WindSong Lyre",sf::Style::Close);
    window->setKeyRepeatEnabled(false);//禁止重复按键
    //防止卡输入法
    #ifdef GPP_COMPILE
    sf::WindowHandle handle=window->getSystemHandle();
    HIMC g_hIMC = NULL;//g_hIMC 用于恢复时使用
    g_hIMC = ImmAssociateContext(handle, NULL);//handle 为要禁用的窗口句柄
    #endif
    //加载图标
    auto image = sf::Image{};
    if (image.loadFromMemory(res_21_png,res_21_png_size)){
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
    window->draw(*gSprite);
    sf::Int32 msec = clock.getElapsedTime().asMilliseconds();
    //把21个按键画出来
    for(int i=0;i<21;i++){
        if(stateMap[keys.at(i)]==0x00){
            cs->setPosition(positionMap[keys.at(i)]);
            window->draw(*cs);
        }else{
            cs_down->setPosition(positionMap[keys.at(i)]);
            window->draw(*cs_down);
        }
        huan->setPosition(positionMap[keys.at(i)].x+5,positionMap[keys.at(i)].y+5);
        window->draw(*huan);
        spriteMap[keys.at(i)]->setPosition(positionMap[keys.at(i)].x+25,positionMap[keys.at(i)].y+28);
        window->draw(*spriteMap[keys.at(i)]);
        sf::Text text;
        text.setFont(*font);
        text.setString(keyNoteMap[keys.at(i)]);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color(164, 166, 120));
        text.setStyle(sf::Text::Regular);
        text.setPosition(positionMap[keys.at(i)].x+39,positionMap[keys.at(i)].y+65);
        window->draw(text);
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