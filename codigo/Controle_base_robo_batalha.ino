#include <Bluepad32.h>
#include "MotorCupim.h"

#define motorDP 0
#define motorDM 0
#define motorEP 0
#define motorEM 0
#define armaDP 0
#define armaDM 0
#define armaEP 0
#define armaEM 0

MotroCupim mover(motorDP, motorDM, motorEP, motorEM);
MotroCupim arma(armaDP, armaDM, armaEP, armaEM);
ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: controle conectado");
            ControllerProperties properties = ctl->getProperties();
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    mover.parado()
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controle desconectado");
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void processGamepad(ControllerPtr ctl) {

    bool controleA = false;
    bool controleB = false;
    int zonaMorta = 30;

    //  a(), b(), x(), y(), l1(), etc...
    if (ctl->a()) {
        Serial.println("a");

        if(ctl->a() && controleA == true){
            controleA = false;
        } else if(ctl->a() && controleA== false){
            controleA = true;
        }

        if(controleA == true){
            Serial.println("LigarArma-A");
            arma.tras();
        } else if(controleA == false){
            Serial.println("DesligarArma-A");
            arma.parado();
        }
    }

    if (ctl->b()) {
        Serial.println("b");

        if(ctl->b() && controleB == true){
            controleB = false;
        } else if(ctl->b() && controleB== false){
            controleB = true;
        }

        if(controleB == true){
            Serial.println("LigarArma-H");
            arma.frente().
        } else if(controleB == false){
            Serial.println("DesligarArma-H");
            arma.parado();
        }
    }

    if (ctl->l2()) {
        Serial.println("tras");
        mover.tras();
    }

    if(ctl->r2()){
        Serial.println("frente");
        mover.frente();
    }

    if(ctl->axisX() > zonaMorta){
        Serial.println("direita");
        mover.direita();
    } else if(ctl->axisX() < -zonaMorta){
        Serial.println("esquerda");
        mover.esquerda();
    } else if(ctl->axisX() > zonaMorta && ctl->r2()){
        Serial.println("direita");
        mover.direita();
    } else if(ctl->axisRX() < -zonaMorta && ctl->r2()){
        Serial.println("esquerda");
        mover.esquerda();
    } else{
        Serial.println("parado");
        mover.parado();
    }

}

void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            } else {
                Serial.println("controle não suportado");
            }
        }
    }
}

// Arduino setup function. Runs in CPU 1
void setup() {
    mover.setup();
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    //BP32.forgetBluetoothKeys();

    BP32.enableVirtualDevice(false);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();
    delay(150);
}
