#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofAddListener(ofxGDImageDownloadEvent::events, this, &ofApp::on_gd_event);
    gd_image_download.setup("YOUR API KEY");
    gd_image_download.download(&image,"IMAGE ID");
    
}

void ofApp::on_gd_event(ofxGDImageDownloadEvent &e) {
    if(!e.ok){
        //  an error
        cout << e.error << endl;
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(image.isAllocated())
    {
        ofSetColor(255);
        image.draw(0,0);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
