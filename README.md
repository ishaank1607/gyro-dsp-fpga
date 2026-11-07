# gyro-dsp-fpga

A custom I2C master written in Verilog for a Basys 3 FPGA that reads an MPU6500 IMU directly, then filters the noisy accel/gyro data in fixed-point RTL.

Goal: Learn fixed-point DSP and verification by building the sensor interface and filters in hardware, checked against a bit-accurate Python model.

Pipeline: MPU6500 → I2C master → register-read FSM → filters → UART out

Status: ESP32 baseline (raw readings on an OLED graph) done. RTL not started.

Plan
(checklist from the schedule below)

Verification approach
Python golden model at the same bit widths. RTL output must match it sample for sample.
