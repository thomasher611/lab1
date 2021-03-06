#include <Arduino.h>
#include "debug.h"

#include <FS.h>

bool isFileSetup = false;

void setupFile() {
    DEBUG("Prepare file system");
    SPIFFS.begin();
    isFileSetup = true;
}

String loadFile(const char* filename) {
    if (!isFileSetup)
        setupFile();

    File file = SPIFFS.open(filename, "r");
    if (!file) {
        DEBUG("File: %s open failed",filename);  
    } else {
        DEBUG("File open success");

        String text = "";
        while (file.available()) {
            text += file.readStringUntil('\n');
            text += "\n";
        }
        file.close();
        return text;
    }
}
