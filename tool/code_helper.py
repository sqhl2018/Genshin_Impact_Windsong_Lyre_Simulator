#帮助写代码的脚本
cl=["Q","W","E","R","T","Y","U","A","S","D","F","G","H","J","Z","X","C","V","B","N","M"]

for i in cl:
    print("case sf::Keyboard::"+i+":onKeyPressed(\""+i+"\");break;")
    
    
for i in cl:
    print("case sf::Keyboard::"+i+":onKeyReleased(\""+i+"\");break;")

      