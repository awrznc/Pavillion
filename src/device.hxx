#include <stdio.h>
#include <windows.h>

namespace Device {

class JoyPad {

public:
    JOYINFOEX JoyInfoEx;
    UINT joystick_number;

    enum Lever {
        L7, L8, L9,
        L4, L5, L6,
        L1, L2, L3
    };

    Lever lever;

    JoyPad() {
        JoyInfoEx.dwSize = sizeof(JOYINFOEX);
        JoyInfoEx.dwFlags = JOY_RETURNALL;
        joystick_number = 0;
        lever = L5;
    }

    int connect() {
        joystick_number = joyGetNumDevs();
        for(unsigned int i=0;i<joyGetNumDevs();i++){
            if(JOYERR_NOERROR == joyGetPosEx(i, &JoyInfoEx))
            printf("Connect to device No.%d.\n",i);
        }
        return 0;
    }

    JOYINFOEX capture(UINT device) {
        joyGetPosEx(device, &JoyInfoEx);
        return JoyInfoEx;
    }

    JOYINFOEX debug_capture(UINT device, char* debug_info) {

        // See information on joystick number 0.
        if (JOYERR_NOERROR == joyGetPosEx(0, &JoyInfoEx)){

            sprintf(debug_info, "0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x",
                JoyInfoEx.dwButtonNumber,
                JoyInfoEx.dwButtons,
                JoyInfoEx.dwFlags,
                JoyInfoEx.dwPOV,
                JoyInfoEx.dwReserved1,
                JoyInfoEx.dwReserved2,
                JoyInfoEx.dwRpos,
                JoyInfoEx.dwSize,
                JoyInfoEx.dwUpos,
                JoyInfoEx.dwVpos,
                JoyInfoEx.dwXpos,
                JoyInfoEx.dwYpos,
                JoyInfoEx.dwZpos);

            printf("%s\n", debug_info);
        } else {
            printf("error\n");
        }
        return JoyInfoEx;
    }
};

};
