#include <string>

class Message{
    private:
        std::string sender;
        std::string text;
    public:
        Message(std::string sender, std::string text){
            this->sender = sender;
            this->text = text;
        }


        std::string getSender(){ return sender;}
        std::string getText(){ return text;}

};