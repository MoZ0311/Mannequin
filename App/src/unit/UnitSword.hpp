// UnitSword class

#pragma once

#include "../player/PlayerCharacter.hpp"

class UnitSword : public PlayerCharacter
{
public:

	UnitSword();

	void update(const double deltaTime, const Vec3 cameraForward) override;

	void draw()const override;

	//void createDiscFrame(const Vec3& centor, const double radius) override;

private:


};
