#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	ofColor color;
	vector<int> hex_list = { 0x2a9d8f, 0xe9c46a, 0xf4a261, 0xe76f51 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}

	this->rect_size = 10;
	for (float x = 60; x <= ofGetWidth() - 60; x += this->rect_size) {

		for (float y = 60; y <= ofGetHeight() - 60; y += this->rect_size) {

			this->rect_location_list.push_back(glm::vec2(x, y));
			
			vector<float> param_list;
			for (int i = 0; i < this->color_list.size(); i++) { param_list.push_back(0); }
			this->rect_param_list.push_back(param_list);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int i = 0; i < this->color_list.size(); i++) {

		auto noise_location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.015), 0, 1, -60, ofGetWidth() + 60), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.015), 0, 1, -60, ofGetHeight() + 60));
		for (int k = 0; k < this->rect_location_list.size(); k++) {

			if (glm::distance(noise_location, this->rect_location_list[k]) < 60) {

				this->rect_param_list[k][i] = this->rect_param_list[k][i] < 100 ? this->rect_param_list[k][i] + 4 : 100;
			}
			else {

				this->rect_param_list[k][i] = this->rect_param_list[k][i] > 0 ? this->rect_param_list[k][i] - 0.5 : 0;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->rect_location_list.size(); i++) {

		for (int k = 0; k < this->color_list.size(); k++) {

			if (this->rect_param_list[i][k] > 0) {

				ofSetColor(ofColor(this->color_list[k]));
				ofDrawRectangle(this->rect_location_list[i], 10, 10);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}