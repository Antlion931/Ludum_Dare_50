#pragma once
#include<Node.hpp>
#include<string>
#include"ColoredButton.hpp"

class DialogueBox : public TextButton{
    public:
        DialogueBox(sf::Text _content);
        void onUpdate(const sf::Time& delta);
        void draw(sf::RenderTarget &target) const;
    protected:
        virtual void onDraw(sf::RenderTarget& target) override;
    private:
        std::string visibleCharacters = "";
        std::string message = "";
        float currentTime = 0.f;
        float newLetterTime = 0.05f;
        bool hidden = false;
        void adjustText();
};