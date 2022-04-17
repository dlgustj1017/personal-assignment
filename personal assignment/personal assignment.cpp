#include <bangtal.h>

SceneID scene1;
ObjectID startButton, endButton, santa, playButton;
int santaX = 0, santaY = 500;
TimerID timer1;

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == endButton) {
		endGame();
	}
	else if (object == startButton) {
		hideObject(startButton);
		hideObject(endButton);

		showObject(playButton);

		startTimer(timer1);

		setTimer(timer1, 10.0f);
		startTimer(timer1);
	}
	else if (object == playButton) {
		santaX = santaX + 30;
		locateObject(santa, scene1, santaX, santaY);

		if (santaX > 1280) {

			showMessage("선물 배달 성공~~~");

			hideObject(playButton);

			setObjectImage(startButton, "restart.png");
			showObject(startButton);
			showObject(endButton);

			santaX = 0;
			locateObject(santa, scene1, santaX, santaY);

			stopTimer(timer1);
		}
	}
}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		showMessage("헉! 선물 배달 실패!");

		hideObject(playButton);

		setObjectImage(startButton, "restart.png");
		showObject(startButton);
		showObject(endButton);

		santaX = 0;
		locateObject(santa, scene1, santaX, santaY);


	}
}

int main() {

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene1 = createScene("산타 레이스", "background.png");

	startButton = createObject("start.png");
	locateObject(startButton, scene1, 590, 70);
	showObject(startButton);

	endButton = createObject("end.png");
	locateObject(endButton, scene1, 590, 20);
	showObject(endButton);

	santa = createObject("santa.png");

	locateObject(santa, scene1, santaX, santaY);
	showObject(santa);

	playButton = createObject("play.png");
	locateObject(playButton, scene1, 610, 30);

	timer1 = createTimer(10.0f);
	showTimer(timer1);


	startGame(scene1);
}