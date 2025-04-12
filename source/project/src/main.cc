/*
 * Copyright (C) 2025 RealAhani - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license, which unfortunately won't be
 * written for another century.
 * You should have received a copy of the MIT license with
 * this file.
 */
#include <raylib.h>
#include <rlgl.h>

#include <print>
#include <random>
#include <string>
#include <string_view>
#include <chrono>

#include "config.hh"
#include "helper.hh"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{
    std::println("hello c++23 ");
    using namespace std::string_literals;
    using namespace std::string_view_literals;
    using namespace myproject::cmake;
// __________ Project Informations __________
#if (MYOS == 1)                                      // OS is Windows
    std::println("WIN");
#elif (MYOS == 2)                                    // OS is GNU/Linux
    std::println("Linux");
#elif (MYOS == 3)                                    // OS is OSX
    std::println("MAC");
#endif
    std::println(myproject::cmake::projectName);     // Project-name!
    std::println(myproject::cmake::projectVersion);  // Project-version!
    // __________ Project Informations __________

    // Raylib window init
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);
    InitWindow(1200, 800, "hello shader");
    SetTargetFPS(0);

    // Window properties
    i32 const gWidth  = {GetScreenWidth()};
    i32 const gHeight = {GetScreenHeight()};
    bool      isQuit  = {false};


    // clang-format off

    // auto const [fontSDF,shader]= RA_Font::initSDFFont("NotoSans-VariableFont_wdth,wght.ttf"sv,20,95);

    auto const [font,fontSize] = RA_Font::initFont(
        "NotoSans-VariableFont_wdth,wght.ttf"sv,
        100,
        TEXTURE_FILTER_BILINEAR);

    // clang-format on
    Shader TestShader = LoadShader(0,
                                   RA_Global::pathToFile("test.fs"sv,
                                                         RA_Global::EFileType::Shader)
                                       .c_str());

    f32 const iRes[2] = {gWidth / 1.f, gHeight / 1.f};
    f32       iTime {};
    Vector2   iMouse {};

    i32 resLoc   = GetShaderLocation(TestShader, "iRes");
    i32 timeLoc  = GetShaderLocation(TestShader, "iTime");
    i32 mouseLoc = GetShaderLocation(TestShader, "iMouse");

    SetShaderValue(TestShader, resLoc, iRes, SHADER_UNIFORM_VEC2);
    SetShaderValue(TestShader, timeLoc, &iTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(TestShader, mouseLoc, &iMouse, SHADER_UNIFORM_VEC2);

    Texture2D texture =
        {rlGetTextureIdDefault(), gWidth, gHeight, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
    // [[maybe_unused]]
    // bool const fex = FileExists("resource/TEST.txt");
    // str const  mystr {LoadFileText("resource/TEST.txt")};
    u16 const wtext {cast(u16, gWidth)};
    u16 const htext {cast(u16, gHeight)};
    Texture2D tempTexture =
        {rlGetTextureIdDefault(), wtext, htext, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

    RenderTexture2D effectTexture = LoadRenderTexture(wtext, htext);
    BeginTextureMode(effectTexture);
    ClearBackground(BLANK);
    BeginShaderMode(TestShader);
    DrawTexture(tempTexture, 0, 0, WHITE);
    EndShaderMode();
    EndTextureMode();
    UnloadShader(TestShader);

    // Main loop
    while (!WindowShouldClose() && !isQuit)
    {
        iTime  = GetTime();
        iMouse = GetMousePosition();
        // Input managment with raylib
        if (IsKeyPressed(KEY_ESCAPE))
        {
            isQuit = true;
        }
        else if (IsKeyPressed(KEY_R))
        {
            UnloadShader(TestShader);
            TestShader = LoadShader(0,
                                    RA_Global::pathToFile("test.fs"sv,
                                                          RA_Global::EFileType::Shader)
                                        .c_str());
            SetShaderValue(TestShader, resLoc, iRes, SHADER_UNIFORM_VEC2);
        }
        SetShaderValue(TestShader, timeLoc, &iTime, SHADER_UNIFORM_FLOAT);
        SetShaderValue(TestShader, mouseLoc, &iMouse, SHADER_UNIFORM_VEC2);
        // Rendering
        ClearBackground(BLACK);
        BeginDrawing();
        // DrawText(mystr.c_str(), width / 2, height / 2, 44, RAYWHITE);

        {
            // BeginShaderMode(TestShader);
            // {
            DrawTextureEx(effectTexture.texture, Vector2 {}, 0.f, 1.f, WHITE);
            // }
            // EndShaderMode();
        }

        DrawFPS(0, 10);
        EndDrawing();
    }
    // Cleaning up and bye
    CloseWindow();
    return 0;
}