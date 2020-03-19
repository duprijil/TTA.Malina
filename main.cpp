#include <stdio.h>
//#include <czmq.h>

#include <webcam.h>
#include <raylib.h>
#include <grab.h>
#include <unistd.h>

#include <zmqWrap.h>

void send_info(zmqIPCPush* sock, float speed, float angle) {
    char buff[32];
    snprintf(buff, sizeof(buff), "%.2f %.2f", speed, angle);
    sock->push_str(buff);
}

int main(void) {
	
    const RGBImage *frame_ptr = nullptr;
    Webcam webcam("/dev/video0", XRES, YRES);
    InitWindow(XRES, YRES, "Camera monitor");
    SetTargetFPS(60);
    
    zmqIPCPush* zmqSocket = new zmqIPCPush("ipc:///tmp/com");
    float angle = 0.00f;
    float speed = 0.00f;
    char buff[10];
    while (!WindowShouldClose()) {

        if(IsKeyPressed(KEY_SPACE)) {
	    speed = 0.00f;
	    angle = 0.00f;
	    send_info(zmqSocket, speed, angle);
	}
        else if(IsKeyPressed(KEY_A)) {
	    angle = -20.00f;
	    send_info(zmqSocket, speed, angle);
	}
        else if(IsKeyPressed(KEY_D)) {
	    angle = 20.00f;
	    send_info(zmqSocket, speed, angle);
	}        
        else if(IsKeyPressed(KEY_E)) {
	    speed += 0.06f;
	    send_info(zmqSocket, speed, angle);
	}
        else if(IsKeyPressed(KEY_Q)) {
	    speed -= 0.06f;
	    send_info(zmqSocket, speed, angle);
	}
        else if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S)) {
	    angle = 0.00f;
	    send_info(zmqSocket, speed, angle);
	}

	frame_ptr = &webcam.frame();
	Frame frame(*frame_ptr);
        BeginDrawing();
            ClearBackground(BLACK);
            frame.draw();
            DrawFPS(10,10);
        EndDrawing();
    }

    CloseWindow();
    
    delete zmqSocket;
 
}
