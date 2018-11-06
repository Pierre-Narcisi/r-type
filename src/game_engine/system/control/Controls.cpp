/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include "Controls.hpp"
#include "component/control/Controller.hpp"

namespace ecs {namespace system {

	void Controls::UpdateControllers(sf::event &event) {
		auto &controllers = secs::Ecs::getConponentList<component::Controller>();
		const float DEAD_ZONE = 0.2f;

		for (auto &controller : controllers) {

			/// LEFT ROTATION
			float rotHorizontal =
				event->controllers._controllers[in[id].controllerId].axeLX;
			if(fabs(rotHorizontal) < DEAD_ZONE)
				rotHorizontal = 0.f;
			float rotVertical =
				event->controllers._controllers[in[id].controllerId].axeLY;
			if(fabs(rotVertical) < DEAD_ZONE)
				rotVertical = 0.f;

			if (rotHorizontal == 0 && rotVertical == 0) {
				in[id].moving = false;
				in[id].deplacement = 90.f;
			}
			else {
				in[id].moving = true;
				float rot = static_cast<float>(atan(rotVertical/rotHorizontal) / M_PI * 180.0);
				if (rotHorizontal > 0) {
					if (rotVertical > 0)
						in[id].deplacement = 360.f - rot;
					else
						in[id].deplacement = -rot;
				} else {
					in[id].deplacement = 180 - rot;
				}
				if (rotVertical == 1)
					in[id].deplacement = 270;
				else if (rotVertical == -1)
					in[id].deplacement = 90;
			}

			/// RIGHT ROTATION
			rotHorizontal =
				event->controllers._controllers[in[id].controllerId].axeRX;
			if(fabs(rotHorizontal) < DEAD_ZONE)
				rotHorizontal = 0.f;
			rotVertical =
				event->controllers._controllers[in[id].controllerId].axeRY;
			if(fabs(rotVertical) < DEAD_ZONE)
				rotVertical = 0.f;

			if (rotHorizontal == 0.f && rotVertical == 0.f) {
				in[id].moving = false;
				in[id].attack = 90.f;
			} else {
				in[id].moving = true;
				float rot = static_cast<float>(atan(rotVertical/rotHorizontal) / M_PI * 180.0);
				if (rotHorizontal > 0) {
					if (rotVertical > 0)
						in[id].attack = 360.f - rot;
					else
						in[id].attack = -rot;
				} else {
					in[id].attack = 180 - rot;
				}
				if (rotVertical == 1)
					in[id].attack = 270;
				else if (rotVertical == -1)
					in[id].attack = 90;
			}
		}
	}
}}