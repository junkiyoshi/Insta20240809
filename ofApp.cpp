#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
}
//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < 30; i++) {

		this->location_list.push_back(glm::vec2(ofRandom(-360, 360), ofRandom(-360, 360)));
		this->life_list.push_back(0);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (abs(this->location_list[i].x) > 460 || abs(this->location_list[i].y) > 460) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.0018, this->location_list[i].y * 0.0018, ofGetFrameNum() * 0.01), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));

		auto color_value = this->life_list[i] < 10 ? ofMap(this->life_list[i], 0, 10, 255, 39) : 39;
		ofSetColor(color_value);

		for (int k = i + 1; k < this->location_list.size(); k++) {

			auto distance = glm::distance(this->location_list[i], this->location_list[k]);
			if (distance < 40) {

				ofSetColor(color_value, ofMap(distance, 0, 40, 255, 0));
				ofDrawLine(this->location_list[i], this->location_list[k]);
			}
		}

		this->location_list[i] = next;
		this->life_list[i] += 2;
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}