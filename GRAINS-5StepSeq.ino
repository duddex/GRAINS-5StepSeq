int counter = 0;
boolean gate = false;
boolean oldgate = false;

void setup() {
    pinMode(8, OUTPUT);
    pinMode(11, OUTPUT);

    pinMode(A0, INPUT); // P3
    pinMode(A1, INPUT); // IN2 / P2
    pinMode(A2, INPUT); // IN1 / P1
    pinMode(A3, INPUT); // IN3
    pinMode(A4, INPUT); // Input "A"
}

void loop() {
    gate = analogRead(A4) > 700; // A4 = Input "A" used as clock input
    if (oldgate != gate) { // only if the status of input A4 changed
        if (gate) {
            counter++;
            switch (counter) {
                case 1:
                    analogWrite(11, 0); // base note
                    break;
                case 2:
                    // A2 = IN1/P1
                    analogWrite(11, analogRead(A2) / 4);
                    break;
                case 3:
                    // A1 = IN2/P2
                    analogWrite(11, analogRead(A1) / 4);
                    break;
                case 4:
                    // A0 = P3 (use for example the "2ATT/CV" module)
                    analogWrite(11, analogRead(A0) / 4);
                    break;
                case 5:
                    // A3 = IN3
                    analogWrite(11, analogRead(A3) / 4);
                    break;
                default:
                    break;
            }

            digitalWrite(8, HIGH);
            if (counter == 5) {
                counter = 0;
            }
        } else {
            digitalWrite(8, LOW);
        }
        oldgate = gate;
    }
}
