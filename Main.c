#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdbool.h> 
#include <math.h>     // Required for sinf and cosf

int main(void) {
    InitWindow(800, 450, "Raylib - 3D FPV Mouse Look");

    // Player setup
    Vector3 playerPos = { 0.0f, 0.0f, 0.0f };
    
    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.5f, 0.0f }; // Start at eye level
    camera.target = (Vector3){ 0.0f, 0.5f, -1.0f };   // Look forward
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Rotational angles (Radians)
    float cameraYaw = -90.0f * DEG2RAD; // Start looking straight ahead (-Z)
    float cameraPitch = 0.0f;           // Start looking level with the horizon
    float mouseSensitivity = 0.003f;    // Adjust this to speed up/slow down mouse look

    // Track mouse lock state (Start locked)
    bool isCursorLocked = true;
    DisableCursor(); 

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Toggle cursor lock state when 'K' is pressed
        if (IsKeyPressed(KEY_K)) {
            isCursorLocked = !isCursorLocked;
            if (isCursorLocked) DisableCursor();
            else EnableCursor();
        }

        // Only look and move if cursor is locked
        if (isCursorLocked) {
            // 1. MOUSE LOOK LOGIC
            Vector2 mouseDelta = GetMouseDelta();
            
            cameraYaw -= mouseDelta.x * mouseSensitivity;
            cameraPitch -= mouseDelta.y * mouseSensitivity;

            // Clamp pitch so you can't flip your neck entirely upside down (89 degrees)
            if (cameraPitch > 89.0f * DEG2RAD)  cameraPitch = 89.0f * DEG2RAD;
            if (cameraPitch < -89.0f * DEG2RAD) cameraPitch = -89.0f * DEG2RAD;

            // 2. MOVE PLAYER LOGIC
            // Calculate forward/right vectors based on where we are looking (Yaw)
            Vector3 forward = { cosf(cameraYaw), 0.0f, sinf(cameraYaw) };
            Vector3 right = { -sinf(cameraYaw), 0.0f, cosf(cameraYaw) };

            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                playerPos = Vector3Add(playerPos, Vector3Scale(forward, 0.1f));
            }
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                playerPos = Vector3Subtract(playerPos, Vector3Scale(forward, 0.1f));
            }
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                playerPos = Vector3Add(playerPos, Vector3Scale(right, 0.1f));
            }
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                playerPos = Vector3Subtract(playerPos, Vector3Scale(right, 0.1f));
            }
        }
        
        // 3. UPDATE CAMERA POS AND TARGET
        camera.position = (Vector3){ playerPos.x, playerPos.y + 0.5f, playerPos.z };

        // Calculate target looking direction vector from angles using spherical coordinates
        Vector3 lookDir;
        lookDir.x = cosf(cameraPitch) * cosf(cameraYaw);
        lookDir.y = sinf(cameraPitch);
        lookDir.z = cosf(cameraPitch) * sinf(cameraYaw);

        camera.target = Vector3Add(camera.position, lookDir);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                Color grassGreen = { 34, 139, 34, 255 };
                DrawPlane((Vector3){ 0.0f, -0.5f, 0.0f }, (Vector2){ 50.0f, 50.0f }, grassGreen);
                
                // Landmarks to see orientation
                DrawCube((Vector3){ 0.0f, 0.5f, -5.0f }, 1.0f, 2.0f, 1.0f, RED);
                DrawCube((Vector3){ 5.0f, 0.5f, 0.0f }, 1.0f, 2.0f, 1.0f, BLUE);
                
                DrawGrid(20, 1.0f);
            EndMode3D();

            // UI
            if (isCursorLocked) {
                DrawText("Mouse Locked. Press 'K' to Unlock", 10, 10, 20, BLACK);
                DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 4, RED); // Crosshair
            } else {
                DrawText("Mouse Unlocked. Press 'K' to Lock", 10, 10, 20, RED);
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}