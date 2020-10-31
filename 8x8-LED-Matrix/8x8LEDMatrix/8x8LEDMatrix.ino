//int col[] = {2, 9, A7, 5, A3, A6, A2, A4};
//int row[] = {8, A1, A0, 3, A5, 4, 7, 6};
int col[] = {6, A2, A3, 3, A5, 4, 8, 9};
int row[] = {2, 7, A7, 5, A0, A6, A1, A4};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    digitalWrite(row[i], HIGH);
  }
}

void loop() {
  for (int c = 0; c < 8; c++) {
    digitalWrite(col[c], HIGH);
    for (int r = 0; r < 8; r++) {
      digitalWrite(row[r], LOW);
      delay(100);
      digitalWrite(row[r], HIGH);
    }
    digitalWrite(col[c], LOW);
  }
}
