import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data/clean_telemetry.csv')

x_data = df['timestamp_ms']
y_data = df['pitch_deg']
plt.plot(x_data, y_data)

plt.title('Drone Pitch Dynamics')
plt.xlabel('Time (ms)')
plt.ylabel('Pitch (Degrees)')
plt.grid(True)

plt.savefig('data/pitch_plot.png')
print("Successfully rendered and saved plot.")