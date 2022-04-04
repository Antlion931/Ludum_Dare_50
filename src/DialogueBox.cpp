#include"DialogueBox.hpp"
#include"Style.hpp"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))



DialogueBox::DialogueBox(sf::Text _content, std::shared_ptr<Node> _target):TextButton(
    {_target->getGlobalTransform().getPosition().x,_target->getGlobalTransform().getPosition().y-60.f},
    {0.f,0.f},
    _content){
    target = _target;
    message = text.getString();
    text.setString("");
    text.setCharacterSize(16);
};

void DialogueBox::adjustText()
{
    float x = 0;
    float y = 0;
    sf::Vector2f targetV = target->getGlobalTransform().getPosition();
    x = targetV.x - text.getGlobalBounds().width/2-60.f;
    y = targetV.y - 90.f;
    text.setPosition(x,y);
}

void DialogueBox::onUpdate(const sf::Time& delta){
    if(!hidden){
        currentTime += delta.asSeconds();
        if(currentTime>=newLetterTime){
            if(message.length()!=0){
            currentTime=0.f;
            visibleCharacters+=message.at(0);
            message.erase(0,1);
            }
            else{
                if(currentTime>=2.5f){
                    hidden = true;
                }
            }
           text.setString(visibleCharacters);
        };
        adjustText();
    }
};

void DialogueBox::onDraw(sf::RenderTarget& target) 
{
    if(!hidden)
    target.draw(text,m_global_transform.getTransform());
};