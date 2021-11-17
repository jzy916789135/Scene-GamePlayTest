#pragma once
#include <iostream>
#include <string>
using namespace std;

struct FVector
{
    float                                           x, y, z, w;
    FVector() { x = y = z = w = 0.0f; }
    FVector(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};

struct FVector2
{
    float                                           x, y;
    FVector2() { x = y = 0.0f; }
    FVector2(float _x, float _y, float _z, float _w) { x = _x; y = _y; }
};

struct FVector3
{
    float                                           x, y, z;
    FVector3() { x = y = z = 0.0f; }
    FVector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};

struct FRotator
{
    float                                           pitch, yaw, roll;
    FRotator() { pitch = yaw = roll = 0.0f; }
    FRotator(float _pitch, float _yaw, float _roll) { pitch = _pitch; yaw = _yaw; roll = _roll; }
};

struct FColor
{
    float                                           R, G, B, A;
    FColor() { R = G = B = A = 0.0f; }
    FColor(float _R, float _G, float _B, float _A) { R = _R; G = _G; B = _B; A = _A; }

};

struct FName
{
    FName();
    FName(std::string& name) { mFname = name; };
    std::string mFname = "Defaule";
};
struct FTransform
{
    FTransform() {};
    FTransform(FVector Pos, FRotator Rot, FVector Sca) : Position(Pos),
        Rotation(Rot), Scale(Sca) {};
    ~FTransform() {};
    FVector Position = FVector();
    FRotator Rotation = FRotator();
    FVector Scale = FVector();

    FVector GetPosition()
    {
        return Position;
    }

    FRotator GetRotation()
    {
        return Rotation;
    }

    FVector GetScale()
    {
        return Scale;
    }

};


