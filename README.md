# UCSC-hackathon-2015


README 
			DYNAMIC_LIGHTING_SOULTION
			A_HANDS_FREE_WAY_TO_CONSERVE_POWER
Purpose:
	This project is intended to implement energy savings by keeping track of the number of people in a room and, by default, will only have the light turned on when there are people present in the room. 

Other:
	However, there is an override that is ideally connected via wifi, which will allow the user to turn the lights on or off from anywhere in the world via a smart phone or computer. For instance, if the user sets this project up in a bedroom they could use their phone to turn off the lights when it is time for them to go to bed. Or they could use it for security purposes 

	Unfortunately, due to hardware limitations, we are unable to track every single person moving into the room. For instance, since the sensor is intended to be mounted at hip level, it would not be able to find a toddler entering. If we were to actually implement this in a non hackathon environment, then then we would have multiple sensors so that we can cover the vast majority of the door instead of only one part of it. While this would make our code more complicated, then we could complete this project much more accurately.

	Furthermore, taking this idea further, we would not only connect sensors to every single door in a house, we would network all of the doors to a central location that could be accessed on a computer or smartphone. This computer or smartphone could turn lights on and off, as well as, view the number of people in each room. This would be useful for monitoring guests, or just general security purposes. Additionally, if a room is known to have zero people in it, a speaker connected to the device could play a loud sound.

	The aREST library is used to communicate with the arduino from a server. 

Actual Implementation: 
	Due to not having a bluetooth or wifi Arduino connector, we simulate the sensor by using the serial communicator over USB. Meaning, that the Arduino has to remain connected to a computer for the purposes of this demonstration. The final product will be significantly prettier and all of the exposed wires will be hidden in a box. 

Known issues:
	It will not work with small children.
