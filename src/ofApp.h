#pragma once

#include "ofMain.h"
#include "Message.h"


#define ENTER_KEY 13
#define BACKSPACE_KEY 8

class ofApp : public ofBaseApp{

	private:
		int timer = 0;
		std::string data = "";
		vector<Message> messages;
		std::string message_draft = "";
		std::string username = "jeremiah";
		std::string password = "admin1";
		std::string password2 = "password1";
		std::string password3 = "password3";
        int scrollCenter;
		int bottomMessage = 11;
		int topMessage = 0;
		bool hasNewMessages = true;
		int numMessagesAtOnce = 11;
		string SERVER = "https://prolog-chatapp-server.herokuapp.com";
	public:
		void setup();
		void update();
		void draw();
		void runOnInterval();
		void sendMessage();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		vector<Message> processData(string data);
		
};
