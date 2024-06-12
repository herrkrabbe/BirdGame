/**
 * Sourced from https://pastebin.com/DqBgCUkx
 * 11. June 2024
 */

#include "FlightQuaternion.h"

// Formula to convert a Euler angle in degrees to a quaternion rotation
FQuat UFlightQuaternion::Euler_To_Quaternion(FRotator Current_Rotation)
{
    FQuat q;                                            // Declare output quaternion
    float yaw = Current_Rotation.Yaw * PI / 180;        // Convert degrees to radians 
    float roll = Current_Rotation.Roll * PI / 180;
    float pitch = Current_Rotation.Pitch * PI / 180;

    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);

    q.W = cy * cr * cp + sy * sr * sp;
    q.X = cy * sr * cp - sy * cr * sp;
    q.Y = cy * cr * sp + sy * sr * cp;
    q.Z = sy * cr * cp - cy * sr * sp;

    return q;                                           // Return the quaternion of the input Euler rotation
}

// Set the scene component's world rotation to the input quaternion
void UFlightQuaternion::SetWorldRotationQuat(USceneComponent* SceneComponent, const FQuat& Desired_Rotation)
{
    if (SceneComponent)
    {
        SceneComponent->SetWorldRotation(Desired_Rotation);
    }
}

// Set the scene component's relative rotation to the input quaternion
void UFlightQuaternion::SetRelativeRotationQuat(USceneComponent* SceneComponent, const FQuat& Desired_Rotation)
{
    if (SceneComponent)
    {
        SceneComponent->SetRelativeRotation(Desired_Rotation);
    }
}

// Add the input delta rotation to the scene component's current local rotation
void UFlightQuaternion::AddLocalRotationQuat(USceneComponent* SceneComponent, const FQuat& Delta_Rotation)
{
    if (SceneComponent)
    {
        SceneComponent->AddLocalRotation(Delta_Rotation);
    }
}

// Set the Actor's world rotation to the input quaternion
void UFlightQuaternion::SetActorWorldRotationQuat(AActor* Actor, const FQuat& Desired_Rotation)
{
    if (Actor)
    {
        Actor->SetActorRotation(Desired_Rotation);
    }
}

// Set the Actor's relative rotation to the input quaternion
void UFlightQuaternion::SetActorRelativeRotationQuat(AActor* Actor, const FQuat& Desired_Rotation)
{
    if (Actor)
    {
        Actor->SetActorRelativeRotation(Desired_Rotation);
    }
}

// Add the input delta rotation to the Actor's current local rotation
void UFlightQuaternion::AddActorLocalRotationQuat(AActor* Actor, const FQuat& Delta_Rotation)
{
    if (Actor)
    {
        Actor->AddActorLocalRotation(Delta_Rotation);
    }
}
