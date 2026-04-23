import csv
import random
import math

filename = 'data/telemetry.csv'
num_rows = 1000

with open(filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['timestamp_ms', 'motor1_pwm', 'motor2_pwm', 
        'motor3_pwm', 'motor4_pwm', 'pitch_deg', 'roll_deg', 'yaw_deg'])

    for i in range(num_rows):
        timestamp_ms = i * 20 
        
        motor1 = random.randint(1450, 1550)
        motor2 = random.randint(1450, 1550)
        motor3 = random.randint(1450, 1550)
        motor4 = random.randint(1450, 1550)
        
        pitch = round(math.sin(i / 50.0) * 15 
                     + random.uniform(-2.0, 2.0), 2)
        roll = round(math.cos(i / 50.0) * 15 
                     + random.uniform(-2.0, 2.0), 2)
        yaw = round(math.sin(i / 100.0) * 5 
                     + random.uniform(-1.0, 1.0), 2)
        
        writer.writerow([timestamp_ms, motor1, motor2, motor3, motor4, 
                         pitch, roll, yaw])

print(f"Successfully generated {num_rows} rows of data in {filename}")