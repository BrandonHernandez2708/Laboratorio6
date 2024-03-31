void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  manejarComandosSerial();
  manejarBotones();
}

// Función para manejar los comandos recibidos por el puerto serial
void manejarComandosSerial() {
  if (Serial.available() > 0) {
    char estadoMonitor = Serial.read();
    switch (estadoMonitor) {
      case 'A':
        encenderGrupoA();
        break;
      case 'B':
        encenderGrupoB();
        break;
      case 'C':
        encenderGrupoC();
        break;
      case 'D':
        encenderGrupoD();
        break;
      case 'E':
        apagarGrupoA();
        break;
      case 'F':
        apagarGrupoB();
        break;
      case 'G':
        apagarGrupoC();
        break;
      case 'H':
        apagarGrupoD();
        break;
      default:
        break;
    }
  }
}

// Funciones para encender y apagar grupos de LEDs
void encenderGrupoA() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
}

void encenderGrupoB() {
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}

void encenderGrupoC() {
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
}

void encenderGrupoD() {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void apagarGrupoA() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void apagarGrupoB() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void apagarGrupoC() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void apagarGrupoD() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

// Función para manejar las acciones de los botones
void manejarBotones() {
  if (digitalRead(10) == LOW) {
    toggleGrupoA();
    delay(100);
  } else if (digitalRead(11) == LOW) {
    toggleGrupoB();
    delay(100);
  } else if (digitalRead(12) == LOW) {
    toggleGrupoC();
    delay(100);
  } else if (digitalRead(13) == LOW) {
    toggleGrupoD();
    delay(100);
  }
}

// Funciones para alternar entre encendido y apagado de grupos de LEDs
void toggleGrupoA() {
  static bool estadoGrupoA = false;
  if (estadoGrupoA) {
    apagarGrupoA();
  } else {
    encenderGrupoA();
  }
  estadoGrupoA = !estadoGrupoA;
}

void toggleGrupoB() {
  static bool estadoGrupoB = false;
  if (estadoGrupoB) {
    apagarGrupoB();
  } else {
    encenderGrupoB();
  }
  estadoGrupoB = !estadoGrupoB;
}

void toggleGrupoC() {
  static bool estadoGrupoC = false;
  if (estadoGrupoC) {
    apagarGrupoC();
  } else {
    encenderGrupoC();
  }
  estadoGrupoC = !estadoGrupoC;
}

void toggleGrupoD() {
  static bool estadoGrupoD = false;
  if (estadoGrupoD) {
    apagarGrupoD();
  } else {
    encenderGrupoD();
  }
  estadoGrupoD = !estadoGrupoD;
}
