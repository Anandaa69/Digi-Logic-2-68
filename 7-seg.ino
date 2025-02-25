int i;
int digit = 0;
int num = 7;  // เริ่มต้นที่เลข 7

bool segMent[10][7] = {
  1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0,
  1, 1, 0, 1, 1, 0, 1,
  1, 1, 1, 1, 0, 0, 1,
  0, 1, 1, 0, 0, 1, 1,
  1, 0, 1, 1, 0, 1, 1,
  1, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1
};

hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer() {
  if (digit == 0) {
    digitalWrite(DG[0], LOW);
    for (i = 0; i < 7; i++) {
      digitalWrite(segMentPin[i], segMent[num][i]);  // แสดงเลข 7
    }
    digitalWrite(DG[1], HIGH);
    digit = 1;
  } else {
    digitalWrite(DG[1], LOW);
    for (i = 0; i < 7; i++) {
      digitalWrite(segMentPin[i], segMent[num + 1][i]);  // แสดงเลข 8
    }
    digitalWrite(DG[0], HIGH);
    digit = 0;
  }
}

void setup() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000 / 30 / 2, true);
  timerAlarmEnable(timer);

  for (i = 0; i < 2; i++) {
    pinMode(DG[i], OUTPUT);
    digitalWrite(DG[i], HIGH);
  }
  for (i = 0; i < 7; i++) {
    pinMode(segMentPin[i], OUTPUT);
    digitalWrite(segMentPin[i], HIGH);
  }
}

void loop() {
}
