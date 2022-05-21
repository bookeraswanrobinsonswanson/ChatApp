#include "ofApp.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(36, 32,56);
    ofHttpResponse resp = ofLoadURL(SERVER+"/beingMsg");
    this->data = resp.data;
    this->messages = processData(resp.data);
    if(int(messages.size()) >= 11){
        topMessage = messages.size()-11;
    }

    // numMessagesAtOnce = ofgetHeight();
}




void ofApp::sendMessage(){
    
}

vector<Message> ofApp::processData(string data){
    vector<Message> messages_temp;
    int i = 0;
    int j = 0;
    string uname;
    while(j<data.size()){
        if(data[j] == ':'){
            uname = data.substr(i, j-i);
            i = j+1;
        }
        if(data[j] == '\n' && !uname.empty()){
            messages_temp.emplace_back(uname, data.substr(i, j-i));
            i = j+1;
        }
        j++;
    }
    return messages_temp;
}


void ofApp::runOnInterval(){
    ofHttpResponse resp = ofLoadURL(SERVER+"/beingMsg");
    if(resp.data.size() > this->data.size()){
        hasNewMessages = true;
    }
    if(resp.data.size() < this->data.size()){
        hasNewMessages = true;
    }
    this->data = resp.data;
    this->messages = processData(resp.data);
    // for(Message message : messages){
    //     cout << "Name: " << message.getSender() << " Text: " << message.getText() << endl;
    // }
    // cout << resp.data << endl;
}
//--------------------------------------------------------------
void ofApp::update(){
    timer++;
    if(timer%15 == 0){
        runOnInterval();
        timer = 0;
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofFill();
    if(int(messages.size()) > 10 && hasNewMessages){
        topMessage = messages.size()-11;
        hasNewMessages = false;
    }
    else if(int(messages.size()) < 11 && hasNewMessages){
        topMessage = 0;
        hasNewMessages = false;
    }
    for(int i = topMessage; i < int(messages.size()); i++){
        if(messages[i].getSender() == username){
            ofSetColor(0, 100, 255);
            ofDrawRectangle(ofGetWidth() - 510, 50+60*(i-topMessage)-10, 300, 50);
            ofSetColor(255, 255, 255);
            ofDrawBitmapString(messages[i].getSender(), ofGetWidth() - 500, 60+60*(i-topMessage));
            ofDrawBitmapString(messages[i].getText(), ofGetWidth() - 480, 80+60*(i-topMessage));
        }
        else{
            ofSetColor(100, 120, 100);
            ofDrawRectangle(190, 50+60*(i-topMessage)-10, 300, 50);
            ofSetColor(255, 255, 255);
            ofDrawBitmapString(messages[i].getSender(), 200, 60+60*(i-topMessage));
            ofDrawBitmapString(messages[i].getText(), 220, 80+60*(i-topMessage));
        }
    }
    // ofDrawBitmapString(data, 100,100);
    ofFill();
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, ofGetHeight()-50, ofGetWidth(), 50);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(message_draft, 100, ofGetHeight()-25);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
        case ENTER_KEY:{
            ofHttpRequest request;
            request.method = ofHttpRequest::POST;
            request.url = SERVER+"/send_message";
            if(message_draft == "booker"){
                username = "booker";
                password = password2;
                message_draft = "Changed user to booker";
            }
            else if(message_draft == "cristian"){
                username = "cristian";
                password = password3;
                message_draft = "Changed user to cristian";
            }
            else if(message_draft == "jeremiah"){
                username = "jeremiah";
                password = "admin1";
                message_draft = "Changed user to jeremiah";
            }
            request.body = "username="+username+"&password="+password+"&message=" + message_draft;
            ofURLFileLoader http;
            auto response = http.handleRequest(request);
            message_draft = "";
            break;
        }
        case BACKSPACE_KEY:
            message_draft = message_draft.substr(0, message_draft.size()-1);
            break;
        case 'w':
            if(topMessage > 0) topMessage--;
            cout << "topMessage: " << topMessage << endl;
            break;
        case 's':
            if(topMessage < messages.size()-11) topMessage++;
            break;
        default:
            message_draft += key;
    } 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // cout << x << ", " << y << " Button: " << button << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // cout << "Pressed" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // cout << "Pressed" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
