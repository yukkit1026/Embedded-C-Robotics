# Embedded-C-Robotics
Small programs for robots!

TurningAndDirectionCorrecting.c showcases diagnosing and trouble shooting a faulty motor. The motor on the robot here is slower than the one on the opposite side I corrected this by using the gyro sensor to notice any drift, from there I sped up the one side that has the faulty motor to keep the path as straight as possible.
90 degree turns where the same. I had to have the left motor at a higher speed than the right. It still didn’t work all that great at first, so I did a big quick turn until the gyro sensor reported it was within an acceptable range. From there I adjusted the turn slowly until the gyro sensor reported it was within +/- 5 degrees on either side of the expected 90 degree turn.
