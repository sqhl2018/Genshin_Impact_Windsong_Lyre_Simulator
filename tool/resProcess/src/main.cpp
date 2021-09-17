#include<iostream>
#include<fstream>
#include<io.h>
using namespace std;

//字符串替换函数
string strreplace(string str,string str1,string str2){
    string::size_type idx=str.find(str1);
    if(idx==string::npos)
    return str;
    str=str.replace(str.find(str1),str1.length(), str2); 
    return strreplace(str,str1,str2);
}


int main(int argc,char**argv){
    ofstream reshOut("./src/res.h");
    if(!reshOut.is_open()){
        return 1;
    }
    ofstream resCppOut("./src/res.cpp");
    if(!resCppOut.is_open()){
        reshOut.close();
        return 1;
    }
    reshOut<<"#ifndef RES_HPP"<<endl<<"#define RES_HPP"<<endl<<"#include<stdint.h>"<<endl<<"#include<map>"<<endl;
    reshOut<<"class resData{"<<endl<<
        "public:"<<endl<<
        "resData(uint8_t ptr[],uint32_t dataSize):p(ptr),size(dataSize){};"<<endl<<
       "uint8_t* p;"<<endl<<
        "uint32_t size;"<<endl<<
    "};"<<endl<<
    "class MResources{"<<endl<<
    "public:"<<endl<<
    "MResources();"<<endl<<
    "std::map<std::string,resData*>resMap;"<<endl<<
    "};"<<endl;
    resCppOut<<"#include\"res.h\""<<endl<<"MResources::MResources(){"<<endl;

    int num=0;
    std:string path("./res");
    ofstream os("./tmp/res_arr.cpp",ios::trunc);
    if(os.is_open()){
        os<<"#include<stdint.h>"<<endl;
        _finddata_t file_info;
        string current_path=path+"/*"; //可以定义后面的后缀为*.exe，*.txt等来查找特定后缀的文件，*.*是通配符，匹配所有类型,路径连接符最好是左斜杠/，可跨平台
        //打开文件查找句柄
        int handle=_findfirst(current_path.c_str(),&file_info);
        //返回值为-1则查找失败
        if(-1==handle)return 1;
        do{
            if(file_info.attrib==_A_SUBDIR){
                //文件夹不处理
            }else{
                std::string pre="res_";
                string fm =strreplace(std::string(file_info.name),".","_");
                reshOut<<"extern uint8_t "<<pre<<fm<<"[];extern uint32_t "<<pre<<fm<<"_size;"<<endl;
                resCppOut<<"\tresMap[\""<<fm<<"\"]=new resData("<<pre<<fm<<","<<pre<<fm<<"_size);"<<endl;
                cout<<file_info.name<<' '<<file_info.time_write<<' '<<file_info.size<<' '<<"file"<<endl;
                 //获得的最后修改时间是time_t格式的长整型，需要用其他方法转成正常时间显示
                std::string fn(path);
                ifstream ist(fn.append("/").append(file_info.name).c_str(),ios::binary);
                std::cout<<fn<<endl;
                char writeBuf[128];
                uint8_t buf[128];

                os<<endl<<"uint32_t "<<pre<<fm<<"_size="<<file_info.size<<";"<<"uint8_t "<<pre<<fm<<"["<<file_info.size<<"]={";
                if(ist.is_open()){
                    while(ist.read((char*)(buf),1)){
                        snprintf(writeBuf,512, "0x%02x,",buf[0]);
                        os<<writeBuf;
                    }
                    os<<"};";
                }else{
                    cout<<"not open fileIn"<<endl;
                }
            }
        }while(!_findnext(handle,&file_info));  //返回0则遍历完
        //关闭文件句柄
        _findclose(handle);
        reshOut<<"#endif";
        resCppOut<<"}";
    } else{
        std::cout<<"not open"<<endl;
    }
   
    return 0;
}
 
