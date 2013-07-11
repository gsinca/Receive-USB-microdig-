#include "testApp.h"
#include <unistd.h>

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    cout << ofGetFrameRate();
    
    soundSample.loadSound("/Users/gregsmith/Music/Samples/kick.aif");
    soundSample2.loadSound("dance_drums.wav");
    soundSample3.loadSound("dance_bass.wav");
    soundSample4.loadSound("dance_chords.wav");
    
    soundSample2.play();
    //soundSample3.play();
    //soundSample4.play();
    soundSample2.setLoop(true);
    soundSample3.setLoop(true);
    soundSample4.setLoop(true);
	
	bSendSerialMessage = false;
	ofBackground(255);	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.loadFont("DIN.otf", 14);
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

	int baud = 9600;
	serial.setup(0, baud); //open the first device
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
    //vidPlayer1.loadMovie("fusenews.mov");
    //vidPlayer1.play();
    
    

}

//--------------------------------------------------------------
void testApp::update(){
	vidPlayer1.update();
	//if (bSendSerialMessage){
		
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to 
		// read as much as we can in groups of three...
		
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		
		unsigned char bytesReturned[3]; //3 byte length array
		
		memset(bytesReadString, 0, 4); //create 4 byte memory location - converts to unsigned char in memory
                                    //extra byte holds the terminatining char when conversion to String happens below
		memset(bytesReturned, 0, 3);  //create 3 byte memory location
		
        //read 3 bytes from serial buffer and puts them into bytesReturned (unsigned char 3 bytes)
        //Once a byte is read it gets deleted from the buffer.  On the next go-around, the remaining byte(s) are read
        //Use this to receive from Arduino DIGITAL input
		//fills the pointer to the unsigned char
        while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
            nTimesRead++;
			nBytesRead = nRead;
                if(bytesReturned[0] == 'b')
                {
                    soundSample.play();
                    if(vidPlayer1.isPlaying() == false){
                        vidPlayer1.play();
                    }else{vidPlayer1.stop();}
                }
            //cout << bytesReturned[0] << endl;
            cout << "Bytes read: "  << nRead << endl;
		};
        
		memcpy(bytesReadString, bytesReturned, 3);  //copy results
        
    if(nBytesRead > 0){
        
        printf("Bytes returned to string: %d \n", ofToInt(bytesReadString));
        circleSize = ofToInt(bytesReadString);
    
     soundSample2.setSpeed((ofToFloat(bytesReadString)/100));
      vidPlayer1.setSpeed(ofToFloat(bytesReadString)/100);
    }
		bSendSerialMessage = false;
		readTime = ofGetElapsedTimef();
	
}

//--------------------------------------------------------------
void testApp::draw(){
    vidPlayer1.draw(10, 10, 480, 320);
    ofSetColor(255, 155, 0);
    ofFill();
    ofCircle(150,150,circleSize/3);
  ofSetColor(220);
	if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		//ofSetColor(220);
	} else {
		//ofSetColor(220);
	}
	string msg;
	msg += "nBytes read " + ofToString(nBytesRead) + "\n";
	msg += "nTimes read " + ofToString(nTimesRead) + "\n";
	msg += "read: " + ofToString(bytesReadString) + "\n";
	msg += "(at time " + ofToString(readTime, 3) + ")";
	font.drawString(msg, 50, 100);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if(key == '1'){
        if(soundSample2.getVolume() != 0){
        soundSample2.setVolume(0);
        }else{soundSample2.setVolume(100);}
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}

